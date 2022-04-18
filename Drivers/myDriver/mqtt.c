/*
 * mqtt.c
 *
 *  Created on: Apr 18, 2022
 *      Author: Satech
 */

#include "mqtt.h"



void ESP8266_Init(UART_HandleTypeDef *_huart)
{
	ESP8266_Uart_t=_huart;


}

void MQTT_Init(MQTT_InitTypeDef_t *MQTT_Init)
{
	MQTT_TypeDef_t* MQTT_TypeStructure = (MQTT_TypeDef_t*) malloc(sizeof(MQTT_TypeDef_t));
	MQTT_TypeStructure->Connect = MQTT_Init->ConnectionType;
	//MQTT_RemainLength->
	MQTT_TypeStructure->ProtocolName[0] = "M";
	MQTT_TypeStructure->Level = 0x04;
	MQTT_TypeStructure->Flag = MQTT_Init-> Flag;
}

HAL_StatusTypeDef ESP8266_Uart(char * const pData)
{
	uint16_t Size = (uint16_t) strlen(pData);
	HAL_StatusTypeDef returnStatement = HAL_UART_Transmit(ESP8266_Uart_t, (uint8_t*) pData, Size, HAL_MAX_DELAY);

	return returnStatement;
}

void Wifi_Connect(char *SSID, char *pwd)
{

	uint8_t tmpBuffer[50];
	uint8_t tmpSize = (uint8_t) sprintf(tmpBuffer,"AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, pwd);
	UNUSED(tmpSize);

	ESP8266_Uart(CWMODE);
	HAL_Delay(1000);
	ESP8266_Uart(CWQAP);
	HAL_Delay(1000);
	ESP8266_Uart(tmpBuffer);
	HAL_Delay(5000);

}


void MQTT_ConnectBroker(char *Ip ,char *Port)
{

}
