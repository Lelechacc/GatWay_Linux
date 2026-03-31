#include "cJSON.h"
#include "log.h"

/**
 * 主函数 - 演示cJSON库的基本使用方法
 *
 * 功能包括：
 * 1. 创建JSON对象并添加数据
 * 2. 将JSON对象转换为字符串
 * 3. 解析JSON字符串并提取数据
 */
int main(void)
{
    // 生成JSON - 创建一个包含姓名和年龄的JSON对象
    char *name = "zhangsan"; // 定义姓名字符串
    int age = 18;            // 定义年龄整数

    // 创建一个空的JSON对象
    cJSON *json = cJSON_CreateObject();
    // 向JSON对象添加字符串类型的"姓名"字段
    cJSON_AddStringToObject(json, "name", name);
    // 向JSON对象添加数值类型的"年龄"字段
    cJSON_AddNumberToObject(json, "age", age);

    // 将JSON对象转换为未格式化的字符串（紧凑形式，无缩进）
    char *json_str = cJSON_PrintUnformatted(json);
    // 输出生成的JSON字符串到日志
    log_debug("生成JSON:%s", json_str);

    // 释放JSON对象占用的内存
    cJSON_Delete(json);

    // 解析JSON字符串 - 从JSON字符串中提取数据
    cJSON *json2 = cJSON_Parse(json_str); // 解析JSON字符串
    // 从解析后的JSON对象中获取"name"字段的字符串值
    char *name2 = cJSON_GetObjectItem(json2, "name")->valuestring;
    // 从解析后的JSON对象中获取"age"字段的整数值
    int age2 = cJSON_GetObjectItem(json2, "age")->valueint;
    // 输出解析结果到日志
    log_debug("解析JSON:name=%s, age=%d", name2, age2);

    // 释放解析后创建的JSON对象占用的内存
    cJSON_Delete(json2);
    // 释放JSON字符串占用的内存
    free(json_str);

    return 0;
}
