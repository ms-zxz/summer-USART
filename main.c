#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
 
void ZXZ_USART1_Init(void)

	{
		GPIO_InitTypeDef GPIO_InitStrue;
		USART_InitTypeDef USART_InitStrue;
		NVIC_InitTypeDef NVIC_InitStrue;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);                     //使能时钟
		
		GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(GPIOA,&GPIO_InitStrue);                                         //初始化PA9 
		
		GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(GPIOA,&GPIO_InitStrue);                                         //初始化PA10
		
		USART_InitStrue.USART_BaudRate=115200;
		USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStrue.USART_Parity=USART_Parity_No;
		USART_InitStrue.USART_StopBits=USART_StopBits_1;
		USART_InitStrue.USART_WordLength=USART_WordLength_8b;
		USART_Init(USART1,&USART_InitStrue);                                      //初始化串口
		
		USART_Cmd(USART1,ENABLE);                                                 //使能串口
		
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                              //开启中断
		
		NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
		NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
		NVIC_Init(&NVIC_InitStrue);                                               //设置中断优先级
	}
 
void USART1_IRQHandler(void)                                                      //中断服务函数

	{
		
		u8 res;
		
		if(USART_GetITStatus(USART1,USART_IT_RXNE))
		{
			
			res=USART_ReceiveData(USART1);                                       //读取
			 
			USART_SendData(USART1,res);                                          //发送

		}

	}

int main(void)

	{

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	                        //优先级2
		ZXZ_USART1_Init();
		while(1);	
		 
	}
