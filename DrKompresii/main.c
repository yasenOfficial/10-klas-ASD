#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct
{
    unsigned short offset;
    unsigned short length;
    unsigned char next_char;
} Token;

void print_banner()
{
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("__     __                       _____                                        _          _______          _ \n");
    printf("\\ \\   / /                      / ____|                                      (_)        |__   __|        | |\n");
    printf(" \\ \\_/ /_ _ ___  ___ _ __  ___| |     ___  _ __ ___  _ __  _ __ ___  ___ ___ _ _ __   __ _| | ___   ___ | |\n");
    printf("  \\   / _` / __|/ _ \\ '_ \\/ __| |    / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\/ __/ __| | '_ \\ / _` | |/ _ \\ / _ \\| |\n");
    printf("   | | (_| \\__ \\  __/ | | \\__ \\ |___| (_) | | | | | | |_) | | |  __/\\__ \\__ \\ | | | | (_| | | (_) | (_) | |\n");
    printf("   |_|\\__,_|___/\\___|_| |_|___/\\_____\\___/|_| |_| |_| .__/|_|  \\___||___/___/_|_| |_|\\__, |_|\\___/ \\___/|_|\n");
    printf("                                                    | |                               __/ |                \n");
    printf("                                                    |_|                              |___/                 \n");
    printf("-----------------------------------------------------------------------------------------------------------------\n\n");
}

// I e input (original) byte array
// O e output (compressed) byte array
// W e sliding window size for searching matches
// F e the maximum match length

unsigned char *lz77_compress(unsigned char *I, unsigned short W, unsigned short F, size_t *compressed_size)
{
    size_t data_len = strlen((char *)I);
    Token *tokens = malloc(MAX_BUFFER_SIZE * sizeof(Token));
    size_t token_count = 0;

    for (size_t i = 0; i < data_len;)
    {
        unsigned short najDobraDuljina = 0;
        unsigned short best_offset = 0;

        for (unsigned short j = 1; j <= W && j <= i; j++)
        {
            unsigned short length = 0;
            do
            {
                length++;
            } while (length < F && i + length < data_len && I[i - j + length] == I[i + length]);

            if (length > najDobraDuljina)
            {
                best_offset = j;
                najDobraDuljina = length;
            }
        }

        if (najDobraDuljina > 0)
        {
            unsigned short extended_duljina = najDobraDuljina;
            do
            {
                extended_duljina++;
            } while (extended_duljina < F && i + extended_duljina < data_len && I[i + extended_duljina] == I[i + najDobraDuljina - 1]);

            tokens[token_count].offset = best_offset;
            tokens[token_count].length = extended_duljina;
            tokens[token_count].next_char = I[i + extended_duljina];
            printf("Pri i=%zu, output (w=%d, l=%d) %c: Poredicata \"%.*s\" e povtorena i posledniq simvol \"%c\" moge da bude produjen %d puti\n",
                   i, best_offset, extended_duljina, I[i + extended_duljina], extended_duljina, &I[i], I[i + najDobraDuljina - 1], extended_duljina - najDobraDuljina);
            i = i + extended_duljina + 1;
        }
        else
        {
            tokens[token_count].offset = 0;
            tokens[token_count].length = 0;
            tokens[token_count].next_char = I[i];
            printf("Pri i=%zu, output (0,0) %c: Nqma namereno suvpadenie\n", i, I[i]);
            i++;
        }

        token_count++;
    }

    *compressed_size = token_count * sizeof(Token);
    unsigned char *O = malloc(*compressed_size);
    memcpy(O, tokens, *compressed_size);
    free(tokens);

    return O;
}

// I is the input (compressed) byte array
// O is the output (decompressed) byte array

unsigned char *lz77_decompress(unsigned char *I, size_t compressed_size)
{
    Token *tokens = (Token *)I;
    size_t token_count = compressed_size / sizeof(Token);
    unsigned char *O = malloc(MAX_BUFFER_SIZE);
    size_t decompressed_duljina = 0;

    for (size_t i = 0; i < token_count; i++)
    {
        if (tokens[i].offset == 0 && tokens[i].length == 0)
        {
            O[decompressed_duljina++] = tokens[i].next_char;
        }
        else
        {
            for (unsigned short j = 0; j < tokens[i].length; j++)
            {
                O[decompressed_duljina] = O[decompressed_duljina - tokens[i].offset];
                decompressed_duljina++;
            }
            O[decompressed_duljina++] = tokens[i].next_char;
        }
    }

    O[decompressed_duljina] = '\0';

    return O;
}

