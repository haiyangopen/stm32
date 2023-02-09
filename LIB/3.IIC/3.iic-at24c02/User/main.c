#include "main.h"

#define size1   sizeof(Tx_String)
uint8_t Rx_String[10];
uint8_t Tx_String[] = {"��ã���ӭʹ��\r\n"};
uint8_t a[size1]= {"nihaoya\r\n"};
uint8_t read_buff[10] = {0};
uint8_t write_page_buff[8] = {1,2,3,4,5,6,7,8};
int main(void)
{
    
    SysTick_Init();//���ȳ�ʼ��ʱ�� 
    led_config_init();//��ʼ��led
    usart_config_init();//��ʼ������1
    iic_config_init();//��ʼ��IIC1
    
    printf("����һ��iic���Գ���\r\n");
    for(int i=0;i<8;i++)
    {
        printf("д֮ǰread_buff����Ϊ��%d\r\n",read_buff[i]);
    }
//    eeprom_write_byte(1,0x55);
//    eeprom_write_wait();
//    eeprom_write_byte(2,0x54);
//    eeprom_write_wait();
    
    eeprom_write_page(0,write_page_buff,8);
    eeprom_write_wait();
    eeprom_read(0,read_buff,8);
    
    for(int i=0;i<8;i++)
    {
        printf("\r\nд֮��read_buff����Ϊ��%d\r\n",read_buff[i]);
    }
    
	while(1)
	{
        LED3_TOGGLE;
        SysTick_Delay_Ms(1000);
	}
}



