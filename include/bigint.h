/*
 * SIMPLE BIGINT LIBRARY
 * 
 * This is a header file for simple bigint library used to calculate values
 * of large factorials. Since not all basic mathematical and logical operations 
 * are needed to calculate factorial of a number, only following operations 
 * are supported:
 * 
 * - addition
 * - multiplication
 * - increment (add value stored in a long variable)
 * - decrement (subtract value stored in a long variable)
 * - is_zero (returns true if number is equal to zero)
 * 
 * Library allows you to convert number stored as a char array into a bigint.
 * Then you can perform operations using library functions and in the end you
 * can convert numbers back to char array or print them to standard output.
 * 
 * Numbers are internally stored as arrays of unsigned long long integers, and
 * all operations are preformed on such arrays.
 * 
 * Made by rdobovic
 * 
 */

#ifndef _INCLUDE_BIGINT_H_
#define _INCLUDE_BIGINT_H_

#include <stdio.h>
#include <stdlib.h>

// Allocate this many chunks at once
#define BIGINT_ALLOC_CHUNKS 10
// Variable type of each chunk
#define BIGINT_CHUNK_TYPE unsigned long long

// Number of bits within a single chunks that can be used
#define BIGINT_CHUNK_BITS (sizeof(BIGINT_CHUNK_TYPE) / 2 * 8 - 1)

// If you don't want to use bigint_init and global variables
// you are free to calculate and set this constants manually for your
// system, just replace variables with calculated numbers
#define BIGINT_CHUNK_DIGITS __bigint_chunk_decimal_digits
#define BIGINT_CHUNK_PADDING __bigint_chunk_decimal_digits_padding

// Number of decimal digits a single chunk can hold
extern int __bigint_chunk_decimal_digits;
// 10 to the power of number of digits above (used for carry calculations)
extern BIGINT_CHUNK_TYPE __bigint_chunk_decimal_digits_padding;

// Structure used to hold bigint
struct bigint {
    int chunks_used;  // Number of chunks currently used to hold value of bigint
    long long *num;   // Array of chunks holding the value of bigint
    size_t num_size;  // Current size of chunks array
};

// Errors that can occur
enum bigint_errors {
    BIGINT_ERROR_ALLOC     = 1, // Failed to allocate memory while creating bigint
    BIGINT_ERROR_REALLOC   = 2, // Failed to increase the size of bigint 
    BIGINT_ERROR_NEGATIVE  = 3, // Cannot subtract value greater than bigint
    BIGINT_ERROR_NOT_DIGIT = 4, // Parser found a non digit inside the given str
    BIGINT_ERROR_NO_SPACE  = 5, // Not enough space in given char array
};

// Macro used to print bigint to standard output, for more info see
// bigint_fprint function description
#define bigint_print(bi) bigint_fprint((bi), stdout)

// Macro used to print bigint library error code to stderr, for more info see
// bigint_fprint_error function description
#define bigint_print_error(error_code) bigint_fprint_error((error_code), stderr)

/*
 * Function: bigint_init
 * -----------------------
 * 
 * Initilize global variabled used by the library. 
 * 
 * If you defined constants BIGINT_CHUNK_DIGITS and BIGINT_CHUNK_PADDING 
 * manually, you can just ignore this function. Otherwise bigint_init() should 
 * be called before any other library function, or strange things will happen.
 * 
 * returns: zero on success, it will never fail
 */

int bigint_init(void);


/*
 * Function: bigint_new
 * ----------------------
 * 
 * A simple function used to allocate new bigint structure from the heap. When
 * you finish using allocated bigint structure you should free the memory using
 * bigint_free function;
 * 
 * returns: zero on success, error code on failure
 */

struct bigint * bigint_new(void);


/*
 * Function: bigint_free
 * ---------------------
 * 
 * Frees the memory allocated using function bigint_new, and thats it.
 * 
 * bi: pointer to the memory that should be freed
 * 
 * returns: zero on success, error code on failure
 */

int bigint_free(struct bigint *bi);


