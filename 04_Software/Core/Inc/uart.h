/**
 ******************************************************************************
 * @file    bsp_aht21_driver.h
 * @author  山海照星河 && iswangxu150@163.com
 * @brief   Header file of aht21 module.
 * @version 1.0.0
 * @date    2025-03-09
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
#ifndef __uart_h
#define __uart_h
#include "stdint.h"

int init_uart(void);

int send_datas(uint8_t const *data, uint32_t const size);

int receive_datas(uint8_t *buff, uint32_t size, uint32_t *num);
#endif 

