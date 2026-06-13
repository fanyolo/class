#include <main.h>

#define GPIOA28ALTFN1 (*(volatile unsigned int*)0xC001A024)
#define GPIOA28OUTENB (*(volatile unsigned int*)0xC001A004)
#define GPIOA28OUT    (*(volatile unsigned int*)0xC001A000)

#define GPIOE13ALTFN0 (*(volatile unsigned int*)0xC001E020)
#define GPIOE13OUTENB (*(volatile unsigned int*)0xC001E004)
#define GPIOE13OUT    (*(volatile unsigned int*)0xC001E000)

#define GPIOB12ALTFN0 (*(volatile unsigned int*)0xC001B020)
#define GPIOB12OUTENB (*(volatile unsigned int*)0xC001B004)
#define GPIOB12OUT    (*(volatile unsigned int*)0xC001B000)

void rgb_init(void)
{
    unsigned int reg = 0;

    reg = GPIOA28ALTFN1;
    reg &= ~(0x3 << 28);
    GPIOA28ALTFN1 = reg;

    reg = GPIOA28OUTENB;
    reg &= ~(0x1 << 28);
    reg |= (0x1 << 28);
    GPIOA28OUTENB = reg;

    reg = GPIOE13ALTFN0;
    reg &= ~(0x3 << 26);
    GPIOE13ALTFN0 = reg;

    reg = GPIOE13OUTENB;
    reg &= ~(0x1 << 13);
    reg |= (0x1 << 13);
    GPIOE13OUTENB = reg;

    reg = GPIOB12ALTFN0;
    reg &= ~(0x3 << 24);
    reg |= (0x2 << 24);
    GPIOB12ALTFN0 = reg;

    reg = GPIOB12OUTENB;
    reg &= ~(0x1 << 12);
    reg |= (0x1 << 12);
    GPIOB12OUTENB = reg;

    //初始状态
    GPIOA28OUT &= ~(0x1 << 28);
    GPIOE13OUT &= ~(0x1 << 13);
    GPIOB12OUT &= ~(0x1 << 12);
}

void delay(volatile int count)
{
    while (count--);
}

void set_led(volatile unsigned int* gpio_out, int pin, int state)
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

void all_led_off(void)
{
    r_led(0);
    g_led(0);
    b_led(0);
}

static void do_system_initial(void)
{
    malloc_init();
    s5p6818_serial_initial();

    led_initial();
    key_initial();
}

int main(int argc, char * argv[])
{
    u32_t keyup = 0;
    u32_t keydown = 0;

    int led_mode = 0;

    do_system_initial();
    rgb_init();

    led_set_ledb_status(LED_STATUS_OFF);
    all_led_off();

    s5p6818_serial_write_string(0, "s5p6818 loop key test ...\r\n");
    s5p6818_serial_write_string(0, "Press key: RED -> GREEN -> BLUE -> RED\r\n");

    while(1)
    {
        keyup = 0;
        keydown = 0;

        if(get_key_event(&keyup, &keydown))
        {
        
            if(keydown != 0)
            {
                if(keydown & KEY_NAME_DOWN)
                {
                    all_led_off();

                    if(led_mode == 0)
                    {
                        r_led(1);
                        s5p6818_serial_write_string(0, "Red LED ON\r\n");
                    }
                    else if(led_mode == 1)
                    {
                        g_led(1);
                        s5p6818_serial_write_string(0, "Green LED ON\r\n");
                    }
                    else if(led_mode == 2)
                    {
                        b_led(1);
                        s5p6818_serial_write_string(0, "Blue LED ON\r\n");
                    }
                }
            }

       
            if(keyup != 0)
            {
                if(keyup & KEY_NAME_DOWN)
                {
                    all_led_off();
                    s5p6818_serial_write_string(0, "LED OFF\r\n");

                    led_mode++;

                    if(led_mode > 2)
                    {
                        led_mode = 0;
                    }
                }
            }
        }

        delay(1000);
    }

    return 0;
}

