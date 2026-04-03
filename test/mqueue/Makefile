log = ../../thirdparty/log.c ../../thirdparty/log.h
mqueue_test:mqueue_test.c $(log)
	gcc $(DEBUG) $^ -o $@ -I ../../thirdparty
	./$@
	rm $@

