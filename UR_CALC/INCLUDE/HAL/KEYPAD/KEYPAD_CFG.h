/*
 * KEYPAD_CFG.h
 *
 *  Created on: Aug 26, 2026
 *      Author: ahmed
 */

#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_

#define KEYPAD_PORT PORTC

#define ROW0 PIN0
#define ROW1 PIN1
#define ROW2 PIN2
#define ROW3 PIN3

#define COL0 PIN4
#define COL1 PIN5
#define COL2 PIN6
#define COL3 PIN7

#define KEYPAD_ROWS {ROW0,ROW1,ROW2,ROW3}
#define KEYPAD_COLS {COL0,COL1,COL2,COL3}

#define KEYPAD_DEBOUNCE_DELAY 30


#endif /* INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_ */
