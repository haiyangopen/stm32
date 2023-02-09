#include "main.h"


int main(void)
{
    led_config_init();
    systick_Init();
	while(1)
	{
        LED3_TOGGLE;
        Delay_ms(500);
        //SysTick_Delay_Ms(1000);
	}
}



