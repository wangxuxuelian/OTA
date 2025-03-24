/**
 ******************************************************************************
 * @file    flash.h
 * @author  山海照星河 && iswangxu150@163.com
 * @brief   Header file of aht21 module.
 * @version 1.0.0
 * @date    2025-03-10
 ******************************************************************************
 * @attention
 *
 * Copyright (c)
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_H
#define __FLASH_H
/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
FLASH_Status EreaseAppSector(uint32_t FLASH_Sector);
void Flash_Write(uint32_t address, uint32_t data);
#endif /* __FLASH_H */

