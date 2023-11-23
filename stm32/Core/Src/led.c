#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "stdlib.h"

void led_update()
{
	if(Mode==Auto_mode)
	{
			HAL_GPIO_WritePin(GPIOA, LED_Mode_Pin, GPIO_PIN_RESET);
			if(pwm==40)
			{
					T_1.R=x1;T_1.G=x2;T_1.B=x3;
					rgb_show(6, T_1);
					HAL_GPIO_WritePin(GPIOA, LED2_Pin|LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);			
			}
			else if(pwm==50)
			{
					rgb_show(6, T_2);
					HAL_GPIO_WritePin(GPIOA, LED2_Pin|LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==75)
			{
					rgb_show(6, T_3);
					HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==90)
			{
					rgb_show(6, T_4);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==100)
			{
					rgb_show(6, T_5);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
			}
	}
	else if(Mode==Manu_mode)
	{
		  HAL_GPIO_WritePin(GPIOA, LED_Mode_Pin, GPIO_PIN_SET);

			if(pwm==0)
			{
	//				T_1.R=x1;T_1.G=x2;T_1.B=x3;
	//				rgb_show(6, T_1);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_SET);				
			}
			else if(pwm==40)
			{
	//			rgb_show(6, T_2);
					HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==50)
			{
	//				rgb_show(6, T_3);
					HAL_GPIO_WritePin(GPIOA, LED2_Pin|LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==75)
			{
	//				rgb_show(6, T_4);
					HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin, GPIO_PIN_RESET);
			}
			else if(pwm==100)
			{
	//				rgb_show(6, T_5);
					HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
			}
		  if(power_on)
		  {
				  rgb_show(6, T_3);
		  }
		  else if(power_on==0)
		  {
			 	if(temp<40)
				{
					T_1.R=x1;T_1.G=x2;T_1.B=x3;
					rgb_show(6, T_1);
				}
				else if(temp>=40&&temp<50)
					rgb_show(6, T_2);
				else if(temp>=50&&temp<55)
					rgb_show(6, T_3);
				else if(temp>=55&&temp<60)
					rgb_show(6, T_4);
				else if(temp>=60)
					rgb_show(6, T_5);
		  }
	 }
}
