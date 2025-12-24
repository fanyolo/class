module dataflow_style(A,B,C,D,E,F,O);
	input 	A,B,C,D,E,F;
	output 	O;
	
	wire 	AND_AB, OR_CD, NOR_EF, XOR_O, XNOR_O;
	
	assign AND_AB = A & B;
	assign OR_CD = C | D;
	assign NOR_EF = ~(E | F);
	assign XOR_O = AND_AB ^ OR_CD;
	assign XNOR_O = OR_CD ~^ NOR_EF;
	assign O = ~(XOR_O & XNOR_O);
	
	//assign O = ~(((A & B) ^ (C | D)) & ((C | D) ~^ ~(E | F)));
	
endmodule