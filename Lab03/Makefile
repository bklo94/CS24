hello: main.o functions.o
	g++ main.o functions.o -o hello
main.o: main.cpp functions.h
	g++ main.cpp -c
functions.o: functions.cpp functions.h
	g++ functions.cpp -c
clean:
	rm hello main.o functions.o

