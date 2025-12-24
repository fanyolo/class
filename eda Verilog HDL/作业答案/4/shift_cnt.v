module shift_cnt(clk, rstn, i_load, i_data, o_cnt);
	parameter 		N0 = 32, N1 = 6;
	input			clk, rstn;
	input			i_load;
	input [N0-1:0] 	i_data;
	output [N1-1:0] o_cnt;

	reg [N0-1:0] 	shiftdata;
	reg [N1-1:0] 	cnt, o_cnt;

	// 带异步清零及同步置位的移位寄存器
	always@(posedge clk or negedge rstn)
	begin
		if (!rstn)
			shiftdata <= 0;
		else if (i_load)
			shiftdata <= i_data;
		else
			shiftdata <= {1'b0, shiftdata[N0-1:1]};
	end
	
	// 带异步清零及同步置位的计数器
	always@(posedge clk or negedge rstn)
	begin
		if (!rstn)
			cnt <= 0;
		else if (i_load)
			cnt <= 0;
		else
			cnt <= cnt + shiftdata[0];
	end
	
	// 带异步清零的寄存器
	always@(posedge clk or negedge rstn)
	begin
		if (!rstn)
			o_cnt <= 0;
		else
			o_cnt <= cnt;
	end
endmodule