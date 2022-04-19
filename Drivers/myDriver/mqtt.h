/*
 * mqtt.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Satech
 */

#ifndef MYDRIVER_INC_MQTT_H_
#define MYDRIVER_INC_MQTT_H_

#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include <string.h>
#include <stdlib.h>

UART_HandleTypeDef *ESP8266_Uart_t;

/**
  * User defined macros for at command set.
  *
  */

#define CWMODE 				"AT+CWMODE=1\r\n"
#define CWMODE_Length 		strlen(CWMODE)
#define CWQAP 				"AT+CWQAP\r\n"
#define CWQAP_Length 		strlen(CWQAP)
#define CIPCLOSE 			"AT+CIPCLOSE\r\n"
#define CIPCLOSE_Length 	strlen(CIPCLOSE)
#define CIPMUX 				"AT+CIPMUX=0\r\n"
#define CIPMUX_Length 		strlen(CIPMUX)
#define CIFSR 				"AT+CIFSR\r\n"
#define CIFSR_Length 		strlen(CIFSR)
#define CIPSEND 			"AT+CIPSEND="
#define CIPSEND_Length 		strlen(CIPSEND)

/*
 * MQTT_Init_Connection_MACROS
 *
 */
#define MQTT_Connect    0x10
#define MQTT_Publish 	0x30
#define MQTT_Subscribe  0x82


/*
 * MQTT_TypeDef_Flag_MACROS
 *
 */
#define MQTT_Flag_CleanSession 0x02
#define MQTT_Flag_WillFlag	   0x04
#define MQTT_Flag_WillQoS	   0x08
#define MQTT_Flag_WillRetain   0x10
#define MQTT_Flag_PasswordFlag 0x20
#define MQTT_Flag_UserNameFlag 0x40


/**
  * MQTT connection frame
  * This frame will be send over TCP/IP
  *
  */

typedef struct{
	uint8_t Connect;				// Connect and Remain Length Bytes(2byte) named as "Fixed Header".
	uint8_t RemainLength;			// Remained Length is hex format of remained byte number after this byte.
	uint8_t ProtocolNameLength[2]; // 16 bit length of protocol name. For MQTT, this variable setted as 0x04.
	char ProtocolName[4];		// For us, "MQTT".
	uint8_t Level;					// 0x04.
	uint8_t Flag;					// Connect Flag Bits. For unsafety connection, use 0x02. @tag MQTT_TypeDef_Flag_MACROS
	uint16_t KeepAlive;				// By Default 60.
	uint16_t ClientIDLength;		// This one will be user defined. Client ID Length.
	char *ClientID;				// Client ID. User Defined.
}MQTT_TypeDef_t;




/**
  * MQTT init type definition
  *
  */

typedef struct{
	uint8_t ConnectionType; // This parameter can be used for select connection type. @tag MQTT_Init_Connection_MACROS
	uint16_t KeepAlive; 	 // This parameter can be used for determine keep alive duration. By default 60.
	uint8_t QoS;			 // This parameter can be used for determine Quality of Services. As a parameter, it can be use 0,1 and 2. (0x00 for test)
	uint8_t Flag;			 //Connect Flag Bits. For unsafety connection, use 0x02. @tag MQTT_TypeDef_Flag_MACROS
	char* ClientID;
}MQTT_InitTypeDef_t;


/**
  * @brief  To use this library, we should use this function firstly.
  * @param  UART_HandleTypeDef.
  * @retval void.
  */
void ESP8266_Init(UART_HandleTypeDef *_huart);


/**
  * @brief  This function assign the MQTT_InitTypeDef_t parameter through
  * @param  UART_HandleTypeDef.
  * @retval void.
  */
void MQTT_Init(MQTT_InitTypeDef_t *MQTT_Init);


/**
  * @brief  Uart transmit callback function.
  * @param  Data which will be transfered.
  * @retval HAL_StatusTypeDef.
  */
HAL_StatusTypeDef ESP8266_Uart(char * const pData);


/**
  * @brief  Wifi connect function
  * @param  Wifi SSID
  * @param  Wifi Password
  * @retval void.
  */
void Wifi_Connect(char *SSID, char *pwd);


/**
  * @brief  This function can used for connect mqtt broker.
  * @param  Ip address of mqtt broker.
  * @param  Port number of mqtt broker.
  * @retval void.
  */
void MQTT_ConnectBroker(char *Ip ,char *Port);


/**
  * @brief  This will be used for connect broker api.
  * @param  Ip address of mqtt broker.
  * @param  Port number of mqtt broker.
  * @retval void.
  */
void ESP8266_TcpConnect(char *Ip ,char *Port);



#endif /* MYDRIVER_INC_MQTT_H_ */
