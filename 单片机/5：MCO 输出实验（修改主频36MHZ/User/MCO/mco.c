#include "mco.h"
//使能GPIOA的时钟，初始化MCO引脚工作模式，配置MCO时钟源		    
void MCO_Init(uint8_t RCC_MCO)
{
	//定义GPIO初始化结构参数变量
	GPIO_InitTypeDef  GPIO_InitStructure;			
	//使能GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//设置PA.8为复用输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//IO口速度为50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//根据设定参数初始化GPIOA.8
	GPIO_Init(GPIOA, &GPIO_InitStructure); 	
	//调用RCC库函数实现MCO输出时钟源选择,实际是对对RCC_CFGR寄存器的24-26位配置
	RCC_MCOConfig(RCC_MCO); 
}

