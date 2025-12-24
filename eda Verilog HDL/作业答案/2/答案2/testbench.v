module testbench;
	reg 	A, B, C;
	wire 	G, Y, R;
	
	// 实例化
	waterdetector 	waterdetector(A, B, C, G, Y, R);
	
	// 产生激励数据
	initial begin
			 A = 1'b0, B = 1'b0, C = 1'b0;
		#10	 A = 1'b0, B = 1'b0, C = 1'b1;
		#10	 A = 1'b0, B = 1'b1, C = 1'b0;
		#10	 A = 1'b0, B = 1'b1, C = 1'b1;
		#10	 A = 1'b1, B = 1'b0, C = 1'b0;
		#10	 A = 1'b1, B = 1'b0, C = 1'b1;
		#10	 A = 1'b1, B = 1'b1, C = 1'b0;
		#10	 A = 1'b1, B = 1'b1, C = 1'b1;
		#10	$stop;
	end
	
	
	// 检测信号变化
	initial begin
		$monitor($time,":\tA=%b\tB=%b\tC=%b\tG=%b\tY=%b\tR=%b\n",A,B,C,G,Y,R);
	end
end module

