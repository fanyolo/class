module RISC16(CLK, Rstn, InstAddr, Inst, DW, DAddr, WData, RData);
	// 输入信号
	input 			CLK, Rstn;              // CLK：时钟信号，Rstn：复位信号（低电平有效）
	// 输出信号
	output [31:0]	InstAddr, DAddr;       // InstAddr：指令地址，DAddr：数据地址（32位地址）
	output			DW;                     // DW：写数据使能信号（1位）
	output [31:0]	WData;                  // WData：写数据（32位）
	// 输入数据
	input  [15:0]	Inst;                   // Inst：指令输入（16位）
	input  [31:0]	RData;                  // RData：读取数据（32位）
	// 参数定义
	parameter 		Rstn_Addr = 0;          // 参数：复位地址（0）

	// IA阶段
	reg Rstn_flag;               // 复位标志
	reg [31:0] PC_reg;           // 程序计数器寄存器，存储当前PC值
	wire [31:0] PC_add2, PC_addoffset, PC; // PC + 2，PC + offset，当前PC
	wire [1:0] PC_Sel;           // PC选择信号，选择新的PC值
	reg PC_W;                    // 程序计数器写使能信号
	// DC阶段
	reg [15:0] IFDC_reg;         // IF到DC阶段的流水线寄存器，存储指令
	reg IFDC_W;                  // IFDC寄存器写使能
	wire IFDC_Flush;             // IFDC清除信号
	reg [31:0] RegFile[31:0];    // 寄存器文件，存储32个32位寄存器
	wire [31:0] Reg0, Reg1;      // 操作数0和操作数1，从寄存器文件读取
	reg [3:0] DC_ALU_OP;         // ALU操作码，控制ALU操作
	reg DC_WB, DC_DW, DC_LD;     // 写回、存储、加载信号
	reg [3:0] DC_BJ;             // 分支条件信号
	wire [1:0] DC_BP_Sel_0, DC_BP_Sel_1; // 旁路选择信号
    // EX阶段
	// reg DCEX_Flush;   // 清除DCEX寄存器的信号（未使用）
	reg [3:0] DCEX_ALU_OP;          // ALU操作码，指示ALU要执行的操作
	reg DCEX_DW, DCEX_LD, DCEX_WB;  // 存储、加载、写回信号，控制数据操作
	reg [31:0] DCEX_Reg0, DCEX_Reg1; // 操作数0和操作数1，传递到ALU进行计算
	reg [4:0] DCEX_imm, DCEX_RegAddr0, DCEX_RegAddr1; // 立即数、寄存器地址0和1，传递给ALU

	wire signed [32:0] ALU_OP0, ALU_OP1; // ALU操作数0和1，供ALU运算使用
	reg signed [32:0] ALU_Result;        // ALU计算结果
	reg ALU_Z, ALU_N;                   // ALU零标志（Z）和负标志（N）
	reg ALU_Z_reg, ALU_N_reg;           // ALU零标志和负标志的寄存器，用于存储ALU的状态

	wire [1:0] EX_BP_Sel_0, EX_BP_Sel_1; // 旁路选择信号，用于数据旁路
	wire [31:0] EX_WData;               // EX阶段的写回数据
	// WB阶段
	reg EXWB_LD;                       // EXWB寄存器的加载信号
	reg EXWB_WB;                       // EXWB寄存器的写回信号
	reg [4:0] EXWB_WAddr;              // EXWB寄存器中的写回地址
	reg [31:0] EXWB_WData;             // EXWB寄存器中的写回数据
	reg [31:0] EXWB_Reg1;              // EXWB寄存器中的操作数1
						
	// XX stage
	reg				WBXX_WB	;												// writeback signal in WBXX register
	reg	[4:0]		WBXX_WAddr;												// writeback address in WBXX register
	reg	[31:0]		WBXX_WData;												// writeback data in WBXX regsiter
	
	
	//	
	// IA stage
	//
	
	// reset flag
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn)
			Rstn_flag <= 1'b1;
		else
			Rstn_flag <= 1'b0;
	end

	assign PC_add2 = PC_reg + 2'b10;
	assign PC_addoffset = PC_reg + {{21{IFDC_reg[9]}},IFDC_reg[9:0],1'b0};
	assign PC = (Rstn_flag == 1'b1) ? Rstn_Addr : 
				(PC_Sel == 2'b00) ? PC_add2 : 
				(PC_Sel == 2'b01) ? PC_addoffset : 
									{21'h000000,IFDC_reg[9:0],1'b0};		// normal case; branch; jump
	
	//
	// IF stage
	//
	
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
	
	// IFDC register
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn)
			IFDC_reg <= 16'h0000;
		else if (IFDC_Flush)
			IFDC_reg <= 16'h0000;
		else if (IFDC_W)
			IFDC_reg <= Inst;
	end
	
	// RegFile
	always@(posedge CLK)
	begin
		if (EXWB_WB)
			RegFile[EXWB_WAddr] <= EXWB_WData;
	end

	// operand 0 and 1 from register file
	assign Reg0 = RegFile[IFDC_reg[9:5]];
	assign Reg1 = RegFile[IFDC_reg[4:0]];

	// decoder
	always@(IFDC_reg[15:10])
	begin
		case(IFDC_reg[15:10])
		6'b010000: begin
			DC_ALU_OP	= 4'b0000;	//ADD
			DC_WB	   	= 1'b1;		//have writeback
			DC_DW	  	= 1'b0;		//no datawrite
			DC_LD	   	= 1'b0;		//no load
			DC_BJ	   	= 4'b0000;	// no Branch, no JUMP
			PC_W	   	= 1'b1;		//LOW POWER PC WAIT
			IFDC_W   	= 1'b1;		//LOW POWER IFDC WAIT
		end
		6'b010001: begin			//SUB
			DC_ALU_OP   = 4'b0001;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b010010: begin			//CMP
			DC_ALU_OP   = 4'b0001;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b010100: begin			//AND
			DC_ALU_OP   = 4'b0010;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b010101: begin			//OR
			DC_ALU_OP   = 4'b0011;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b010110: begin			//XOR
			DC_ALU_OP   = 4'b0100;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b100000: begin			//LSL
			DC_ALU_OP   = 4'b0101;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b100001: begin			//LSR
			DC_ALU_OP   = 4'b0110;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b100010: begin			//ASR
			DC_ALU_OP   = 4'b0111;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b100111: begin			//MOV
			DC_ALU_OP   = 4'b1000;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b011000: begin			//LD
			DC_ALU_OP   = 4'b1001;
			DC_WB       = 1'b1;
			DC_DW       = 1'b0;
			DC_LD		= 1'b1;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b011001: begin			//ST
			DC_ALU_OP   = 4'b1010;
			DC_WB       = 1'b0;
			DC_DW       = 1'b1;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110000: begin			//BZ  
			DC_ALU_OP   = 4'b1011 ;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0001;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110001: begin			//BNZ  
			DC_ALU_OP   = 4'b1011 ;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0010;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110010: begin			//BLE  
			DC_ALU_OP   = 4'b1011 ;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0011;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110011: begin			//BLT  
			DC_ALU_OP   = 4'b1011 ;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0100;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110100: begin			//BGE  
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0101;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110100: begin			//BGT  
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0110;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b110110: begin			//B  
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0111;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b111000: begin			//JUMP 
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b1000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b000000: begin			//NOP
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b1;
			IFDC_W		= 1'b1;
		end
		6'b000001: begin			//WAIT
			DC_ALU_OP   = 4'b1011;
			DC_WB       = 1'b0;
			DC_DW       = 1'b0;
			DC_LD		= 1'b0;
			DC_BJ 		= 4'b0000;
			PC_W		= 1'b0;
			IFDC_W		= 1'b0;
		end
		endcase
		
	end
	
	// Branch
	
	// select signal for PC
	assign PC_Sel = 	(DC_BJ == 4'b0001 && ALU_Z == 1'b1) 					? 2'b01 :	//BZ
						(DC_BJ == 4'b0010 && ALU_Z == 1'b0) 					? 2'b01 : 	//BNZ
						(DC_BJ == 4'b0011 && (ALU_Z == 1'b1 || ALU_N == 1'b1))	? 2'b01	:	//BLE
						(DC_BJ == 4'b0100 && (ALU_Z == 1'b0 && ALU_N == 1'b1))	? 2'b01 :   //BLT
						(DC_BJ == 4'b0101 && (ALU_Z == 1'b1 || ALU_N == 1'b0))	? 2'b01 :   //BGE
						(DC_BJ == 4'b0110 && (ALU_Z == 1'b0 && ALU_N == 1'b0))	? 2'b01 :   //BLT
						(DC_BJ == 4'b0111)										? 2'b01 :	//BGE
						(DC_BJ == 4'b1000)                                      ? 2'b10 :   //JUMP
																				  2'b00;	//NO_JUMP
						
	
	
	// clear signal for IFDC register
	assign IFDC_Flush = (PC_Sel != 2'b00) ? 1'b1 : 1'b0;
	
	
	assign EX_BP_Sel_0 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr0))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr0)) ? 2'b10:
																	  2'b00;
						 
	assign EX_BP_Sel_1 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr1))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr1)) ? 2'b10:
																	  2'b00;
	// bypass controller 0			 
	assign DC_BP_Sel_0 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr0))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr0)) ? 2'b10:
																	  2'b00;
	assign DC_BP_Sel_1 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr1))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr1)) ? 2'b10:
																	  2'b00;
						 
	// DataRAM interface				 
	assign DW 		=  DC_DW;
	assign DAddr 	= (DC_BP_Sel_1 == 2'b01) ? DCEX_Reg1 :
					  (DC_BP_Sel_1 == 2'b10) ? EXWB_Reg1 :
											   Reg1;
	assign WData 	= (DC_BP_Sel_0 == 2'b01) ? EXWB_WData :
					  (DC_BP_Sel_0 == 2'b10) ? WBXX_WData :
											   Reg0;
							
	
	//
	// EX stage
	//

	// DCEX registers
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn) begin
			DCEX_ALU_OP 	<= 4'b0000;
			DCEX_DW			<= 1'b0;
			DCEX_LD			<= 1'b0;
			DCEX_WB			<= 1'b0;
			DCEX_Reg0 		<= 32'h00000000;
			DCEX_Reg1		<= 32'h00000000;
			DCEX_imm		<= 5'h00;
			DCEX_RegAddr0 	<= 5'h00;
			DCEX_RegAddr1 	<= 5'h00;
		end
		else begin
			DCEX_ALU_OP 	<= DC_ALU_OP;
			DCEX_DW			<= DC_DW;
			DCEX_LD			<= DC_LD;
			DCEX_WB			<= DC_WB;
			DCEX_Reg0 		<= Reg0;
			DCEX_Reg1		<= Reg1;
			DCEX_imm		<= IFDC_reg[4:0];
			DCEX_RegAddr0 	<= IFDC_reg[9:5];
			DCEX_RegAddr1 	<= IFDC_reg[4:0];
		end
	end



	// bypass controller 1					 
	assign EX_BP_Sel_0 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr0))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr0)) ? 2'b10:
																	  2'b00;
						 
	assign EX_BP_Sel_1 = (EXWB_WB && (EXWB_WAddr == DCEX_RegAddr1))	? 2'b01:
						 (WBXX_WB && (WBXX_WAddr == DCEX_RegAddr1)) ? 2'b10:
																	  2'b00;
						 

						 
	// ALU
	
	// operands
	assign  ALU_OP0 = (EX_BP_Sel_0 == 2'b01) ? EXWB_WData :
					  (EX_BP_Sel_0 == 2'b10) ? WBXX_WData :
											   DCEX_Reg0;
												
	assign  ALU_OP1 = (EX_BP_Sel_1 == 2'b01) ? EXWB_WData :
					  (EX_BP_Sel_1 == 2'b10) ? WBXX_WData :
											   DCEX_Reg1;						 
	
	// ALU operations
	always@(DCEX_ALU_OP or ALU_OP0 or ALU_OP1 or DCEX_imm or ALU_Z_reg or ALU_N_reg)
	begin
		case(DCEX_ALU_OP)
			4'b0000: begin		//ADD
				ALU_Result = ALU_OP0 + ALU_OP1;
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0001:begin		//SUB、CMP
				ALU_Result = ALU_OP0 - ALU_OP1;
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0010:begin		//AND
				ALU_Result = ALU_OP0 & ALU_OP1;
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0011:begin		//OR
				ALU_Result = ALU_OP0 | ALU_OP1;
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0100:begin		//XOR
				ALU_Result = ALU_OP0 ^ ALU_OP1;
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0101:begin		//LSL
				ALU_Result = {ALU_OP0[30:0],0};
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0110:begin		//LSR
				ALU_Result = {0,ALU_OP0[31:1]};
				if (ALU_Result == 0)
					ALU_Z = 1'b1;
				else
					ALU_Z = 1'b0;
				if (ALU_Result[32:31] == 2'b11)
					ALU_N = 1'b1;
				else
					ALU_N = 1'b0;
			end
			4'b0111:begin		//ASR
				ALU_Result = {ALU_OP0[31],ALU_OP0[31:1]};
				if (ALU_Result == 0)
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
			4'b1001: begin		//LD
				ALU_Result = 32'h00000000;
				ALU_Z = 1'b0;
				ALU_N = 1'b0;
			end
			4'b1010: begin		//ST
				ALU_Result = 32'h00000000;
				ALU_Z = 1'b0;
				ALU_N = 1'b0;
			end
			4'b1011: begin 		//Bcc
				ALU_Result = 32'h00000000;
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
	
	// flag registers
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
	
	//
	// EXWB
	//
		
	// EXWB registers
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn) begin
			EXWB_LD		<= 1'b0;
			EXWB_WB 	<= 1'b0;
			EXWB_Reg1	<= 32'h00000000;
			EXWB_WAddr 	<= 5'h00;
			EXWB_WData 	<= 32'h00000000;
		end
		else begin
			EXWB_LD		<= DCEX_LD;
			EXWB_WB 	<= DCEX_WB;
			EXWB_Reg1   <= DCEX_Reg1;
			EXWB_WAddr 	<= DCEX_RegAddr0;
			EXWB_WData 	<= EX_WData;
		end
	end
	
	
	//
	// WBXX
	//
	
	// WBXX registers
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn) begin
			WBXX_WB 	<= 1'b0;
			WBXX_WAddr 	<= 5'h00;
			WBXX_WData 	<= 32'h00000000;
		end
		else begin
			WBXX_WB 	<= EXWB_WB;
			WBXX_WAddr 	<= EXWB_WAddr;
			WBXX_WData 	<= EXWB_WData;
		end
	end	


endmodule








