
#include <Arduino.h>
#include "HW_input.h"
#include "argButton.h"

void evenInput(uint8_t pin, uint8_t level);
void evenButton(uint8_t indentify, even_button_t status);

HW_input pin_0(0, LOW, evenInput);
argButton Button_1(1, LOW, evenButton);

void evenInput(uint8_t pin, uint8_t level)
{
	Button_1.changeLevel(level);
}
void evenButton(uint8_t indentify, even_button_t status)
{
	Serial.printf("\r\n===> id: %d, status %d\r\n", indentify, status);
}

void setup()
{
	Serial.begin(115200);
	Serial.setTimeout(10);

	pin_0.active(100);
}
void loop()
{
	delay(1);
}
