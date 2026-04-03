#ifndef __AOO_MQTT_H__
#define __AOO_MQTT_H__

#include <MQTTClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"


#define ADDRESS "tcp://192.168.58.59:1883"
#define CLIENTID "b253ba38-daf6-4b37-984f-5d8fdc6a1cfa"
#define TOPIC_RTG "RTG"
#define TOPIC_GTR "GTR"
// #define PAYLOAD "Hello World!"  数据不是固定的 所以取消define
#define QOS 1
#define TIMEOUT 10000L
// 初始化客户端
int main(int argc, char *argv[]);

/**
 * @brief 初始化MQTT客户端
 *
 * @return int
 */
int app_mqtt_init();

/**
 * @brief 关闭MQTT客户端
 *
 * @return
 */
void app_mqtt_close(void);


/**
 * @brief 发送数据到MQTT服务器
 *
 * @return int
 */
int app_mqtt_send(char *json);

/**
 * @brief 接收处理远程消息的回调函数
 *
 * @return
 */
void app_mqtt_registercb(int (*callback)(char *json));
#endif /* __AOO_MQTT_H__ */
