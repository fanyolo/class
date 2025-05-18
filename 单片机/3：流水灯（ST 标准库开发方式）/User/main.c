#include "stm32f10x.h"

volatile uint32_t TimingDelay;

void Delay_Init(void) { 
    SysTick_Config(SystemCoreClock / 1000); // 1ms ????
}

void Delay_ms(uint32_t ms) {
    TimingDelay = ms;
    while (TimingDelay != 0);
}

int main(void)
{
uint32_t i;

// 定义一个 GPIO_InitTypeDef 类型的结构体
GPIO_InitTypeDef GPIO_InitStructure;
	
// 开启 GPIO 端口时钟
// RCC->APB2ENR |= (1<<3);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);


// GPIO 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB, &GPIO_InitStructure);	
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1);	
	
Delay_Init();	
	
while (1)
{
// 使引脚输出低电平, 点亮 LED
GPIO_ResetBits(GPIOB,GPIO_Pin_5);

/* 延时一段时间 */
Delay_ms(1000);

/* 使引脚输出高电平，关闭 LED1*/
GPIO_SetBits(GPIOB,GPIO_Pin_5);

	
	
GPIO_ResetBits(GPIOB,GPIO_Pin_0);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
GPIO_ResetBits(GPIOB,GPIO_Pin_1);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_1);

GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0);


GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0);


GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_1);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_1);


GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1);
Delay_ms(1000);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1);

Delay_ms(1000);
	
}
}





