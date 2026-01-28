//uart_inc.h

parameter r_START=3'b001, r_CENTER=3'b010, r_WAIT=3'b011,
	  r_SAMPLE=3'b100, r_STOP=3'b101;

parameter x_IDLE=3'b000, x_START=3'b010, x_WAIT=3'b011,
          x_SHIFT=3'b100, x_STOP=3'b101;
parameter x_STARTbit=2'b00, x_STOPbit=2'b01, x_ShiftReg=2'b10;

parameter LO=1'b0, HI=1'b1, X=1'bx;

parameter WORD_LEN=8;                        
parameter XTAL_CLK=53125000;                 
parameter BAUD=2400;                         
parameter CLK_DIV=XTAL_CLK/(BAUD*16*2);      
parameter CW=10;                             

parameter SEL_XMIT_DAT       =3'b000,
          SEL_REC_DAT        =3'b000,
          SEL_BAUD_REG_LO    =3'b001,
          SEL_BAUD_REG_HI    =3'b010,
          SEL_STAT_REG       =3'b011,
          SEL_INT_STAT_REG   =3'b100,
          SEL_INT_ENA_REG    =3'b101;