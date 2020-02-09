#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEM_OFFSET 0x200

void disassembleCHIP8(uint8_t *buffer, int pc)
{
    uint8_t *code = &buffer[pc];
    uint8_t nibble = code[0] >> 4;

    printf("%04X %02X %02X  ", pc, code[0], code[1]);

    switch(nibble)
    {
        case 0x0:
        {
            switch(code[1])
            {
                case 0xe0:
                    printf("%-10s\n", "CLS");
                    break;
                case 0xee:
                    printf("%-10s\n", "RET");
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN 0");
            }
            break;
        }
        case 0x01:
            printf("%-10s $%01X%02X\n", "JUMP", code[0] & 0xf, code[1]);
            break;
        case 0x02:
            printf("%-10s $%01X%02X\n", "CALL", code[0] & 0xf, code[1]);
            break;
        case 0x03:
            printf("%-10s V%01X, #$%02X\n", "SKIP.EQ", code[0] & 0xf, code[1]);
            break;
        case 0x04:
            printf("%-10s V%01X, #$%02X\n", "SKIP.NE", code[0] & 0xf, code[1]);
            break;
        case 0x05:
            printf("%-10s V%01X, V%01X\n", "SKIP.EQ", code[0] & 0xf, code[1]);
            break;
        case 0x06:
            printf("%-10s V%01X, #$%02X\n", "MVI", code[0] & 0x0f, code[1]);
            break;
        case 0x07:
            printf("%-10s V%01X, #$%02X\n", "ADI", code[0] & 0x0f, code[1]);
            break;
        case 0x08:
        {
            uint8_t operation = code[1] & 0x0f;
            switch (operation)
            {
                case 0x0:
                    printf("%-10s V%01X, V%01X\n", "MOV", code[0] & 0x0f, code[1] >> 4);
                    break;
                case 0x1:
                    printf("%-10s V%01X, V%01X\n", "OR", code[0] & 0x0f, code[1] >> 4);              
                    break;
                case 0x2:
                    printf("%-10s V%01X, V%01X\n", "AND", code[0] & 0x0f, code[1] >> 4);              
                    break;
                case 0x3:
                    printf("%-10s V%01X, V%01X\n", "XOR", code[0] & 0x0f, code[1] >> 4);              
                    break;
                case 0x4:
                    printf("%-10s V%01X, V%01X\n", "ADD", code[0] & 0x0f, code[1] >> 4);              
                    break;
                case 0x5:
                    printf("%-10s V%01X, V%01X\n", "SUB", code[0] & 0x0f, code[1] >> 4);              
                    break;                    
                case 0x6:
                    printf("%-10s V%01X, V%01X\n", "SHR", code[0] & 0x0f, code[1] >> 4);              
                    break;                    
                case 0x7:
                    printf("%-10s V%01X, V%01X, V%01X\n", "SUB", code[0] & 0x0f, code[1] >> 4, code[0] & 0x0f);              
                    break;
                case 0xe:
                    printf("%-10s V%01X, V%01X\n", "SHL", code[0] & 0x0f, code[1] >> 4);
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN 8");
            }
            break;
        }
        case 0x9:
            printf("%-10s V%01X, V%01X\n", "SKIP.NE", code[0] & 0x0f, code[1] >> 4);
            break;
        case 0xa:
            printf("%-10s I,  #$%01X%02X\n", "MVI", code[0] & 0xf, code[1]);
            break;
        case 0xb:
            printf("%-10s $%01X%02X(V0)\n", "JUMP", code[0] & 0xf, code[1]);
            break;
        case 0xc:
            printf("%-10s V%01X, #$%02X\n", "RNDMSK", code[0] & 0xf, code[1]);
            break;
        case 0xd:
            printf("%-10s V%01X, V%01X, #$%01X\n", "RNDMSK", code[0] & 0xf, code[1] >> 4, code[1] & 0x0f);   
            break;         
        case 0xe:
        {
            uint8_t instruction = code[1] & 0x0f;
            switch(instruction)
            {
                case 0x9e:
                    printf("%-10s V%01X\n", "SKIPKEY.Y", code[0] & 0xf);
                    break;
                case 0xa1:
                    printf("%-10s V%01X\n", "SKIPKEY.N", code[0] & 0xf);
                    break;
                default:
                    printf("%-10s\n", "UNKNOWN E");
            }
            break;
        }
        case 0xf:
        {
            uint8_t instruction = code[1];
            switch(instruction)
            {
				case 0x07:
                    printf("%-10s V%01X, DELAY\n", "MOV", code[0] & 0xf);
                    break;
				case 0x1e:
                    printf("%-10s I, V%01X\n", "ADI", code[0] & 0xf);
                    break;
				case 0x0a:
                    printf("%-10s V%01X\n", "KEY", code[0] & 0xf);
                    break;
				case 0x15:
                    printf("%-10s DELAY, V%01X\n", "MOV", code[0] & 0xf);
                    break;
				case 0x18:
                    printf("%-10s SOUND, V%01X\n", "MOV", code[0] & 0xf);
                    break;
				case 0x29:
                    printf("%-10s I, V%01X\n", "SPRITECHAR", code[0] & 0xf);
                    break;
				case 0x33:
                    printf("%-10s (I), V%01X\n", "MOVBCD", code[0] & 0xf);
                    break;
				case 0x55:
                    printf("%-10s (I), V0-V%01X\n", "MOVM", code[0] & 0xf);
                    break;
				case 0x65:
                    printf("%-10s V0-V%01X, (I)\n", "MOVM", code[0] & 0xf);
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

uint8_t *load_file(char *file_location, int *file_size)
{
    FILE *fp = fopen(file_location, "rb");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", file_location);
        exit(EXIT_FAILURE);
    }

    // Get the file size, allocate memory and read the data into allocated memory.
    fseek(fp, 0L, SEEK_END);
    *file_size = ftell(fp);
    rewind(fp);
    uint8_t *buffer = malloc(*file_size + MEM_OFFSET);
    fread(buffer + MEM_OFFSET, *file_size, 1, fp);
    fclose(fp);

    return buffer;
}

int main(int argc, char **argv)
{
    if (argv[1] == NULL)
    {
        printf("Usage: ./disassembleCHIP8 file");
        exit(EXIT_FAILURE); 
    }

    int file_size;
    uint8_t *buffer = load_file(argv[1], &file_size);

    for (int pc = MEM_OFFSET; pc < file_size + MEM_OFFSET; pc += 2)
    {
        disassembleCHIP8(buffer, pc);
    }

    return 0;
}