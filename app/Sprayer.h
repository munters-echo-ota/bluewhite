#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include "ImplementModule.h"
#include "SPIDevice.h"

class Sprayer : public Implement, public SPIDevice
{
public:
	Sprayer(ID Id) { _id = Id; }
	virtual ~Sprayer() {}

	virtual void TurnOn()	{ SendControlCmd(true);  }
	virtual void TurnOff()  { SendControlCmd(false); }

private:
	Sprayer(const Sprayer&) = delete;
	Sprayer & operator=(const Sprayer&) = delete;

	static const int		POLLING_TIME_SEC = 8;
	static const SPI_DEV	SPRAYER_SPI_DEV = SPI_DEV_2;

	virtual SPI_DEV GetSPIDev() { return SPRAYER_SPI_DEV; }
	virtual long GetPollingTimeSec() { return POLLING_TIME_SEC; }
	virtual void OnTelemetry(bool isOn, Implement::FUEL_LEVEL Level) { ImplementModule::Instance()->OnTelemetry(GetId(), isOn, Level); }
};

