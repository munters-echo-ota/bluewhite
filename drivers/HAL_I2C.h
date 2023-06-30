#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { I2C_REG_STATE, I2C_REG_FUEL_LEVEL } I2C_REG;

void HAL_I2CInit();
void HAL_I2CWriteData(uint8_t Addr, I2C_REG Reg, const void* Msg, size_t MsgLen);
void HAL_I2CReadData(uint8_t Addr, I2C_REG Reg, void* Msg, size_t MsgLen);

#ifdef __cplusplus
}
#endif
