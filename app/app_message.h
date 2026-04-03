#ifndef __APP_MESSAGE_H__
#define __APP_MESSAGE_H__
#include "stdio.h"  //sprintf
#include "string.h"  //memcpy
#include "cJSON.h"
#include "log.h"
#include <stdint.h>
/** */
char *app_message_BytesToJson(uint8_t *bytes, int bytes_len);

/**
 * @brief json字符串转为字节数组
 *
 * @return int
 */
int app_message_jsonToBytes(char *json, uint8_t *bytes_buf, int buf_size);
#endif /* __APP_COMMON_H__ */
