#include "main.h"

uint8_t a[]= {"nihaoya\r\n"};
char ch1;
int main(void)
{

    SysTick_Init();//���ȳ�ʼ��ʱ��
    LED_GPIO_Config();
    usart_config_init();
    //USART_Config();
    //usart_dma_config_init();
    //printf("���  nihao ��ӭʹ��\r\n");
	while(1)
	{
        USART_ClearFlag(DEBUG_USARTx,USART_FLAG_RXNE);
        ch1 = getchar();
        
        printf("ch=%c\n",ch1);
	}
}


 
