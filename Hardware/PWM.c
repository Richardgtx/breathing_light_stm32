#include "stm32f10x.h"                  // Device header
uint16_t Num;
void Pwm_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef Sa;
	Sa.TIM_ClockDivision=TIM_CKD_DIV1;
	Sa.TIM_CounterMode=TIM_CounterMode_Up;
	Sa.TIM_Period=100-1;
	Sa.TIM_Prescaler=720-1;;
	Sa.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&Sa);
	
	
	TIM_OCInitTypeDef Ta;
	Ta.TIM_OCMode=TIM_OCMode_PWM1;
	Ta.TIM_OutputState=TIM_OutputState_Enable;
	Ta.TIM_Pulse=0;
	Ta.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &Ta);
	
	GPIO_InitTypeDef GPIO_InitStrucuture;
	GPIO_InitStrucuture.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrucuture.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStrucuture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrucuture);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_InitTypeDef Pa;
	Pa.NVIC_IRQChannel=TIM2_IRQn;
	Pa.NVIC_IRQChannelCmd=ENABLE;;
	Pa.NVIC_IRQChannelPreemptionPriority=1;
	Pa.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&Pa);
	TIM_Cmd(TIM2,ENABLE);
}
uint16_t Pwm_get(void)
{
	return Num;
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}
