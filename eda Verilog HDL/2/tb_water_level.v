// tb_water_level.v
`timescale 1ns/1ps
module tb_water_level;
    reg a, b, c;      // 传感器输入
    wire G, Y, R;     // 指示灯输出

   
    water_level dut(
        .a(a), .b(b), .c(c),
        .G(G), .Y(Y), .R(R)
    );

    initial begin
        {a,b,c} = 3'bxxx; #100;  // 起始未知，便于波形分界
        {a,b,c} = 3'b111; #500; // C以下（危险）→ 预期 R=1
        {a,b,c} = 3'b110; #500; // B~C（异常） → 预期 Y=1
        {a,b,c} = 3'b100; #500; // A~B（正常） → 预期 G=1
        {a,b,c} = 3'b000; #500; // A以上（过高）→ 预期 Y=1
        #200 $finish;
    end
endmodule

