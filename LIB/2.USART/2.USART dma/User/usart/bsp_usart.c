#include "./usart/bsp_usart.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

void usart_config_init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
    USART_InitTypeDef   USART_InitSyruct;
    
    // 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin    = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin    = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStruct);
    
    USART_InitSyruct.USART_BaudRate             = DEBUG_USART_BAUDRATE;
    USART_InitSyruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    USART_InitSyruct.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitSyruct.USART_Parity               = USART_Parity_No;
    USART_InitSyruct.USART_StopBits             = USART_StopBits_1;
    USART_InitSyruct.USART_WordLength           = USART_WordLength_8b;
    USART_Init(DEBUG_USARTx,&USART_InitSyruct);
    
    USART_Cmd(DEBUG_USARTx,ENABLE);
}

void usart_dma_config_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;
    // 开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitStruct.DMA_BufferSize   = 10;
    DMA_InitStruct.DMA_DIR          = DMA_DIR_PeripheralDST;
    DMA_InitStruct.DMA_M2M          = DMA_M2M_Disable;
    DMA_InitStruct.DMA_MemoryBaseAddr   = (uint32_t)a;
    DMA_InitStruct.DMA_MemoryDataSize   = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_MemoryInc        = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_PeripheralBaseAddr   = (uint32_t)(USART1_BASE+0x04);
    DMA_InitStruct.DMA_PeripheralDataSize   = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_PeripheralInc        = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_Init(DMA1_Channel4,&DMA_InitStruct);
    DMA_Cmd(DMA1_Channel4,ENABLE);
    USART_DMACmd(DEBUG_USARTx,USART_DMAReq_Tx,ENABLE);
}
/*****************  发送一个字节 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*****************  发送两个字节 **********************/

void Usart_SendHalfword( USART_TypeDef * pUSARTx, uint16_t ch )
{
    uint8_t temp_h;
    uint8_t temp_l;
    
    temp_h = (ch & 0xff00) >> 8;
    temp_l = ch &0xff;
    /* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,temp_h);		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
    /* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,temp_l);		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);		
}

/*****************  发送一个字节 **********************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *ch, uint8_t num)
{
    uint8_t i = 0;
    for(i=0;i<num;i++)
    {
        Usart_SendByte(pUSARTx,ch[i]);
    }
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);	
	
}

/*****************  发送一个字节 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
    do
    {
        Usart_SendByte( pUSARTx, *str++);
    }while(*str != '\0');
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);	
}

//串口重定义
int fputc(int ch,FILE *f)
{
    USART_SendData(DEBUG_USARTx,(uint8_t) ch);
    while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE) == RESET);
    return ch;
}


