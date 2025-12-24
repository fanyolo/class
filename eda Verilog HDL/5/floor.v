

module floor (
    input  wire       clk,
    input  wire       rstn,          // 低有效复位
    input  wire       floor1,        // 目标层输入(高有效)
    input  wire       floor2,
    input  wire       floor3,
    output reg  [2:0] led          
);

    reg  [2:0] req;                  // {req3,req2,req1}
    wire [2:0] set_req = {floor3, floor2, floor1};
    reg  [2:0] clr_req;             

    always @(posedge clk or negedge rstn) begin
        if (!rstn)
            req <= 3'b000;
        else
            req <= (req | set_req) & ~clr_req;   
    end


    parameter S1 = 2'd0, S2 = 2'd1, S3 = 2'd2;
    reg [1:0] state, next_state;

    
    reg dir, next_dir;

    always @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            state <= S1;
            dir   <= 1'b1;
        end else begin
            state <= next_state;
            dir   <= next_dir;
        end
    end

  
    always @* begin
        next_state = state;
        next_dir   = dir;

        case (state)
            S1: begin
                if (req[1] | req[2]) begin
                    next_state = S2;
                    next_dir   = 1'b1;            // 上行
                end
            end

            S2: begin
                if (dir) begin                    // 上行优先
                    if (req[2]) begin
                        next_state = S3; next_dir = 1'b1;
                    end else if (req[0]) begin
                        next_state = S1; next_dir = 1'b0;
                    end
                end else begin                     // 下行优先
                    if (req[0]) begin
                        next_state = S1; next_dir = 1'b0;
                    end else if (req[2]) begin
                        next_state = S3; next_dir = 1'b1;
                    end
                end
            end

            S3: begin
                if (req[0] | req[1]) begin
                    next_state = S2;
                    next_dir   = 1'b0;            // 下行
                end
            end

            default: begin
                next_state = S1; next_dir = 1'b1;
            end
        endcase
    end

   
    always @* begin
        led     = 3'b000;
        clr_req = 3'b000;

        case (state)
            S1: begin
                led = 3'b001;
                if (req[0]) clr_req = 3'b001;
            end
            S2: begin
                led = 3'b010;
                if (req[1]) clr_req = 3'b010;
            end
            S3: begin
                led = 3'b100;
                if (req[2]) clr_req = 3'b100;
            end
            default: led = 3'b001;
        endcase
    end

endmodule
