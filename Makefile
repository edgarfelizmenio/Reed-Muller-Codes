CC=gcc

all: init main binaries run

init:
	@mkdir -p bin
	@mkdir -p src

main: ./src/main.c
	@echo "compiling..."
	$(CC) -o ./bin/main ./src/main.c

binaries: ./src/rm_encoder.c ./src/rm_decoder.c
	@echo "building binary files..."
	$(CC) -o ./bin/rm_encoder ./src/rm_encoder.c
	$(CC) -o ./bin/rm_decoder ./src/rm_decoder.c	

run:
	@echo "running..."
	./bin/main > ./bin/out.txt
	./bin/rm_encoder
	./bin/rm_decoder
