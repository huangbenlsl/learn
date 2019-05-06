#include "main.h"

volatile static u8 gps_recv_buf[256];
volatile static u8 gps_recv_data[256];
volatile static u8 gps_length=0;


void gps_init(u32 baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
		NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  //��������ʹ��ʱ�ӣ������У�RCC_APB2Periph_USART1�Ǳز����ٵģ����˻��ʣ����ڴ����õ���PA9��
  //PA10����ʹ��ʱ������ʵ����USART1Ĭ�ϵľ���PA9��PA10��������һ�������ˣ���Ȼ��Ҫ�Ǽ���
  //���|RCC_APB2Periph_GPIOAҲ�ǲ�����ģ�ֻ���ظ��ˡ�
  /*  USART1_TX -> PA9 */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	       //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ  
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*  USART1_RX ->	PA10*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = baudRate; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������

  USART_Init(USART2, &USART_InitStructure); //�����ϸ���ֵ�Ľṹ�����⺯��USART_Init���г�ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_Init(&NVIC_InitStructure);
	
//  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
  USART_Cmd(USART2, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()
}

void USART2_IRQHandler(void)
{
	volatile u32 sr;
	volatile u32 data;
	volatile static u8 index=0;


//	if(USART_GetFlagStatus(USART2,USART_IT_RXNE)==SET)
//	{
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//		gps_recv_buf[index++] = USART2->DR;
//	}	
//	
//	if(USART_GetFlagStatus(USART2,USART_IT_IDLE) == SET)
//	{
//		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
//		gps_length = index;
//		USART1->DR = gps_length;
//		index = 0;
//	}
		sr = USART2->SR;
	data = USART2->DR;
	USART1->DR = USART2->DR;
}

