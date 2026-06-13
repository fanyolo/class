#include <main.h>

volatile int state = 0;

// LED 寄存器定义
#define GPIOA28ALTFN1 (*(volatile unsigned int*)0xC001A024)
#define GPIOA28OUTENB (*(volatile unsigned int*)0xC001A004)
#define GPIOA28OUT    (*(volatile unsigned int*)0xC001A000)

#define GPIOE13ALTFN0 (*(volatile unsigned int*)0xC001E020)
#define GPIOE13OUTENB (*(volatile unsigned int*)0xC001E004)
#define GPIOE13OUT    (*(volatile unsigned int*)0xC001E000)

#define GPIOB12ALTFN0 (*(volatile unsigned int*)0xC001B020)
#define GPIOB12OUTENB (*(volatile unsigned int*)0xC001B004)
#define GPIOB12OUT    (*(volatile unsigned int*)0xC001B000)

#define KEY_ALTFN    (*(volatile unsigned int*)0xC001B028)  // GPIOBALTFN1
#define KEY_OUTENB   (*(volatile unsigned int*)0xC001B004)  // GPIOBOUTENB
#define KEY_DETMODE  (*(volatile unsigned int*)0xC001B00C)  // GPIOBDETMODE
#define KEY_PAD      (*(volatile unsigned int*)0xC001B008)  // GPIOBPAD

void rgb_init(void)
{
    unsigned int reg = 0;
    
    /* r - GPIOA28 */
    reg = GPIOA28ALTFN1;
    reg &= ~(0x3 << 28);
    GPIOA28ALTFN1 = reg;
    reg = GPIOA28OUTENB;
    reg |= (0x1 << 28);
    GPIOA28OUTENB = reg;

    /* g - GPIOE13 */
    reg = GPIOE13ALTFN0;
    reg &= ~(0x3 << 26);
    GPIOE13ALTFN0 = reg;
    reg = GPIOE13OUTENB;
    reg |= (0x1 << 13);
    GPIOE13OUTENB = reg;

    /* b - GPIOB12 */
    reg = GPIOB12ALTFN0;
    reg &= ~(0x3 << 24);
    reg |= (0x1 << 24);
    GPIOB12ALTFN0 = reg;
    reg = GPIOB12OUTENB;
    reg |= (0x1 << 12);
    GPIOB12OUTENB = reg;

    GPIOA28OUT &= ~(0x1 << 28);
    GPIOE13OUT &= ~(0x1 << 13);
    GPIOB12OUT &= ~(0x1 << 12);
}

// 按键初始化为外部中断模式
void key_interrupt_init(void)
{
    unsigned int reg = 0;
    
    // 配置GPIOB30为外部中断模式（ALT FUNCTION 0xF）
    reg = KEY_ALTFN;
    reg &= ~(0x3 << 28);
    reg |= (0xF << 28);
    KEY_ALTFN = reg;
    
    // 禁用输出
    reg = KEY_OUTENB;
    reg &= ~(0x1 << 30);
    KEY_OUTENB = reg;
    
    // 设置上升沿检测
    reg = KEY_DETMODE;
    reg &= ~(0x3 << 28);
    reg |= (0x1 << 28);
    KEY_DETMODE = reg;
}

void delay(volatile int count)
{
    while (count--) ;
}

void set_led(unsigned int* gpio_out, int pin, int val)
{
    if (val)
        *gpio_out |= (0x1 << pin);
    else
        *gpio_out &= ~(0x1 << pin);
}

void r_led(int val) { set_led(&GPIOA28OUT, 28, val); }
void g_led(int val) { set_led(&GPIOE13OUT, 13, val); }
void b_led(int val) { set_led(&GPIOB12OUT, 12, val); }

static void do_system_initial(void)
{
    malloc_init();
    s5p6818_irq_init();
    s5p6818_serial_initial();
    key_initial();
}

int main(int argc, char * argv[])
{
    volatile int i = 0;

    do_system_initial();
    
    rgb_init();
    key_interrupt_init();
    
    s5p6818_irq_set_type(128 + 8, IRQ_TYPE_EDGE_RISING);
    s5p6818_irq_enable(128 + 8);
    
    r_led(0);
    g_led(0);
    b_led(0);
    
    // 初始state为0
    state = 0;
    
    s5p6818_serial_write_string(0, "System Ready. All LEDs OFF.\r\n");
    s5p6818_serial_write_string(0, "Press button to light Red LED...\r\n");

    while(1)
    {
        if (state == 1)
        {
            state = 0;
            
            s5p6818_serial_write_string(0, "Button Pressed! Red LED ON\r\n");
            
            // 红灯亮
            r_led(1);
            for (i = 0; i < 500000; i++);
            r_led(0);
            
            s5p6818_serial_write_string(0, "Red LED OFF\r\n");
        }
        
        for (i = 0; i < 1000; i++);
    }

    return 0;
}
