#ifndef HAL_N5110_N5110_INT_H_
#define HAL_N5110_N5110_INT_H

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

#endif /* HAL_N5110_N5110_INT_H */
