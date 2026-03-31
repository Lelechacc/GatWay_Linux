
DEBUG := -g -O0 -Wall # -g -O0 -Wall 是编译选项，用于生成调试信息、关闭优化、显示所有警告、将警告视为错误
log = thirdparty/log.c thirdparty/log.h # 变量log 定义为thirdparty/log.c thirdparty/log.h
json = thirdparty/json.c thirdparty/json.h  #变量json ,	定义thirdparty/json.c thirdparty/json.h
app_common = app/app_common.c app/app_common.h  #变量app_common 定义为app/app.c app/app.h



app_compile: test/app_common_test.c $(app_common) $(log)
	gcc $(DEBUG) $^ -o $@ -I app -I thirdparty
	./$@
	rm $@

log_test: test/log_test.c $(log)
	# 使用gcc编译器编译源文件,-I thirdparty 指定头文件搜索路径
	gcc $(DEBUG) $^ -o $@ -I thirdparty
	# 运行生成的可执行文件
	-./$@
	# 删除生成的可执行文件
	-rm $@

json_test: test/json_test.c $(log) $(json)
	gcc $^ -o $@ -I thirdparty
	-./$@
	-rm $@
