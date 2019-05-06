#include "Usart.h"

void dataLinkUserConfig(uint32_t baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	
	
  //��������ʹ��ʱ�ӣ������У�RCC_APB2Periph_USART1�Ǳز����ٵģ����˻��ʣ����ڴ����õ���PA9��
  //PA10����ʹ��ʱ������ʵ����USART1Ĭ�ϵľ���PA9��PA10��������һ�������ˣ���Ȼ��Ҫ�Ǽ���
  //���|RCC_APB2Periph_GPIOAҲ�ǲ������ģ�ֻ���ظ��ˡ�
  /*  USART1_TX -> PA9 */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	       //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ  
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*  USART1_RX ->	PA10*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = baudRate; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������
  USART_Init(USART1, &USART_InitStructure); //�����ϸ���ֵ�Ľṹ�����⺯��USART_Init���г�ʼ��


	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_Init(&NVIC_InitStructure);
	
//  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_Cmd(USART1, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()
}

void usart1Print(char *str)
{
	while(*str)
	{
		USART_SendData(USART1,*str++);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}


void USART1_IRQHandler(void)
{
	volatile u32 sr;
	volatile u32 data;
	sr = USART1->SR;
	data = USART1->DR;
//	LED_BLU_TOGGLE();
	USART1->DR = data;
}
