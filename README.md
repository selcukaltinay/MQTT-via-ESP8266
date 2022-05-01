**MQTT via ESP8266**

*This library is not yet complete. But you can still make a TCP connection.*

Init Functions

``` c
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
```

Wifi and TCP Connection Functions

``` c
/**
  * @brief  Wifi connect function
  * @param  Wifi SSID
  * @param  Wifi Password
  * @retval void.
  */
void Wifi_Connect(char *SSID, char *pwd);


/**
  * @brief  This will be used for connect broker api.
  * @param  Ip address of mqtt broker.
  * @param  Port number of mqtt broker.
  * @retval void.
  */
void ESP8266_TcpConnect(char *Ip ,char *Port);
```

Mqtt Connection // I'm still trying to fix this function. Not taking echo when we send array after cipsend.

``` c
/**
  * @brief  This function can used for connect mqtt broker.
  * @param  Ip address of mqtt broker.
  * @param  Port number of mqtt broker.
  * @retval void.
  */
void MQTT_ConnectBroker(char *Ip ,char *Port);
```
