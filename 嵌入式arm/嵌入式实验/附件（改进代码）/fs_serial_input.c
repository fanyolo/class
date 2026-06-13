#include <main.h>

#define BUF_SIZE 256

static void do_system_initial(void)
{
    s5p6818_serial_initial();
}
int main(int argc, char * argv[])
{
    u8_t buf[BUF_SIZE] = {0};
    u8_t ch = 0;
    int pos = 0;
    int i = 0;

    do_system_initial();

    s5p6818_serial_write_string(0, "  Serial Echo Test\r\n");
   
    s5p6818_serial_write_string(0, "Please type Chinese or English, then press Enter.\r\n");

    while(1)
    {
        if(s5p6818_serial_read(0, &ch, 1) == 1)
        {
           
            if(ch == '\r' || ch == '\n')
            {
              
                if(pos == 0)
                {
                    continue;
                }

                s5p6818_serial_write_string(0, "recv: [");
                s5p6818_serial_write(0, (char *)buf, pos);
                s5p6818_serial_write_string(0, "]\r\n");

          
                for(i = 0; i < BUF_SIZE; i++)
                {
                    buf[i] = 0;
                }

                pos = 0;
            }
            else
            {
              
                if(pos < BUF_SIZE - 1)
                {
                    buf[pos++] = ch;
                }
                else
                {
                 
                    s5p6818_serial_write_string(0, "recv: [");
                    s5p6818_serial_write(0, (char *)buf, pos);
                    s5p6818_serial_write_string(0, "]\r\n");

                    for(i = 0; i < BUF_SIZE; i++)
                    {
                        buf[i] = 0;
                    }

                    pos = 0;
                }
            }
        }
    }

    return 0;
}

