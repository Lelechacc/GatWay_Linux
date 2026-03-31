// #include "../thirdparty/log.h"
#include "log.h" // 要将thirdparty指定为include搜索路径
                 // 在编译时需要使用 -I thirdparty 参数来告诉编译器头文件位置

/**
 * 主函数 - 演示日志库的使用方法
 *
 * 这个程序会演示所有日志级别的使用：
 * - LOG_TRACE: 最详细的跟踪信息
 * - LOG_DEBUG: 调试信息
 * - LOG_INFO: 一般信息
 * - LOG_WARN: 警告信息
 * - LOG_ERROR: 错误信息
 * - LOG_FATAL: 致命错误信息
 */
int main(int argc, char const *argv[])
{
    // 设置输出级别 - 可选功能，如果取消注释可以设置最低显示的日志级别
    // log_set_level(LOG_DEBUG);

    // 使用TRACE级别记录跟踪信息 - 通常是最高详细度的信息
    log_trace("trace...");

    // 使用DEBUG级别记录调试信息 - 开发过程中使用的详细信息
    log_debug("debug...");

    // 使用INFO级别记录常规信息 - 程序运行的一般状态
    log_info("info...");

    // 使用WARN级别记录警告信息 - 表示可能出现问题但不影响运行的情况
    log_warn("warn...");

    // 使用ERROR级别记录错误信息 - 表示发生了错误但程序仍可继续运行
    log_error("error...");

    // 使用FATAL级别记录致命错误信息 - 表示发生了严重错误，程序可能无法继续运行
    // 支持格式化字符串，类似于printf函数
    log_fatal("fatal..., msg=%s", "fatal msg");

    // 程序正常退出，返回成功状态码

    return 0;
}
