#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>      
// 使用编写的GPIO固件库点亮 LED
int main(void)
{

uint32_t i;

// 定义一个 GPIO_InitTypeDef 类型的结构体
GPIO_InitTypeDef GPIO_InitStructure;
	
// 开启 GPIO 端口时钟
RCC_APB2ENR |= (1<<3);

// GPIO 
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB, &GPIO_InitStructure);	

while (1)
{
// 使引脚输出低电平, 点亮 LED
GPIO_ResetBits(GPIOB,GPIO_Pin_5);

/* 延时一段时间 */
for(i=0; i<2000000;i++);

/* 使引脚输出高电平，关闭 LED1*/
GPIO_SetBits(GPIOB,GPIO_Pin_5);

	
	
GPIO_ResetBits(GPIOB,GPIO_Pin_0);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
GPIO_ResetBits(GPIOB,GPIO_Pin_1);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_1);

GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0);


GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_0);


GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_1);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_1);


GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1);
for(i=0; i<2000000;i++);
GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1);

for(i=0; i<2000000;i++);
	
}
}

void SystemInit(void)
{
	// 函数体为空，目的是为了骗过编译器不报错
}




