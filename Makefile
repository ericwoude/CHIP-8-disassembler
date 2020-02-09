CC     := gcc
CFLAGS := -Wall

all:
	${CC} ${CFLAGS} -o disassembler disassembler.c