void write_to_file(const char *filename, unsigned char *data, size_t size)
{
    FILE *file = fopen(filename, "wb"); // weitre binarno
    if (!file)
    {
        perror("Ne uspqh da otvorq faila za pisane");
        exit(EXIT_FAILURE);
    }
    fwrite(data, 1, size, file);
    fclose(file);
}

void print_compressed(unsigned char *compressed_data, size_t compressed_size)
{
    Token *tokens = (Token *)compressed_data;
    size_t token_count = compressed_size / sizeof(Token);

    for (size_t i = 0; i < token_count; i++)
    {
        printf("(%d,%d)%c", tokens[i].offset, tokens[i].length, tokens[i].next_char);
    }
    printf("\n");
}

unsigned char *read_from_file(const char *filename, size_t *size)
{
    FILE *file = fopen(filename, "rb"); // chetem binarno
    if (!file)
    {
        perror("Ne uspqh da otvorq faila za chetene");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(*size);
    fread(data, 1, *size, file);
    fclose(file);

    return data;
}

int main(int argc, char *argv[])
{
    // printf("argc: %d\n", argc);
    if (argc < 4)
    {
        fprintf(stderr, "Kak se izpolzva: %s <mode> <input_file> <output_file> [window_size] [lookahead_size]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];

    // for (int i = 0; i < argc; i++) {
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }

    size_t input_size;
    unsigned char *input_data = read_from_file(input_file, &input_size);

    print_banner();
    if (strcmp(mode, "decompress") == 0)
    {

        unsigned char *decompressed_data = lz77_decompress(input_data, input_size);

        write_to_file(output_file, decompressed_data, strlen((char *)decompressed_data));
        free(decompressed_data);
    }
    else if (strcmp(mode, "compress") == 0)
    {
        if (argc != 6)
        {
            fprintf(stderr, "Nevalidni argumenti!", argv[0]);
            exit(EXIT_FAILURE);
        }

        unsigned int W = (unsigned int)atoi(argv[4]); // prevrushtame v 'int' tip
        unsigned int F = (unsigned int)atoi(argv[5]); // moge da bude napraweno i sus 'short' kato tip

        size_t compressed_size;
        unsigned char *compressed_data = lz77_compress(input_data, W, F, &compressed_size);
        write_to_file(output_file, compressed_data, compressed_size);

        printf("\n-----------------------------------------------------------------------------------------------------------------\n\nOutput: ");
        print_compressed(compressed_data, compressed_size);

        free(compressed_data);
    }
    else
    {
        fprintf(stderr, "Nevaliden mode. Izpolzvaj 'compress' ili 'decompress'.\n");
        exit(EXIT_FAILURE);
    }

    free(input_data);
    return 0;
}

// Primeren input za kompresiq (in.txt): "HAHAHAAAALSSSUSUSSSSHJSHS"
// ./main.exe compress in.txt out.txt 20 10

/*
OUTPUT:

Pri i=0, output (0,0) H: Nqma namereno suvpadenie
Pri i=1, output (0,0) A: Nqma namereno suvpadenie
Pri i=2, output (w=2, l=7) L: Poredicata "HAHAAAA" e povtorena i posledniq simvol "A" moge da bude produjen 3 puti
Pri i=10, output (0,0) S: Nqma namereno suvpadenie
Pri i=11, output (w=1, l=2) U: Poredicata "SS" e povtorena i posledniq simvol "S" moge da bude produjen 0 puti
Pri i=14, output (w=2, l=6) H: Poredicata "SUSSSS" e povtorena i posledniq simvol "S" moge da bude produjen 3 puti
Pri i=21, output (0,0) J: Nqma namereno suvpadenie
Pri i=22, output (w=3, l=2) S: Poredicata "SH" e povtorena i posledniq simvol "H" moge da bude produjen 0 puti

-----------------------------------------------------------------------------------------------------------------

Output: (0,0)H(0,0)A(2,7)L(0,0)S(1,2)U(2,6)H(0,0)J(3,2)S
*/