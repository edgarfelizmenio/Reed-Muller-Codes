CC = gcc

OBJECTS = \
	common.o\
	list.o\
	monomial.o\
	matrix.o\
	reedmuller.o\
	utils.o\
	vector.o

all: init main binaries run

init:
	@mkdir -p bin
	@mkdir -p src

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

main: ./src/main.c $(OBJECTS)
	@echo "compiling..."
	$(CC) -o ./bin/main ./src/main.c $(OBJECTS)

binaries: ./src/rm_encoder.c ./src/rm_decoder.c $(OBJECTS)
	@echo "building binary files..."
	$(CC) -o ./bin/rm_encoder ./src/rm_encoder.c $(OBJECTS)
	$(CC) -o ./bin/rm_decoder ./src/rm_decoder.c $(OBJECTS)

run:
	@echo "running..."
	./bin/main > ./bin/out.txt
	./bin/rm_encoder
	./bin/rm_decoder
