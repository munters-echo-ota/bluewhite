#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include "HAL_SPI.h"
#include <thread>
#include <mutex>

class SPIDevice
{
public:
	virtual ~SPIDevice();

	virtual SPI_DEV GetSPIDev() = 0;
	virtual long GetPollingTimeSec() = 0;
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) = 0;

protected:
	SPIDevice();

	void ThreadFunc();
	void SendControlCmd(bool isOn);

	bool volatile	_quit;
	std::thread		_thread;
	std::mutex		_mutex;
};

