#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_OFFSET 0x200 // Programs are always loaded at 0x200.

void disassembleCHIP8(uint8_t* buffer, int pc)
{
    uint8_t* op = &buffer[pc];
    uint8_t nibble = op[0] >> 4;

    printf("%04X %02X %02X  ", pc, op[0], op[1]);

    /*
     * The CHIP-8 has 35 different opops of 2 bytes in length.
     * These bytes are stored in op[0] and op[1] respectively.
     *
     * For most opcodes, the instruction can be deduced from the
     * 4 left-most bits, while the remaining 12 bits are used for
     * constants or register identifiers. For specifics, refer
     * to the Wikipedia page on CHIP-8.
     */

    switch(nibble)
    {
        case 0x0:
        {
            switch(op[1])
            {
                case 0xe0:
                    printf("%-10s\n", "CLS");
                    break;
                case 0xee:
                    printf("%-10s\n", "RET");
                    break;
                default:
                    printf("%-10s $%01X%02X\n", "CALLR", op[0] & 0xf, op[1]);
            }
            break;
        }
        case 0x01:
            printf("%-10s $%01X%02X\n", "JUMP", op[0] & 0xf, op[1]);
            break;
        case 0x02:
            printf("%-10s $%01X%02X\n", "CALL", op[0] & 0xf, op[1]);
            break;
        case 0x03:
            printf("%-10s V%01X, #$%02X\n", "SKIP.EQ", op[0] & 0xf, op[1]);
            break;
        case 0x04:
            printf("%-10s V%01X, #$%02X\n", "SKIP.NE", op[0] & 0xf, op[1]);
            break;
        case 0x05:
            printf("%-10s V%01X, V%01X\n", "SKIP.EQ", op[0] & 0xf, op[1]);
            break;
        case 0x06:
            printf("%-10s V%01X, #$%02X\n", "MVI", op[0] & 0x0f, op[1]);
            break;
        case 0x07:
            printf("%-10s V%01X, #$%02X\n", "ADI", op[0] & 0x0f, op[1]);
            break;
        case 0x08:
        {
            uint8_t operation = op[1] & 0x0f;
            switch (operation)
            {
                case 0x0:
                    printf("%-10s V%01X, V%01X\n", "MOV", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x1:
                    printf("%-10s V%01X, V%01X\n", "OR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x2:
                    printf("%-10s V%01X, V%01X\n", "AND", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x3:
                    printf("%-10s V%01X, V%01X\n", "XOR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x4:
                    printf("%-10s V%01X, V%01X\n", "ADD", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x5:
                    printf("%-10s V%01X, V%01X\n", "SUB", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x6:
                    printf("%-10s V%01X, V%01X\n", "SHR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x7:
                    printf("%-10s V%01X, V%01X, V%01X\n", "SUB", op[0] & 0x0f, op[1] >> 4, op[0] & 0x0f);
                    break;
                case 0xe:
                    printf("%-10s V%01X, V%01X\n", "SHL", op[0] & 0x0f, op[1] >> 4);
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN 8");
            }
            break;
        }
        case 0x9:
            printf("%-10s V%01X, V%01X\n", "SKIP.NE", op[0] & 0x0f, op[1] >> 4);
            break;
        case 0xa:
            printf("%-10s I,  #$%01X%02X\n", "MVI", op[0] & 0xf, op[1]);
            break;
        case 0xb:
            printf("%-10s $%01X%02X(V0)\n", "JUMP", op[0] & 0xf, op[1]);
            break;
        case 0xc:
            printf("%-10s V%01X, #$%02X\n", "RNDMSK", op[0] & 0xf, op[1]);
            break;
        case 0xd:
            printf("%-10s V%01X, V%01X, #$%01X\n", "RNDMSK", op[0] & 0xf, op[1] >> 4, op[1] & 0x0f);
            break;
        case 0xe:
        {
            switch(op[1])
            {
                case 0x9e:
                    printf("%-10s V%01X\n", "SKIPKEY.Y", op[0] & 0xf);
                    break;
                case 0xa1:
                    printf("%-10s V%01X\n", "SKIPKEY.N", op[0] & 0xf);
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN E");
            }
            break;
        }
        case 0xf:
        {
            uint8_t instruction = op[1];
            switch(instruction)
            {
				case 0x07:
                    printf("%-10s V%01X, DELAY\n", "MOV", op[0] & 0xf);
                    break;
				case 0x0a:
                    printf("%-10s V%01X\n", "KEY", op[0] & 0xf);
                    break;
				case 0x15:
                    printf("%-10s DELAY, V%01X\n", "MOV", op[0] & 0xf);
                    break;
				case 0x18:
                    printf("%-10s SOUND, V%01X\n", "MOV", op[0] & 0xf);
                    break;
				case 0x1e:
                    printf("%-10s I, V%01X\n", "ADI", op[0] & 0xf);
                    break;
				case 0x29:
                    printf("%-10s I, V%01X\n", "SPRITECHAR", op[0] & 0xf);
                    break;
				case 0x33:
                    printf("%-10s (I), V%01X\n", "MOVBCD", op[0] & 0xf);
                    break;
				case 0x55:
                    printf("%-10s (I), V0-V%01X\n", "MOVM", op[0] & 0xf);
                    break;
				case 0x65:
                    printf("%-10s V0-V%01X, (I)\n", "MOVM", op[0] & 0xf);
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN F");
            }
            break;
        }
        default:
            printf("%-10s\n", "UNKNOWN");
    }
}

uint8_t* load_file(char* file_location, int* file_size)
{
    FILE* fp = fopen(file_location, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", file_location);
        exit(EXIT_FAILURE);
    }

    // Get the file size and read data into allocated memory.
    fseek(fp, 0L, SEEK_END);
    *file_size = ftell(fp);
    rewind(fp);

    uint8_t* buffer = malloc(*file_size + MEM_OFFSET);
    fread(buffer + MEM_OFFSET, *file_size, 1, fp);
    fclose(fp);

    return buffer;
}

int main(int argc, char** argv)
{
    if (argv[1] == NULL)
    {
        printf("Usage: ./disassembleCHIP8 file\n");
        exit(EXIT_FAILURE);
    }

    int file_size;
    uint8_t* buffer = load_file(argv[1], &file_size);

    for (int pc = MEM_OFFSET; pc < file_size + MEM_OFFSET; pc += 2)
    {
        disassembleCHIP8(buffer, pc);
    }

    return 0;
}