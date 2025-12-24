module gate_style(A,B,C,D,E,F,O);
	input 	A,B,C,D,E,F;
	output 	O;
	
	wire 	AND_AB, OR_CD, NOR_EF, XOR_O, XNOR_O;
	
	AND2 	u1(AND_AB, A, B);
	OR2 	u2(OR_CD, C, D);
	NOR2	u3(NOR_EF, E, F);
	XOR		u4(XOR_O, AND_AB, OR_CD);
	XNOR	u5(XNOR_O, OR_CD, NOR_EF);
	NAND2	u6(O, XOR_O, XNOR_O);

endmodule