#ifndef __ARG_BUTTON_H_
#define __ARG_BUTTON_H_

#include "Arduino.h"
#include "Ticker.h"

typedef enum
{
	EVEN_BUTTON_UNKNOW = 0,
	EVEN_BUTTON_CLICK = 1,		  //__|''|_________
	EVEN_BUTTON_DOUBLE_CLICK = 2, //__|''|__|''|___
	EVEN_BUTTON_PRESS = 3,		  //____|''
	EVEN_BUTTON_RELEASE = 4		  //''''|__
} even_button_t;

typedef std::function<void(uint8_t indentify, even_button_t status)> fButtonReport;

class argButton
{
private:
	//định nghĩa nút nhấn
	uint8_t _id;
	uint8_t _level;
	fButtonReport _cb;

	// variable support
	int8_t _cnt = 0;
	Ticker *_tick;
	uint32_t _clickTicks = 400;

	enum
	{
		_waitEven,
		_pressFirst,
		_releaseFirst,
		_pressUnknow,
	} _btWorkStatus;

	void check(void);

public:
	argButton(uint8_t indentify, uint8_t lv_active, fButtonReport cb) : _id(indentify), _level(lv_active), _cb(cb)
	{
		_tick = new Ticker;
	}
	~argButton()
	{
		delete _tick;
	}

	void changeLevel(uint8_t status);

	void setTimeClick(uint32_t ticks)
	{
		_clickTicks = ticks;
	}
};

#endif