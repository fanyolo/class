//
//	
// top level design
module RISC16_Uart(CLK, Rstn, RXD, TXD);
   input            CLK;
   input           Rstn;
   input			RXD;
   output			TXD;
   
	wire           	DW;
	wire [31:0]    	InstAddr, DAddr;
	wire [15:0]    	Inst;
	wire [31:0]    	RData, WData;
	wire 			M_DW; 
	wire [7:0]		M_Addr;
	wire [31:0]		M_WData;
	wire [31:0]		M_RData;
	wire 			U_mp_cs_l;
	wire [2:0]		U_mp_addx;
	wire [7:0]		U_mp_data_to_uart;
	wire [7:0]		U_mp_data_from_uart;
	wire 			U_mp_rd_l,	U_mp_wr_l;
 

	// instantiate Instruction Memory
	InstRAM	InstRAM(
		.address	(InstAddr[8:1]	),
		.clock		(CLK		),
		.q			(Inst		)
	); 

   // instantiate RISC16
   RISC16 RISC16(
		.CLK		(CLK		), 
		.Rstn		(Rstn		), 
		.InstAddr	(InstAddr	), 
		.Inst		(Inst		), 
		.DW			(DW			), 
		.DAddr		(DAddr		), 
		.WData		(WData		), 
		.RData		(RData		)
	);
	
	// instantiate BUS
	bus bus(
		.CLK		(CLK		), 
		.Rstn		(Rstn		),
		.DW			(DW			),
		.DAddr		(DAddr		),
		.WData		(WData		),
		.RData		(RData		),
		.M_DW		(M_DW		),
		.M_Addr		(M_Addr		),
		.M_WData	(M_WData	),
		.M_RData	(M_RData	),
		.U_mp_cs_l	(U_mp_cs_l	),
		.U_mp_addx	(U_mp_addx	),
		.U_mp_data_to_uart		(U_mp_data_to_uart),
		.U_mp_data_from_uart	(U_mp_data_from_uart),
		.U_mp_rd_l	(U_mp_rd_l	),	
		.U_mp_wr_l	(U_mp_wr_l	)
	);
	
	// instantiate Data Memory
	DataRAM DataRAM(
		.address	(M_Addr		),
		.clock		(CLK		),
		.data		(M_WData	),
		.wren		(M_DW		),
		.q			(M_RData	)
	);

	// instantiate UART
	uart uart(
		.sys_rst_l(Rstn),
		.sys_clk(CLK),
		.uart_clk(),
		.mp_clk(CLK),
		.mp_cs_l(U_mp_cs_l),
		.mp_addx(U_mp_addx),
		.mp_data_to_uart(U_mp_data_to_uart),
		.mp_data_from_uart(U_mp_data_from_uart),
		.mp_rd_l(U_mp_rd_l),
		.mp_wr_l(U_mp_wr_l),
		.mp_int_l(),
		.uart_XMIT_dataH(TXD),
		.uart_REC_dataH(RXD),
		.stat_rec_dataH(),
		.stat_xmit_emptyH()
	);


endmodule
