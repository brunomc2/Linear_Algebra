output: bin obj basic gauss_jordan qr least_squares main
	g++ -Wall ./obj/* -o ./bin/output.out

bin:
	mkdir ./bin

obj:
	mkdir ./obj

basic: obj ./src/basic.cpp ./lib/basic.h
	g++ -I./lib -Wall -g -c ./src/basic.cpp -o ./obj/basic.o

gauss_jordan: obj ./src/gauss_jordan.cpp ./lib/gauss_jordan.h
	g++ -I./lib -Wall -g -c ./src/gauss_jordan.cpp -o ./obj/gauss_jordan.o

qr: obj ./src/qr.cpp ./lib/qr.h
	g++ -I./lib -Wall -g -c ./src/qr.cpp -o ./obj/qr.o

least_squares: obj ./src/least_squares.cpp ./lib/least_squares.h
	g++ -I./lib -Wall -g -c ./src/least_squares.cpp -o ./obj/least_squares.o

main: obj main.cpp
	g++ -I./lib -Wall -g -c main.cpp -o ./obj/main.o

run: output
	./bin/output.out

clean:
	rm ./obj/*
	rm ./bin/*
