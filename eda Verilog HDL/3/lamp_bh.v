
module lamp_bh(
  input  wire [2:0] fault,   // 1=故障
  output reg        R,       // 红灯
  output reg        Y        // 黄灯
);
  reg [1:0] s;
  always @* begin
    R = 1'b0; Y = 1'b0;
    s = {1'b0,fault[0]} + {1'b0,fault[1]} + {1'b0,fault[2]};
    case (s)
      2'd1: Y = 1'b1;                 
      2'd2: R = 1'b1;                 
      2'd3: begin Y=1'b1; R=1'b1; end 
      default: ;                      
    endcase
  end
endmodule