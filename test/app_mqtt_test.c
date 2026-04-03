#include "app_mqtt.h"
#include <unistd.h>

int receive_callback(char *json)
{
    log_debug("receive 中接收到消息为:%s", json);
    return 0;
}
int main(int argc, char *argv[])
{

    // 初始化mqtt
    app_mqtt_init();
    // 发送一个消息
    app_mqtt_send("\n{\"命令为\":\"发送\",\n\"数据为\":{\"Bin\":\"in_test\"}}");
    // 注册一个接受回调函数
    app_mqtt_registercb(receive_callback);
    // 睡眠是为了让其他客户端发送消息
    sleep(20);
    app_mqtt_close();

    return 0;
}