/*
 * Function: bigint_realloc
 * ------------------------
 * 
 * Used to expand memory of the bigint by the length given in 
 * BIGINT_ALLOC_CHUNKS constant. Function is intended for internal use and there
 * is no need to use it outside of bigint library.
 * 
 * bi: pointer to bigint whoose memory should be expanded
 * 
 * returns: zero on success, error code on failure
 */

int bigint_realloc(struct bigint *bi);


/*
 * Function: bigint_parse
 * ----------------------
 * 
 * Used to parse char array of ASCII digits and store it as a single number
 * within bigint structure. Number must be in base 10.
 * 
 * bi: pointer to bigint structure where number should be stored
 * str: pointer to the char array of digits
 * str_len: length of char array
 * 
 * returns: zero on success, error code on failure
 */

int bigint_parse(struct bigint *bi, char *str, long str_len);


/*
 * Function: bigint_copy
 * ---------------------
 * 
 * Simple function used to copy value from one bigint structure to another.
 * 
 * from: pointer to bigint structure holding the value to copy
 * to: pointer to bigint structure where that value should be stored
 * 
 * returns: zero on success, error code on failure
 */

int bigint_copy(struct bigint *from, struct bigint *to);


/*
 * Function: bigint_add
 * --------------------
 * 
 * Used to SUM two bigints and store result into another bigint structure
 * 
 * result: pointer to bigint structure where result of operation should be saved
 * a: pointer to bigint structure holding the first number to sum
 * b: pointer to bigint structure holding the second number to sum
 * 
 * returns: zero on success, error code on failure
 */

int bigint_add(struct bigint *result, struct bigint *a, struct bigint *b);


/*
 * Function: bigint_mul
 * --------------------
 * 
 * Used to MULTIPLY two bigints and store result into another bigint structure
 * 
 * result: pointer to bigint structure where result of operation should be saved
 * a: pointer to bigint structure holding the first factor
 * b: pointer to bigint structure holding the second factor
 * 
 * returns: zero on success, error code on failure
 */

int bigint_mul(struct bigint *result, struct bigint *a, struct bigint *b);


/*
 * Function: bigint_incr
 * ---------------------
 * 
 * Used to INCREMENT bigint structure by the value of value variable
 * 
 * bi: pointer to bigint structure to increment
 * value: given bigint should be incremented by this value
 * 
 * returns: zero on success, error code on failure
 */

int bigint_incr(struct bigint *bi, long value);


/*
 * Function: bigint_decr
 * ---------------------
 * 
 * Used to DECREMENT bigint structure by the value of value variable. But the
 * value of variable must not be greater than the value of bigint. Otherwise
 * an error will occur.
 * 
 * bi: pointer to bigint structure to decrement
 * value: given bigint should be decremented by this value
 * 
 * returns: zero on success, error code on failure
 */

int bigint_decr(struct bigint *bi, long value);


/*
 * Function: bigint_is_zero
 * ------------------------
 * 
 * Used to check if given bigint is equal to zero
 * 
 * bi: pointer to bigint structure to check
 * 
 * returns: zero on success, will never fail
 */

int bigint_is_zero(struct bigint *bi);


/*
 * Function: bigint_to_string
 * --------------------------
 * 
 * Converts number stored in given bigint structure into array of ASCII
 * characters. It stores those charactes in given char array. If given char
 * array is too small to store the whole number error code BIGINT_ERROR_NO_SPACE
 * will be returned.
 * 
 * bi: pointer to bigint structure to convert
 * str: pointer to char array where result should be stored
 * str_len: max length of given char array (nullbyte not included)
 * 
 * returns: zero on success, error code on failure
 */

int bigint_to_string(struct bigint *bi, char *str, long str_len);


/*
 * Function: bigint_fprint
 * ----------------------
 * 
 * Converts the bigint into readable format and prints it to specified file.
 * 
 * bi: pointer to bigint structure to print
 * 
 * returns: zero on success, error code on failure
 */

int bigint_fprint(struct bigint *bi, FILE *out_file);


/*
 * Function: bigint_fprint_error
 * --------------------
 * 
 * Prints library error code in human readable format to specified file.
 * 
 * error_code: one of the codes from bigint_errors enumeration
 * 
 * returns: noting
 */

void bigint_fprint_error(int error_code, FILE *out_file);

#endif