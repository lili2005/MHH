/*
 * LCD_PROGRAM.c
 *
 *  Created on: Aug 26, 2026
 *      Author: ahmed
 */


#include <util/delay.h>
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"

#include "../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../INCLUDE/HAL/LCD/LCD_PRIVATE.h"
#include "../INCLUDE/HAL/LCD/LCD_CFG.h"


void HLCD_voidInit(void)
{
    MDIO_voidSetPortDirection(LCD_DATA_PORT, 0xFF);
    MDIO_voidSetPortValue(LCD_DATA_PORT, 0x00);

    MDIO_voidSetPortDirection(LCD_CONTROL_PORT, 0xFF);
    MDIO_voidSetPortValue(LCD_CONTROL_PORT, 0x00);

	_delay_ms(32);

	HLCD_voidSendCommand(FUNCTION_SET);

	_delay_ms(1);

	HLCD_voidSendCommand(DISPLAY_ON_OFF_CONTROL);

	_delay_ms(1);

	HLCD_voidSendCommand(DISPLAY_CLEAR);

	_delay_ms(2);

	HLCD_voidSendCommand(ENTRY_MODE_SET);

}

void HLCD_voidSendCommand(u8 A_u8Command)
{

	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_LOW);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);


	MDIO_voidSetPortValue(LCD_DATA_PORT,A_u8Command);


	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
}


void HLCD_voidSendData(u8 A_u8Data)
{

	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_HIGH);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);

	MDIO_voidSetPortValue(LCD_DATA_PORT,A_u8Data);

	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
		_delay_ms(2);
	MDIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
}



void HLCD_voidSendString(u8 *A_Pu8String)
{
	while(*A_Pu8String>0)
	{
		HLCD_voidSendData(*A_Pu8String++);
	}
}

void HLCD_voidClearDisplay(void)
{
	//Display Clear
	HLCD_voidSendCommand(DISPLAY_CLEAR);
	//wait for more than 1.53 ms
	_delay_ms(2);
}

void HLCD_voidGoToPos(LCD_ROWS A_LcdRowNo , LCD_COLS  A_LcdColNo)
{
	switch(A_LcdRowNo)
	{
	case ROW1: HLCD_voidSendCommand(LCD_ROW1_ADDRESS + A_LcdColNo); break;
	case ROW2: HLCD_voidSendCommand(LCD_ROW2_ADDRESS + A_LcdColNo); break;
	default: break;
	}
	_delay_ms(1);
}

void HLCD_voidDisplayNumberUNSigned(u32 A_u32Number)
{
	u32 local_u32Number=1;
	if(A_u32Number==0)
	{
		HLCD_voidSendData('0');
	}
	while(A_u32Number != 0)
	{
		local_u32Number = ((local_u32Number*10)+(A_u32Number %10));
		A_u32Number/=10;
	}
	while(A_u32Number != 1)
	{
		HLCD_voidSendData((local_u32Number%10)+48);
		local_u32Number/=10;
	}
}

 void HLCD_voidDisplayNumberSigned(s32 A_s32Number)
  {
   u32 local_u32Number=1;
   if(A_s32Number==0)
   {
      HLCD_voidSendData('0');
   }
   if (A_s32Number<0)
	{
		HLCD_voidSendData('-');
		A_s32Number *= -1;
	}

	while (A_s32Number != 0)
	{
		local_u32Number = ((local_u32Number*10)+ (A_s32Number%10));
		A_s32Number /= 10;
	}
	while (local_u32Number!= 1)
	{
		HLCD_voidSendData((local_u32Number%10)+48);
		local_u32Number /= 10;
	}
  }

void HLCD_voidSendSpecialCharacter(u8 *A_pu8PatternArr, u8 A_u8PatternNumber,LCD_ROWS A_LcdRowNo,LCD_COLS A_LcdColNo)
{
	u8 local_u8CGRamAdderss;
	local_u8CGRamAdderss = A_u8PatternNumber * 8;
	SET_BIT(local_u8CGRamAdderss,6);
	HLCD_voidSendCommand(local_u8CGRamAdderss);

	for(u8 i=0; i<8;i++)
	{
		HLCD_voidSendData(A_pu8PatternArr[i]);
	}

	HLCD_voidGoToPos(A_LcdRowNo,A_LcdColNo);
	HLCD_voidSendData(A_u8PatternNumber);
}


