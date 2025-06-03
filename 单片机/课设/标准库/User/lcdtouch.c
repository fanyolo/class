//触摸屏程序

#include "lcdtouch.h" 
#include "./lcd/bsp_ili9341_lcd.h" 


#include <stddef.h> 
#include <stdio.h>  

//外部变量声明 主函数
extern uint8_t h;                   // main.c
extern uint8_t m;                   // main.c
extern uint8_t s;                   // main.c
extern uint8_t lcd_flag;            // 当前调整的单位
extern volatile uint8_t time_updated_flag; 


Touch_Button button[BUTTON_NUM]; //按钮数组
static void Touch_Button_Init(void);

//内部函数
static void Draw_SelectUnit_Button(void *btn);
static void Draw_IncrementVal_Button(void *btn);
static void Command_Select_Adjust_Unit(void *btn);
static void Command_Increment_Selected_Unit(void *btn);

//按钮尺寸
#define BTN_HEIGHT 40
#define BTN_WIDTH 100 
#define BTN_SPACING 20
#define BTN_START_Y (LCD_Y_LENGTH - BTN_HEIGHT - 20) 
#define BTN_COL1_X  ((LCD_X_LENGTH - (2 * BTN_WIDTH + BTN_SPACING)) / 2)
#define BTN_COL2_X  (BTN_COL1_X + BTN_WIDTH + BTN_SPACING)


//初始化
void Palette_Init(uint8_t LCD_Mode) {
    uint8_t i;
    (void)LCD_Mode; 

    Touch_Button_Init(); 

//画按钮
    for (i = 0; i < BUTTON_NUM; i++) {
        if (button[i].draw_btn != NULL) {
            button[i].draw_btn(&button[i]);
        }
    }
   
}


//按键初始化
void Touch_Button_Init(void) {
    //按键0
    button[0].start_x = BTN_COL1_X;
    button[0].start_y = BTN_START_Y;
    button[0].end_x   = BTN_COL1_X + BTN_WIDTH;
    button[0].end_y   = BTN_START_Y + BTN_HEIGHT;
    button[0].touch_flag = 0;
    button[0].draw_btn = Draw_SelectUnit_Button;
    button[0].btn_command = Command_Select_Adjust_Unit;
    button[0].para = PARAM_SELECT_UNIT; // ?? palette.h

    //按键1
    button[1].start_x = BTN_COL2_X;
    button[1].start_y = BTN_START_Y;
    button[1].end_x   = BTN_COL2_X + BTN_WIDTH;
    button[1].end_y   = BTN_START_Y + BTN_HEIGHT;
    button[1].touch_flag = 0;
    button[1].draw_btn = Draw_IncrementVal_Button;
    button[1].btn_command = Command_Increment_Selected_Unit;
    button[1].para = PARAM_INCREMENT_VALUE; // ?? palette.h
}


//触摸按下处理
void Touch_Button_Down(uint16_t x, uint16_t y) {
    uint8_t i;
    for (i = 0; i < BUTTON_NUM; i++) {
        if (x <= button[i].end_x && x >= button[i].start_x &&
            y <= button[i].end_y && y >= button[i].start_y) {
            if (button[i].touch_flag == 0) {
                button[i].touch_flag = 1; //标志已经按下
                if (button[i].draw_btn != NULL) {
                    button[i].draw_btn(&button[i]);  //显示按下
                }
            }
        } else { //按下超出范围
            if (button[i].touch_flag == 1) {
                button[i].touch_flag = 0;
                 if (button[i].draw_btn != NULL) {
                    button[i].draw_btn(&button[i]); 
                }
            }
        }
    }
}


//触摸抬起
void Touch_Button_Up(uint16_t x, uint16_t y) {
    uint8_t i;
    for (i = 0; i < BUTTON_NUM; i++) {
       
        if (button[i].touch_flag == 1 &&
            x <= button[i].end_x && x >= button[i].start_x &&
            y <= button[i].end_y && y >= button[i].start_y) {
            button[i].touch_flag = 0; 
            if (button[i].draw_btn != NULL) {
                button[i].draw_btn(&button[i]); 
            }
            if (button[i].btn_command != NULL) {
                button[i].btn_command(&button[i]); 
            }
        }
       
        else if (button[i].touch_flag == 1) {
             button[i].touch_flag = 0;
             if (button[i].draw_btn != NULL) {
                button[i].draw_btn(&button[i]);
            }
        }
    }
}

