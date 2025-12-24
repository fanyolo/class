
module water_level (
    input  wire a,   
    input  wire b,  
    input  wire c,   
    output reg  G,   // 绿灯
    output reg  Y,   // 黄灯
    output reg  R    // 红灯
);
    always @* begin
       
        G = 1'b0; Y = 1'b0; R = 1'b0;

      
        case ({a,b,c})
            3'b100: G = 1'b1;                 // A~B 正常区 → 绿灯
            3'b110: Y = 1'b1;                 // B~C 异常区 → 黄灯
            3'b000: Y = 1'b1;                 // A以上(过高) → 黄灯
            3'b111: R = 1'b1;                 // C以下(危险) → 红灯

            default: begin
            
                Y = 1'b1;
            end
        endcase
    end
endmodule

