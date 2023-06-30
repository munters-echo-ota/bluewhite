#include "I2CDevice.h"
#include "ImplementModule.h"
#include "HAL_I2C.h"
#include <chrono>
#include <thread>

I2CDevice::I2CDevice() : _quit(false), _thread(&I2CDevice::ThreadFunc, this)
{
	HAL_I2CInit();
}

I2CDevice::~I2CDevice()
{
	_quit = true;
	_thread.join();
}

void I2CDevice::ThreadFunc()
{
	uint8_t addr = GetI2CAddr();

	while (!_quit)
	{
		std::this_thread::sleep_for(std::chrono::seconds(GetPollingTimeSec()));
		int state = 0;
		Implement::FUEL_LEVEL level = 0;
		{
			std::unique_lock<std::mutex> lock(_mutex);

			HAL_I2CReadData(addr, I2C_REG_STATE, &state, sizeof(state));
			HAL_I2CReadData(addr, I2C_REG_FUEL_LEVEL, &level, sizeof(level));
		}

		OnTelemetry(state != 0, level);
	}
}

void I2CDevice::SendControlCmd(bool isOn)
{
	std::unique_lock<std::mutex> lock(_mutex);

	uint8_t onOff = isOn ? 1 : 0;
	HAL_I2CWriteData(GetI2CAddr(), I2C_REG_STATE, &onOff, sizeof(onOff));
}
