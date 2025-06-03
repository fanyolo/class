#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "misc.h" 

#include "./usart/bsp_usart.h"	     //串口
#include "./led/bsp_led.h"           
#include "./lcd/bsp_ili9341_lcd.h"
#include "./flash/bsp_spi_flash.h" 
#include "lcdtouch.h"                  //lcd触摸屏
#include "./lcd/bsp_xpt2046_lcd.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//全局变量的定义
//上下课铃的类型
typedef enum {
    BELL_TYPE_START_CLASS,
    BELL_TYPE_END_CLASS
} BellType;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    BellType type;
    uint8_t triggered_today;
} BellScheduleEntry;

//响铃的时刻表
BellScheduleEntry school_schedule[] = {{7,  50, BELL_TYPE_START_CLASS,   0},
    {8,  0,  BELL_TYPE_START_CLASS, 0}, {8,  45, BELL_TYPE_END_CLASS,   0},
    {8,  55, BELL_TYPE_START_CLASS, 0}, {9,  40, BELL_TYPE_END_CLASS,   0},
    {10, 0,  BELL_TYPE_START_CLASS, 0}, {10, 45, BELL_TYPE_END_CLASS,   0},
    {10, 55, BELL_TYPE_START_CLASS, 0}, {11, 40, BELL_TYPE_END_CLASS,   0},
    {13,50,  BELL_TYPE_START_CLASS, 0},
    {14, 0,  BELL_TYPE_START_CLASS, 0}, {14, 45, BELL_TYPE_END_CLASS,   0},
    {14, 55, BELL_TYPE_START_CLASS, 0}, {15, 40, BELL_TYPE_END_CLASS,   0},
    {16, 0,  BELL_TYPE_START_CLASS, 0}, {16, 45, BELL_TYPE_END_CLASS,   0},
    {16, 55, BELL_TYPE_START_CLASS, 0}, {17, 40, BELL_TYPE_END_CLASS,   0},
    {19, 0,  BELL_TYPE_START_CLASS, 0}, {19, 45, BELL_TYPE_END_CLASS,   0},
    {19, 55, BELL_TYPE_START_CLASS, 0}, {20, 40, BELL_TYPE_END_CLASS,   0}
};
const uint8_t schedule_size = sizeof(school_schedule) / sizeof(BellScheduleEntry);

//时间变量，lcd单位显示
uint8_t h, m, s;
uint8_t lcd_flag;

//串口接收
#define RX_BUFFER_SIZE 30        //接收缓冲区的大小
uint8_t rx_buffer[RX_BUFFER_SIZE];   
uint8_t rx_data; 
uint8_t rx_index = 0;   //缓冲区索引
uint8_t rx_flag = 0;    //接收完成标志

//蜂鸣器
uint8_t is_beeping = 0;
volatile uint32_t system_timer_ms = 0;
uint32_t beep_start_time_ms = 0;    //开始时间
uint32_t beep_duration_ms = 0;      //持续时间
volatile uint8_t time_updated_flag = 0;

//函数声明
void SystemClock_Config_SPL(void);
void GPIO_Keys_Init_SPL(void);
void TIM2_Init_SPL(void);
void BEEP_GPIO_Config_SPL(void);
void Error_Handler_SPL(void);
void Delay_Ms(uint32_t nTime);
uint32_t Get_SystemTicks(void);
void SysTick_Init(void);

static void LCD_Test(void); 
void key_scan(void);
void StartBellRing(BellType type);
void StopBellRing(void);
void HandleBellState(void);      //响铃计时控制
void CheckAndTriggerBell(void);  //判断时候响铃


extern void USART_Config(void); 
extern void LED_GPIO_Config(void);
extern void ILI9341_Init(void);
extern void XPT2046_Init(void); 
extern void Calibrate_or_Get_TouchParaWithFlash(uint8_t mode, uint8_t use_flash_para); 
extern void Palette_Init(uint8_t scan_mode); 
extern void XPT2046_TouchEvenHandler(void); 


//滴答定时器
void SysTick_Init(void) {
    if (SysTick_Config(SystemCoreClock / 1000)) { // 1ms interrupt
        Error_Handler_SPL();
    }
}
//延时函数
void Delay_Ms(uint32_t nTime) {
    uint32_t current_ticks = system_timer_ms;
    while ((system_timer_ms - current_ticks) < nTime);
}


uint32_t Get_SystemTicks(void) {
    return system_timer_ms;  // ??????,?????
}


