#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include <thread>
#include <mutex>

class I2CDevice
{
public:
	virtual ~I2CDevice();

	virtual uint8_t GetI2CAddr() = 0;
	virtual long GetPollingTimeSec() = 0;
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) = 0;

protected:
	I2CDevice();

	void ThreadFunc();
	void SendControlCmd(bool isOn);

	bool volatile	_quit;
	std::thread		_thread;
	std::mutex		_mutex;
};

