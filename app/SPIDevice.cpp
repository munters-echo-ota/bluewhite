#include "SPIDevice.h"
#include "ImplementModule.h"
#include <chrono>
#include <thread>

SPIDevice::SPIDevice() : _quit(false), _thread(&SPIDevice::ThreadFunc, this)
{
	HAL_SPIInit();
}

SPIDevice::~SPIDevice()
{
	_quit = true;
	_thread.join();
}

void SPIDevice::ThreadFunc()
{
	SPI_DEV dev = GetSPIDev();

	while (!_quit)
	{
		std::this_thread::sleep_for(std::chrono::seconds(GetPollingTimeSec()));
		int state = 0;
		Implement::FUEL_LEVEL level = 0;
		{
			std::unique_lock<std::mutex> lock(_mutex);

			HAL_SPIReadReg(dev, SPI_REG_STATE, &state, sizeof(state));
			HAL_SPIReadReg(dev, SPI_REG_FUEL_LEVEL, &level, sizeof(level));
		}

		OnTelemetry(state != 0, level);
	}
}

void SPIDevice::SendControlCmd(bool isOn)
{
	std::unique_lock<std::mutex> lock(_mutex);

	uint8_t onOff = isOn ? 1 : 0;
	HAL_SPIWriteReg(GetSPIDev(), SPI_REG_STATE, &onOff, sizeof(onOff));
}
