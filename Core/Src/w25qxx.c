#include "w25qxx.h"

extern SPI_HandleTypeDef hspi1;
static void W25QXX_CS_Low(void)
{
    HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_RESET);
}

static void W25QXX_CS_High(void)
{
    HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_SET);
}

void W25QXX_Init(void)
{
	W25QXX_CS_High();
	HAL_Delay(10);
}

uint32_t W25QXX_ReadID(void)
{
    uint8_t tx[4] = {0x9F, 0xFF, 0xFF, 0xFF};
    uint8_t rx[4] = {0};

    /* 1. 选中Flash */
    W25QXX_CS_Low();

    /* 2. 发送命令，同时产生时钟接收数据 */
    HAL_SPI_TransmitReceive(&hspi1,
                            tx,
                            rx,
                            4,
                            HAL_MAX_DELAY);

    /* 3. 结束通信 */
    W25QXX_CS_High();

    /*
       rx[0]：发送0x9F期间收到的数据，无意义
       rx[1]：Manufacturer ID
       rx[2]：Memory Type
       rx[3]：Capacity
    */

    return ((uint32_t)rx[1] << 16)
         | ((uint32_t)rx[2] << 8)
         |  (uint32_t)rx[3];
}

void W25QXX_WriteEnable(void)
{
	uint8_t cmd = 0x06;
	W25QXX_CS_Low();
	HAL_SPI_Transmit(&hspi1,&cmd,1,HAL_MAX_DELAY);
	W25QXX_CS_High();
}

uint8_t W25QXX_ReadStatus(void)
{
	uint8_t cmd = 0x05;
	uint8_t status = 0;
	W25QXX_CS_Low();
	HAL_SPI_Transmit(&hspi1,&cmd,1,HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi1,&status,1,HAL_MAX_DELAY);
	W25QXX_CS_High();
	return status;
}

void W25QXX_WaitBusy(void)
{
	while(W25QXX_ReadStatus() & 0x01){}
}

void W25QXX_SectorErase(uint32_t addr)
{
	uint8_t cmd[4] ;
	
	W25QXX_WriteEnable();
	cmd[0] = 0x20;
	cmd[1] = (addr >> 16) & 0xFF;
	cmd[2] = (addr >> 8) & 0xFF;
	cmd[3] = addr & 0xFF;
	W25QXX_CS_Low();
  HAL_SPI_Transmit(&hspi1,cmd,4,HAL_MAX_DELAY);
  W25QXX_CS_High();
  W25QXX_WaitBusy();	
}

void W25QXX_PageProgram(uint32_t addr,uint8_t *data,uint16_t len)
{
	uint8_t cmd[4];
	W25QXX_WriteEnable();
	cmd[0] = 0x02;
	cmd[1] = (addr >> 16) & 0xFF;
	cmd[2] = (addr >> 8) & 0xFF;
	cmd[3] =  addr & 0xFF;
	W25QXX_CS_Low();
	HAL_SPI_Transmit(&hspi1,cmd,4,HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi1,data,len,HAL_MAX_DELAY);
	W25QXX_CS_High();
	W25QXX_WaitBusy();
}

void W25QXX_ReadData(uint32_t addr,uint8_t *data,uint16_t len)
{
    uint8_t cmd[4];
    cmd[0] = 0x03;
    cmd[1] = (addr >> 16) & 0xff;
    cmd[2] = (addr >> 8) & 0xff;
    cmd[3] = addr & 0xff;
    W25QXX_CS_Low();
    HAL_SPI_Transmit(&hspi1,cmd,4,HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1,data,len,HAL_MAX_DELAY);
    W25QXX_CS_High();
}