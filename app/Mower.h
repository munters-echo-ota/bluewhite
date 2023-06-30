#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include "ImplementModule.h"
#include "SPIDevice.h"

class Mower : public Implement, public SPIDevice
{
public:
	Mower(ID Id) { _id = Id; }
	virtual ~Mower() {}

	virtual void TurnOn()	{ SendControlCmd(true);  }
	virtual void TurnOff()  { SendControlCmd(false); }

private:
	Mower(const Mower&) = delete;
	Mower & operator=(const Mower&) = delete;

	static const int		POLLING_TIME_SEC = 2;
	static const SPI_DEV	MOWER_SPI_DEV = SPI_DEV_1;

	virtual SPI_DEV GetSPIDev() { return MOWER_SPI_DEV; }
	virtual long GetPollingTimeSec() { return POLLING_TIME_SEC; }
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) { ImplementModule::Instance()->OnTelemetry(GetId(), isOn, Level); }
};

