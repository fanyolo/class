module behaviour_style(A,B,C,Y,R);
  input A,B,C;
  output Y,R;
  reg Y,R;
  always@(A or B or C)
    case({A,B,C})
		3'b000 : begin 
			Y = 1'b0;
			R = 1'b0; 
		end
		3'b001 : begin 
			Y = 1'b1;
			R = 1'b0; 
		end
		3'b010 : begin 
			Y = 1'b1;
			R = 1'b0; 
		end
		3'b011 : begin 
			Y = 1'b0;
			R = 1'b1; 
		end
		3'b100 : begin 
			Y = 1'b1;
			R = 1'b0; 
		end
		3'b101 : begin 
			Y = 1'b0;
			R = 1'b1; 
		end
		3'b110 : begin 
			Y = 1'b0;
			R = 1'b1; 
		end
		3'b111 : begin 
			Y = 1'b1;
			R = 1'b1; 
		end
		default : begin 
			Y = 1'bx;
			R = 1'bx; 
		end
    endcase
endmodule
