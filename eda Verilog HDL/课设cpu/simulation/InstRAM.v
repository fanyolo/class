// Instruction Memory for testing

module InstRAM (CLK, InstAddr, Inst);
	parameter 				WIDTH = 8;
	
	input					CLK;
	input      	[WIDTH-1:0] InstAddr;
	output	 	[15:0] 		Inst;

   reg  [15:0] RAM [(1<<(WIDTH-1))-1:0];
	reg [WIDTH-1:0] InstAddr_reg;

	// Initialize DataRAM
   initial begin
         $readmemb("InstRAM.dat",RAM);
   end

	// Register the address
	always@(posedge CLK)
		InstAddr_reg <= InstAddr;
		
   // Read
   assign Inst = RAM[(InstAddr_reg>>1)];

endmodule
