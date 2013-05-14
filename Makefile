CC=gcc

all: init main run

init:
	@mkdir -p bin

main: main.c
	@echo "compiling..."
	$(CC) -o ./bin/main main.c
	
run:
	@echo "running..."
	./bin/main > ./bin/out.txt
