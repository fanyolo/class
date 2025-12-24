`timescale 1ns/1ns
module testbench;
	reg A, B, C;
	wire Y0, R0, Y1, R1;
  
	behaviour_style U1(A,B,C,Y0,R0);
	data_style U2(A,B,C,Y1,R1);
  
	initial begin
			A=0;B=0;C=0;
		#50 A=0;B=0;C=1;
		#50 A=0;B=1;C=0;
		#50 A=0;B=1;C=1;
		#50 A=1;B=0;C=0;
		#50 A=1;B=0;C=1;
		#50 A=1;B=1;C=0;
		#50 A=1;B=1;C=1;
		#50 A=0;B=0;C=0;
		#50 $stop;
	end
  
	initial begin
		$monitor($time,":\tA=%b\tB=%b\tC=%b\tY0=%b\tR0=%b\tY1=%b\tR1=%b\n",A,B,C,Y0,R0,Y1,R1);
	end
  
endmodule
