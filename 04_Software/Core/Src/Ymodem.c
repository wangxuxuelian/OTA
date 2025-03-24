/**
  ******************************************************************************
  * @file    Ymodem.c
  * @author  山海照星河 && iswangxu150@163.com
  * @brief   Implement the protocol of Ymodem.
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
#include "Ymodem.h"


/* Private define ------------------------------------------------------------*/

/*Ymodem protocol commands*/
#define CMD_SOH (0x01)
#define CMD_STX (0x02)
#define CMD_EOT (0x04)
#define CMD_ACK (0x06)
#define CMD_NAK (0x15)
#define CMD_CA  (0x18)
#define CMD_C   (0x43)
/* Private typedef -----------------------------------------------------------*/
typedef enum {
    IDLE = 0,
    RECEIVING,
    ERROR,
} status_t;
typedef enum {
    START_FRAME = 0,
    DATA_FRAME,
    END_FRAME,
} frame_t;

typedef struct ymodem {
    status_t statu;

}ymodem_t;





/* Private macro -------------------------------------------------------------*/
#define START_FRAME_SIZE   (133)
#define DATA_FRAME_SIZE_1  (133)
#define DATA_FRAME_SIZE_2  (1029)
#define END_FRAME_SIZE     (133)

/* Private variables ---------------------------------------------------------*/
static pf_port_receive_data g_receive;
static pf_port_send_data      g_write;
static pf_port_save_data       g_save;
static ymodem_t g_ymodem;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void send_cmd(uint8_t cmd)
{
    uint8_t CMD = cmd;
    g_write(&CMD, 1);
}

static int get_frame(uint8_t *const buff, uint32_t size, frame_t type)
{
    int ret_val = 0;

    if ((type == DATA_FRAME) && (size < DATA_FRAME_SIZE_2)) {
        return -1;
    }
    if ((type == START_FRAME) && (size < START_FRAME_SIZE)) {
        return -1;
    }
    if ((type == END_FRAME) && (size < END_FRAME_SIZE)) {
        return -1;
    }

    ret_val = g_receive(buff, size);

    return ret_val;
}






/* extern variables ---------------------------------------------------------*/

/* extern fuctions ---------------------------------------------------------*/
uint32_t ymodem_receive_file(uint8_t * const buff, uint32_t const size, \
    pf_port_receive_data receive_fuction,       \
    pf_port_send_data   write_fuction,           \
    pf_port_save_data   save_fuction)
{
    uint8_t tmp_buff[DATA_FRAME_SIZE_2];
    uint32_t ret_val = 0;
    uint32_t count = 0;
    uint32_t i = 0;

    if ((NULL == buff) | (0 == size)) {
        return INVAILD_PRAMMENT;
    }

    if ((NULL != g_receive) || (NULL != g_write) || \
        (NULL != g_save)) {
        return INTERNEL_ERR;
    }

    g_receive      = receive_fuction;
    g_write        =   write_fuction;
    g_save         =    save_fuction;
    g_ymodem.statu =            IDLE;

    /* start transfer*********************/
    while (1) {
        send_cmd(CMD_C);
        if (g_receive(tmp_buff, START_FRAME_SIZE) == START_FRAME_SIZE) {
            send_cmd(CMD_ACK);
            
            break;      
        }
        i++;
        if (i == 1) {
            ret_val = SEND_NOT_REACH;
            return ret_val;
        }
    }
    
    /*get a start frame data***************/

    


}