#include <main.h>

#define ADCCON				0xC0053000
#define ADCDAT 				0xC0053004
#define ADCINTENB 			0xC0053008
#define ADCINTCLR 			0xC005300C
#define PRESCALERCON 		0xC0053010

#define rADCCON				(*(volatile unsigned int *)ADCCON)
#define rADCDAT				(*(volatile unsigned int *)ADCDAT)
#define rADCINTENB			(*(volatile unsigned int *)ADCINTENB)
#define rADCINTCLR			(*(volatile unsigned int *)ADCINTCLR)
#define rPRESCALERCON		(*(volatile unsigned int *)PRESCALERCON)

#define RESET_ID_ADC                60

#define APEN_BITP       (15)
#define PRES_BITP       (0)

/* ADCCON */
#define DATA_SEL_VAL    (0)     /* 0:5clk, 1:4clk, 2:3clk, 3:2clk, 4:1clk, 5:0clk */
#define CLK_CNT_VAL     (6)     /* 28nm ADC */

#define DATA_SEL_BITP   (10)    /* 13:10 */
#define CLK_CNT_BITP    (6)     /* 9:6 */
#define ASEL_BITP       (3)
#define ADCON_STBY      (2)
#define ADEN_BITP       (0)

/* ADCINTENB */
#define AIEN_BITP       (0)

/* ADCINTCLR */
#define AICL_BITP       (0)


struct NX_RSTCON_RegisterSet
{
	 volatile unsigned int    REGRST[(69+31)>>5];
};
static struct NX_RSTCON_RegisterSet *__g_pRegister;
typedef enum
{
    RSTCON_ASSERT   = 0UL,
    RSTCON_NEGATE   = 1UL
}RSTCON;
void NX_RSTCON_SetRST(unsigned int RSTIndex, RSTCON STATUS)
{
	unsigned int regvalue;

    regvalue    = *(volatile unsigned int  *)(&__g_pRegister->REGRST[RSTIndex >> 5]);

    regvalue    &= ~(1UL << (RSTIndex & 0x1f));
    regvalue    |= (STATUS & 0x01) << (RSTIndex & 0x1f);

    *(volatile unsigned int  *)(&__g_pRegister->REGRST[RSTIndex >> 5]) = (unsigned int  )(regvalue);
}

char string[1024] = "";
char* itoa(unsigned int value)
{

	int i = 0, j = 0;
	int len = 0;
	do
	{
		if(value == 0)
		{
			string[i++] = 0;
		}
		else
		{
			char c = value % 10 + '0';
			string[i++] = c;
			value /= 10;
		}
	}
		while(value != 0);
	string[i] = '\0';
	len = strlen(string);
	for(j=0; j<len/2; j++)
	{
		char temp = string[j];
		string[j] = string[len-j-1];
		string[len-j-1] = temp;
	}
	return string;

}

static void mydelay_ms(int time)
{
	int i, j;
	while(time--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

void adc_init(char ch)
{
	unsigned int adccon = 0;
	unsigned int reg = 0;

	s5p6818_serial_write_string(0, "\n adc init!!\n\r");

	unsigned int RSTIndex = RESET_ID_ADC;
	__g_pRegister = (struct NX_RSTCON_RegisterSet *)((void *)0xC0012000);
	NX_RSTCON_SetRST(RSTIndex, RSTCON_ASSERT);
	NX_RSTCON_SetRST(RSTIndex, RSTCON_NEGATE);

	adccon = ((DATA_SEL_VAL & 0xf) << DATA_SEL_BITP) |
	         ((CLK_CNT_VAL & 0xf) << CLK_CNT_BITP) |
	         (0 << ADCON_STBY);
	rADCCON = adccon;

	reg = rPRESCALERCON;
	reg &= ~(0x3FF << PRES_BITP);
	reg |= 0xFF << PRES_BITP;
	reg |= 0x1 << APEN_BITP;
	rPRESCALERCON = reg;

	rADCINTCLR = (1 << AICL_BITP);
	rADCINTENB = (1 << AIEN_BITP);

	reg = rADCCON;
	reg &= ~(0x7 << ASEL_BITP);
	reg |= (ch << ASEL_BITP);
	rADCCON = reg;
}


int tester_adc(int argc, char * argv[])
{
	unsigned int reg = 0;
	unsigned int data = 0;

	unsigned int data1= 0;
	unsigned int data10 = 0;
	unsigned int data100 = 0;

	s5p6818_serial_write_string(0, "\n adc test!!\n\r");

	while (1) {
		reg = rADCCON;
		reg |= (1 << ADEN_BITP);
		rADCCON = reg;

		data = (rADCDAT & 0xfff);


//		s5p6818_serial_write_string(0, "data= ");
//		s5p6818_serial_write_string(0, itoa(data));
//		s5p6818_serial_write_string(0, "\n");


				data100 = data / 4;
				data10 = data100 / 10;
				data1 = data100 % 10;

//				s5p6818_serial_write_string(0, "F2");
//				s5p6818_serial_write_string(0, itoa(data));

				s5p6818_serial_write_string(0, "温度为");
				s5p6818_serial_write_string(0, itoa(data10));
				s5p6818_serial_write_string(0, ".");
				s5p6818_serial_write_string(0, itoa(data1));
				s5p6818_serial_write_string(0, "℃");
				s5p6818_serial_write_string(0, "\n");

				s5p6818_serial_write_string(0, "压强为");
				s5p6818_serial_write_string(0, itoa(data100));
				s5p6818_serial_write_string(0, "Pa");
				s5p6818_serial_write_string(0, "\n");

		mydelay_ms(2000);
	}

	return 0;
}

