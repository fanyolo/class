module bus(CLK, Rstn, DW, DAddr, WData, RData, M_DW, M_Addr, M_WData, M_RData, U_mp_cs_l, U_mp_addx, U_mp_data_to_uart,	U_mp_data_from_uart, U_mp_rd_l,	U_mp_wr_l);

	input 			CLK, Rstn;
	input			DW;
	input [31:0]	DAddr;
	input [31:0]	WData;
	output  [31:0]	RData;
	output 			M_DW; 
	output [7:0]	M_Addr;
	output [31:0]	M_WData;
	input [31:0]	M_RData;
	output 			U_mp_cs_l;
	output [2:0]	U_mp_addx;
	output [7:0]	U_mp_data_to_uart;
	input [7:0]		U_mp_data_from_uart;
	output 			U_mp_rd_l,	U_mp_wr_l;
	
	wire 			access_mem;
	reg 			rd_mem_reg;
	reg	[7:0]		data_from_uart_reg;
	
	assign access_mem = (DAddr[31:10] === 22'h000000)? 1'b1 : 1'b0;
	
	always@(posedge CLK or negedge Rstn)
	begin
		if (!Rstn)
			rd_mem_reg <= 1'b0;
		else if (!DW && access_mem)
			rd_mem_reg <= 1'b1;
		else
			rd_mem_reg <= 1'b0;
	end
	
	assign M_DW = (access_mem) ? DW : 1'b0;
	assign M_Addr = (access_mem)? DAddr[9:2] : 8'h00;
	assign M_WData = WData;
	
	assign U_mp_cs_l = (access_mem) ? 1'b1 : 1'b0;
	assign U_mp_rd_l = (access_mem) ? 1'b1 : DW;
	assign U_mp_wr_l = (access_mem) ? 1'b1 : ~DW;
	assign U_mp_addx = (access_mem) ? 3'h0 : DAddr[2:0];
	assign U_mp_data_to_uart = WData[7:0];
	
	always@(posedge CLK)
		data_from_uart_reg <= U_mp_data_from_uart;
		
	assign RData = (rd_mem_reg) ? M_RData : {24'h000000, data_from_uart_reg};	
	
endmodule








