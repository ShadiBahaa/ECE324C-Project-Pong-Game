#ifndef MAIN_H
#define MAIN_H

#define PLAYERWIDTH   4
#define PLAYERHIGHT   13
#define BALLRADIUS      3
#define BALL_X_SPEED_START  2
#define BALL_Y_SPEED_START  2
#define PADDLE_SPEED_START  1

#define OK_PIN_PORT     GPIO_PORT_D
#define OK_PIN_PIN      GPIO_PIN_3

#define UP_PIN_PORT     GPIO_PORT_D
#define UP_PIN_PIN      GPIO_PIN_1

#define DOWN_PIN_PORT     GPIO_PORT_D
#define DOWN_PIN_PIN      GPIO_PIN_2

#define BUZZER_PORT				GPIO_PORT_D
#define BUZZER_PIN				GPIO_PIN_0

#define LED_RED_PIN_PORT		GPIO_PORT_B
#define LED_RED_PIN_PIN			GPIO_PIN_0

#define LED_GREEN_PIN_PORT		GPIO_PORT_B
#define LED_GREEN_PIN_PIN			GPIO_PIN_1

#define BLUETOOTH_UART_NO   UART_2

#define REFRESH_RATE_PERIODE        800000*3/2//(133333 * 5 - 1)

typedef struct{
    s16 xPos;
    s16 yPos;
    s16 speed;
}PADDLE_t;

typedef struct{
    s16 xPos;
    s16 yPos;
    s16 xSpeed;
    s16 ySpeed;
}BALL_t;

u8 APP_u8DisplayOpening(void);
void APP_voidPlayMulti(void);
void APP_voidPlaySingle(void);
void APP_voidDrawFillRect(s16 A_s16XPos, s16 A_s16YPos, u8 A_u8Width, u8 A_u8Hight);
void APP_voidDrawFillCircle(s16 A_s16XPos, s16 A_s16YPos, s16 A_s16Radius);
void APP_voidDrawCircle(s16 A_s16XPos, s16 A_s16YPos, s16 A_s16Radius);
void APP_voidDrawVLine(s16 A_s16XPos, s16 A_s16Y1Pos, s16 A_s16Y2Pos);
u8 APP_u8CheckBallRectCollide(BALL_t* A_pBALL, PADDLE_t *A_pPaddle);
void APP_voidRefreshIRQ(void);
u8 APP_u8GetNumLength(u8 A_u8Num);
void APP_voidUARTRQ(void);

#endif
