//SYNC.V
module sync (clk_in,sys_rst_l, d, q);
  input  clk_in;
  input  sys_rst_l;
  input  d;
  output q;
  reg  pipe1, pipe2;
always@ (posedge clk_in or negedge sys_rst_l)
  if (~sys_rst_l) begin pipe1 <= 0; pipe2 <= 0; end
  else begin pipe1 <= d;pipe2 <= pipe1; end
assign q= pipe2;
endmodule