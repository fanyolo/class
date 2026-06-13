#include <main.h>
static void do_system_initial(void)
{
    s5p6818_serial_initial();
}

int main(int argc, char * argv[])
{
    int i = 0, j = 0;

    do_system_initial();
    /*
     * Write topic information
     */

    while(1)
    {
//      s5p6818_serial_write(0, "s5p6818 serial0 stdio test ...\r\nzjt8204220813\r\n", 33);
        s5p6818_serial_write(0, "樊博文 电信2303 8207230322\r\n", sizeof("樊博文 电信2303 8207230322\r\n") - 1);
        for ( i = 0; i < 2000; i++)
            for (j = 0; j <2000; j++);
    }

    return 0;
}

