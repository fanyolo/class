`timescale 1ns/1ps

module testbench;
	parameter		CLK_PERIOD = 10;
	reg				clk, rstn, load;
	reg [31:0]	data;
	wire [5:0]	cnt;

	// 实例化(参数传递）
	shift_cnt	#(32, 6) shift_cnt(
					.clk	(clk), 
					.rstn	(rstn), 
					.i_load	(load), 
					.i_data	(data), 
					.o_cnt	(cnt)
				);
				
	// 产生时钟激励
	always begin
		clk = 1'b1;
		#((CLK_PERIOD)/2) clk = 1'b0;
		#((CLK_PERIOD)/2);
	end
	
	// 产生复位激励
	initial begin
		rstn = 1'b0;		//复位
		#(5*CLK_PERIOD+1) 	rstn = 1'b1;	//释放复位
		#(1000*CLK_PERIOD) 	$stop;		//暂停仿真
	end
	
	// 产生其它激励信号
	initial begin
		load = 1'b0;
		#(10*CLK_PERIOD+1);
		forever begin
			load = 1'b1;
			data = $random();
			#CLK_PERIOD;
			load = 1'b0;
			#(CLK_PERIOD*40);
		end
	end
	
		// 检测并输出结果
	initial begin
		$monitor($time, "\tdata = %h, cnt = %d", data, cnt);
	end
endmodule