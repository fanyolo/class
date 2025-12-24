// 门级描述 
module work_1 (A, B, C, D, E, F, O);
  input  A, B, C, D, E, F;  
  output O;                 

  wire t1, t2, t3, t4, t5;

  and  G0 (t1, A, B);        // t1 = A & B
  or   G1 (t2, C, D);        // t2 = C | D
  nor  G2 (t3, E, F);        // t3 = ~(E | F)
  xor  G3 (t4, t1, t2);      // t4 = t1 ^ t2
  xnor G4 (t5, t2, t3);      // t5 = ~(t2 ^ t3)
  nand G5 (O,  t4, t5);      // O  = ~(t4 & t5)

endmodule

//数据流描述 
module work_2 (A, B, C, D, E, F, O);
  input  A, B, C, D, E, F;
  output O;

  // O = NAND( XOR(A&B, C|D), XNOR(C|D, ~(E|F)) )
  assign O = ~ ( ((A & B) ^ (C | D)) & ((C | D) ~^ (~(E | F))) );
endmodule



// testbench
module tb_work;
  reg A, B, C, D, E, F;   
  wire o_gate, o_data;    


  work_1 U_GATE ( .A(A), .B(B), .C(C), .D(D), .E(E), .F(F), .O(o_gate) );
  work_2 U_DATA ( .A(A), .B(B), .C(C), .D(D), .E(E), .F(F), .O(o_data) );

  initial begin
    $timeformat(-9, 0, " ns", 1);
    $monitor("%t  A=%b B=%b C=%b D=%b E=%b F=%b  | gate=%b data=%b",
             $time, A,B,C,D,E,F, o_gate, o_data);

    A=0; B=0; C=0; D=0; E=0; F=0; #10;
    A=1; B=0; C=1; D=0; E=1; F=0; #10;
    A=0; B=1; C=1; D=1; E=0; F=1; #10;
    A=1; B=1; C=0; D=1; E=1; F=1; #10;
    A=0; B=0; C=1; D=0; E=0; F=1; #10;

    $finish;
  end
endmodule




