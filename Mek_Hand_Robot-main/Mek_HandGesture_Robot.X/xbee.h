/* 
 * File:   xbee.h
 * Author: Elvar Ágúst Ólafsson
 *


#include "system_init.h"
#include "uart.h"


/*****************XBEE FRAME- REGISTER MAP******/
#define START_DELIMITER                     0x7E
#define AT_COMMAND_FRAME                    0x08
#define TRANSMIT_REQUEST_FRAME              0x10
#define REMOTE_AT_COMMAND_FRAME             0x17
#define IO_DATA_SAMPLE_FRAME                0x92
#define AT_COMMAND_RESPONSE_FRAME           0x88
#define REMOTE_AT_COMMAND_RESPONSE_FRAME    0x97
#define RECEIVE_PACKET_FRAME                0x90
#define TRANSMIT_STATUS_FRAME               0x8B

#define FRAME_ID                            0x01
#define REMOTE_AT_COMMAND_OPT               0x02
#define TRANSMIT_REQUEST_OPT                0x00
#define TRANSMIT_REQUEST_BROADCAST_RADIUS   0x00



/**
 * @brief   This function Initates XBee Transmiter & receiver
 *          -Set Start delimiter
 *          -query or set command parameters 
 *          -Delivery status 

 * @param         
 * @return  void
 * 
 */