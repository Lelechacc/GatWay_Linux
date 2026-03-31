#include "app_common.h" // 因为在vscode里面设置好了 让头文件自动搜索，所以这里不需要写路径
#include "log.h"
int main(int argc, char const *argv[])

{

    long time = app_commen_getCurrentTime();
    log_debug("time = %ld", time);

    return 0;
}
