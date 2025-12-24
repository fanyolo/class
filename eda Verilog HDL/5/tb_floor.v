
`timescale 1ns/1ps
module tb_floor;
    reg clk, rstn;
    reg floor1, floor2, floor3;
    wire [2:0] led;

    // DUT
    floor dut(
        .clk(clk), .rstn(rstn),
        .floor1(floor1), .floor2(floor2), .floor3(floor3),
        .led(led)
    );

   
    initial begin
        clk = 0;
        forever #5 clk = ~clk;     // 10ns 周期
    end

  
    initial begin
        $dumpfile("tb_floor.vcd");
        $dumpvars(0, tb_floor);
    end

  
    initial begin
        $display(" time    led   req dir state | f1 f2 f3");
        $monitor("%5t   %b   %b   %0d    %0d   |  %b  %b  %b",
                 $time, led, dut.req, dut.dir, dut.state,
                 floor1, floor2, floor3);
    end

 
    task press1; begin floor1=1; @(posedge clk); floor1=0; end endtask
    task press2; begin floor2=1; @(posedge clk); floor2=0; end endtask
    task press3; begin floor3=1; @(posedge clk); floor3=0; end endtask

    
    initial begin
        rstn   = 0; floor1 = 0; floor2 = 0; floor3 = 0;
        repeat (2) @(posedge clk);
        rstn   = 1;                         

        // 测试1：请求到 3 楼
        @(posedge clk); press3();

        repeat (4) @(posedge clk);

        // 测试2：在 3 楼请求到 1 楼
        press1();

        // 测试3：下行途中在 3→2 之间再请求 2 楼
        repeat (1) @(posedge clk); press2();

        // 结束
        repeat (10) @(posedge clk);
        $finish;
    end
endmodule
