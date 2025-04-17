CC = /usr/bin/gcc
CFLAGS = -Wall -O2 -fsanitize=address -g -lcurl
TARGETS = start_server clean

default: all
all: $(TARGETS)

start_server: Server.o
	@echo "Linking..."
	@$(CC) $(CFLAGS) Server.c -o run_server

%.o:%.c
	@echo "Compiling..."
	@$(CC) $(CFLAGS) -c $< 

clean:
	rm -f *.o
	@./run_server ./dist/browser
