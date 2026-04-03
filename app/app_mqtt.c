#include "app_mqtt.h"

#define topicName pull
static MQTTClient client;
static MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer; // 连接的配置选项
static MQTTClient_message pubmsg = MQTTClient_message_initializer;                  //  消息对象
static int (*receive_callback)(char *json) = NULL;

// 发布主题成功的回调
static void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Bin发布主题完成!  \n" );
}
// 收到消息的回调
static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int result = 0;
    if (receive_callback != NULL)
    {
        result = receive_callback((char *)message->payload) == 0 ? 1 : 0;
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return result;
    // printf("Bin收到信息!\n");
    // printf("   主题为！  topic: %s\n", topicName);
    // printf("  内容为！ message: %.*s\n", message->payloadlen, (char *)message->payload);
    // MQTTClient_freeMessage(&message); // 释放主题 因为占用内存了
    // MQTTClient_free(topicName);       // 释放内容 因为占用内存了
    // return 1;                         // 返回1 代表成功
}
// 断开连接的回调函数
static void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("   断开的原因是因为！: %s\n", cause);
}

int app_mqtt_init()
{
    int result;
    // 1.初始化客户端
    if ((result = MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        log_error("初始化客户端失败！");
        return -1;
    }
    // 2.设置回调函数（连接断开的回调，发送完成的回调，收到消息的回调）
    if ((result = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        log_error("设置回调函数失败！");
        MQTTClient_destroy(&client); // 销毁客户端
        return -1;
    }
    // 3.启动客户端进行连接
    if ((result = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        log_error("连接服务器失败！");
        MQTTClient_destroy(&client); // 销毁客户端
        return -1;
    }
    // 4.订阅主题
    if ((result = MQTTClient_subscribe(client, TOPIC_RTG, QOS)) != MQTTCLIENT_SUCCESS)
    {
        log_error("订阅主题失败！");
        MQTTClient_destroy(&client); // 销毁客户端
        MQTTClient_disconnect(client, TIMEOUT);
        return -1;
    }

    log_debug("Bin ~客户端模块初始化成功！！！！");
    return 0;
};
void app_mqtt_close(void)
{
    // 1.取消订阅
    MQTTClient_unsubscribe(client, TOPIC_RTG);
    // 2.断开连接
    MQTTClient_disconnect(client, TIMEOUT);
    // 3.销毁客户端
    MQTTClient_destroy(&client);
}

int app_mqtt_send(char *json)
{
    // 将json保存到 pubmsg中
    pubmsg.payload = json;
    pubmsg.payloadlen = (int)strlen(json);
    pubmsg.qos = QOS;
    if (MQTTClient_publishMessage(client, TOPIC_GTR, &pubmsg, NULL) != MQTTCLIENT_SUCCESS)
    {
        log_error("Bin ~ 发送消息失败！");
    }

    log_debug("Bin ~ 发送消息成功!json : %s", json);

    return 0;
}

void app_mqtt_registercb(int (*callback)(char *json))
{
    receive_callback = callback;
}
