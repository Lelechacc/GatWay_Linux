#ifndef __APP_POOL_H__
#define __APP_POOL_H__

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <log.h>

// 任务结构体
typedef struct
{
    int (*hanshu)(void *); // 任务函数
    void *canshu;          // 任务参数
} JGT;

/**
 * @brief 初始化线程池(同时创建消息队列)
 * @param size 线程池大小
 * @return int 0:成功 -1:失败
 */
int app_pool_init(int size);

/**
 * @brief 关闭线程池
 * @return int 0:成功 -1:失败
 */
int app_pool_close();

/**
 * @brief 向线程池中添加任务
 * @param func 任务函数
 * @param argv 任务参数
 */
int app_pool_register_JGT(int (*func)(void *), void *canshu);

#endif /* __APP_POOL_H__ */

