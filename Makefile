CC = gcc
TARGET = main

CFLAGS = -Wall -Wextra -g -pedantic -std=c99
LIBS = -lraylib -labg_ui -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXcursor

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LIBS)
	@echo " Build OK -> $@"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf ./$(TARGET)