CC=gcc

all: init main binaries run

init:
	@mkdir -p bin

main: main.c
	@echo "compiling..."
	$(CC) -o ./bin/main main.c

binaries: rm_encoder.c rm_decoder.c
	@echo "building binary files..."
	$(CC) -o ./bin/rm_encoder rm_encoder.c
	$(CC) -o ./bin/rm_decoder rm_decoder.c	

run:
	@echo "running..."
	./bin/main > ./bin/out.txt
	./bin/rm_encoder
	./bin/rm_decoder
