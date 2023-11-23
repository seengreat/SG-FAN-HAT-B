#ifndef __WS2812_H__
#define __WS2812_H__
 
#include "main.h"
 

#define CODE_1       (38)     //Count times with a 1-code timer 
#define CODE_0       (19)     //Count times with a 0-code timer
 
/*Create a structure that defines the size of a single LED tri-color value*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;

#define Pixel_NUM 6  //RGB Quantity Macro Definition

extern RGB_Color_TypeDef T_1;
extern RGB_Color_TypeDef T_2;
extern RGB_Color_TypeDef T_3;
extern RGB_Color_TypeDef T_4;
extern RGB_Color_TypeDef T_5;
extern RGB_Color_TypeDef BLACK;
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);
void Reset_Load(void); //
void RGB_SendArray(void);          //
//void RGB_RED(uint16_t Pixel_Len);  //
//void RGB_GREEN(uint16_t Pixel_Len);//
//void RGB_BLUE(uint16_t Pixel_Len); //
//void RGB_WHITE(uint16_t Pixel_Len);//
void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb);
void led_loop(void);

void RGB_T_1(uint16_t Pixel_Len);
void RGB_T_2(uint16_t Pixel_Len);
void RGB_T_3(uint16_t Pixel_Len);
void RGB_T_4(uint16_t Pixel_Len);
void RGB_T_5(uint16_t Pixel_Len);

					
 
#endif
