#include <pthread.h>
#include <unistd.h>
#include <log.h>
#include <stdio.h>

void first_thread(void)
{
    log_debug("子线程1创建成功，开始创建子线程，子线程标识为 %d\n", gettid());
}

void second_thread(void)
{
    log_debug("子线程2创建成功，开始创建子线程，子线程标识为 %d\n", gettid());
}
int main(int argc, char *argv[])
{

    log_debug("主线程创建成功，开始创建子线程，主线程标识为 %d\n", gettid());
    // 创建子线程的标识
    pthread_t pt1, pt2;

    // 创建子线程
    pthread_create(&pt1, NULL, first_thread, NULL);
    pthread_create(&pt2, NULL, second_thread, NULL);

    // int pthread_create(pthread_t * thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
    // log_debug("hello world");

    // 等分线程执行完毕
    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);
    log_debug("主线程结束！！标识为  %d",gettid()); // 主线程结束
    return 0;
}
