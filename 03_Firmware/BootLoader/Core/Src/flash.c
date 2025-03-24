/**
  ******************************************************************************
  * @file    flash.c
  * @author  山海照星河 && iswangxu150@163.com
  * @brief   AHT21 device driver. Provide io fuctions.
  * @version 1.0.0
  * @date    2025-03-10
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c).
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
    @verbatim
  ==============================================================================
                    ##### Dht21 Peripheral features #####
  ==============================================================================





                    ##### How to use this driver #####
  ==============================================================================




    @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_flash.h"

/* Includes ------------------------------------------------------------------*/
#include "Flash.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

void Flash_Unlock(void) {
    FLASH_Unlock();
    while (FLASH_GetStatus() == FLASH_BUSY);
}

void Flash_Lock(void) {
    FLASH_Lock();
}

//擦除APP区域的数据
// f4是按扇区操作，计划将app放在扇区6  FLASH_Sector_6，备份app放在扇区7
FLASH_Status EreaseAppSector(uint32_t FLASH_Sector)
{
	Flash_Unlock();
	FLASH_Status FLASHStatus = FLASH_EraseSector(FLASH_Sector, VoltageRange_3);
	Flash_Lock();
	return FLASHStatus;
}


void Flash_Write(uint32_t address, uint32_t data) {
    // 解锁Flash
    Flash_Unlock();
    
    // 清除所有标志位
	  // FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
    
    // 编程一个字（32位）
    FLASH_Status status = FLASH_ProgramWord(address, data);
    
    // 检查编程是否成功
    if (status == FLASH_COMPLETE) {
        // 数据写入成功
			  // log_d("Flash_Write success"); 
    } else {
        // 数据写入失败
        // 在这里添加错误处理代码
			  //log_e("Flash_Write fail"); 
    }
    
    // 锁定Flash
    Flash_Lock();
}
