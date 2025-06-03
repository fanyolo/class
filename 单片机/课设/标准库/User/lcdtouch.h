#ifndef _LCDTOUCH_H_ 
#define _LCDTOUCH_H_

#include "stm32f10x.h"
#include "./lcd/bsp_ili9341_lcd.h" 


#define BUTTON_NUM 2 

#define PARAM_SELECT_UNIT      1 
#define PARAM_INCREMENT_VALUE  2 


#define T_BTN_HEIGHT     40   
#define T_BTN_WIDTH      110  
#define T_BTN_SPACING    20   
#define T_BTN_MARGIN_Y   20   
#define T_BTN_START_Y    (LCD_Y_LENGTH - T_BTN_HEIGHT - T_BTN_MARGIN_Y)

// ????X?????,?????????
#define T_BTN_TOTAL_WIDTH (2 * T_BTN_WIDTH + T_BTN_SPACING) 
#define T_BTN_AREA_START_X ((LCD_X_LENGTH - T_BTN_TOTAL_WIDTH) / 2) 

#define T_BTN_UNIT_SELECT_X     (T_BTN_AREA_START_X)                          
#define T_BTN_VALUE_INCREMENT_X (T_BTN_AREA_START_X + T_BTN_WIDTH + T_BTN_SPACING) 



#if LCD_RGB_888 

#define RGB(R,G,B)	( (R<< 16) | (G << 8) | (B))	
#else
/* RGB565???? */
#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	
#endif


#define CL_WHITE         RGB(255,255,255) /* ?? */
#define CL_BLACK         RGB(  0,  0,  0) /* ?? (????) */
#define CL_BLUE4         RGB(  0, 64,128) /* ??? (???????,?????) */

// ??????? (???????? CL_BUTTON_GREY, CL_BTN_FACE ???)
#define CL_BTN_BACKGROUND_NORMAL   RGB(220, 220, 220) // ????????? (???)
#define CL_BTN_BACKGROUND_PRESSED  CL_WHITE           // ????????? (??,????)
// ??,?????????? CL_BUTTON_GREY:
// #define CL_BTN_BACKGROUND_NORMAL   CL_BUTTON_GREY



typedef struct
{
    uint16_t start_x;     // ???x????
    uint16_t start_y;     // ???y????
    uint16_t end_x;       // ???x????
    uint16_t end_y;       // ???y????
    uint32_t para;        // ??????,?????????? (PARAM_SELECT_UNIT ? PARAM_INCREMENT_VALUE)
    uint8_t touch_flag;   // ??????? (0:???, 1:???)

    void (*draw_btn)(void * btn);     // ???????????
    void (*btn_command)(void * btn);  // ?????????????

} Touch_Button;


void Palette_Init(uint8_t LCD_Mode); 
void Touch_Button_Down(uint16_t x, uint16_t y);
void Touch_Button_Up(uint16_t x, uint16_t y);



#endif 