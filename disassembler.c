#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_OFFSET 0x200 // Programs are always loaded at 0x200.

void disassembleCHIP8(uint8_t* buffer, int pc)
{
    uint8_t* op = &buffer[pc];
    uint8_t nibble = op[0] >> 4;

    printf("%04X %02X %02X   ", pc, op[0], op[1]);

    /*
     * The CHIP-8 has 35 different opcodes of 2 bytes in length.
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
                    printf("%s\n", "CLS");
                    break;
                case 0xee:
                    printf("%s\n", "RET");
                    break;
                default:
                    printf("%-4s %01X%02X\n", "SYS", op[0] & 0xf, op[1]);
            }
            break;
        }
        case 0x01:
            printf("%-4s %01X%02X\n", "JP", op[0] & 0xf, op[1]);
            break;
        case 0x02:
            printf("%-4s %01X%02X\n", "CALL", op[0] & 0xf, op[1]);
            break;
        case 0x03:
            printf("%-4s V%-2X #%02X\n", "SE", op[0] & 0xf, op[1]);
            break;
        case 0x04:
            printf("%-4s V%-2X #%02X\n", "SNE", op[0] & 0xf, op[1]);
            break;
        case 0x05:
            printf("%-4s V%-2X V%01X\n", "SE", op[0] & 0xf, op[1]);
            break;
        case 0x06:
            printf("%-4s V%-2X #%02X\n", "LD", op[0] & 0x0f, op[1]);
            break;
        case 0x07:
            printf("%-4s V%-2X #%02X\n", "ADD", op[0] & 0x0f, op[1]);
            break;
        case 0x08:
        {
            uint8_t operation = op[1] & 0x0f;
            switch (operation)
            {
                case 0x0:
                    printf("%-4s V%-2X V%01X\n", "LD", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x1:
                    printf("%-4s V%-2X V%01X\n", "OR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x2:
                    printf("%-4s V%-2X V%01X\n", "AND", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x3:
                    printf("%-4s V%-2X V%01X\n", "XOR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x4:
                    printf("%-4s V%-2X V%01X\n", "ADD", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x5:
                    printf("%-4s V%-2X V%01X\n", "SUB", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x6:
                    printf("%-4s V%-2X V%01X\n", "SHR", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0x7:
                    printf("%-4s V%-2X V%01X\n", "SUBN", op[0] & 0x0f, op[1] >> 4);
                    break;
                case 0xe:
                    printf("%-4s V%-2X V%01X\n", "SHL", op[0] & 0x0f, op[1] >> 4);
                    break;
                default:
                    printf("%-4s %-2X\n", "UNKN", 0x8);
            }
            break;
        }
        case 0x9:
            printf("%-4s V%-2X V%01X\n", "SNE", op[0] & 0x0f, op[1] >> 4);
            break;
        case 0xa:
            printf("%-4s I   %01X%02X\n", "LD", op[0] & 0xf, op[1]);
            break;
        case 0xb:
            printf("%-4s V0  %01X%02X\n", "JP", op[0] & 0xf, op[1]);
            break;
        case 0xc:
            printf("%-4s V%-2X #%02X\n", "RND", op[0] & 0xf, op[1]);
            break;
        case 0xd:
            printf("%-4s V%-2X V%-2X #%02X\n", "DRW", op[0] & 0xf, op[1] >> 4, op[1] & 0x0f);
            break;
        case 0xe:
        {
            switch(op[1])
            {
                case 0x9e:
                    printf("%-4s V%01X\n", "SKP", op[0] & 0xf);
                    break;
                case 0xa1:
                    printf("%-4s V%01X\n", "SKNP", op[0] & 0xf);
                    break;
                default:
                    printf("%-4s %-2X\n", "UNKN", 0xe);
            }
            break;
        }
        case 0xf:
        {
            switch(op[1])
            {
                case 0x07:
                    printf("%-4s V%-2X DT\n", "LD", op[0] & 0xf);
                    break;
                case 0x0a:
                    printf("%-4s V%-2X K\n", "LD", op[0] & 0xf);
                    break;
                case 0x15:
                    printf("%-4s %-3s V%01X\n", "LD", "DT", op[0] & 0xf);
                    break;
                case 0x18:
                    printf("%-4s %-3s V%01X\n", "LD", "ST", op[0] & 0xf);
                    break;
                case 0x1e:
                    printf("%-4s %-3s V%01X\n", "ADD", "I", op[0] & 0xf);
                    break;
                case 0x29:
                    printf("%-4s %-3s V%01X\n", "LD", "F", op[0] & 0xf);
                    break;
                case 0x33:
                    printf("%-4s %-3s V%01X\n", "LD", "B", op[0] & 0xf);
                    break;
                case 0x55:
                    printf("%-4s %-3s V%01X\n", "LD", "[I]", op[0] & 0xf);
                    break;
                case 0x65:
                    printf("%-4s V%-2X [I]\n", "LD", op[0] & 0xf);
                    break;
                default:
                    printf("%-4s %-2X\n", "UNKN", 0xf);

            }
            break;
        }
        default:
            printf("%-4s\n", "UNKN");
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
        printf("Usage: ./disassembler file\n");
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
