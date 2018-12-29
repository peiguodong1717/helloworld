#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

uint8_t Time_FL1;
uint8_t Time_FL23;
extern u8 flage;
extern s32 Heigh_new;
void IWDG_Init(uint16_t prer,uint16_t rlr)
{
	IWDG->KR=0X5555;       //解除寄存器保护        
	IWDG->PR=prer;         // 写入初始化分频值
	IWDG->RLR=rlr;         // 写入自动装载值
	IWDG->KR=0XAAAA;       //开启寄存器保护
	IWDG->KR=0XCCCC;       //启动看门狗
}

void IWDG_Feed(void)
{
  IWDG->KR=0XAAAA;                                  
}

void TIM2_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能TIM2时钟
	
	//时钟预分频系数 驱动计数器的时钟 CK_CNT=CK_INT/(71+1) = 1M  计数器计数1次时间等于1/CK_CNT = 1us
	
	TIM_TimeBaseStructure.TIM_Period = arr;     //设定计数器自动重装值     
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );//允许更新中断 

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	TIM_Cmd(TIM2, ENABLE);  //使能定时器2
}

void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能TIM2时钟
	
	//时钟预分频系数 驱动计数器的时钟 CK_CNT=CK_INT/(71+1) = 1M  计数器计数1次时间等于1/CK_CNT = 1us
	
	TIM_TimeBaseStructure.TIM_Period = arr;     //设定计数器自动重装值     
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//允许更新中断 

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	
}
void TIM4_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能TIM2时钟
	
	//时钟预分频系数 驱动计数器的时钟 CK_CNT=CK_INT/(71+1) = 1M  计数器计数1次时间等于1/CK_CNT = 1us
	
	TIM_TimeBaseStructure.TIM_Period = arr;     //设定计数器自动重装值     
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE );//允许更新中断 

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	TIM_Cmd(TIM4, ENABLE);  //使能定时器2
}

void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	}
}
u8 cnt;
void TIM3_IRQHandler()
{

	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		cnt++;
		if((cnt>=100)&&(USART_Fpt&0xf0)){
			cnt = 0;
			USART_Fpt=0x01;
			//printf("hearbeat=021025010110,0,%d,2018120613030206",Heigh_new);
			USART_Fpt=0x11;
		}
		IWDG_Feed();//喂狗
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
	}
}
void TIM4_IRQHandler()
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{	

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
	}
}