// 系统时钟初始化
void SystemClock_Config_SPL(void) {
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS) {
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08);

        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK2Config(RCC_HCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        FLASH_SetLatency(FLASH_Latency_2);
    } else {
        Error_Handler_SPL();
    }
}

// 按键引脚初始化
void GPIO_Keys_Init_SPL(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13; 
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;  
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// 蜂鸣器引脚初始化
void BEEP_GPIO_Config_SPL(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_8); 
}

// 定时器2   1s中断 更新时间
void TIM2_Init_SPL(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler = 7199; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 9999;    
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

// 蜂鸣器控制
void Beeper_On(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void Beeper_Off(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void StartBellRing(BellType type) {
    char bellMsg[30];
    if (!is_beeping) {
        Beeper_On();
        is_beeping = 1;
        beep_start_time_ms = Get_SystemTicks();
        if (type == BELL_TYPE_START_CLASS) {
            beep_duration_ms = 30 * 1000;
            sprintf(bellMsg, "Bell: START CLASS ");
        } else {
            beep_duration_ms = 20 * 1000;
            sprintf(bellMsg, "Bell: END CLASS   ");
        }
        ILI9341_DispStringLine_EN_CH(LINE(14), bellMsg); 
    }
}

void StopBellRing(void) {
    Beeper_Off();
    is_beeping = 0;
    beep_duration_ms = 0;
    ILI9341_DispStringLine_EN_CH(LINE(14), (char*)"                  ");  //清除响铃标志
}

void HandleBellState(void) {
    if (is_beeping) {
        if ((Get_SystemTicks() - beep_start_time_ms) >= beep_duration_ms) {
            StopBellRing();
        }
    }
}

void CheckAndTriggerBell(void) {
    static uint8_t midnight_reset_done = 0;
    static uint8_t last_minute_checked = 61; 
    int i; 
    if (is_beeping) return;

    if (h == 0 && m == 0 && s < 2) { 
        if (!midnight_reset_done) {
            for (i = 0; i < schedule_size; i++) {
                school_schedule[i].triggered_today = 0;
            }
            midnight_reset_done = 1;
        }
    } else {
        midnight_reset_done = 0;
    }

    if (s == 0 && m != last_minute_checked) { 
        for (i = 0; i < schedule_size; i++) {
            if (school_schedule[i].hour == h &&
                school_schedule[i].minute == m &&
                !school_schedule[i].triggered_today) {
                school_schedule[i].triggered_today = 1;
                StartBellRing(school_schedule[i].type);
                break; 
            }
        }
        last_minute_checked = m; 
    }
    if (s != 0) { 
        last_minute_checked = 61; 
    }
}

// 按键扫描
void key_scan(void) {
    static uint8_t k1_last_state = 1; 
    static uint8_t k2_last_state = 1; 
    uint8_t k1_current_state, k2_current_state;

    k1_current_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
    k2_current_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

    if (k1_last_state == 1 && k1_current_state == 0) { 
        Delay_Ms(20); 
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0) { 
            if (lcd_flag == 0) { s++; if (s >= 60) s = 0; }      
            else if (lcd_flag == 1) { m++; if (m >= 60) m = 0; } 
            else if (lcd_flag == 2) { h++; if (h >= 24) h = 0; } 
            time_updated_flag = 1; 
        }
    }
    k1_last_state = k1_current_state;

    if (k2_last_state == 1 && k2_current_state == 0) { 
        Delay_Ms(20); 
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) { 
            lcd_flag++;
            if (lcd_flag >= 3) lcd_flag = 0; 
            time_updated_flag = 1; 
        }
    }
    k2_last_state = k2_current_state;
}

//lcd显示
static void LCD_Test(void) {
    char dispBuff[100]; 

    ILI9341_DispStringLine_EN_CH(LINE(2), (char*)"任务： 自动打铃器  8207230322");
    sprintf(dispBuff,"  时间:%02d:%02d:%02d ", h, m, s);
    ILI9341_DispStringLine_EN_CH(LINE(0), dispBuff);

    if(lcd_flag == 0) {
        sprintf(dispBuff,"现在按键2调整的单位是秒 "); 
    } else if(lcd_flag == 1) {
        sprintf(dispBuff,"现在按键2调整的单位是分 "); 
    } else { 
        sprintf(dispBuff,"现在按键2调整的单位是时 "); 
    }
    ILI9341_DispStringLine_EN_CH(LINE(4), dispBuff);
    
    ILI9341_DispStringLine_EN_CH(LINE(5), (char*)"按键k1修改调整单位 ");
    ILI9341_DispStringLine_EN_CH(LINE(6), (char*)"按键k2调整具体时间(按下+1) ");
    ILI9341_DispStringLine_EN_CH(LINE(7), (char*)"上课响铃30秒，下课响铃20秒 ");

    ILI9341_DispStringLine_EN_CH(LINE(8), (char*)"上课时间具体如下（早上和下午有预备铃）");
    ILI9341_DispStringLine_EN_CH(LINE(9), (char*)" 8:00--8:45    8:55--9:40");
    ILI9341_DispStringLine_EN_CH(LINE(10), (char*)"10:00-10:45  10:55-11:40");
    ILI9341_DispStringLine_EN_CH(LINE(11), (char*)"14:00-14:45  14:55-15:40");
    ILI9341_DispStringLine_EN_CH(LINE(12), (char*)"16:00-16:45  16:55-17:40");
    ILI9341_DispStringLine_EN_CH(LINE(13), (char*)"19:00-19:45  19:55-20:40");
}


void Error_Handler_SPL(void) {
    volatile int i; 
    NVIC_DisableIRQ(SysTick_IRQn);
    NVIC_DisableIRQ(TIM2_IRQn);

    while (1) {
        for(i=0; i<500000; i++); 
    }
}

// 主函数
int main(void) {
    int temp_h, temp_m, temp_s_uart;
    

	
    SystemClock_Config_SPL();
    SysTick_Init();

    USART_Config();      
    LED_GPIO_Config();
    GPIO_Keys_Init_SPL();  
    ILI9341_Init();
    XPT2046_Init();      

    Calibrate_or_Get_TouchParaWithFlash(3, 0); 
                                         
    BEEP_GPIO_Config_SPL();
    TIM2_Init_SPL();

    ILI9341_GramScan(0); 
    Palette_Init(0); 
    
	
	LCD_SetBackColor(RGB(255,255,255));
    ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	
     



    h = 6; m = 0; s = 0; 
    lcd_flag = 0;
    time_updated_flag = 1; 

    while (1) {
        if (time_updated_flag) {//时间更新  刷新显示
            LCD_Test(); 
           
            time_updated_flag = 0;
        }
        HandleBellState(); 
        CheckAndTriggerBell(); 
        key_scan();        

        XPT2046_TouchEvenHandler(); 

        if (rx_flag) { //中断标志位
			//判断主机发送的信息
            if (strcmp((char*)rx_buffer, "hour") == 0) {
                printf("hour->%02d\r\n", h);
            } else if (strcmp((char*)rx_buffer, "minute") == 0) {
                printf("minute->%02d\r\n", m);
            } else if (strcmp((char*)rx_buffer, "second") == 0) {
                printf("second->%02d\r\n", s);
            } else if (strcmp((char*)rx_buffer, "ALL") == 0) {
                printf("ALL->%02d:%02d:%02d\r\n", h, m, s);
            } else if (strlen((char*)rx_buffer) == 8 && rx_buffer[2] == ':' && rx_buffer[5] == ':') {
                if (sscanf((char*)rx_buffer, "%2d:%2d:%2d", &temp_h, &temp_m, &temp_s_uart) == 3) {
                    if (temp_h >= 0 && temp_h < 24 && temp_m >= 0 && temp_m < 60 && temp_s_uart >= 0 && temp_s_uart < 60) {
                        TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);  //取临时数据，避免数据冲突
                        h = (uint8_t)temp_h;
                        m = (uint8_t)temp_m;
                        s = (uint8_t)temp_s_uart;
                        TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
                        printf("Time Updated Successfully to %02d:%02d:%02d\r\n", h,m,s);//串口显示更新时间成功
                        time_updated_flag = 1;
                    } else {
                        printf("Invalid Time Value in Command\r\n");   
                    }
                } else {
                    printf("Invalid Time Format in Command\r\n");   
                }
            } else {
                printf("Invalid Command: \"%s\"\r\n", (char*)rx_buffer);  //串口错误发送提示
            }
            memset(rx_buffer, 0, RX_BUFFER_SIZE);  //清空接收
            rx_index = 0;
            rx_flag = 0;    //清除标志
        }
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    printf("Wrong parameters value: file %s on line %lu\r\n", (char*)file, line);
    Error_Handler_SPL();
}
#endif


