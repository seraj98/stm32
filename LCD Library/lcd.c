/*
 * lcd.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Sword
 */

#include <stdio.h>
//#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "lcd.h"


//Global variables for LCD
//GPIO_TypeDef	*lcdPort;
u8		lcdPort;
u8		lcdRsPin; //3
u8		lcdEnPin; //2
u8		lcdDataPin[8]; //4 11 6 7 8 9 10 5

void lcdSetup(u8 PORT, u8 RS, u8 En, u8 D0, u8 D1, u8 D2,u8 D3, u8 D4, u8 D5, u8 D6, u8 D7)
{
// Assign Pin values to global variables
	lcdPort=PORT;
	lcdRsPin=RS;
	lcdEnPin=En;
	lcdDataPin[0]=D0;
	lcdDataPin[1]=D1;
	lcdDataPin[2]=D2;
	lcdDataPin[3]=D3;
	lcdDataPin[4]=D4;
	lcdDataPin[5]=D5;
	lcdDataPin[6]=D6;
	lcdDataPin[7]=D7;

}

void lcdEnable()
{
	// Give a small 0 to 1 and 1 to 0 pulse on Enable pin to transfer port data
	MGPIO_voidSetPinValue(lcdPort, lcdEnPin, MGPIO_HIGH);
	HAL_Delay(1);
	MGPIO_voidSetPinValue(lcdPort, lcdEnPin, MGPIO_LOW);

}

void lcdWrite(u8 data)
//	Writes one byte of data to the LCD Pins
{
	for(int i=0;i<8;i++)
	{
		if(data & (1<<i))
			MGPIO_voidSetPinValue(lcdPort, lcdDataPin[i], MGPIO_HIGH);
		else
			MGPIO_voidSetPinValue(lcdPort, lcdDataPin[i], MGPIO_LOW);
	}
	lcdEnable();
}

void lcdCommand(u8 command)
{
//	Sends Command data to LCD
	MGPIO_voidSetPinValue(lcdPort, lcdRsPin, MGPIO_LOW);	// Set RS to 0 for commands
	lcdWrite(command);
}

void lcdInit()
{
	lcdCommand(0x38); 	//  0 0 1 DL N F — — 0x30= 0011 0000 DL=1 means 8 Bit Mode
	HAL_Delay(10);
	lcdCommand(0x38);
	HAL_Delay(10);
	lcdCommand(0x38);
	HAL_Delay(10);
	lcdCommand(0x0F);	// 0 0 0 0 1 D C B		0x0E= 0000 1110 D=1 Display ON, C=1 Cursor ON
	HAL_Delay(10);
//	lcdCommand(0x0F);
//	HAL_Delay(10);
//	lcdCommand(0x0F);
}

void lcdChar(u8 ch)
{
//	Display One Byte of Data to LCD
	MGPIO_voidSetPinValue(lcdPort, lcdRsPin, MGPIO_HIGH);	// Set RS Pin 1 for Data
	lcdWrite(ch);
}

void lcdString(char * string)
{
//	Display a String of characters
	while(*string)
		lcdChar(*string++);
}

void lcdWriteInt(char * format, u32 number )
{
//	Display integer numbers format is standard c printf() like %d etc
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

void lcdWriteFloat(char * format, double number )
{
//	Display a floating point number
	char buffer[20];
	sprintf(buffer,format,number);
	lcdString(buffer);
}

void lcdSetCursor(u8 row, u8 col)
{
//	Sets the cursor position
	MGPIO_voidSetPinValue(lcdPort, lcdRsPin, MGPIO_LOW);	// RS=0;
	switch (row)
	{
	case 0:
		lcdWrite(0x80+col); break;
	case 1:
		lcdWrite(0xC0+col); break;
	case 2:
		lcdWrite(0x80+0x14+col); break;
	case 3:
		lcdWrite(0xC0+0x14+col); break;
	}
}

void lcdClearDisplay(void){

	lcdCommand(lcdClear);
}


