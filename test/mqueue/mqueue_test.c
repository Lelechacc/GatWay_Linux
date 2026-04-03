#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>
#include <pthread.h>
#include "log.h"
static const char *mq_Bin = "/mqueue_test";
static mqd_t mqd;
// 线程接收函数
void *thread1(void *arg)
{
    char buf[1024];
    sleep(1);

    // 接收消息
    int ret = mq_receive(mqd, buf, 1024, NULL);
    if (ret == -1)
    {
        log_error("mq_receive接收消息失败 error");
    }
    log_info("接收消息成功 %s", buf);

}

// 线程发送函数
void *thread2(void *arg)
{

    char *buf = "彬哥大帅比";
    // 发送消息
    int ret = mq_send(mqd, buf, strlen(buf) + 1, 0);
    if (ret == -1)
    {
        log_error("mq_send发送消息失败 error");
    }
    log_info("发送消息成功 %s", buf);
}

int main()
{
    // 队列属性
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    // 创建队列
    mqd = mq_open(mq_Bin, O_CREAT | O_RDWR, 0644, &attr);
    if (mqd == -1)
    {
        log_error("mq_open队列创建失败 error");
    }

    // 创建两个线程
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);
    sleep(2);
    // 关闭消息队列
    mq_close(mqd);
    return 0;
}
