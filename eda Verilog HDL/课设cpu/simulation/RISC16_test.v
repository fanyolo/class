
// top level design for testing
module RISC16_test();
   parameter		   WIDTH = 8;
   reg                 CLK;
   reg                 Rstn;
   
   wire           DW;
   wire [31:0]    InstAddr, DAddr;
   wire [15:0]    Inst;
   wire [31:0]    RData, WData;
       

   // instantiate RISC16 to be tested
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
	
	// instantiate Data Memory for testing
	DataRAM	#(8)	DataRAM(
		.CLK		(CLK		),
		.Rstn		(Rstn		),
		.DW			(DW			),
		.DAddr		(DAddr		),
		.WData		(WData		),
		.RData		(RData		)
	);
	
	// instantiate Data Memory for testing
	InstRAM	#(8)	InstRAM(
		.CLK		(CLK		),
		.InstAddr	(InstAddr	),
		.Inst		(Inst		)
	);

   // initialize test
   initial
      begin
         Rstn = 1; 
         # 22; 
         Rstn = 0;
         # 100;
         Rstn = 1;
      end

   // generate clock to sequence tests
   always
      begin
         CLK = 1; 
         # 5; 
         CLK = 0; 
         # 5;
      end

   always@(posedge CLK)
      begin
         if(InstAddr == 32'h000000c2) begin
				$display("Execution error happened!!!");
				$stop;
			end
			if (InstAddr == 32'h000000bc) begin
				$display("Simulation completely successful");
				$stop;
			end
      end
endmodule
