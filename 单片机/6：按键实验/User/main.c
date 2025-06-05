#include "stm32f10x.h"

void GPIOA_Initialization(void);			
void GPIOB_Initialization(void);
void GPIOC_Initialization(void);
void NVIC_Initialization(void);	
void EXTI_Initialization(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

int main(void)
{         
    GPIOA_Initialization();
    GPIOB_Initialization();
    GPIOC_Initialization();
    NVIC_Initialization();
    EXTI_Initialization();
    while(1);
}

void GPIOA_Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;			
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIOC_Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;			
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIOB_Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5;	  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	   GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_5);//初始状态，两个灯都灭
}

void NVIC_Initialization(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

    // PA0 EXTI0 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    // PC13 EXTI13 
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Initialization(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    // PA0 EXTI0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;  		
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		  
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;	 				 
    EXTI_Init(&EXTI_InitStructure);	

    // PC13 EXTI13
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13); 
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;  		
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		  
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;	 				 
    EXTI_Init(&EXTI_InitStructure);	
}

void EXTI0_IRQHandler(void)
{  
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
    {
        // PB0 
        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0))
            GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        else
            GPIO_SetBits(GPIOB, GPIO_Pin_0);

        EXTI_ClearITPendingBit(EXTI_Line0);   
    }    
}

void EXTI15_10_IRQHandler(void)
{  
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) 
    {
        // PB5
        if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5))
            GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        else
            GPIO_SetBits(GPIOB, GPIO_Pin_5);

        EXTI_ClearITPendingBit(EXTI_Line13);   
    }    
}
