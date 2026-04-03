#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__

#include <sys/time.h>
#include "app_message.h"

#include "stdio.h"
#include "string.h"
#include "cJSON.h"
#include "log.h"
/**
 * @brief 获取当前时间毫秒数
 *
 * @return long
 */
long app_commen_getCurrentTime(void);
#endif /* __APP_COMMON_H__ */
