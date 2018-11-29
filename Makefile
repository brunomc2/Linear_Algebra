CC=g++ -I./lib -Wall -g -c

output: bin obj  basic  gauss_jordan  least_squares qr grade_calc main
	g++ -Wall ./obj/* -o ./bin/output.out

bin:
	mkdir ./bin

obj:
	mkdir ./obj

basic: ./src/basic.cpp ./lib/basic.h
	$(CC) ./src/basic.cpp -o ./obj/basic.o

gauss_jordan: ./src/gauss_jordan.cpp ./lib/gauss_jordan.h
	$(CC) ./src/gauss_jordan.cpp -o ./obj/gauss_jordan.o

least_squares: ./src/least_squares.cpp ./lib/least_squares.h
	$(CC) ./src/least_squares.cpp -o ./obj/least_squares.o

qr: ./src/qr.cpp ./lib/qr.h
	$(CC) ./src/qr.cpp -o ./obj/qr.o

grade_calc: ./src/grade_calc.cpp ./lib/grade_calc.h
	$(CC) ./src/grade_calc.cpp -o ./obj/grade_calc.o

main: obj main.cpp
	$(CC) main.cpp -o ./obj/main.o

run: output
	./bin/output.out

clean:
	rm ./obj/*
	rm ./bin/*
