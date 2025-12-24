module data_style(A,B,C,Y,R);
  input A,B,C;
  output Y,R;

  assign  Y = (~A&~B&C)|(~A&B&~C)|(A&~B&~C)|(A&B&C);
  assign  R = (A&B)|(B&C)|(A&C);
  
endmodule