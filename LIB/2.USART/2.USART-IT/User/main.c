#include "main.h"

#define size1   sizeof(Tx_String)
uint8_t Rx_String[10];
uint8_t Tx_String[] = {"��ã���ӭʹ��\r\n"};
uint8_t a[size1]= {"nihaoya\r\n"};

int main(void)
{
    
    SysTick_Init();//���ȳ�ʼ��ʱ��
    LED_GPIO_Config();
    //USART_Config();
    usart_config_init();
    //usart_dma_config_init();
    printf("���  nihao ��ӭʹ��\r\n");
    printf("%s",Tx_String);
	while(1)
	{
        LED3_TOGGLE;
        SysTick_Delay_Ms(1000);
	}
}



