#include "app_pool.h"
mqd_t mqd;
const char *lalaladuilie = "/mq_jgt";

static pthread_t *xianchen;
static int xianchen_num;

int app_pool_init(int size)
{
    // 初始化消息队列
    struct mq_attr attr;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = sizeof(JGT);
    if ((mqd = mq_open(lalaladuilie, O_CREAT | O_RDWR, 0666, &attr)) == -1)
    {
        log_debug("队列创建失败mq_open error");
        return -1;
    }
    // 初始化线程池
    xianchen = size;
    xianchen = (pthread_t *)malloc(sizeof(pthread_t) * size);
    if (xianchen_num == NULL)
    {
        perror("malloc");
        mq_unlink(xianchen);
        return -1;
    }
    for (int i = 0; i < size; i++)
    {
        pthread_create(&xianchen[i], NULL, thread_func, NULL);
    }

    return 0;
}

int app_pool_close()
{
    return 0;
}

int app_pool_register_JGT(int (*func)(void *), void *canshu)
{
    return 0;
}
