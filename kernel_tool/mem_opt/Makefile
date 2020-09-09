
TARGET=mem_opt

SRC := $(TARGET).c

#CC := gcc
CC := arm-linux-gnueabihf-gcc
CFLAGS +=


all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY:clean
clean:
	rm $(TARGET)

