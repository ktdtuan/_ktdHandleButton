#include "argButton.h"

void argButton::check(void)
{
	// if callback is null then no work
	if (_cb == NULL)
	{
		_btWorkStatus = _waitEven;
		return;
	}

	// wait for next step. but report current step
	switch (_btWorkStatus)
	{
	case _waitEven:
		break;
	case _pressFirst:
		_cb(_id, EVEN_BUTTON_PRESS);
		break;
	case _releaseFirst:
		if (_cnt == 0)
			_cb(_id, EVEN_BUTTON_RELEASE);
		if (_cnt == 1)
			_cb(_id, EVEN_BUTTON_CLICK);
		if (_cnt == 2)
			_cb(_id, EVEN_BUTTON_DOUBLE_CLICK);
		break;
	case _pressUnknow:
		// _cb(_id, EVEN_BUTTON_UNKNOW);
		break;
	default:
		// _cb(_id, EVEN_BUTTON_UNKNOW);
		break;
	}

	// refresh value _btWorkStatus
	_btWorkStatus = _waitEven;
}

void argButton::changeLevel(uint8_t status)
{
	// static variable
	static int8_t _statusOld = -1;
	static uint32_t _startTime = -1;

	// variable cacullator now
	uint32_t now = millis();
	uint32_t waitTime = (now - _startTime);
	_startTime = now;

	// set timeout callback
	if (_statusOld != status)
	{
		_statusOld = status;
		_tick->once_ms<void *>(_clickTicks + 50, [](void *arg){ ((argButton *)(arg))->check(); },this);
	}

	// handle status button
	switch (_btWorkStatus)
	{
	case _waitEven:
		if (_level == status)
			_btWorkStatus = _pressFirst;
		else
			_btWorkStatus = _releaseFirst;

		_cnt = 0;
		break;
	case _pressFirst:
		if (waitTime < _clickTicks)
		{
			_cnt += 1;
			_btWorkStatus = _releaseFirst;
		}
		else
			_btWorkStatus = _pressUnknow;
		break;
	case _releaseFirst:
		if (_cnt == 0)
			_btWorkStatus = _pressUnknow;
		else
			_btWorkStatus = _pressFirst;
		break;
	case _pressUnknow:
		break;
	default:
		break;
	}
}