//切换单位按钮
static void Draw_SelectUnit_Button(void *btn) {
    Touch_Button *ptr = (Touch_Button *)btn;
    char caption[20]; //文字
    uint16_t text_width_pixels;
    uint16_t btn_bg_color, text_color = CL_BLACK; 

    sprintf(caption, "切换单位 ");
   
    text_width_pixels = 16*2 + 8*1 + 16*1; //宽度计算

    btn_bg_color = (ptr->touch_flag == 1) ? CL_BTN_BACKGROUND_PRESSED : CL_BTN_BACKGROUND_NORMAL;

    // ??????
    LCD_SetColors(btn_bg_color, CL_WHITE); // ???,???(????)
    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y,
                          ptr->end_x - ptr->start_x,
                          ptr->end_y - ptr->start_y, 1); // ????

    // ?????? (??)
    LCD_SetColors(text_color, btn_bg_color); // ????,?????
    LCD_SetFont(&Font8x16); // ?? Font8x16 ? main.c ???,????
    ILI9341_DispString_EN_CH(ptr->start_x + (BTN_WIDTH - text_width_pixels) / 2,
                             ptr->start_y + (BTN_HEIGHT - 16) / 2, // 16 ?????
                             caption);

    // ??????
    LCD_SetColors(CL_BLUE4, CL_WHITE); // ???? (?? CL_BLUE4 ???)
    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y,
                          ptr->end_x - ptr->start_x,
                          ptr->end_y - ptr->start_y, 0); // ????? (???)
}

//+1按钮
static void Draw_IncrementVal_Button(void *btn) {
    Touch_Button *ptr = (Touch_Button *)btn;
    const char *caption = "按下+1 "; // ?? "+1"
    uint16_t text_width_pixels = 16*2; // "??" ????????
    uint16_t btn_bg_color, text_color = CL_BLACK;

    btn_bg_color = (ptr->touch_flag == 1) ? CL_BTN_BACKGROUND_PRESSED : CL_BTN_BACKGROUND_NORMAL;

    LCD_SetColors(btn_bg_color, CL_WHITE);
    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y,
                          ptr->end_x - ptr->start_x,
                          ptr->end_y - ptr->start_y, 1);

    LCD_SetColors(text_color, btn_bg_color);
    LCD_SetFont(&Font8x16);
    ILI9341_DispString_EN_CH(ptr->start_x + (BTN_WIDTH - text_width_pixels) / 2,
                             ptr->start_y + (BTN_HEIGHT - 16) / 2,
                             (char*)caption);

    LCD_SetColors(CL_BLUE4, CL_WHITE);
    ILI9341_DrawRectangle(ptr->start_x, ptr->start_y,
                          ptr->end_x - ptr->start_x,
                          ptr->end_y - ptr->start_y, 0);
}

//按钮执行函数
static void Command_Select_Adjust_Unit(void *btn) {
    Touch_Button *this_button = (Touch_Button *)btn;

    lcd_flag++;
    if (lcd_flag >= 3) {
        lcd_flag = 0; // ???? ? -> ? -> ? -> ?
    }
    time_updated_flag = 1; // ?? main.c ????

  
    if (this_button != NULL && this_button->draw_btn != NULL) {
        this_button->draw_btn(this_button);
    }
}


static void Command_Increment_Selected_Unit(void *btn) {
    (void)btn; // ???????????????

    switch (lcd_flag) {
        case 0: // ???
            s++;
            if (s >= 60) s = 0;
            break;
        case 1: // ???
            m++;
            if (m >= 60) m = 0;
            break;
        case 2: // ???
            h++;
            if (h >= 24) h = 0;
            break;
        default:
            // ????,?????
            lcd_flag = 0;
            break;
    }
    time_updated_flag = 1; // ?? main.c ????
}
