/*
 * lcd.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Sword
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_


void lcdSetup(u8 PORT, u8 RS, u8 En, u8 D0, u8 D1,u8 D2,u8 D3,u8 D4,u8 D5,u8 D6,u8 D7 );
void lcdEnable();
void lcdWrite(u8 data);
void lcdCommand(u8 command);
void lcdInit();
void lcdChar(u8 ch);
void lcdString(char * string);
void lcdWriteInt(char * format, u32 number );
void lcdWriteFloat(char * format, double number );

void lcdSetCursor(u8 row, u8 col);
void lcdClearDisplay(void);

#define lcdClear		0x01
#define lcdCursorOFF	0x0C
#define lcdCursorON		0x0E
#define lcdCursorBlink	0x0F
#define lcdCursorHome	0x02
#define lcdShiftRight	0x1E
#define lcdShiftLeft	0x18
#define lcdOFF			0x08
#define lcdON			0x0C
#define lcdCursorLeft	0x10
#define lcdCursorRight	0x14





#endif /* INC_LCD_H_ */
