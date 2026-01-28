module RISC16(CLK, Rstn, InstAddr, Inst, DW, DAddr, WData, RData);

	input 			CLK, Rstn;
	output [31:0]	InstAddr, DAddr;
	input  [15:0]	Inst;
	output			DW;
	output [31:0]	WData;
	input  [31:0]	RData;
	
	parameter 		Rstn_Addr = 0;
	
	// IA stage 取指阶段
	reg				Rstn_flag;                                  //复位标识
	reg	[31:0]	PC_reg;											//程序计数器
	wire	[31:0]	PC_add2, PC_addoffset, PC;					//指令+2，跳转地址计算
	wire	[1:0]		PC_Sel;									//地址选择信号
	reg				PC_W;										//计数器写使能

	// DC stage 译码阶段
	reg	[15:0]	IFDC_reg;										//流水线寄存器，存储从取指阶段传递的指令。
	reg			IFDC_W;											//write signal for IFDC register
	wire		IFDC_Flush;										//清空 IFDC_reg 的信号，用于处理分支预测错误或跳转时清空流水线
	reg	[31:0]	RegFile[31:0];									//寄存器文件，32 个 32 位寄存器，用于存储操作数或中间计算结果。
	wire	[31:0]	Reg0, Reg1;									//寄存器文件中读取的两个操作数。
	reg	[3:0]		DC_ALU_OP;									//译码阶段的 ALU 操作码，指示 ALU 执行何种运算
	
	reg				DC_WB, DC_DW, DC_LD;						//写回使能信号，写存储器使能信号，加载信号，用于指示是否从数据存储器读取数据
	reg	[3:0]		DC_BJ;										//分支跳转信号，指示当前是否需要分支跳转
	wire  [1:0]		DC_BP_Sel_0, DC_BP_Sel_1;                   //数据旁路选择信号，用于解决数据冒险问题
	
	// EX stage 执行阶段
 	//reg				DCEX_Flush;												//clear signal for DCEX register
	                                                            //ALU算数逻辑单元，用来执行算术运算和逻辑运算等操作
	reg [3:0]		DCEX_ALU_OP;								//从译码阶段传递到执行阶段的 ALU 操作码
	reg				DCEX_DW, DCEX_LD, DCEX_WB;					//存储器写使能信号、加载信号和写回信号，分别控制访存和寄存器的写操作
	reg [31:0]		DCEX_Reg0, DCEX_Reg1;						//操作数寄存器，存储 ALU 的两个操作数
	reg [4:0]		DCEX_imm, DCEX_RegAddr0, DCEX_RegAddr1; 	//DCEX_imm: 立即数操作数,
																//DCEX_RegAddr0 和 DCEX_RegAddr1: 操作数寄存器地址。
	
	wire signed [32:0]		ALU_OP0, ALU_OP1;					//旁路控制后输入到 ALU 的两个操作数。
	reg signed  [32:0]		ALU_Result;							// 运算结果
	reg				ALU_Z, ALU_N;								// ALU 的标志位，ALU_Z 表示运算结果是否为零，ALU_N 表示结果是否为负
	reg				ALU_Z_reg, ALU_N_reg;						// 标志位寄存器，用于存储 ALU_Z 和 ALU_N 的值。
	
	wire	[1:0]		EX_BP_Sel_0,EX_BP_Sel_1;				// 执行阶段的数据旁路选择信号
	wire [31:0]		EX_WData;									// 写回的数据，可能是 ALU 结果或数据存储器读取的数据

	// WB stage 写回阶段
	reg				EXWB_LD;                                    //加载信号，从执行阶段传递过来。
	reg				EXWB_WB;									// 写回信号，指示是否将数据写回寄存器
	reg	[4:0]		EXWB_WAddr;									// writeback address in EXWB register
	reg	[31:0]	EXWB_WData;										// writeback data in EXWB register
									
	

	
	// XX stage 最后写回阶段
	reg				WBXX_WB;									// 写回信号，从 EXWB 阶段传递过来的最终信号
	reg	[4:0]		WBXX_WAddr;									// 最终写回寄存器的地址。
	reg	[31:0]	WBXX_WData;										// 最终写回寄存器的数据。
	
	
	
	
	//	
	// IA stage
	//
	
	// reset flag
	always@(posedge CLK or negedge Rstn)	//当异步复位的时候，异步复位信号置1，将有关寄存器清0
	begin
		if (!Rstn)
			Rstn_flag <= 1'b1;
		else
			Rstn_flag <= 1'b0;
	end

	assign PC_add2 = PC_reg + 2'b10;			//计算下一地址，在当前PC_reg的值加2

	
	assign PC_addoffset = PC_reg + {{21{IFDC_reg[9]}},IFDC_reg[9:0],1'b0};//根据 IFDC_reg 来设置，即偏移地址左移一位，高位补符号位

	assign PC = (Rstn_flag == 1'b1)? Rstn_Addr : 
				(PC_Sel == 2'b00)? PC_add2 : 
				(PC_Sel == 2'b01) ? PC_addoffset : 
				{21'h000000,IFDC_reg[9:0],1'b0};	
  
    //根据不同的条件选择信号 PC_Sel 来确定下一指令的地址。如果复位信号 Rstn_flag 为1，
	//直接使用预定义的 Rstn_Addr 复位PC值；否则，根据 PC_Sel 选择是正常顺序执行（PC_add2）、还是跳转。
	// IF stage
	
	
	// PC register
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn)
			PC_reg <= 32'h00000000;
		else if (PC_W)
			PC_reg <= PC;
	end

	// instruction address for InstRAM
	assign InstAddr = PC;

	//
	// DC stage
	//
	
	// IFDC register   IFDC流水线寄存器
	always@(posedge CLK or negedge Rstn) //异步复位时，IFDC寄存器异步清0；然后如果清除IFDC_reg的信号有效，IFDC寄存器同步清0
	begin                                //IFDC寄存器写信号有效的话，立即数的值存入IFDC寄存器
		if (!Rstn)
			IFDC_reg <= 16'h0000;
		else if (IFDC_Flush)
			IFDC_reg <= 16'h0000;
		else if (IFDC_W)
			IFDC_reg <= Inst;
	end
	
	// RegFile                           //这个部分是寄存器组，一共32个寄存器，每一个寄存器存放32位的数据
	always@(posedge CLK)                 //如果写回信号有效，那么将写回数据赋值给相应写回地址对应的寄存器
	                                     //即前面的指令更新了寄存器组的值
	begin
		if (EXWB_WB)
			RegFile[EXWB_WAddr] <= EXWB_WData;
	end

	// operand 0 and 1 from register file 
	assign Reg0 = RegFile[IFDC_reg[9:5]]; //指令对应的操作数高位的对应寄存器的值
	assign Reg1 = RegFile[IFDC_reg[4:0]]; //指令对应的操作数低位的对应寄存器的值

	// decoder                              解指令部分
	// the following code has not been finished, please add here!!!!
	always@(IFDC_reg[15:10])               //对操作码判断，从而确定采用哪一个操作
	begin
		case(IFDC_reg[15:10])               
		6'b010000: begin          //ADD对应的解指令         
			DC_ALU_OP	= 4'b0000; //ALU模块对应的操作码，0000，即ADD
			DC_WB	   	= 1'b1;    //写回信号，高电平有效
			DC_DW  		= 1'b0;    //存储信号，高电平有效
			DC_LD	   	= 1'b0;    //加载信号，高电平有效
			DC_BJ	   	= 4'b0000; //分支与跳转信号，0000，即无分支无跳转
			PC_W	   	= 1'b1;    //PC写信号，高电平有效
			IFDC_W   	= 1'b1;    //IFDC写信号，高电平有效
     		//DCEX_Flush 	= 1'b0;
		end
		// please add the code!!!!!
		6'b010001: begin           //SUB对应的解指令
			DC_ALU_OP	= 4'b0001;	//ALU模块对应的操作码，0001，即SUB/CMP
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b010010: begin           //CMP对应的解指令
			DC_ALU_OP	= 4'b0001;	//ALU模块对应的操作码，0001，即SUB/CMP
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b010100: begin           //AND对应的解指令
			DC_ALU_OP	= 4'b0010;	//ALU模块对应的操作码，0010，即AND
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b010101: begin           //OR对应的解指令
			DC_ALU_OP	= 4'b0011;	//ALU模块对应的操作码，0011，即OR
			DC_WB	   	= 1'b1;    
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;   
			IFDC_W   	= 1'b1;   
			//DCEX_Flush 	= 1'b0;
		end
		6'b010110: begin           //XOR对应的解指令
			DC_ALU_OP	= 4'b0100;	//ALU模块对应的操作码，0100，即XOR
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b100000: begin           //LSL对应的解指令
			DC_ALU_OP	= 4'b0101;	//ALU模块对应的操作码，0101，即LSL
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b100001: begin           //LSR对应的解指令
			DC_ALU_OP	= 4'b0110;	//ALU模块对应的操作码，0110，即LSR
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;    
			//DCEX_Flush 	= 1'b0;
		end
		6'b100010: begin           //ASR对应的解指令
			DC_ALU_OP	= 4'b0111;	//ALU模块对应的操作码，0111，即ASR
			DC_WB	   	= 1'b1;    
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b100111: begin            //MOV对应的解指令
			DC_ALU_OP	= 4'b1000;	//ALU模块对应的操作码，1000，即MOV
			DC_WB	   	= 1'b1;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;    
			//DCEX_Flush 	= 1'b0;
		end
		6'b011000: begin           //LD对应的解指令
			DC_ALU_OP	= 4'b1001;	//ALU模块对应的操作码，1001，对应LD/ST/BZ/BNZ/BLE/BLT/BGE/BGT/JUMP/NOP/WAIT
			DC_WB	   	= 1'b1;     //写回信号，高电平有效
			DC_DW  		= 1'b0;     //存储信号，低电平无效
			DC_LD	   	= 1'b1;     //加载信号，高电平有效
			DC_BJ	   	= 4'b0000;	//分支与跳转信号，0000，即无分支无跳转
			PC_W	   	= 1'b1;     //PC写信号，高电平有效
			IFDC_W   	= 1'b1;     //IFDC写信号，高电平有效
			//DCEX_Flush 	= 1'b0;
		end
		6'b011001: begin           //ST对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b1;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b0;
		end
		6'b110000: begin           //BZ对应的解指令
			DC_ALU_OP	= 4'b1001;	//ALU模块对应的操作码，1001，对应LD/ST/BZ/BNZ/BLE/BLT/BGE/BGT/JUMP/NOP/WAIT
			DC_WB	   	= 1'b0;    
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0001;	//分支与跳转信号，0001，即第一种分支
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;    
			//DCEX_Flush 	= 1'b1;
		end
		6'b110001: begin           //BNZ对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;    
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0010;	
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b1;
		end
		6'b110010: begin           //BLE对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0011;	
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b1;
		end
		6'b110011: begin           //BLT对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0100;	
			PC_W	   	= 1'b1;     
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b1;
		end
		6'b110100: begin           //BGE对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;    
			DC_DW  		= 1'b0;    
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0101;	
			PC_W	   	= 1'b1;   
			IFDC_W   	= 1'b1;    
			//DCEX_Flush 	= 1'b1;
		end
		6'b110101: begin           //BGT对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     //写回信号，低电平无效
			DC_DW  		= 1'b0;     //存储信号，低电平无效
			DC_LD	   	= 1'b0;     //加载信号，低电平无效
			DC_BJ	   	= 4'b0110;	//分支与跳转信号，0110，即第六种分支
			PC_W	   	= 1'b1;     //PC写信号，高电平有效
			IFDC_W   	= 1'b1;     //IFDC写信号，高电平有效
			//DCEX_Flush 	= 1'b1;
		end
		6'b110110: begin           //B对应的解指令
			DC_ALU_OP	= 4'b1001;
			DC_WB	   	= 1'b0;   
			DC_DW  		= 1'b0;   
			DC_LD	   	= 1'b0;    
			DC_BJ	   	= 4'b0111;	
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b1;
		end
		6'b111000: begin           //JUMP对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b1000;	
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;     
			//DCEX_Flush 	= 1'b1;
		end
		6'b000000: begin           //NOP对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;  
			DC_LD	   	= 1'b0;   
			DC_BJ	   	= 4'b0000;	//分支与跳转信号，0000，即无分支无跳转
			PC_W	   	= 1'b1;    
			IFDC_W   	= 1'b1;   
			//DCEX_Flush 	= 1'b0;
		end
		6'b000001: begin           //WAIT对应的解指令
			DC_ALU_OP	= 4'b1001;	
			DC_WB	   	= 1'b0;     
			DC_DW  		= 1'b0;     
			DC_LD	   	= 1'b0;     
			DC_BJ	   	= 4'b0000;	
			PC_W	   	= 1'b0;     
			IFDC_W   	= 1'b0;    
			//DCEX_Flush 	= 1'b1;
		end
		default: begin             //条件分支写完整，避免生成锁存器
			DC_ALU_OP	= 4'bxxxx;	
			DC_WB	   	= 1'bx;
			DC_DW  		= 1'bx;
			DC_LD	   	= 1'bx;
			DC_BJ	   	= 4'bxxxx;	
			PC_W	   	= 1'bx;
			IFDC_W   	= 1'bx;
			//DCEX_Flush 	= 1'b1;
		end
		endcase

		
		
	end
	
	// Branch 分支部分
	
	// select signal for PC  
	// the following code has not been finished, please add here!!!!
	assign PC_Sel = 	(DC_BJ == 4'b0001 && ALU_Z == 1'b1) ? 2'b01 :	//BZ					
						(DC_BJ == 4'b0010 && ALU_Z == 1'b0) ? 2'b01 :	//BNZ
						(DC_BJ == 4'b0011 && (ALU_Z == 1'b1 || ALU_N == 1'b1)) ? 2'b01 :	//BLE
						(DC_BJ == 4'b0100 && (ALU_Z == 1'b0 && ALU_N == 1'b1)) ? 2'b01 :	//BLT
						(DC_BJ == 4'b0101 && (ALU_Z == 1'b1 || ALU_N == 1'b0)) ? 2'b01 :	//BGE
						(DC_BJ == 4'b0110 && (ALU_Z == 1'b0 && ALU_N == 1'b0)) ? 2'b01 :	//BGT
						(DC_BJ == 4'b0111 ) ? 2'b01 :	//B
						(DC_BJ == 4'b1000 ) ? 2'b10 : 2'b00;	//JUMP
						// If DC_BJ is 4'b0001 and ALU_Z is 1'b1, then PC_Sel is set to 2'b01, indicating selection of PC_addoffset.
						// Similar conditions apply for other branches (BNZ, BLE, BLT, BGE, BGT, B).
						// If DC_BJ is 4'b1000, PC_Sel is set to 2'b10, representing selection of {21'h000000, IFDC_reg[9:0], 1'b0}.
						// If none of the conditions are met, PC_Sel defaults to 2'b00, representing selection of PC_add2.

	// clear signal for IFDC register
	// IFDC寄存器的清除信号，清除IFDC后续的操作和输入到IFDC的指令，确保在分支等情况下正确更新下一条指令的地址。
	assign IFDC_Flush = (PC_Sel != 2'b00) ? 1'b1 : 1'b0;
	
	// bypass controller 0 or Forwarding 旁路机制/前递机制，用于解决数据冒险（data hazards）问题
	// the following code has not been finished, please add here!!!!
	
	// bybass controller0输出的选择信号，在DC阶段	
	// DATA选择信号
	assign DC_BP_Sel_0 = ((IFDC_reg[9:5] == DCEX_RegAddr0) && DCEX_WB)?2'b01:
								// If the destination register address of the current instruction
								// is equal to the register address of the computation result in the EX stage
								// and the EX stage is performing a write-back, select 2'b01.
								((IFDC_reg[9:5] == EXWB_WAddr) && EXWB_WB)?2'b10:2'b00;
								// If the destination register address of the current instruction
								// is equal to the write-back address in the WB stage and the WB stage
								// is performing a write-back, select 2'b10. Otherwise, select 2'b00 for no data bypass.
	// ADDR选择信号	
	assign DC_BP_Sel_1= ((IFDC_reg[4:0] == DCEX_RegAddr0) && DCEX_WB)?2'b01:
								// If the source register address of the current instruction is equal to
                        // the register address of the computation result in the EX stage and the
                        // EX stage is performing a write-back, select 2'b01.
	                     ((IFDC_reg[4:0] == EXWB_WAddr) && EXWB_WB)?2'b10:2'b00;
								// If the source register address of the current instruction is equal to
								// the write-back address in the WB stage and the WB stage is performing
								// a write-back, select 2'b10. Otherwise, select 2'b00 for no address bypass.				
		
	
	// DataRAM interface			数据存储器接口部分	 
	// the following code has not been finished, please add here!!!!

	assign DW 		= DC_DW;                              //控制信号，是否将数据写入内存
	                                                     //数据写入内存的地址，根据DC_BP_Sel_1的值选择不同的数据来源
	assign DAddr 	= (DC_BP_Sel_1 == 2'b00) ? Reg1 :     //不进行数据旁路，直接使用Reg1
							(DC_BP_Sel_1 == 2'b01) ? EX_WData ://选择来自执行阶段（EX）的数据旁路，使用EX_WData。
							EXWB_WData;                        //选择来自写回阶段（WB）的数据旁路，使用 EXWB_WData
							
	                                                     //写入内存的数据，根据DC_BP_Sel_0的值选择不同的数据来源
	assign WData 	= (DC_BP_Sel_0 == 2'b00) ? Reg0 :     //不进行数据旁路，直接使用 Reg0。
							(DC_BP_Sel_0 == 2'b01) ? EX_WData ://选择来自执行阶段（EX）的数据旁路，使用 EX_WData。
							EXWB_WData;                        //选择来自写回阶段（WB）的数据旁路，使用 EXWB_WData。
							                                   

	// EX stage

	// DCEX registers   DCEX流水线寄存器
	always@(posedge CLK or negedge Rstn)	 //将DCEX寄存器更新为来自上一阶段（DC 阶段）的信号，确保数据正确流入执行阶段。
	begin
		if (!Rstn) begin
			DCEX_ALU_OP 	<= 4'b0000;
			DCEX_DW			<= 1'b0;
			DCEX_LD			<= 1'b0;
			DCEX_WB			<= 1'b0;
			DCEX_Reg0 		<= 32'h00000000;
			DCEX_Reg1		<= 32'h00000000;
			DCEX_imm			<= 5'h00;
			DCEX_RegAddr0 	<= 5'h00;
			DCEX_RegAddr1 	<= 5'h00;
		end
 		/*else if (DCEX_Flush) begin
			DCEX_ALU_OP 	<= 4'b0000;
			DCEX_DW			<= 1'b0;
			DCEX_LD			<= 1'b0;
			DCEX_WB			<= 1'b0;
			DCEX_Reg0 		<= 32'h00000000;
			DCEX_Reg1		<= 32'h00000000;
			DCEX_imm			<= 5'h00;
			DCEX_RegAddr0 	<= 5'h00;
			DCEX_RegAddr1 	<= 5'h00;
		end */
		else begin
			DCEX_ALU_OP 	<= DC_ALU_OP;
			DCEX_DW			<= DC_DW;
			DCEX_LD			<= DC_LD;
			DCEX_WB			<= DC_WB;
			DCEX_Reg0 		<= Reg0;
			DCEX_Reg1		<= Reg1;
			DCEX_imm			<= IFDC_reg[4:0];
			DCEX_RegAddr0 	<= IFDC_reg[9:5];
			DCEX_RegAddr1 	<= IFDC_reg[4:0];
		end
	end



	// bypass controller 1
	// the following code has not been finished, please add here!!!!
	assign EX_BP_Sel_0 = ((DCEX_RegAddr0 == EXWB_WAddr) && EXWB_WB)?2'b01:			// If the register address of the first operand (Reg0) in the EX stage
																											// matches the write-back address in the WB stage and the WB stage is
																											// performing a write-back, select 2'b01.
	                     ((DCEX_RegAddr0 == WBXX_WAddr) && WBXX_WB)?2'b10:2'b00; 	// If the register address of the first operand (Reg0) in the EX stage
																											// matches the write-back address in the write-back after stage (WBXX)
																											// and the WBXX stage is performing a write-back, select 2'b10.
						 
	assign EX_BP_Sel_1 = ((DCEX_RegAddr1 == EXWB_WAddr) && EXWB_WB)?2'b01:
	                     ((DCEX_RegAddr1 == WBXX_WAddr) && WBXX_WB)?2'b10:2'b00;
  				 
						 
	// ALU
	// the following code has not been finished, please add here!!!!
	// 根据Bypass控制器的信号选择ALU的输入操作数，ALU_OP0和ALU_OP1分别是ALU的两个输入操作数。
	// EX_BP_Sel_0 and EX_BP_Sel_1 are signals from the bypass controller, determining which stage's data to use as ALU inputs.
	assign  ALU_OP0 = (EX_BP_Sel_0 == 2'b00) ? {DCEX_Reg0[31], DCEX_Reg0} :
					  (EX_BP_Sel_0 == 2'b01) ? {EXWB_WData[31], EXWB_WData}:
					  {WBXX_WData[31], WBXX_WData};			
	assign  ALU_OP1 = (EX_BP_Sel_1 == 2'b00) ? {DCEX_Reg1[31], DCEX_Reg1} :
					  (EX_BP_Sel_1 == 2'b01) ? {EXWB_WData[31], EXWB_WData}:
					  {WBXX_WData[31], WBXX_WData};		

	
	
	// ALU operations
	// the following code has not been finished, please add here!!!!
	// Flag： N：计算结果为负时为1，否则为0；Z：计算结果为0时为1，否则为0；
	always@(DCEX_ALU_OP or ALU_OP0 or ALU_OP1 or DCEX_imm or ALU_Z_reg or ALU_N_reg)
	begin
		case(DCEX_ALU_OP)    //根据操作码指导ALU模块的操作
			4'b0000: begin		//ADD
				ALU_Result = ALU_OP0 + ALU_OP1;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			// please add the code for other instructions here!!!!
			
			4'b0001: begin		//SUB OR CMP
				ALU_Result = ALU_OP0 - ALU_OP1;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0010: begin		//AND
				ALU_Result = ALU_OP0 & ALU_OP1;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0011: begin		//OR
				ALU_Result = ALU_OP0 | ALU_OP1;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0100: begin		//XOR
				ALU_Result = ALU_OP0 ^ ALU_OP1;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0101: begin		//LSL
				ALU_Result = ALU_OP0 << DCEX_imm;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0110: begin		//LSR
				ALU_Result = ALU_OP0 >> DCEX_imm;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0111: begin		//ASR
				ALU_Result = ALU_OP0 >>> DCEX_imm;
				if (ALU_Result == 0)//由结果更新标志位
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			
			
			4'b1000: begin		//MOV
				ALU_Result = {27'h0000000, DCEX_imm};
				ALU_Z = ALU_Z_reg;
				ALU_N = ALU_N_reg;
			end
			default: begin
				ALU_Result = ALU_OP1;
				ALU_Z = ALU_Z_reg;
				ALU_N = ALU_N_reg;	
			end
		endcase			
	end
	
	// flag registers   标志位寄存器
	always@(posedge CLK or negedge Rstn) 
	begin
		if (!Rstn) begin
			ALU_Z_reg <= 1'b0;
			ALU_N_reg <= 1'b0;
		end 
		else begin
			ALU_Z_reg <= ALU_Z;
			ALU_N_reg <= ALU_N;
		end
	end
	
	// writeback data in EX stage
	assign EX_WData = (DCEX_LD) ? RData : ALU_Result[31:0];
	// If the current instruction is a load operation (DCEX_LD is true), 
	// then EX_WData will be set to the data read from memory (RData).
	// Otherwise, if it is not a load operation, EX_WData will be set to the result of ALU computation (ALU_Result[31:0]).

	// EXWB
	
	// EXWB registers EXWB流水线寄存器
	always@(posedge CLK or negedge Rstn)//异步复位所有寄存器清零，时钟上升沿读入数据
	begin
		if (!Rstn) begin
			EXWB_LD		<= 1'b0;
			EXWB_WB 		<= 1'b0;
			EXWB_WAddr 	<= 5'h00;
			EXWB_WData 	<= 32'h00000000;
		end
		else begin
			EXWB_LD		<= DCEX_LD;
			EXWB_WB 		<= DCEX_WB;
			EXWB_WAddr 	<= DCEX_RegAddr0;
			EXWB_WData 	<= EX_WData;
		end
	end
	

	// WBXX

	// WBXX registers WBXX流水线寄存器
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn) begin
			WBXX_WB 		<= 1'b0;
			WBXX_WAddr 	<= 5'h00;
			WBXX_WData 	<= 32'h00000000;
		end
		else begin
			WBXX_WB 		<= EXWB_WB;
			WBXX_WAddr 	<= EXWB_WAddr;
			WBXX_WData 	<= EXWB_WData;
		end
	end	


endmodule








