/*
 * SIMPLE BIGINT LIBRARY
 * 
 * This is source code for functions defined in bigint.h header file. Since this
 * is a school project and we don't have enough time to write too many comments,
 * this file will contain only minimal descriptions. For more details refer to
 * the bigint.h header file.
 * 
 * Made by rdobovic
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <bigint.h>
#include <string.h>

// Number of decimal digits a single chunk can hold
int __bigint_chunk_decimal_digits;
// 10 to the power of number of digits above (used for carry calculations)
BIGINT_CHUNK_TYPE __bigint_chunk_decimal_digits_padding;

// Initilize global library variables
int bigint_init(void) {
    int i = 0, digits = 0;
    BIGINT_CHUNK_TYPE num = (~(~0ULL << BIGINT_CHUNK_BITS));

    // Count how many decimal digits can fit into a single chunk
    while (num > 0) { 
        num /= 10; 
        ++digits;
    }

    __bigint_chunk_decimal_digits = digits;

    // Calculate 10 to the power of number of digits
    BIGINT_CHUNK_TYPE _padding;
    for (num = 1ULL, i = 0; i < __bigint_chunk_decimal_digits; i++) {
        num *= 10ULL;
    }

    __bigint_chunk_decimal_digits_padding = num;
    return 0;
}

// Allocate memory and initilize new bigint variable
struct bigint * bigint_new(void) {

    struct bigint *bi = malloc(sizeof(struct bigint));

    if (!bi)
        return NULL;

    bi->num_size = sizeof(BIGINT_CHUNK_TYPE) * BIGINT_ALLOC_CHUNKS;
    bi->num = malloc(bi->num_size);

    if (!bi->num) {
        free(bi);
        return NULL;
    }

    bi->chunks_used = 0;

    return bi;
}

// Free the memory taken by given bigint variable
int bigint_free(struct bigint *bi) {
    free(bi->num);
    free(bi);
    return 0;
}

// Realocate memory of bigint variable to have BIGINT_ALLOC_CHUNKS chunks
// more than it had until now, and set allocated chunks to 0
int bigint_realloc(struct bigint *bi) {
    size_t original_size = bi->num_size;
    bi->num_size += BIGINT_ALLOC_CHUNKS * sizeof(BIGINT_CHUNK_TYPE);

    void *tmp = realloc(bi->num, bi->num_size);

    if (tmp == NULL) {
        return BIGINT_ERROR_REALLOC;
    }

    memset(tmp + original_size, 0, bi->num_size - original_size);
    bi->num = tmp;
    return 0;
}

// Parse char array of digits into bigint
int bigint_parse(struct bigint *bi, char *str, long str_len) {
    int err, i, num_index = -1;
    BIGINT_CHUNK_TYPE padding;
    
    for (i = str_len - 1; i >= 0; i--) {

        if (num_index == bi->num_size / sizeof(BIGINT_CHUNK_TYPE)) {
            if (err = bigint_realloc(bi))
                return err;
        }

        if ((str_len - i - 1) % BIGINT_CHUNK_DIGITS == 0) {
            padding = 1;
            bi->num[++num_index] = 0;
        }

        if (!isdigit(str[i]))
            return BIGINT_ERROR_NOT_DIGIT;

        bi->num[num_index] += (str[i] - '0') * padding;
        padding *= 10;
    }

    bi->chunks_used = num_index + 1;
    return 0;
}

// Copy value of one bigint to another
int bigint_copy(struct bigint *from, struct bigint *to) {
    int i, err;

    for (i = 0; i < from->chunks_used; i++) {
        if (i == to->num_size / sizeof(BIGINT_CHUNK_TYPE)) {
            if (err = bigint_realloc(to))
                return err;
        }

        to->num[i] = from->num[i];
    }

    to->chunks_used = from->chunks_used;
}

// Sum two bigints and store the result into result variable
int bigint_add(struct bigint *result, struct bigint *a, struct bigint *b) {

    int err;
    long long i, j;
    BIGINT_CHUNK_TYPE carry = 0ULL;

    for (i = 0; i < a->chunks_used || i < b->chunks_used || carry > 0; i++) {

        // Increase size of number if needed
        if (i == result->num_size / sizeof(BIGINT_CHUNK_TYPE)) {
            if (err = bigint_realloc(result))
                return err;
        }

        result->num[i] = carry + 
            (i < a->chunks_used ? a->num[i] : 0ULL) +
            (i < b->chunks_used ? b->num[i] : 0ULL);

        carry = result->num[i] / BIGINT_CHUNK_PADDING;
        result->num[i] %= BIGINT_CHUNK_PADDING;
    }

    result->chunks_used = i;
    return 0;
}

// Multiply two bigints and store the result into result variable
int bigint_mul(struct bigint *result, struct bigint *a, struct bigint *b) {

    int err;
    long long i, j;
    BIGINT_CHUNK_TYPE carry = 0;

    if (a->chunks_used == 0 || b->chunks_used == 0) {
        result->chunks_used = 0;
        return 0;
    }
    
    memset(result->num, 0, result->num_size);

    for (i = 0; i < b->chunks_used; i++) {
        for (j = 0; j < a->chunks_used; j++) {

            // Increase size of number if needed
            if (i + j + 4 == result->num_size / sizeof(BIGINT_CHUNK_TYPE)) {
                if (err = bigint_realloc(result))
                    return err;
            }
            
            result->num[j + i] += a->num[j] * b->num[i] + carry;
            carry = result->num[j + i] / BIGINT_CHUNK_PADDING;
            result->num[j + i] %= BIGINT_CHUNK_PADDING;
        }

        while (carry > 0) {
            result->num[i + (j++)] += carry;
            carry = result->num[j + i] / BIGINT_CHUNK_PADDING;
            result->num[i + j] %= BIGINT_CHUNK_PADDING;
        }
    }

    result->chunks_used = i + j - 1;

    return 0;
}

// Increment bigint by the given value
int bigint_incr(struct bigint *bi, long value) {
    int i, err;
    bi->num[0] += value;
    
    for (i = 0; bi->num[i] / BIGINT_CHUNK_PADDING; i++) {
        if (i == bi->num_size / sizeof(BIGINT_CHUNK_TYPE)) {
            if (err = bigint_realloc(bi))
                return err;
        } 

        if (bi->chunks_used == i + 1)
            bi->num[bi->chunks_used++] = 0;
        
        bi->num[i + 1] += bi->num[i] / BIGINT_CHUNK_PADDING;
        bi->num[i] %= BIGINT_CHUNK_PADDING;
    }

    return 0;
}

// Decrement bigint by the given value
int bigint_decr(struct bigint *bi, long value) {
    unsigned long long i;

    if (bi->num[0] < value) {
        for (i = 0ULL; i == 0 || bi->num[i] == 0; i++) {
            if (bi->chunks_used == i + 1)
                return BIGINT_ERROR_NEGATIVE;
            
            bi->num[i] += BIGINT_CHUNK_PADDING - (i > 0);
        }

        --bi->num[i];

        if (!bi->num[i])
            --bi->chunks_used;
    }

    bi->num[0] -= value;

    if (!bi->num[0] && bi->chunks_used == 1)
        bi->chunks_used = 0;

    return 0;
}

// Check if given bigint is equal to zero
int bigint_is_zero(struct bigint *bi) {
    return bi->chunks_used == 0;
}

// Convert given bigint to char array of ASCII characters
int bigint_to_string(struct bigint *bi, char *str, long str_len) {

    long long i, j, str_index = 0;

    BIGINT_CHUNK_TYPE highest_chunk, padding = 1;

    if (bi->chunks_used == 0) {
        if (str_len == 0)
            return BIGINT_ERROR_NO_SPACE;
        str[0] = '0';
        str[1] = '\0';
        return 0;
    }

    highest_chunk = bi->num[bi->chunks_used - 1];

    while (highest_chunk != 0ULL) {
        highest_chunk /= 10;
        padding *= 10;
    }

    padding /= 10;

    for (; padding > 0ULL; padding /= 10ULL) {
        if (str_index >= str_len)
            return BIGINT_ERROR_NO_SPACE;
        str[str_index++] = (bi->num[bi->chunks_used - 1] / padding % 10) + '0';
    }

    for (i = bi->chunks_used - 2; i >= 0; i--) {
        padding = BIGINT_CHUNK_PADDING / 10;

        while (padding != 0) {
            if (str_index >= str_len)
                return BIGINT_ERROR_NO_SPACE;
            str[str_index++] = (bi->num[i] / padding % 10) + '0';
            padding /= 10;
        }
    }

    str[str_index] = '\0';
    return 0;
}

// Print given bigint to given file descriptor
int bigint_fprint(struct bigint *bi, FILE *out_file) {

    long long i, j, str_index = 0;

    BIGINT_CHUNK_TYPE highest_chunk, padding = 1;

    if (bi->chunks_used == 0) {
        fputc('0', out_file);
        return 0;
    }

    highest_chunk = bi->num[bi->chunks_used - 1];

    while (highest_chunk != 0ULL) {
        highest_chunk /= 10;
        padding *= 10;
    }

    padding /= 10;

    for (; padding > 0ULL; padding /= 10ULL) {
        fputc((bi->num[bi->chunks_used - 1] / padding % 10) + '0', out_file);
    }

    for (i = bi->chunks_used - 2; i >= 0; i--) {
        padding = BIGINT_CHUNK_PADDING / 10;

        while (padding != 0) {
            fputc((bi->num[i] / padding % 10) + '0', out_file);
            padding /= 10;
        }
    }

    return 0;
}

// Print library error code in human readable format
void bigint_fprint_error(int error_code, FILE *out_file) {
    switch (error_code) {
        case BIGINT_ERROR_ALLOC:
            fprintf(out_file, "BIGINT_ERROR_ALLOC: Failed to allocate memory");
            break;
        case BIGINT_ERROR_REALLOC:
            fprintf(out_file, "BIGINT_ERROR_REALLOC: Failed to reallocate memory");
            break;
        case BIGINT_ERROR_NEGATIVE:
            fprintf(out_file, 
                "BIGINT_ERROR_NEGATIVE: You cannot decrement bigint by"
                " the value greater than itself, it cannot be negative"
            );
            break;
        case BIGINT_ERROR_NO_SPACE:
            fprintf(out_file, 
                "BIGINT_ERROR_NO_SPACE: Cannot convert number to"
                " string, not enough space in the char array"
            );
            break;
        case BIGINT_ERROR_NOT_DIGIT:
            fprintf(out_file,
                "BIGINT_ERROR_NOT_DIGIT: Failed to parse char array, given"
                " string contains non digit characters"
            );
            break;
        default:
            fprintf(out_file,
                "BIGINT_ERROR: Unknown error occured (This should never happen)"
            );
            break;
    }
}