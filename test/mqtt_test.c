#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "cJSON.h"

#define ADDRESS "tcp://192.168.58.59:1883"
#define CLIENTID "b253ba38-daf6-4b37-984f-5d8fdc6a1cfa"
#define TOPIC_PULL "pull"
#define TOPIC_PUSH "push"
#define PAYLOAD "Hello World!"
#define QOS 1
#define TIMEOUT 10000L

static MQTTClient_message pubmsg = MQTTClient_message_initializer;
// 发布主题成功的回调
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Bin发布主题完成!  \n");
}
// 收到消息的回调
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Bin收到信息!\n");
    printf("   主题为！  topic: %s\n", topicName);
    printf("  内容为！ message: %.*s\n", message->payloadlen, (char *)message->payload);
    MQTTClient_freeMessage(&message); // 释放主题 因为占用内存了
    MQTTClient_free(topicName);       // 释放内容 因为占用内存了
    return 1;                         // 返回1 代表成功
}
// 断开连接的回调函数
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("   断开的原因是因为！: %s\n", cause);
}

int main(int argc, char *argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
                                MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto exit;
    }

    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }

    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n",
           TOPIC_PULL, CLIENTID, QOS);
    if ((rc = MQTTClient_subscribe(client, TOPIC_PULL, QOS)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to subscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    else
    {
        int ch;
        do
        {
            ch = getchar();
        } while (ch != 'Q' && ch != 'q');

        if ((rc = MQTTClient_unsubscribe(client, TOPIC_PULL)) != MQTTCLIENT_SUCCESS)
        {
            printf("Failed to unsubscribe, return code %d\n", rc);
            rc = EXIT_FAILURE;
        }
    }

    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    if ((rc = MQTTClient_publishMessage(client, TOPIC_PUSH, &pubmsg, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to publish message, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }

    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to disconnect, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    return rc;

destroy_exit:
    MQTTClient_destroy(&client);
exit:
    return rc;
}
