//ONE_SHOT.v
module one_shot (sys_rst_l, clk_in, d, q);
  input  sys_rst_l;
  input  clk_in;
  input  d;
  output q;
  reg    d_del;

always@ (posedge clk_in or negedge sys_rst_l)
  if (~sys_rst_l) d_del <= 1'b1;
  else d_del <= ~d;
assign q=d & d_del;
endmodule