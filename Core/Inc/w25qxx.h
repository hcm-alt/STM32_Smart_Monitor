#ifndef __W25QXX_H
#define __W25QXX_H

#include "main.h"

void W25QXX_Init(void);

uint32_t W25QXX_ReadID(void);

void W25QXX_WriteEnable(void);
uint8_t W25QXX_ReadStatus(void);
void W25QXX_WaitBusy(void);
void W25QXX_SectorErase(uint32_t addr);

void W25QXX_PageProgram(uint32_t addr,uint8_t *data,uint16_t len);
void W25QXX_ReadData(uint32_t addr,uint8_t *data,uint16_t len);
#endif