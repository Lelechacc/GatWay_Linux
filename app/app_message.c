#include "app_message.h"

char *app_message_BytesToJson(uint8_t *bytes, int bytes_len)
{
    // 1.从字节数组中提取数据
    // 01 00 00 61 45 01 00  ->
    //  {"device_id ": 1 ,"motor_status":"on" ,"cur_angle":"  3600.0"}


    // 1.从字节数组中提取数据
    int device_id = bytes[0];
    char *motor_status = bytes[5] == 0 ? "off" : "on"; //数据的第五位是状态为0就是off
    float cur_angle = 0.0;
    memcpy(&cur_angle, bytes + 1, 4); //当前角度是一个float  向右移一位所以+1
    char cur_angle_str[9]; //整数6为 小位1位 结束符1位 0-8  共九位
    sprintf(cur_angle_str, "%8.1f", cur_angle);
    // 2，生成json

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "device_id", device_id);
    cJSON_AddStringToObject(root, "motor_status", motor_status);
    cJSON_AddStringToObject(root, "cur_angle", cur_angle_str);
    char *json = cJSON_Print(root);
    // 3.释放内存

    cJSON_Delete(root);

    // 4.返回json消息
    return json;
}

int app_message_jsonToBytes(char *json, uint8_t *bytes_buf, int buf_size)
{

    if (buf_size < 9)
    {
        log_error("buf_size < 9");
        return -1;
    }

    // 从JSON 中解析提取数据​‌‍⁠​{"device_id ": 1 ,"target_angle":3600 ,"max_speed":60}

    //  01 00 00 61 45 00 00 70 42
    // 创建一个JSON对象
    cJSON *root = cJSON_Parse(json);
    // 解析device_id
    uint8_t device_id = cJSON_GetObjectItem(root, "device_id")->valueint;
    float target_angle = cJSON_GetObjectItem(root, "target_angle")->valueint;
    float max_speed = cJSON_GetObjectItem(root, "max_speed")->valueint;

    bytes_buf[0] = device_id;
    memcpy(bytes_buf + 1, &target_angle, 4);
    memcpy(bytes_buf + 5, &max_speed, 4);
    // 释放内存

    cJSON_Delete(root);
    return 9;
}
