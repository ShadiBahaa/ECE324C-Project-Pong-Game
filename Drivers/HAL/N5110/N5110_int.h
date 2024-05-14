#ifndef HAL_N5110_N5110_INT_H_
#define HAL_N5110_N5110_INT_H


typedef enum N5110_STATE_e{
	N5110_LOW,
	N5110_HIGH
}N5110_STATE_t;

#define N5110_SCREENW									84
#define N5110_SCREENH									48

void HN5110_vInit(void);
void HN5110_vPrintChar(u8 A_u8data);
void HN5110_vPrintString(u8 *PA_u8String);
void HN5110_vPrintNumber(s32 A_s32Number);
void HN5110_vSetCursor(u8 A_u8ColNum, u8 A_u8RowNum);
void HN5110_vClear(void);
void HN5110_vDrawFullImage(u8 *PA_u8Data);
void HN5110_vDisplayCustomChar(const u8 *PA_u8Data);
void HN5110_vDisplay2DImage(const u8 PA_u8Data[][7],u8 A_u8length);
void HN5110_vHome(void);
//Buffer Functions
void HN5110_vSetPixel(u8 A_u8Xpos,u8 A_u8Ypos, N5110_STATE_t A_enState);
void HN5110_vDisplayBuffer(void);
void HN5110_vClearBuffer(void);
void HN5110_vAddCharBuffer(u8 A_u8Xpos,u8 A_u8Ypos, u8 A_u8Data);
void HN5110_vAddStringBuffer(u8 A_u8Xpos,u8 A_u8Ypos,u8 *PA_u8String);
void HN5110_vAddNumberBuffer(u8 A_u8Xpos,u8 A_u8Ypos,s32 A_s32Number);
#endif /* HAL_N5110_N5110_INT_H */
