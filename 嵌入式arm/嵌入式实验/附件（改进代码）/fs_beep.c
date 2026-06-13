#include <main.h>

#define PWM_CH  2

#define TO_PERIOD_NS(freq)        (1000000000UL / (freq))
#define TO_DUTY_NS(duty, freq)    (TO_PERIOD_NS(freq) * (duty) / 100)

//音符频率，单位：Hz 
#define NOTE_REST 0

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

static void do_system_initial(void)
{
    malloc_init();

    s5p6818_pwm_init();
    s5p6818_serial_initial();
}

static void delay_ms(unsigned int ms)
{
    volatile unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 50000; j++)
        {
        }
    }
}

static void play_tone(unsigned int freq, unsigned int duration_ms)
{
    unsigned int period;
    unsigned int duty;

    if(freq == NOTE_REST)
    {
        pwm_config_u(PWM_CH, 0, TO_PERIOD_NS(1000));
        delay_ms(duration_ms);
        return;
    }

    period = TO_PERIOD_NS(freq);
    duty = period / 2;

    pwm_config_u(PWM_CH, duty, period);

    delay_ms(duration_ms);

    pwm_config_u(PWM_CH, 0, period);
    delay_ms(30);
}

//小星星前两句 
static const unsigned int melody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4,
    NOTE_A4, NOTE_A4, NOTE_G4,

    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4,
    NOTE_D4, NOTE_D4, NOTE_C4
};

static const unsigned int duration[] = {
    40, 40, 40, 40,
    40, 40, 80,

    40, 40, 40, 40,
    40, 40, 80
};

static void play_music(void)
{
    int i;
    int count;

    count = sizeof(melody) / sizeof(melody[0]);

    for(i = 0; i < count; i++)
    {
        play_tone(melody[i], duration[i]);
    }

    pwm_config_u(PWM_CH, 0, TO_PERIOD_NS(1000));
}

int main(int argc, char * argv[])
{
    do_system_initial();

    s5p6818_serial_write_string(0, "s5p6818 pwm music test ...\r\n");

    pwm_init(PWM_CH, 0, 0);

    s5p6818_pwm_enable();

    play_music();

    while(1)
    {
    }

    return 0;
}

