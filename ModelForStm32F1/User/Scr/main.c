#include "main.h"
#include <rtthread.h>


static struct rt_thread led_operate_thread;
static struct rt_thread gps_deal_thread;

static rt_uint8_t rt_led_operate_thread_stack[1024];
static rt_uint8_t rt_gps_deal_thread_stack[1024];



static void led_operate_thread_entry(void* param)
{
	while(1)
	{
		LED_BLU_ON();
		rt_thread_delay(100);
		LED_BLU_OFF();
		rt_thread_delay(100);

	}
}
static void gps_deal_thread_entry(void* param)
{
	while(1)
	{
		rt_thread_delay(1000);
	}
}
int main (void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ledConfig();
	dataLinkUserConfig(115200);//usart1
	gps_init(9600);
	rt_thread_init(&led_operate_thread,"led_operate",led_operate_thread_entry,RT_NULL,rt_led_operate_thread_stack,sizeof(rt_led_operate_thread_stack),4,20);
	rt_thread_init(&gps_deal_thread,"ledoff",gps_deal_thread_entry,RT_NULL,rt_gps_deal_thread_stack,sizeof(rt_gps_deal_thread_stack),3,20);
	
	rt_thread_startup(&led_operate_thread);
	rt_thread_startup(&gps_deal_thread);
	
	while (1)
	{		
		rt_thread_delay(100);
	}
}

