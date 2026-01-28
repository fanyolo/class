//BAUD.v
module baud(sys_clk,sys_rst_l,baud_clk,baud_rate_div);
  `include "uart_inc.h"
  input sys_clk;
  input sys_rst_l;
  output baud_clk;
  input [15:0]baud_rate_div;
  reg   [15:0] clk_div;
  reg   baud_clk;
  always@ (posedge sys_clk or negedge sys_rst_l)
    if (~sys_rst_l) begin clk_div <=0; baud_clk <=0; end
    else if (clk_div ==baud_rate_div) begin
      clk_div  <=0;
      baud_clk <=~baud_clk;
      end
    else begin
      clk_div  <=clk_div+ 1'b1;
      baud_clk <=baud_clk;
    end
endmodule