CC = gcc
CFLAGS = -Wall -Wextra -I.

TARGET = build/imageConverter
OBJ = build/imageConverter.o build/image.o

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/imageConverter.o: imageConverter.c image.h
build/image.o: image.c image.h

clean:
	rm -rf build

.PHONY: clean
