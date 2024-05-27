# (Da, pomolih chatgpt da mi napishe makefile-a ne sum go pisal az (vie kazahte che e ok))

# Kak se izpolzva:

# ``` make main ``` - build
# ``` ./main ``` - run
# ``` make clean ``` - clean build

CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

DEPS = $(OBJS:.o=.d)

TARGET = main

INC_DIRS = -I.

LIBS =

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) $(OBJS) $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIRS) -MMD -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)
