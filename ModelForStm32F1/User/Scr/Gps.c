#include "main.h"

volatile static u8 gps_recv_buf[256];
volatile static u8 gps_recv_data[256];
volatile static u8 gps_length=0;


void gps_init(u32 baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;  //定义串口初始化结构体
		NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  //本函数（使能时钟）参数中，RCC_APB2Periph_USART1是必不可少的，有人会问，对于串口用到的PA9和
  //PA10不用使能时钟吗？其实由于USART1默认的就是PA9和PA10，所以这一个就行了，当然你要是加上
  //这个|RCC_APB2Periph_GPIOA也是不报错的，只是重复了。
  /*  USART1_TX -> PA9 */			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	       //选中串口默认输出管脚         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //定义输出最大速率 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//定义管脚9的模式  
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //调用函数，把结构体参数输入进行初始化		   
  /*  USART1_RX ->	PA10*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = baudRate; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No;		//校验位 无
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//使能接收和发送引脚

  USART_Init(USART2, &USART_InitStructure); //将以上赋完值的结构体带入库函数USART_Init进行初始化
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_Init(&NVIC_InitStructure);
	
//  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
  USART_Cmd(USART2, ENABLE);//开启USART1，注意与上面RCC_APB2PeriphClockCmd()
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

