// Data Memory for testing

module DataRAM (CLK, Rstn, DW, DAddr, WData, RData);
	parameter 				WIDTH = 8;
	input                  	CLK;
	input					Rstn;
	input                  	DW;
	input      	[WIDTH-1:0] DAddr; 
	input		[31:0]		WData;
	output	 	[31:0] 		RData;

   reg  [31:0] RAM [(1<<(WIDTH-2))-1:0];
   reg  [WIDTH-1 :0] DAddr_reg;
   reg				DW_reg;
   reg 	[31:0]		WData_reg;

	// Initialize DataRAM
   initial begin
         $readmemh("DataRAM.dat",RAM);
   end
   
   // Register the address
   always@(posedge CLK or negedge Rstn)
   begin
	if (!Rstn) begin
		DAddr_reg <= 0;
		DW_reg <= 0;
		WData_reg <= 0;
	end
	else begin
		DAddr_reg <= DAddr;
		DW_reg <= DW;
		WData_reg <= WData;
	end
   end

   // Write
   always@(posedge CLK)
   begin
      if(DW_reg)
		RAM[DAddr_reg[WIDTH-1:2]] <= WData_reg;
	end    
	     
   // Read
   assign RData = RAM[DAddr_reg>>2];

endmodule
