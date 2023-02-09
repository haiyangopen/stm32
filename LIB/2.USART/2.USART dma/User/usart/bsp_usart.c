#include "./usart/bsp_usart.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

void usart_config_init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;
    USART_InitTypeDef   USART_InitSyruct;
    
    // �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	// �򿪴��������ʱ��
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
    // ����DMAʱ��
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
/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*****************  ���������ֽ� **********************/

void Usart_SendHalfword( USART_TypeDef * pUSARTx, uint16_t ch )
{
    uint8_t temp_h;
    uint8_t temp_l;
    
    temp_h = (ch & 0xff00) >> 8;
    temp_l = ch &0xff;
    /* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,temp_h);		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
    /* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,temp_l);		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);		
}

/*****************  ����һ���ֽ� **********************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *ch, uint8_t num)
{
    uint8_t i = 0;
    for(i=0;i<num;i++)
    {
        Usart_SendByte(pUSARTx,ch[i]);
    }
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);	
	
}

/*****************  ����һ���ֽ� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
    do
    {
        Usart_SendByte( pUSARTx, *str++);
    }while(*str != '\0');
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);	
}

//�����ض���
int fputc(int ch,FILE *f)
{
    USART_SendData(DEBUG_USARTx,(uint8_t) ch);
    while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TXE) == RESET);
    return ch;
}


