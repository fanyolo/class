//UART.v
module uart( 
	sys_rst_l,
	sys_clk, uart_clk,
     
	mp_clk,
	mp_cs_l,
	mp_addx,
	mp_data_to_uart,
	mp_data_from_uart,
	mp_rd_l,
	mp_wr_l, mp_int_l,
     
	uart_XMIT_dataH,
	uart_REC_dataH,
     
	stat_rec_dataH,
	stat_xmit_emptyH
	  );
`include "uart_inc.h"

  input sys_rst_l;
  input sys_clk;
  output uart_clk;

input mp_clk;
input mp_cs_l;
input [2:0] mp_addx;
input [7:0] mp_data_to_uart;
output [7:0] mp_data_from_uart;
input  mp_rd_l;
input mp_wr_l;
output mp_int_l;

output  uart_XMIT_dataH;
input  uart_REC_dataH;

output  stat_rec_dataH;
output  stat_xmit_emptyH;

wire uart_clk;
wire [15:0]baud_rate_div;
wire xmit_start_pulseH;
wire xmit_doneH;
wire [7:0]reg_xmit_dat;
wire xmit_busyH;
wire [7:0]rec_dataH;
wire rec_readyH;
wire stat_rec_dataH;
wire stat_xmit_emptyH;

mp_int iMP_INT(
  
    .sys_rst_l(sys_rst_l),
    .uart_clk(uart_clk),
    .mp_clk(mp_clk),
    .mp_cs_l(mp_cs_l),
    .mp_addx(mp_addx),
    .mp_data_from_uart(mp_data_from_uart),
    .mp_data_to_uart(mp_data_to_uart),
    .mp_rd_l(mp_rd_l),
    .mp_wr_l(mp_wr_l),
    .mp_int_l(mp_int_l),
 
    .baud_rate_div(baud_rate_div),
  
    .start_pulseH(xmit_start_pulseH),
    .xmit_doneH(xmit_doneH),
    .reg_xmit_dat(reg_xmit_dat),
    .xmit_busyH(xmit_busyH),
  
    .rec_dataH(rec_dataH),
    .rec_readyH(rec_readyH),
  
    .stat_rec_dataH(stat_rec_dataH),
    .stat_xmit_emptyH(stat_xmit_emptyH)
      );

u_xmit  iXMIT( .sys_clk(uart_clk),
    .sys_rst_l(sys_rst_l),
    .uart_xmitH(uart_XMIT_dataH),
    .xmitH(xmit_start_pulseH),
    .xmit_dataH(reg_xmit_dat),
    .xmit_doneH(xmit_doneH)
      );

u_rec iRECEIVER(
    .sys_rst_l(sys_rst_l),
    .sys_clk(uart_clk),
    .uart_dataH(uart_REC_dataH),
    .rec_dataH(rec_dataH),
    .rec_readyH(rec_readyH)
      );

baud iBAUD(
    .sys_clk(sys_clk),
    .sys_rst_l(sys_rst_l),
    .baud_clk(uart_clk),
    .baud_rate_div(baud_rate_div)
       );
endmodule