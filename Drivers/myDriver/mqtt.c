/*
 * mqtt.c
 *
 *  Created on: Apr 18, 2022
 *      Author: Satech
 */

#include "mqtt.h"

MQTT_TypeDef_t *MQTT_Conf;

void ESP8266_Init(UART_HandleTypeDef *_huart)
{
	ESP8266_Uart_t=_huart;


}

void MQTT_Init(MQTT_InitTypeDef_t *MQTT_Init)
{
	MQTT_TypeDef_t* MQTT_TypeStructure = (MQTT_TypeDef_t*) malloc(sizeof(MQTT_TypeDef_t));
	MQTT_TypeStructure->Connect = MQTT_Init->ConnectionType;
	MQTT_TypeStructure->RemainLength = (12 + strlen(MQTT_Init->ClientID)); // 12 stands for 2 + length<MQTT> + 6
	MQTT_TypeStructure->ProtocolNameLength[0]=0;
	MQTT_TypeStructure->ProtocolNameLength[1]=4;
	MQTT_TypeStructure->ProtocolName[0] = 'M';
	MQTT_TypeStructure->ProtocolName[1] = 'Q';
	MQTT_TypeStructure->ProtocolName[2] = 'T';
	MQTT_TypeStructure->ProtocolName[3] = 'T';
	MQTT_TypeStructure->Level = 0x04;
	MQTT_TypeStructure->Flag = MQTT_Init-> Flag;
	MQTT_TypeStructure->KeepAlive = MQTT_Init->KeepAlive;
	MQTT_TypeStructure->ClientIDLength = strlen(MQTT_Init->ClientID);
	MQTT_TypeStructure->ClientID = MQTT_Init->ClientID;
	MQTT_Conf = MQTT_TypeStructure;
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

void ESP8266_TcpConnect(char *Ip ,char *Port)
{

	char tcpFrame[150];
	uint8_t tcpFrameSize=0;
	tcpFrameSize = sprintf(tcpFrame,"AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",Ip,Port);
	UNUSED(tcpFrameSize);
	ESP8266_Uart(tcpFrame);
	HAL_Delay(1000);
}


void MQTT_ConnectBroker(char *Ip ,char *Port)
{
	char connectFrame[100]={0};
	char frameSizeInfo[100]={0};
	uint8_t connectFrameSize;
	ESP8266_Uart(CIPCLOSE);
	HAL_Delay(100);
	ESP8266_Uart(CIPMUX);
	HAL_Delay(100);
	ESP8266_Uart(CIFSR);
	HAL_Delay(100);

	ESP8266_TcpConnect(Ip,Port);

	//connectFrameSize = sprintf(connectFrame, "%c%c%c%c%s%c%c%c%c%c%c%s", (char)MQTT_Conf->Connect, (char)MQTT_Conf->RemainLength,(char)MQTT_Conf->ProtocolNameLength[0],(char)MQTT_Conf->ProtocolNameLength[1],(char*)MQTT_Conf->ProtocolName,(char)MQTT_Conf->Level,(char)MQTT_Conf->Flag,(char)0x00,(char)MQTT_Conf->KeepAlive,(char)MQTT_Conf->ClientIDLength,MQTT_Conf->ClientID);
	sprintf(frameSizeInfo,"AT+CIPSEND=%d\r\n",connectFrameSize);
	ESP8266_Uart(frameSizeInfo);
	HAL_Delay(500);
	ESP8266_Uart("ABC");
	HAL_Delay(5000);


}
