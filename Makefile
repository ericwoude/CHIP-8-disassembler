CC     := gcc
CFLAGS := -Wall

default: all

all: format compile test

lint:
	@find . -type f \( -iname "*.h" -or -iname "*.c" \) | xargs clang-format -i --dry-run

format:
	@find . -type f \( -iname "*.h" -or -iname "*.c" \) | xargs clang-format -i

compile:
	${CC} ${CFLAGS} -o disassembler disassembler.c

test:
	@./test.sh