
#include <Arduino.h>
#include "HW_input.h"
#include "argButton.h"

void evenInput(uint8_t pin, uint8_t level);
void evenButton(uint8_t indentify, even_button_t status);

#define NumberButton 2
const uint8_t arrayPin[NumberButton] = {12, 13};
const uint8_t arrayIdButton[NumberButton] = {1, 2};

HW_input pin12(arrayPin[0], LOW, evenInput);
HW_input pin13(arrayPin[1], LOW, evenInput);
HW_input arrayInput[NumberButton] = {pin12, pin13};

argButton Button_1(arrayIdButton[0], LOW, evenButton);
argButton Button_2(arrayIdButton[1], LOW, evenButton);
argButton arrayButton[NumberButton] = {Button_1, Button_2};

void evenInput(uint8_t pin, uint8_t level)
{
	for (uint8_t i = 0; i < NumberButton; i++)
	{
		if (arrayPin[i] == pin)
			arrayButton[i].changeLevel(level);
	}
}
void evenButton(uint8_t indentify, even_button_t status)
{
	Serial.printf("\r\n===> id: %d, status %d\r\n", indentify, status);
}

void setup()
{
	Serial.begin(115200);
	Serial.setTimeout(10);

	for (uint8_t i = 0; i < NumberButton; i++)
	{
		arrayInput[i].active(80);
	}
}
void loop()
{
	delay(1);
}
