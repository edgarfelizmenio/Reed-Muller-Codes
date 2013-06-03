CC = gcc

OBJECTS = \
	common.o\
	list.o\
	monomial.o\
	matrix.o\
	reedmuller.o\
	utils.o\
	vector.o

all: init rmtest binaries run clean

init:
	@mkdir -p bin
	@mkdir -p src
	@mkdir -p test

common.o: ./src/common.c ./src/common.h
	$(CC) -o common.o -c ./src/common.c

list.o: ./src/list.c ./src/list.h ./src/common.h
	$(CC) -o list.o -c ./src/list.c

vector.o: ./src/vector.c ./src/vector.h ./src/common.h
	$(CC) -o vector.o -c ./src/vector.c

monomial.o: ./src/monomial.c ./src/monomial.h ./src/common.h
	$(CC) -o monomial.o -c ./src/monomial.c

matrix.o: ./src/matrix.c ./src/matrix.h ./src/common.h ./src/vector.h
	$(CC) -o matrix.o -c ./src/matrix.c

reedmuller.o: ./src/reedmuller.c ./src/reedmuller.h ./src/common.h ./src/list.h ./src/vector.h ./src/monomial.h ./src/matrix.h 
	$(CC) -o reedmuller.o -c ./src/reedmuller.c

utils.o: ./src/utils.c ./src/utils.h ./src/common.h ./src/vector.h
	$(CC) -o utils.o -c ./src/utils.c

rmtest: ./test/test1.c ./test/test2.c $(OBJECTS)
	@echo "testing..."
	$(CC) -o ./test/test1 ./test/test1.c $(OBJECTS)
	$(CC) -o ./test/test2 ./test/test2.c $(OBJECTS)
	./test/test1 > test1_out.txt 2> test1_errlog.txt
	./test/test2 > test2_out.txt 2> test2_errlog.txt
	rm -f ./test/test1 ./test/test2
	rm -f ./test/test1.exe ./test/test2.exe

binaries: ./src/rm_encoder.c ./src/rm_decoder.c $(OBJECTS)
	@echo "building binary files..."
	$(CC) -o ./bin/rm_encoder ./src/rm_encoder.c $(OBJECTS)
	$(CC) -o ./bin/rm_decoder ./src/rm_decoder.c $(OBJECTS)

run:
	@echo "running..."
	./bin/rm_encoder
	./bin/rm_decoder

clean:
	@echo "cleaning..."
	rm *.o
