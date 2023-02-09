#include "./iic/bsp_iic.h"


 /**
  * @brief  I2C GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void iic_config_init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
    I2C_InitTypeDef   I2C_InitSyruct;
    
    // 打开串口GPIO的时钟
	BSP_I2CX_GPIO_APBxClkCmd(BSP_I2CX_SCL_GPIO_CLK|BSP_I2CX_SDA_GPIO_CLK, ENABLE);
	// 打开串口外设的时钟
	BSP_I2CX_APBxClkCmd(BSP_I2CX_CLK, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin    = BSP_I2CX_SCL_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF_OD;
    GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(BSP_I2CX_SCL_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin    = BSP_I2CX_SDA_GPIO_PIN;
    GPIO_Init(BSP_I2CX_SDA_GPIO_PORT,&GPIO_InitStruct);
    
    I2C_InitSyruct.I2C_Ack      = I2C_Ack_Enable;
    I2C_InitSyruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitSyruct.I2C_ClockSpeed          = BSP_I2CX_SPEED;
    I2C_InitSyruct.I2C_DutyCycle           = I2C_DutyCycle_2;
    I2C_InitSyruct.I2C_Mode                = I2C_Mode_I2C;
    I2C_InitSyruct.I2C_OwnAddress1         = I2C_OWN_ADDRESS;
    
    I2C_Init(BSP_I2CX,&I2C_InitSyruct);
    
    I2C_Cmd(BSP_I2CX,ENABLE);
}

//void usart_dma_config_init(void)
//{
//    DMA_InitTypeDef DMA_InitStruct;
//    // 开启DMA时钟
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//    DMA_InitStruct.DMA_BufferSize   = 10;
//    DMA_InitStruct.DMA_DIR          = DMA_DIR_PeripheralDST;
//    DMA_InitStruct.DMA_M2M          = DMA_M2M_Disable;
//    DMA_InitStruct.DMA_MemoryBaseAddr   = (uint32_t)a;
//    DMA_InitStruct.DMA_MemoryDataSize   = DMA_MemoryDataSize_Byte;
//    DMA_InitStruct.DMA_MemoryInc        = DMA_MemoryInc_Enable;
//    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
//    DMA_InitStruct.DMA_PeripheralBaseAddr   = (uint32_t)(USART1_BASE+0x04);
//    DMA_InitStruct.DMA_PeripheralDataSize   = DMA_PeripheralDataSize_Byte;
//    DMA_InitStruct.DMA_PeripheralInc        = DMA_PeripheralInc_Disable;
//    DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
//    DMA_Init(DMA1_Channel4,&DMA_InitStruct);
//    DMA_Cmd(DMA1_Channel4,ENABLE);
//    USART_DMACmd(DEBUG_USARTx,USART_DMAReq_Tx,ENABLE);
//}


//向eeprom写入一个字节数据
void eeprom_write_byte(uint8_t addr,uint8_t data)
{
    //产生起始信号
    I2C_GenerateSTART(BSP_I2CX,ENABLE);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_MODE_SELECT) == ERROR );
    
    I2C_Send7bitAddress(BSP_I2CX,EEPROM_ADDRESS,I2C_Direction_Transmitter);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR );
    //发送内存地址
    I2C_SendData(BSP_I2CX,addr);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR );
    //发送数据
    I2C_SendData(BSP_I2CX,data);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR );
    
    I2C_GenerateSTOP(BSP_I2CX,ENABLE);
}

//向eeprom写入多个字节数据
void eeprom_write_page(uint8_t addr,uint8_t *data,uint8_t num)
{
    //产生起始信号
    I2C_GenerateSTART(BSP_I2CX,ENABLE);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_MODE_SELECT) == ERROR );
    
    I2C_Send7bitAddress(BSP_I2CX,EEPROM_ADDRESS,I2C_Direction_Transmitter);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR );
    //发送内存地址
    I2C_SendData(BSP_I2CX,addr);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR );
    //发送数据
    while(num--)
    {
        I2C_SendData(BSP_I2CX,*data++);
        while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR );
//        data++;
//        num--;
    }
    
    
    I2C_GenerateSTOP(BSP_I2CX,ENABLE);
}

//向eeprom读取数据
void eeprom_read(uint8_t addr,uint8_t *data,uint8_t num)
{
    //产生起始信号
    I2C_GenerateSTART(BSP_I2CX,ENABLE);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_MODE_SELECT) == ERROR );
    //发送设备地址
    I2C_Send7bitAddress(BSP_I2CX,EEPROM_ADDRESS,I2C_Direction_Transmitter);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR );
    //发送内存地址
    I2C_SendData(BSP_I2CX,addr);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR );
    
    //产生起始信号
    I2C_GenerateSTART(BSP_I2CX,ENABLE);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_MODE_SELECT) == ERROR );
    //发送设备地址
    I2C_Send7bitAddress(BSP_I2CX,EEPROM_ADDRESS,I2C_Direction_Receiver);
    while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR );
    
    //while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR );
    while(num)
    {
        if(num == 1)
        {
            I2C_AcknowledgeConfig(BSP_I2CX,DISABLE);
        }
        while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR ); 
        *data = I2C_ReceiveData(BSP_I2CX);
//        while( I2C_CheckEvent(BSP_I2CX,I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR );
        num--;
        data++;
    }
    I2C_GenerateSTOP(BSP_I2CX,ENABLE);
    I2C_AcknowledgeConfig(BSP_I2CX,ENABLE);
}

void eeprom_write_wait(void)
{
    do
    {
        I2C_GenerateSTART(BSP_I2CX,ENABLE);
        while( I2C_GetFlagStatus(BSP_I2CX,I2C_FLAG_SB) == RESET );
        //发送设备地址
        I2C_Send7bitAddress(BSP_I2CX,EEPROM_ADDRESS,I2C_Direction_Transmitter);
    }
    while( I2C_GetFlagStatus(BSP_I2CX,I2C_FLAG_ADDR) == RESET );
    
    I2C_GenerateSTOP(BSP_I2CX,ENABLE);
}



