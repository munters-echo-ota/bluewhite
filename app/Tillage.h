#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include "ImplementModule.h"
#include "I2CDevice.h"

class Tillage : public Implement, public I2CDevice
{
public:
	Tillage(ID Id) { _id = Id; }
	virtual ~Tillage() {}

	virtual void TurnOn()	{ SendControlCmd(true);  }
	virtual void TurnOff()  { SendControlCmd(false); }

private:
	Tillage(const Tillage&) = delete;
	Tillage & operator=(const Tillage&) = delete;

	static const int		POLLING_TIME_SEC = 1;
	static const uint8_t	TILAGE_DEVICE_I2C_ADDR = 0x10;

	virtual uint8_t GetI2CAddr() { return TILAGE_DEVICE_I2C_ADDR; }
	virtual long GetPollingTimeSec() { return POLLING_TIME_SEC; }
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) { ImplementModule::Instance()->OnTelemetry(GetId(), isOn, Level); }
};

