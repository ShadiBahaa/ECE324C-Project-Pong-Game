#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#include "../tm4c123gh6pm.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/GPIO/GPIO_Cfg.h"
#include "../MCAL/GPTM/GPTM_Interface.h"
#include "../MCAL/SSI/SSI_int.h"
#include "../MCAL/UART/UART_Config.h"
#include "../MCAL/UART/UART_Interface.h"
#include "../HAL/N5110/N5110_int.h"

#define PLAYERWIDTH   4
#define PLAYERHIGHT   16


typedef struct{
    u8 xPos;
    u8 yPos;
    s8 speed;
}PADDLE_t;

typedef struct{
    u8 xPos;
    u8 yPos;
    s8 xSpeed;
    s8 ySpeed;
}BALL_t;


int main(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  GPIO_PORTA_DIR_R |= 0xC0;             // make PA6,7 Print
  GPIO_PORTA_AFSEL_R |= 0x2C;           // enable alt funct on PA2,3,5
  GPIO_PORTA_AFSEL_R &= ~0xC0;          // disable alt funct on PA6,7
  GPIO_PORTA_DEN_R |= 0xEC;             // enable digital I/O on PA2,3,5,6,7
                                        // configure PA2,3,5 as SSI
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFF0F00FF)+0x00202200;
                                        // configure PA6,7 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0x00FFFFFF)+0x00000000;
  GPIO_PORTA_AMSEL_R &= ~0xEC;
	HN5110_vInit();
    drawFillCircle(N5110_SCREENW / 2, N5110_SCREENH / 2, 3);
    while (1)
    {
    }
    
}

void DisplayOpening(void){
    PADDLE_t PaddleOne, PaddleTwo;
    BALL_t Ball;

    PaddleOne.xPos = 0;
    PaddleOne.yPos = (N5110_SCREENH / 2) - (PLAYERHIGHT / 2);
    PaddleOne.speed = -3;

    PaddleTwo.xPos = N5110_SCREENW - PLAYERWIDTH;
    PaddleTwo.yPos = (N5110_SCREENH / 2) - (PLAYERHIGHT / 2);
    PaddleTwo.speed = 3;

    Ball.xPos = (N5110_SCREENW / 2);
    Ball.yPos = (N5110_SCREENH / 2);



}


void drawFillCircle(s16 A_s16XPos, s16 A_s16YPos, s16 A_s16Radius){
    s16 local_s16pk = 1 - A_s16Radius;
    s16 local_s16XPos = 0, local_s16YPos = A_s16Radius;

    while (local_s16XPos < local_s16YPos)
    {
        drawVLine(A_s16XPos + local_s16XPos, A_s16YPos + local_s16YPos, A_s16YPos - local_s16YPos);
        drawVLine(A_s16XPos + local_s16YPos, A_s16YPos + local_s16XPos, A_s16YPos - local_s16XPos);
        drawVLine(A_s16XPos - local_s16XPos, A_s16YPos + local_s16YPos, A_s16YPos - local_s16YPos);
        drawVLine(A_s16XPos - local_s16YPos, A_s16YPos + local_s16XPos, A_s16YPos - local_s16XPos);

        ++local_s16XPos;

        if(local_s16pk <= 0){
            local_s16pk += 2 * local_s16XPos + 3;
        }else{
            --local_s16YPos;

            local_s16pk += 2 * (local_s16XPos - local_s16YPos) + 5;
        }
    }
}

void drawVLine(u8 A_u8XPos, u8 A_u8Y1Pos, u8 A_u8Y2Pos){
    u8 local_u8Iterrator = 0;

    for(local_u8Iterrator = A_u8Y1Pos; A_u8Y1Pos <= A_u8Y2Pos; ++local_u8Iterrator){
        if(A_u8XPos < N5110_SCREENW && local_u8Iterrator < N5110_SCREENH)
            HN5110_vSetPixel(A_u8XPos, local_u8Iterrator, 1);
    }
}