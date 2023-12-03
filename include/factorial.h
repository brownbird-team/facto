#ifndef _INCLUDE_FACTORIAL_H_
#define _INCLUDE_FACTORIAL_H_

#include <stdio.h>

// If your system is 32-bit, you should lower the limit of first and third mode
// since your long double variables are smaller

// Largest factorial that can fit into double
#define FACTORIAL_MAX_NORMAL    "30"
// Limited for practical reasons, feel free to change this
#define FACTORIAL_MAX_PRECISE   "1000001"
// Largest factorial that can fit into double
#define FACTORIAL_MAX_STIRLING  "30"

/*
 * Function: factorial_calc_normal
 * -------------------------------
 * 
 * Calculate factorial of number stored inside char array. Print result to
 * out_file file descriptor, if an error occurs print it to err_file. This
 * function performs calculatons using long double variables, so there is a
 * limit on how big factorial it can calculate.
 * 
 * str: pointer to char array containing ascii number
 * str_len: length of str char array
 * out_file: file where result should be printed
 * err_file: file where error should be printed if it occurs
 */

void factorial_calc_normal(char *str, FILE *out_file, FILE *err_file);


/*
 * Function: factorial_calc_precise
 * --------------------------------
 * 
 * Calculate factorial of number stored inside char array. Print result to
 * out_file file descriptor, if an error occurs print it to err_file. This
 * function performs calculatons using local "simple bigint" library, that means
 * it can calculate factorial of any size, but for practical reasons, it is
 * limited to number stored in FACTORIAL_MAX_PRECISE macro
 * 
 * str: pointer to char array containing ascii number
 * str_len: length of str char array
 * out_file: file where result should be printed
 * err_file: file where error should be printed if it occurs
 */

void factorial_calc_precise(char *str, FILE *out_file, FILE *err_file);


/*
 * Function: factorial_calc_stirling
 * ---------------------------------
 * 
 * Calculate factorial of number stored inside char array. Print result to
 * out_file file descriptor, if an error occurs print it to err_file. This
 * function calculates aproximation of factorial using stirling's formula,
 * it also uses doubles for calculation, so factorial it can calculate is 
 * limited.
 * 
 * str: pointer to char array containing ascii number
 * str_len: length of str char array
 * out_file: file where result should be printed
 * err_file: file where error should be printed if it occurs
 */

void factorial_calc_stirling(char *str, FILE *out_file, FILE *err_file);

#endif