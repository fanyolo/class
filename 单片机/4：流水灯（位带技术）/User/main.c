// 位带操作，流水灯
#include "stm32f10x.h"

uint32_t Color[8][3] ={{1,1,0},{0,1,1},{1,0,1},{0,1,0},{0,0,1},{1,0,0},{0,0,0},{1,1,1}};
uint32_t i,j;
#define GPIOB_ODR_ADDR (GPIOB_BASE+12)	
#define PB0_ADDR  (0x42000000 + (GPIOB_ODR_ADDR-0x40000000)*8*4 + 0*4)
#define PB1_ADDR  (0x42000000 + (GPIOB_ODR_ADDR-0x40000000)*8*4 + 1*4)
#define PB5_ADDR  (0x42000000 + (GPIOB_ODR_ADDR-0x40000000)*8*4 + 5*4)
#define PB0  *(volatile uint32_t *)(PB0_ADDR)
#define PB1  *(volatile uint32_t *)(PB1_ADDR)	
#define PB5  *(volatile uint32_t *)(PB5_ADDR)
	
void GPIOB_Init(void)
{
RCC->APB2ENR |= (1<<3);              //GPIOB CLOCK	
GPIOB->CRL &= ~(0x0F<<(4*0));    //GREEN  PB0  推挽输出 速度10MHz
GPIOB->CRL |= (0x01<<(4*0));	
GPIOB->CRL &= ~(0x0F<<(4*1));    //BLUE   PB1   推挽输出 速度10MHz
GPIOB->CRL |= (0x01<<(4*1));	
GPIOB->CRL &= ~(0x0F<<(4*5));     //RED    PB5   推挽输出 速度10MHz
GPIOB->CRL |= (0x01<<(4*5));		
}

int main(void)
{
     i = 0;
	GPIOB_Init();

	while(1)
	{
	      PB0 = Color[i][0];
     	  PB1 = Color[i][1];
          PB5 = Color[i][2];
	i++;
	if(i >= 8)	
	     {
	          i = 0;
	     }
       for(j=0; j<5000000;j++);	
	}	
}

