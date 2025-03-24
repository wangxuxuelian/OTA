/**
 ******************************************************************************
 * @file    Ymodem.h
 * @author  山海照星河 && iswangxu150@163.com
 * @brief   Header file of Ymodem module.
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
#ifndef __YMODEM_H
#define __YMODEM_H
 
/**
 * Log default configuration for EasyLogger.
 * NOTE: Must defined before including the <elog.h>
 */
#ifndef LOG_TAG
    #define LOG_TAG              "Ymodem_protocol"
#endif
#undef LOG_LVL
#ifdef YMODEM_LOG_LVL
    #define LOG_LVL              ELOG_LVL_DEBUG
#endif

/* Includes ------------------------------------------------------------------*/
#include "elog.h"
#include "stdint.h"
/* Exported types ------------------------------------------------------------*/
typedef int (*pf_port_receive_data)(uint8_t * const buff, uint32_t size);
typedef int (*pf_port_send_data)   (uint8_t * const buff, uint32_t size);

typedef int (*pf_port_save_data)   (uint8_t * const buff, uint32_t size);

typedef enum {
    SUCCESS = 0,                /*成功*/
    BUFFER_NOT_ENOUGH,          /*缓冲区不够用*/
    TIME_OUT,                   /*超时*/
    SEND_NOT_REACH,             /*发送方不可到达*/

    INVAILD_PRAMMENT,
    INTERNEL_ERR,      
} statu_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/



/* Exported functions ------------------------------------------------------- */

uint32_t ymodem_receive_file(uint8_t * const buff, uint32_t const size, \
                            pf_port_receive_data receive_fuction,       \
                            pf_port_send_data   write_fuction,           \
                            pf_port_save_data   save_fuction);



#endif /* __YMODEM_H */