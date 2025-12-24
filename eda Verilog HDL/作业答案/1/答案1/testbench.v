module testbench;
	reg 	A, B, C, D, E, F;
	wire 	O1, O2;
	
	// 实例化
	gate_style 	u1(A, B, C, D, E, F, O1);
	dataflow_style 	u2(A, B, C, D, E, F, O2);
	
	// 产生激励数据
	initial begin
			A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b0, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b0, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b0, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b0, E = 1'b1, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b0, F = 1'b1;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b0;
		#10	A = 1'b1, B = 1'b1, C = 1'b1, D = 1'b1, E = 1'b1, F = 1'b1;
		#10	$stop;
	end
	
	/*
	always
	begin
		F = 1'b0;
		#10 F = 1'b1;
		#10;
	end
	
	always
	begin
		E = 1'b0;
		#20 E = 1'b1;
		#20;
	end
	
	always
	begin
		D = 1'b0;
		#40 D = 1'b1;
		#40;
	end
	
	always
	begin
		C = 1'b0;
		#80 C = 1'b1;
		#80;
	end
	
	always
	begin
		B = 1'b0;
		#160 B = 1'b1;
		#160;
	end
	
	always
	begin
		A = 1'b0;
		#320 A = 1'b1;
		#320;
		#10 $stop;
	end
	*/
	
	// 检测信号变化
	initial begin
		$monitor($time,":\tA=%b\tB=%b\tC=%b\tD=%b\tE=%b\tF=%b\tO1=%b\tO2=%b\n",A,B,C,D,E,F,O1,O2);
	end
end module

