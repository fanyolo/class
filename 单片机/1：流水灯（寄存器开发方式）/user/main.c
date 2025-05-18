//寄存器

#include "stm32f10x.h" 

int main(void)
{
    unsigned int i, j;
    unsigned int Color[8] = {0x20, 0x01, 0x02, 0x21, 0x03, 0x22, 0x23, 0x00};


    RCC_APB2ENR |= (1 << 3);

    GPIOB_CRL &= ~(0x0F << (4 * 0));  
    GPIOB_CRL |= (0x01 << (4 * 0));

    GPIOB_CRL &= ~(0x0F << (4 * 1)); 
    GPIOB_CRL |= (0x01 << (4 * 1));

    GPIOB_CRL &= ~(0x0F << (4 * 5)); 
    GPIOB_CRL |= (0x01 << (4 * 5));

    while (1)
    {
        for (j = 0; j < 8; j++)
        {
            GPIOB_ODR = ~(Color[j]); 
            for (i = 0; i < 2000000; i++);  
        }
    }
}



// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{	
}



