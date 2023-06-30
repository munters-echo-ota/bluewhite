#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { SPI_DEV_1, SPI_DEV_2, SPI_DEV_3 } SPI_DEV;
typedef enum { SPI_REG_STATE, SPI_REG_FUEL_LEVEL } SPI_REG;

void HAL_SPIInit();
void HAL_SPIWriteReg(SPI_DEV Dev, SPI_REG Reg, const void* Data, size_t DataLen);
void HAL_SPIReadReg(SPI_DEV Dev, SPI_REG Reg, void* Data, size_t DataLen);

#ifdef __cplusplus
}
#endif
