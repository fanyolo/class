
module lamp_df(
  input  wire [2:0] fault,   // 1=故障
  output wire       R,       // 红灯
  output wire       Y        // 黄灯
);
  wire [1:0] s;
  assign s = {1'b0,fault[0]} + {1'b0,fault[1]} + {1'b0,fault[2]};
  assign Y = (s==2'd1) | (s==2'd3);
  assign R = (s==2'd2) | (s==2'd3);
endmodule