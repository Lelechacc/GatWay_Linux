#include "app_message.h"
#include <stdio.h>  // 加上这个，为了使用 printf
#include <stdlib.h> // 加上这个，为了使用 free
int main(int argc, char *argv[])
{

    uint8_t data[50] = {0x01, 0x02, 0x04, 0x32, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};

    char *json = app_message_BytesToJson(data, sizeof(data));
    printf("\n");

    log_info("解析出来的json数据是!!!!= %s", json);
    printf("\n");
    free(json);

    char *json2 = "{\"device_id\": 1, \"target_angle\":3600, \"max_speed\": 107}";

    uint8_t bytes_buf[50] = {0};
    int data_int = app_message_jsonToBytes(json2, bytes_buf, sizeof(bytes_buf));
    printf("解析过的json的数据是data_int = %d\n", data_int);
    for (size_t i = 0; i < data_int; i++) // 因为要打印成16进制所以，%02x ，这里的0指的是不足补0 ，X后面的空格指的是数据中间有空格//bytes:01 00 00 61 45 00 00 70 42
    {
        printf("%02x  ", bytes_buf[i]);
    }

    printf("\n");
    return 0;
}
