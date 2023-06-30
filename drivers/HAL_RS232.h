#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void HAL_RS232Init();
int HAL_RS232WaitForByte(int TimeoutSec, uint8_t* Byte);
void HAL_RS232SendBuff(const uint8_t* Buff, size_t Len);

#ifdef __cplusplus
}
#endif
