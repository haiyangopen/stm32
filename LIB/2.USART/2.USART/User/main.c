#include "main.h"


int main(void)
{
//    uint8_t a[10]={0},i=0;
//    for(i=0;i<10;i++)
//    {
//        a[i] = i;
//    }
    uint8_t a[10]= {1,2,3,4,5,6,7,8,9,10};
    SysTick_Init();//���ȳ�ʼ��ʱ��
    LED_GPIO_Config();
    //USART_Config();
    usart_config_init();
    //Usart_SendByte(DEBUG_USARTx,'a');
    //Usart_SendHalfword(DEBUG_USARTx,0xffff);
    //Usart_SendArray(DEBUG_USARTx,a,10);
    Usart_SendString(DEBUG_USARTx,"nihao\r\n");
    Usart_SendString(DEBUG_USARTx,"��ӭʹ��\r\n");
    printf("���  nihao ��ӭʹ��\r\n");
	while(1)
	{
        LED3_TOGGLE;
        SysTick_Delay_Ms(1000);
	}
}



