/*
 * FACTORIAL CALCULATION
 *
 * This functions are abstraction for factorial calculation, they take number
 * string from console and a file descriptor where they should write result of
 * the calculation and another file where they should write errors
 * 
 * Made by rdobovic
 * 
 */

#include <math.h>
#include <string.h>
#include <factorial.h>
#include <helpers.h>
#include <bigint.h>
#include <constants.h>

// Calculate factorial using double variables
void factorial_calc_normal(char *str, FILE *out_file, FILE *err_file) {
    int n;
    double result = 1;

    if (!digits_only(str)) {
        fprintf(err_file, "facto error: Factorial must contain only digits 0-9\n");
        return;
    }

    if (!number_smaller_or_equal(str, FACTORIAL_MAX_NORMAL)) {
        fprintf(err_file, 
            "facto error: Maximum factorial [%s] mode can calculate is %s!\n",
            facto_mode_name(FACTO_MODE_NORMAL), FACTORIAL_MAX_NORMAL
        );
        return;
    }

    sscanf(str, "%d", &n);

    while (n > 0)
        result *= (n--);

    fprintf(out_file, "%s! = %.2lf\n", str, result);
}

// Calculate factorial using bigint library
void factorial_calc_precise(char *str, FILE *out_file, FILE *err_file) {
    int i, err = 0;
    struct bigint *n, *res[2];

    if (!digits_only(str)) {
        fprintf(err_file, "facto error: Factorial must contain only digits 0-9\n");
        return;
    }

    if (!number_smaller_or_equal(str, FACTORIAL_MAX_PRECISE)) {
        fprintf(err_file, 
            "facto error: In [%s] mode facto calc is limited to %s!\n", 
            facto_mode_name(FACTO_MODE_PRECISE), FACTORIAL_MAX_PRECISE
        );
        return;
    }

    bigint_init();

    n = bigint_new();
    res[0] = bigint_new();
    res[1] = bigint_new();

    if (!n || !res[0] || !res[1]) {
        fprintf(err_file, "facto error: Failed to allocate memory for bigint library\n");
        return;
    }

    err |= bigint_parse(n, str, strlen(str));
    err |= bigint_parse(res[1], "1", 1);

    if (!err)
        for (i = 0; !bigint_is_zero(n); i = !i) {
            err |= bigint_mul(res[i], res[!i], n);
            err |= bigint_decr(n, 1);

            if (err) break;
        }

    if (err) {
        fprintf(err_file, "facto error: ");
        bigint_fprint_error(err, err_file);
        fprintf(err_file, "\n\n");
        return;
    }

    fprintf(out_file, "%s! = ", str);
    bigint_fprint(res[i], out_file);
    fprintf(out_file, "\n");

    bigint_free(n);
    bigint_free(res[0]);
    bigint_free(res[1]);
}

// Calculate factorial using stirling formula
void factorial_calc_stirling(char *str, FILE *out_file, FILE *err_file) {
    
    double n, result;

    if (!digits_only(str)) {
        fprintf(err_file, "facto error: Factorial must contain only digits 0-9\n");
        return;
    }

    if (!number_smaller_or_equal(str, FACTORIAL_MAX_STIRLING)) {
        fprintf(err_file, 
            "facto error: Maximum factorial [%s] mode can calculate is %s!\n", 
            facto_mode_name(FACTO_MODE_NORMAL), FACTORIAL_MAX_STIRLING
        );
        return;
    }

    sscanf(str, "%lf", &n);

    result = sqrt(2 * FACTO_PI * n) * pow(n / FACTO_E, n);

    fprintf(out_file, "%s! = %.2lf\n", str, result);
}