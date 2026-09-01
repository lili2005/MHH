/*
 * main.c
 *
 *  Created on: Aug 26, 2026
 *      Author: ahmed
 */

#include <util/delay.h>
#include "../INCLUDE/LIB/STD_TYPES.h"
#include "../INCLUDE/LIB/BIT_MATH.h"
#include "../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../INCLUDE/HAL/LCD/LCD_INTERFACE.h"


u64* str2int (u8 *stParameter, u16 numOfOperations)
{
    u16 valueDigit = 0, lengthNumber = 0;
    u64 valueNumber = 0;
    static u64 Parameters[10];

    for(u16 i = 0; i <= numOfOperations; i++)
    {
        valueNumber = 0;
        lengthNumber = 0;
        for(u16 j = 0; j < 20; j++)
        {
            if(stParameter[i*11 + j] == '\0'){ break; }
            else{ lengthNumber++; }
        }
        for(u16 j = 1;  j <= lengthNumber; j++)
        {
            valueDigit = (u16)(stParameter[i*11 + j-1] - '0');
            valueNumber = (valueNumber * 10) + valueDigit;
        }
        Parameters[i] = valueNumber;
    }
    return Parameters;
}

u8 *int2str(s64 Result)
{
    u16 digit;
    static u8 stResult[20];
    u8 temp[20];
    u16 tempIndex = 0, stResultIndex = 0;
    u8 isNegative = 0;

    if(Result == 0)
    {
        stResult[0] = '0';
        stResult[1] = '\0';
        return stResult;
    }

    if(Result < 0)
    {
        isNegative = 1;
        Result = -Result;
    }

    while(Result != 0)
    {
        digit = Result % 10;
        temp[tempIndex] = '0' + digit;
        tempIndex++;
        Result /= 10;
    }

    if(isNegative)
    {
        stResult[stResultIndex] = '-';
        stResultIndex++;
    }

    while(tempIndex > 0)
    {
        tempIndex--;
        stResult[stResultIndex] = temp[tempIndex];
        stResultIndex++;
    }

    stResult[stResultIndex] = '\0';
    return stResult;
}

s64 sum(s64 x ,s64 y){return x+y;}
s64 sub(s64 x ,s64 y){return x-y;}
s64 mul(s64 x ,s64 y){return x * y;}
s64 div(s64 x ,s64 y)
{
	if (y == 0)
	{
		return 0xFFFF ;
	}
	return x / y;
}

s64 calculate(u64 *Parameter, u8* Operation, u8 numOfOperations)
{
	u64 Result = Parameter[0];

	for(int i = 0; i < numOfOperations; i++)
	{
		switch(Operation[i])
		{
		case '+':
			Result = sum(Result, Parameter[i+1]);
			break;
		case '-':
			Result = sub(Result, Parameter[i+1]);
			break;
		case '/':
			Result = div(Result, Parameter[i+1]);
			break;
		case '*':
			Result = mul(Result, Parameter[i+1]);
			break;
		}
		if(Result == 0xFFFF){break;}
	}
	return Result;
}

int main()
{
	HLCD_voidInit();
	KEYPAD_voidInit();

	HLCD_voidSendString("WELCOME");
	_delay_ms(1000);
	HLCD_voidClearDisplay();

	u8 stParameter[10][11], Operation[10];
	u64 *Parameter;

	s64 Result;
	u8 key;

	u8 numOfOperations = 0, numOfParameters = 0, ParameterIndex = 0, numOfchars = 0;

	while(1)
	{
		key = KEYPAD_u8GetPressedKey();
		switch(key)
		{
		case 255: break;
		case 'c':
		{
			HLCD_voidClearDisplay();

			numOfOperations = 0;
			numOfParameters = 0;
			ParameterIndex = 0;
			numOfchars = 0;

			break;
		}
		case '=':
		{
			HLCD_voidClearDisplay();
			HLCD_voidSendData('=');

			Parameter = str2int(stParameter, numOfOperations);
			Result = calculate(Parameter, Operation, numOfOperations);

			if(Result == 0xFFFF)
			{
				HLCD_voidSendString("ER: DIV BY 0");
			}
			else if(numOfParameters != numOfOperations + 1)
			{
				HLCD_voidSendString("ER: INSUF PARAs");
			}
			else
			{
				u8* stResult = int2str(Result);
				HLCD_voidSendString(stResult);
			}
			numOfOperations = 0;
			numOfParameters = 0;
			ParameterIndex = 0;
			numOfchars = 0;

			while(KEYPAD_u8GetPressedKey() == 255){}

			HLCD_voidClearDisplay();
			break;
		}
		case '+':
		case '-':
		case '/':
		case '*':
		{
			if(numOfOperations < 9)
			{
			    numOfchars++;
			    if(numOfchars > 16){ HLCD_voidClearDisplay(); numOfchars = 0; }

			    Operation[numOfOperations] = key;
			    HLCD_voidSendData(key);
			    numOfOperations++;
			    ParameterIndex = 0;
			}
			break;
		}
		default:
		{
			if(ParameterIndex < 10)
			{
			    numOfchars++;
			    if(numOfchars > 16){ HLCD_voidClearDisplay(); numOfchars = 0; }

			    HLCD_voidSendData(key);
			    stParameter[numOfOperations][ParameterIndex] = key;
			    ParameterIndex++;
                stParameter[numOfOperations][ParameterIndex] = '\0';

                if(ParameterIndex == 1)
                {
                    numOfParameters++;
                }
			}
			break;
		}
		}
	}
    return 0;
}

