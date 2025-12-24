
module count (
    input  wire        clk,
    input  wire        rst_n,     // 低有效异步复位
    input  wire        Load,      // 同步装载 IN
    input  wire [31:0] IN,        // 待计数数据
    output reg  [5:0]  count_out  // 结果寄存输出（0~32）
);
    // 32位移位寄存器（唯一）
    reg [31:0] shift_reg;
    // 6位计数器（唯一，用于累加1的个数）
    reg [5:0]  cnt;

    wire is_last_bit = (shift_reg == 32'd1); // 本拍处理“最后一个且为1”的情况
    wire is_empty    = (shift_reg == 32'd0); // 移位寄存器已空

    // 异步清零与主时序
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            shift_reg <= 32'd0;
            cnt       <= 6'd0;
            count_out <= 6'd0;
        end else if (Load) begin
            shift_reg <= IN;      // 装入32位输入
            cnt       <= 6'd0;    // 新一轮计数清零
            // count_out 在本轮结束前保持上一结果
        end else begin
            cnt       <= cnt + shift_reg[0];
            shift_reg <= {1'b0, shift_reg[31:1]};

            if (is_last_bit) begin
                count_out <= cnt + 6'd1; 
            end else if (is_empty) begin
                count_out <= cnt;       
            end
        end
    end
endmodule
