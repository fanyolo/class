#define GPIOA28ALTFN1 (*(volatile unsigned int*)0xC001A024)
#define GPIOA28OUTENB (*(volatile unsigned int*)0xC001A004)
#define GPIOA28OUT (*(volatile unsigned int*)0xC001A000)
#define GPIOE13ALTFN0 (*(volatile unsigned int*)0xC001E020)
#define GPIOE13OUTENB (*(volatile unsigned int*)0xC001E004)
#define GPIOE13OUT (*(volatile unsigned int*)0xC001E000)
#define GPIOB12ALTFN0 (*(volatile unsigned int*)0xC001B020)
#define GPIOB12OUTENB (*(volatile unsigned int*)0xC001B004)
#define GPIOB12OUT (*(volatile unsigned int*)0xC001B000)
void rgb_init(void)
{
unsigned int reg = 0;
 /* r */
reg = GPIOA28ALTFN1;
reg &= ~(0x3 << 28);
GPIOA28ALTFN1 = reg;
reg = GPIOA28OUTENB;
reg &= ~(0x1 << 28); reg |= (0x1 << 28);
GPIOA28OUTENB = reg;

/* g */
reg = GPIOE13ALTFN0;
reg &= ~(0x3 << 26);
GPIOE13ALTFN0 = reg;
reg = GPIOE13OUTENB;
 reg &= ~(0x1 << 13);
reg |= (0x1 << 13);
 GPIOE13OUTENB = reg;

 /* b */
reg = GPIOB12ALTFN0;
reg &= ~(0x3 << 24);
reg |= (0x2 << 24);
GPIOB12ALTFN0 = reg;
reg = GPIOB12OUTENB;
reg &= ~(0x1 << 12);
reg |= (0x1 << 12);
GPIOB12OUTENB = reg;

 //初始状态，关闭所有LED
GPIOA28OUT &= ~(0x1 << 28);
GPIOE13OUT &= ~(0x1 << 13);
GPIOB12OUT &= ~(0x1 << 12);
}

void delay(volatile int count) //延时函数
{
    while (count--) ;
}

void set_led(unsigned int* gpio_out, int pin, int state) //控制对应LED灯的亮灭
{
    if (state)
    {
        *gpio_out |= (0x1 << pin);
    }
     else
    {
         *gpio_out &= ~(0x1 << pin);
    }
}

void r_led(int state)
{
    set_led(&GPIOA28OUT, 28, state);
}

void g_led(int state)
{
    set_led(&GPIOE13OUT, 13, state);
}

void b_led(int state)
{
    set_led(&GPIOB12OUT, 12, state);
}

void main(void)
{
    rgb_init();
while (1)
{
    g_led(0);
    b_led(0);
    r_led(1);
    delay(7500000);
    g_led(1);
    b_led(0);
    r_led(0);
    delay(7500000);
    g_led(0);
    b_led(1);
    r_led(0);
    delay(7500000);
}
return;
}
