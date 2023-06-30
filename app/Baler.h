#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include "ImplementModule.h"
#include "I2CDevice.h"

class Baler : public Implement, public I2CDevice
{
public:
	Baler(ID Id) { _id = Id; }
	virtual ~Baler() {}

	virtual void TurnOn()	{ SendControlCmd(true);  }
	virtual void TurnOff()  { SendControlCmd(false); }

private:
	Baler(const Baler&) = delete;
	Baler & operator=(const Baler&) = delete;

	static const int		POLLING_TIME_SEC = 3;
	static const uint8_t	BALER_DEVICE_I2C_ADDR = 0x20;

	virtual uint8_t GetI2CAddr() { return BALER_DEVICE_I2C_ADDR; }
	virtual long GetPollingTimeSec() { return POLLING_TIME_SEC; }
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) { ImplementModule::Instance()->OnTelemetry(GetId(), isOn, Level); }
};

