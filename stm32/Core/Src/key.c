#include "key.h"
#include "i2c.h"
uint8_t key_scan;
int i=0,time_count=0;
void key_scanf()
{
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_SET)//Button not pressed
	{
				key_scan=0;//Clear key flag
				i=0;//Clear keystroke timing
	}
	if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_RESET)//Button pressed
		{
			key_scan=1;	//Set Key Flag
			HAL_Delay(10);//eliminate jitter
			if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_RESET)
			{
					while(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_RESET)//Wait for the button to pop up
					{
							HAL_I2C_Slave_Receive(&hi2c1, RE_BUFF, 2, 100);//Continue to receive IIC data while the key is pressed.
							if(i>=2000)//Key presses longer than 2s
								break;//Get out of the waiting	
					}
					if(i<2000)
					{
						if(Mode==Manu_mode)//Manual mode, increase fan speed
						{
							if(pwm<100)
							{
								pwm=pwm+25;
								if(pwm==25)pwm=40;
								if(pwm==65)pwm=50;
							}
							else if(pwm>=100)
							{
								pwm=0;
							}
		
						}
				}
			}
			if(i>=2000)//Press for more than 2s to switch modes
			{
				if(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_RESET)
				{
					if(Mode==Auto_mode)
					{
						Mode=Manu_mode;
						pwm=75;
//						HAL_GPIO_WritePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
					}
					else if(Mode==Manu_mode&&!power_on)
					{
						Mode=Auto_mode;
//						HAL_GPIO_TogglePin(GPIOA, LED0_Pin);
					}
//						HAL_GPIO_TogglePin(GPIOA, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin);
					
						while(HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin)==GPIO_PIN_RESET)
								HAL_I2C_Slave_Receive(&hi2c1, RE_BUFF, 2, 100);
				}
//				key_scan=0;
			}
		}
}
