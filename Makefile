CC     := gcc
CFLAGS := -Wall

default: all

all: format compile test

lint:
	@find . -type f \( -iname "*.h" -or -iname "*.c" \) | xargs clang-format -i -n -Werror

format:
	@find . -type f \( -iname "*.h" -or -iname "*.c" \) | xargs clang-format -i

compile-debug:
	${CC} ${CFLAGS} -o disassembler disassembler.c

compile-release:
	${CC} ${CFLAGS} -O3 -DNDEBUG -o disassembler disassembler.c

test:
	@./test.sh