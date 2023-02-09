#include "main.h"

//uint8_t a[]= {1,2,3,4,5,6,7,8,9,10};
uint8_t a[]= {"nihaoya\r\n"};
int main(void)
{
//    uint8_t a[10]={0},i=0;
//    for(i=0;i<10;i++)
//    {
//        a[i] = i;
//    }
    
    SysTick_Init();//优先初始化时钟
    LED_GPIO_Config();
    //USART_Config();
    usart_config_init();
    usart_dma_config_init();
    //Usart_SendByte(DEBUG_USARTx,'a');
    //Usart_SendHalfword(DEBUG_USARTx,0xffff);
    //Usart_SendArray(DEBUG_USARTx,a,10);
//    Usart_SendString(DEBUG_USARTx,"nihao\r\n");
//    Usart_SendString(DEBUG_USARTx,"欢迎使用\r\n");
//    printf("你好  nihao 欢迎使用\r\n");
	while(1)
	{
        LED3_TOGGLE;
        SysTick_Delay_Ms(1000);
	}
}



