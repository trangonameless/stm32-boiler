/*
 * seg7.c
 *
 *  Created on: Sep 23, 2025
 *      Author: patry
 */
#include <stdbool.h>
#include "seg7.h"
#include "gpio.h"

static uint32_t actual_value;
static uint32_t active_digit;
extern volatile int set_temp;

static void set_output(uint8_t mask)

{

	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, mask & 0x01);

	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, mask & 0x02);

	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, mask & 0x04);

	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, mask & 0x08);

	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, mask & 0x10);

	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, mask & 0x20);

	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, mask & 0x40);

}


void seg7_show_digit(uint32_t value)
{
	switch (value % 10) {
	case 0:
		set_output(0b0111111);
		break;
	case 1:
		set_output(0b0000110);
		break;
	case 2:
		set_output(0b1011011);
		break;
	case 3:
		set_output(0b1001111);
		break;
	case 4:
		set_output(0b1100110);
		break;
	case 5:
		set_output(0b1101101);
		break;
	case 6:
		set_output(0b1111101);
		break;
	case 7:
		set_output(0b0000111);
		break;
	case 8:
		set_output(0b1111111);
		break;
	case 9:
		set_output(0b1101111);
		break;
	}
}

void seg7_show(uint32_t value)

{

	actual_value = value;
}

void seg7_update(void)
{
    HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_SET);

    if (active_digit == 0) {
        // dziesiątki
        seg7_show_digit(set_temp / 10);
        HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
        active_digit = 1;
    } else {
        // jedności
        seg7_show_digit(set_temp % 10);
        HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
        active_digit = 0;
    }
}

