#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../TM4C123GH6PMn.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SSI/SSI_int.h"
#include "N5110_prv.h"
#include "N5110_cfg.h"
#include "N5110_int.h"

static void HN5110_vWriteCommand(u8 A_u8Data){
		while(MSSI_u8Check_Busy() == N5110_HIGH){}
		WRT_BIT(N5110_PORT->DATA,N5110_DC_PIN,N5110_DC_COMMAND);
		//GPIO_WritePin(N5110_PORT,N5110_DC_PIN,N5110_DC_COMMAND);
		MSSI_vTransmit_single((u16)A_u8Data);
}

static void HN5110_vWriteData(u8 A_u8Data){
		while(MSSI_u8Check_NotEmpty() == N5110_LOW){}
		WRT_BIT(N5110_PORT->DATA,N5110_DC_PIN,N5110_DC_DATA);
		//GPIO_WritePin(N5110_PORT,N5110_DC_PIN,N5110_DC_DATA);
		MSSI_vTransmit_continuous((u16)A_u8Data);
}

void HN5110_vInit(void){
	volatile u8 delay;
	MSSI_vInit();
	//GPIO_WritePin(N5110_PORT,N5110_RST_PIN,N5110_LOW);	
	//N5110_PORT->DATA &= ~(1<<N5110_RST_PIN);
	CLR_BIT(N5110_PORT->DATA,N5110_RST_PIN);
	for(delay=0; delay<10; delay++);// delay minimum 100 ns
	SET_BIT(N5110_PORT->DATA,N5110_RST_PIN);
	//GPIO_WritePin(N5110_PORT,N5110_RST_PIN,N5110_HIGH);
	//N5110_PORT->DATA |= (1<<N5110_RST_PIN);
	HN5110_vWriteCommand(N5110_COMMAND_FUNCTION_EX);
	HN5110_vWriteCommand(N5110_COMMAND_BIAS_SYSTEM);	
	HN5110_vWriteCommand(N5110_COMMAND_VOP);
	HN5110_vWriteCommand(N5110_COMMAND_TEMP);
	HN5110_vWriteCommand(N5110_COMMAND_FUNCTION_BS);
	HN5110_vWriteCommand(N5110_COMMAND_NORMAL_MODE);
}

void HN5110_vPrintChar(u8 A_u8data){
  u8 L_u8count;
  HN5110_vWriteData(N5110_DATA_Blank_Coulumn);                 // blank vertical line padding
  for(L_u8count=0; L_u8count<5; L_u8count+=1){
    HN5110_vWriteData( ASCII[A_u8data - 0x20][L_u8count]);
  }
  HN5110_vWriteData(N5110_DATA_Blank_Coulumn);                 // blank vertical line padding
}

void HN5110_vPrintString(u8 *PA_u8String){
	u8 L_u8Counter = 0;
	while(PA_u8String[L_u8Counter] != '\0')
	{
		HN5110_vPrintChar(PA_u8String[L_u8Counter++]);
	}
}

void HN5110_vPrintNumber(s32 A_s32Number){
	u32 l_u32Number=1;
	if(A_s32Number==0){
		HN5110_vPrintChar('0');
	}
	if(A_s32Number<0){
		HN5110_vPrintChar('-');
		A_s32Number*=-1;
	}
	while(A_s32Number !=0){
		l_u32Number= (l_u32Number*10)+(A_s32Number%10);
		A_s32Number =A_s32Number/10;
	}
	while(l_u32Number!=1){
		HN5110_vPrintChar((l_u32Number%10)+'0');
		l_u32Number=l_u32Number/10;
	}
}

void HN5110_vSetCursor(u8 A_u8ColNum, u8 A_u8RowNum){
  if((A_u8ColNum <= 11) && (A_u8RowNum <= 5)){        // bad input
    HN5110_vWriteCommand( N5110_COMMAND_X_POS|(A_u8ColNum*7));     // setting bit 7 updates X-position as each char 7 columns we multiply by 7 
		HN5110_vWriteCommand( N5110_COMMAND_Y_POS|A_u8RowNum);         // setting bit 6 updates Y-position
  }
}

void HN5110_vClear(void){
  u16 l_u8counter = 0;
  for(l_u8counter=0; l_u8counter < N5110_SCREENW*N5110_SCREENH/8; l_u8counter+=1){
    HN5110_vWriteData(N5110_DATA_Blank_Coulumn);
  }
	HN5110_vHome();
}

void HN5110_vDrawFullImage(u8 *PA_u8Data){
  u16 l_u8counter = 0;
		HN5110_vHome();
  for(l_u8counter=0; l_u8counter < N5110_SCREENW*N5110_SCREENH/8; l_u8counter+=1){
    HN5110_vWriteData(PA_u8Data[l_u8counter]);
  }
}


void HN5110_vDisplayCustomChar(const u8 *PA_u8Data){
	u8 L_u8ColCount;
	for(L_u8ColCount=0; L_u8ColCount<7; L_u8ColCount+=1){
		HN5110_vWriteData( PA_u8Data[L_u8ColCount]);
	}
}

void HN5110_vDisplay2DImage(const u8 PA_u8Data[][N5110_SIZEOFCHAR],u8 A_u8length){
	u8 L_u8CharCount;
	for(L_u8CharCount=0; L_u8CharCount<A_u8length; L_u8CharCount+=1){
		HN5110_vDisplayCustomChar(PA_u8Data[L_u8CharCount]);
	}
}

void HN5110_vHome(void){
	HN5110_vSetCursor(0, 0);
}
