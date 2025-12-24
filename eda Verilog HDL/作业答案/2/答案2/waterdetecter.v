module waterdetector(A,B,C,G,Y,R);
	input 	A,B,C;
	output 	G,Y,R;

    reg G,Y,R;

    // use case 
    always@(A,B,C)
    begin
        case ({A,B,C})
            3'b100 : begin
                G = 1'b1;
                Y = 1'b0;
                R = 1'b0;
            end
            3'000,3'b110 : begin
                G = 1'b0;
                Y = 1'b1;
                R = 1'b0;
            end
            3'b111 : begin
                G = 1'b0;
                Y = 1'b0;
                R = 1'b1;
            end
            default : begin
                G = 1'bx;
                Y = 1'bx;
                R = 1'bx;
            end
        endcase
    end

    // use if...else...
    /*
    always(A,B,C)
    begin
        if (!A)
            {G,Y,R} = 3'b010;
        else if (!B)
            {G,Y,R} = 3'b100;
        else if (!C)
            {G,Y,R} = 3'b010;
        else
            {G,Y,R} = 3'b001;
    end
    */

   // 
   /*
   always(*)
   begin
      if (A & !B)
         G = 1'b1;
      else
         G = 1'b0;
   end

   always@(*)
   begin
      if ((!A) || (B & !C))
         Y = 1'b1;
      else
         Y = 1'b0;
   end

   always@(*)
   begin
      if (C)
         R = 1'b1;
      else 
         R = 1'b0;
   end 
   */	
endmodule
