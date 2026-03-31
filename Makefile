main: main.c hello.o
	gcc -o main main.c hello.o
	./main

hello.o: hello.c hello.h
	gcc -c hello.c

clean:
	rm main hello.o main.o
