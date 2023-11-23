#include "ws2812.h"
#include "tim.h"
 
#include "stdlib.h"

//extern uint8_t x1,x2,x3;
/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED      = {255,0,0};   //
const RGB_Color_TypeDef ORANGE   = {127,106,0};
const RGB_Color_TypeDef YELLOW   = {127,216,0};
const RGB_Color_TypeDef GREEN    = {0,255,0};
const RGB_Color_TypeDef CYAN	 	 = {0,255,255};
const RGB_Color_TypeDef BLUE     = {0,0,255};
const RGB_Color_TypeDef PURPLE	 = {238,130,238};
 RGB_Color_TypeDef BLACK    = {0,0,0};
const RGB_Color_TypeDef WHITE    = {255,255,255};
const RGB_Color_TypeDef MAGENTA  = {255,0,220};

RGB_Color_TypeDef T_1      ;//T<40¡ãC
RGB_Color_TypeDef T_2      = {127,255,255};//40¡ãC =< T < 50¡ãC
RGB_Color_TypeDef T_3      = {255,255,0};//50¡ãC =< T < 55¡ãC
RGB_Color_TypeDef T_4      = {255,127,0};//55¡ãC =< T < 60¡ãC
RGB_Color_TypeDef T_5      = {255,0,0};//60¡ãC =< T 

/**/
uint32_t Pixel_Buf[Pixel_NUM+1][24];       
 

/*************************************************************
** Function name:       RGB_SetColor
** Descriptions:        Sets the color of a single RGB LED, converting the 24BIT of RGB in the structure to code 0 and code 1
** Input parameters:    LedId:RGB Serial Number;Color:Defined Color Structures
** Output parameters:   Pixel_Buf:PWM Output Array
** Returned value:      None
** Remarks:             None
*************************************************************/
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i; 
	if(LedId > Pixel_NUM)return; //
	
	for(i=0;i<8;i++) Pixel_Buf[LedId][i]   = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0 );//?????0~7????G
	for(i=8;i<16;i++) Pixel_Buf[LedId][i]  = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0 );//?????8~15????R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0 );//?????16~23????B
}
 

/*************************************************************
** Function name:       Reset_Load
** Descriptions:        The last line is loaded with 24 zeros, outputting a PWM wave with a duty cycle of 0 for 24 cycles, as the final reset delay
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/

void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}
 
/*************************************************************
** Function name:       RGB_SendArray
** Descriptions:        Sending Array
** Output parameters:   &htim3:timers;TIM_CHANNEL_1:channel;Pixel_Buf:Array to be loaded;(Pixel_NUM+1)*24:Number of transmissions
** Returned value:      None
** Remarks:             None
*************************************************************/
void RGB_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
}
 
/*

*/
void RGB_T_1(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//
	{
		RGB_SetColor(i,T_1);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*

*/
void RGB_T_2(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//
	{
		RGB_SetColor(i,T_2);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*

*/
void RGB_T_3(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//
	{
		RGB_SetColor(i,T_3);
	}
	Reset_Load();
	RGB_SendArray();
}
 
/*

*/
void RGB_T_4(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//
	{
		RGB_SetColor(i,T_4);
	}
	Reset_Load();
	RGB_SendArray();
}
 
void RGB_T_5(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//
	{
		RGB_SetColor(i,T_5);
	}
	Reset_Load();
	RGB_SendArray();
}
/*************************************************************
** Function name:       rgb_show
** Descriptions:        Display the specified color
** Output parameters:   Pixel_Len:Number of display lamps;rgb:Color code to be displayed
** Returned value:      None
** Remarks:             None
*************************************************************/

void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)
	{
		RGB_SetColor(i,rgb);
	}
	Reset_Load();
	RGB_SendArray();
}
