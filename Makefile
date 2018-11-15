output: bin obj basic gauss_jordan main
	g++ -Wall ./obj/* -o ./bin/output.out

bin:
	mkdir ./bin

obj:
	mkdir ./obj

basic: obj ./src/basic.cpp ./lib/basic.h
	g++ -I./lib -Wall -g -c ./src/basic.cpp -o ./obj/basic.o

gauss_jordan: obj ./src/gauss_jordan.cpp ./lib/gauss_jordan.h
	g++ -I./lib -Wall -g -c ./src/gauss_jordan.cpp -o ./obj/gauss_jordan.o

main: obj main.cpp
	g++ -I./lib -Wall -g -c main.cpp -o ./obj/main.o

run: output
	./bin/output.out

clean:
	rm ./obj/*
	rm ./bin/*
