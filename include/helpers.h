#ifndef _INCLUDE_HELPERS_H_
#define _INCLUDE_HELPERS_H_

#include <sys/time.h>

/*
 * Function: digits_only
 * ---------------------
 * 
 * Check if char array contains only digits
 * 
 * str: char array to check
 */

int digits_only(char *str);


/*
 * Function: facto_mode_name
 * -------------------------
 * 
 * Returns pointer to string representation of mode
 * 
 * mode_code: one of values from enum facto_modes
 */

char * facto_mode_name(int mode_code);


/*
 * Function: number_smaller_or_equal
 * ---------------------------------
 * 
 * Check if number stored in first char array is smaller than
 * 
 * number: number to check (ascii string)
 * max_value: max value number can have (ascii string)
 */

int number_smaller_or_equal(char *number, char *max_value);


/*
 * Function: timeval_subtract
 * ---------------------------------
 * 
 * Subtracts timeval x - y and stores result in result
 * 
 * result: result is stored here
 * x, y: values to subtract
 */

int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y);

#endif