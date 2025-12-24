`timescale 1ns/1ps

module count_tb;

  reg         clk;
  reg         rst_n;
  reg         Load;
  reg  [31:0] IN;
  wire [5:0]  count_out;

  count dut (
    .clk       (clk),
    .rst_n     (rst_n),
    .Load      (Load),
    .IN        (IN),
    .count_out (count_out)
  );

  // 10ns 时钟
  initial clk = 1'b0;
  always #5 clk = ~clk;

  // 单拍装载、等待 33 拍后检查
  task automatic apply_check(input [31:0] vec, input [5:0] expect, input [127:0] name);
    begin
      @(negedge clk);
      IN   <= vec;
      Load <= 1'b1;
      @(posedge clk);    
      Load <= 1'b0;

      repeat (33) @(posedge clk);

      if (count_out !== expect) begin
        $display("[%0t] %-10s FAIL  IN=0x%08h expect=%0d got=%0d",
                 $time, name, vec, expect, count_out);
        $stop;   
      end else begin
        $display("[%0t] %-10s PASS  IN=0x%08h count_out=%0d",
                 $time, name, vec, count_out);
      end
      @(posedge clk);
    end
  endtask

  initial begin
    // 复位
    rst_n = 1'b0; Load = 1'b0; IN = 32'h0;
    repeat (3) @(posedge clk);
    rst_n = 1'b1;
    @(posedge clk);

    // 四组简单用例
    apply_check(32'h0000_0000, 6'd0 , "all_zero");
    apply_check(32'hFFFF_FFFF, 6'd32, "all_one");
    apply_check(32'h8000_0001, 6'd2 , "ends_1");
    apply_check(32'hF0F0_0F0F, 6'd16, "mix_16");

    $display("[%0t] ALL SIMPLE TESTS PASSED ✔", $time);
    $finish;   // 结束仿真
  end

endmodule
