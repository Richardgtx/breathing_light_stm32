#include "stm32f10x.h"  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
uint8_t KeyNum;
int main(void)
{
	OLED_Init();
	OLED_ShowString(1,1,"NUM: ");
	OLED_ShowString(2,1,"CNT: ");
	OLED_ShowString(3,1,"k: ");
	Pwm_Init();
	
	while(1)
	{
		uint16_t k=100;
		for(uint16_t i=100;i>1;i--)
		{
			TIM_SetCompare1(TIM2,k);
			k-=1;
			OLED_ShowNum(3,4,k,5);
			Delay_ms(10);
		}
		for(uint16_t i=100;i>1;i--)
		{
			TIM_SetCompare1(TIM2,k);
			k+=1;
			OLED_ShowNum(3,4,k,5);
			Delay_ms(10);
		}
	}
}
