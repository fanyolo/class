//  MCO���ʵ��

#include "mco.h"

int main(void)
{
//	MCO_Init(RCC_MCO_PLLCLK_Div2);
             MCO_Init(RCC_MCO_SYSCLK);
//             MCO_Init(RCC_MCO_HSI);
//             MCO_Init(RCC_MCO_HSE);
//             MCO_Init(RCC_MCO_NoClock);

	while(1);
}
//主频为72MHZ




//修改主频为36MHZ

//void SystemClock_36MHz(void) {
//    // 使能HSE（外部高速时钟）
//    RCC_HSEConfig(RCC_HSE_ON);
//    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

//    // 配置PLL：HSE作为PLL输入，6倍频
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
//    RCC_PLLCmd(ENABLE);
//    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

//    // 设置系统时钟分频为2（72MHz / 2 = 36MHz）
//    RCC_HCLKConfig(RCC_SYSCLK_Div2);

//    // 切换系统时钟源为PLL
//    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//    while (RCC_GetSYSCLKSource() != 0x08);
//}

//void MCO_Init(void) {
//    // 使能GPIOA时钟
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//    // 配置GPIOA.8为复用推挽输出
//    GPIO_InitTypeDef GPIO_InitStruct;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//    // 设置MCO时钟源为SYSCLK
//    RCC_MCOConfig(RCC_MCO_SYSCLK);
//}

//int main(void) {
//    // 配置系统时钟为36MHz
//    SystemClock_36MHz();

//    // 初始化MCO
//    MCO_Init();

//    while (1) {
//        // 主循环
//    }
//}