#include <main.h>
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

GPIOA28OUT &= ~(0x1 << 28);
GPIOE13OUT &= ~(0x1 << 13);
GPIOB12OUT &= ~(0x1 << 12);
}
static void do_system_initial(void)
{
	malloc_init();
	s5p6818_serial_initial();
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

int main(int argc, char * argv[])
{
	volatile int i = 0;
	volatile int j = 0;

	do_system_initial();

	rgb_init();

	s5p6818_serial_write_string(0, "S5P6818 reset test...\r\n");
	s5p6818_serial_write_string(0, "System will reset\r\n");
	s5p6818_serial_write_string(0, "Wait for system restart\r\n");

	g_led(0);
	b_led(0);
	r_led(1);

	for (i = 0; i < 2000; i++)
		for (j = 0; j < 3000; j++);



	write32((S5P6818_SYS_PWRCONT), (read32((S5P6818_SYS_PWRCONT)) & ~(0x1<<3)) | (0x1<<3));
	write32((S5P6818_SYS_PWRMODE), (read32((S5P6818_SYS_PWRMODE)) & ~(0x1<<12)) | (0x1<<12));

	while(1) {
		s5p6818_serial_write_string(0, "It's not going to print!!!!!\r\n");

	}

	return 0;
}

