

`timescale 1ns/1ps
module tb;
  reg  [2:0] fault;
  wire R, Y;

  // 二选一：测谁留谁
  lamp_df dut(.fault(fault), .R(R), .Y(Y));
  // lamp_bh dut(.fault(fault), .R(R), .Y(Y));

  initial begin
    $display("time  fault | Y R  (期望: 1台10, 2台01, 3台11)");
    $monitor("%4t  %b | %b %b", $time, fault, Y, R);

    fault=3'b000; #10;
    fault=3'b001; #10;
    fault=3'b010; #10;
    fault=3'b100; #10;
    fault=3'b011; #10;
    fault=3'b101; #10;
    fault=3'b110; #10;
    fault=3'b111; #10;
    $finish;
  end
endmodule
