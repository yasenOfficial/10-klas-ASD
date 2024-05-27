#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    unsigned short offset;
    unsigned short length;
    unsigned char next_char;
} Token;

unsigned char* lz77_compress(unsigned char* data, unsigned short window_size, unsigned short lookahead_size, size_t *compressed_size) {
    size_t data_len = strlen((char*)data);
    Token *tokens = malloc(MAX_BUFFER_SIZE * sizeof(Token));
    size_t token_count = 0;
    
    for (size_t i = 0; i < data_len;) {
        unsigned short best_length = 0;
        unsigned short best_offset = 0;

        for (unsigned short j = 1; j <= window_size && j <= i; j++) {
            unsigned short length = 0;
            while (length < lookahead_size && i + length < data_len && data[i - j + length] == data[i + length]) {
                length++;
            }
            if (length > best_length) {
                best_offset = j;
                best_length = length;
            }
        }

        if (best_length > 0) {
            tokens[token_count].offset = best_offset;
            tokens[token_count].length = best_length;
            tokens[token_count].next_char = data[i + best_length];
            i += best_length + 1;
        } else {
            tokens[token_count].offset = 0;
            tokens[token_count].length = 0;
            tokens[token_count].next_char = data[i];
            i++;
        }

        token_count++;
    }

    *compressed_size = token_count * sizeof(Token);
    unsigned char *compressed_data = malloc(*compressed_size);
    memcpy(compressed_data, tokens, *compressed_size);
    free(tokens);

    return compressed_data;
}

unsigned char* lz77_decompress(unsigned char* data, size_t compressed_size) {
    Token *tokens = (Token*)data;
    size_t token_count = compressed_size / sizeof(Token);
    unsigned char *decompressed_data = malloc(MAX_BUFFER_SIZE);
    size_t decompressed_len = 0;

    for (size_t i = 0; i < token_count; i++) {
        if (tokens[i].offset == 0 && tokens[i].length == 0) {
            decompressed_data[decompressed_len++] = tokens[i].next_char;
        } else {
            for (unsigned short j = 0; j < tokens[i].length; j++) {
                decompressed_data[decompressed_len] = decompressed_data[decompressed_len - tokens[i].offset];
                decompressed_len++;
            }
            decompressed_data[decompressed_len++] = tokens[i].next_char;
        }
    }

    decompressed_data = realloc(decompressed_data, decompressed_len + 1);
    decompressed_data[decompressed_len] = '\0';
    
    return decompressed_data;
}

void write_to_file(const char *filename, unsigned char *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(data, 1, size, file);
    fclose(file);
}

unsigned char* read_from_file(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
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

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <mode> <input_file> <output_file> [window_size] [lookahead_size]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];

    size_t input_size;
    unsigned char *input_data = read_from_file(input_file, &input_size);

    if (strcmp(mode, "compress") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Usage for compress: %s compress <input_file> <output_file> <window_size> <lookahead_size>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        unsigned short window_size = (unsigned short)atoi(argv[4]);
        unsigned short lookahead_size = (unsigned short)atoi(argv[5]);

        size_t compressed_size;
        unsigned char *compressed_data = lz77_compress(input_data, window_size, lookahead_size, &compressed_size);
        write_to_file(output_file, compressed_data, compressed_size);
        free(compressed_data);

    } else if (strcmp(mode, "decompress") == 0) {
        unsigned char *decompressed_data = lz77_decompress(input_data, input_size);
        write_to_file(output_file, decompressed_data, strlen((char*)decompressed_data));
        free(decompressed_data);
    } else {
        fprintf(stderr, "Invalid mode. Use 'compress' or 'decompress'.\n");
        exit(EXIT_FAILURE);
    }

    free(input_data);
    return 0;
}
