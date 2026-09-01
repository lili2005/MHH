/*
 * KEYPAD_PROGRAM.c
 *
 *  Created on: Aug 26, 2026
 *      Author: ahmed
 */


#include <util/delay.h>
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"

#include "../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_PRIVATE.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_CFG.h"


void KEYPAD_voidInit()
{

	MDIO_voidSetPinDirection(KEYPAD_PORT, COL0, DIO_OUTPUT);
	MDIO_voidSetPinDirection(KEYPAD_PORT, COL1, DIO_OUTPUT);
	MDIO_voidSetPinDirection(KEYPAD_PORT, COL2, DIO_OUTPUT);
	MDIO_voidSetPinDirection(KEYPAD_PORT, COL3, DIO_OUTPUT);

	MDIO_voidSetPinDirection(KEYPAD_PORT, ROW0, DIO_INPUT);
	MDIO_voidSetPinDirection(KEYPAD_PORT, ROW1, DIO_INPUT);
	MDIO_voidSetPinDirection(KEYPAD_PORT, ROW2, DIO_INPUT);
    MDIO_voidSetPinDirection(KEYPAD_PORT, ROW3, DIO_INPUT);


    MDIO_voidSetPortValue(KEYPAD_PORT, 0xFF);
}

u8 KEYPAD_u8GetPressedKey()
{
    u8 static G_u8ArrOfCols[COL_NO] = KEYPAD_COLS;
    u8 static G_u8ArrOfRows[ROW_NO] = KEYPAD_ROWS;
    u8 L_u8KeyValue = 255;

    for(u16 L_u8ColCounter = 0; L_u8ColCounter < COL_NO; L_u8ColCounter++)
    {

        for(u8 c = 0; c < COL_NO; c++)
        {
            MDIO_voidSetPinValue(KEYPAD_PORT, G_u8ArrOfCols[c],
                (c == L_u8ColCounter) ? DIO_LOW : DIO_HIGH);
        }

        for(u16 L_u8RowCounter = 0; L_u8RowCounter < ROW_NO; L_u8RowCounter++)
        {
            if(MDIO_pinValueGetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8RowCounter]) == KEYPAD_PRESSED)
            {
                _delay_ms(KEYPAD_DEBOUNCE_DELAY);

                if(MDIO_pinValueGetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8RowCounter]) == KEYPAD_PRESSED)
                {
                    L_u8KeyValue = Global_u8ArrOfKeyValue[L_u8RowCounter][L_u8ColCounter];

                    while(MDIO_pinValueGetPinValue(KEYPAD_PORT, G_u8ArrOfRows[L_u8RowCounter]) == KEYPAD_PRESSED);
                    return L_u8KeyValue;
                }
            }
        }
    }
    return L_u8KeyValue;
}
