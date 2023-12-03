/*  _____          _        
 * |  ___|_ _  ___| |_ ___  
 * | |_ / _` |/ __| __/ _ \ 
 * |  _| (_| | (__| || (_) |
 * |_|  \__,_|\___|\__\___/ 
 * 
 * This is just another simple factorial calculator. Facto allows you to
 * calculate factorials of the number using normal long double variables,
 * using bigint library and using stirling's formula. You can choose where
 * result of an operation should be printed, to the console or into the file.
 *
 * Made by rdobovic
 * 
 */

#include <stdio.h>
#include <sys/time.h>
#include <ctype.h>
#include <string.h>
#include <messages.h>
#include <helpers.h>
#include <factorial.h>
#include <constants.h>

int main() {

    FILE *out_file = stdout;                            // File where result is written to
    char out_file_name[FACTO_MAX_SAVED_FILENAME] = "";  // Name of the output file above
    int current_mode = FACTO_MODE_NORMAL;               // Current mode program is operating in
    char input_buff[FACTO_INPUT_BUFFER_SIZE] = "";      // This is where input from the console is stored

    // Print motd defined in messages.h
    print_project_motd();

    // Main loop
    while (1) {

        int i, cmd_len = 0;
        char *cmd_start = input_buff;

        // Print prompts and wait for the user input
        printf("[%s] >> ", facto_mode_name(current_mode));
        fgets(input_buff, FACTO_INPUT_BUFFER_SIZE, stdin);

        printf("\n");

        // Trim whitespaces
        while (isspace(*cmd_start) && *cmd_start != '\0')
            ++cmd_start;

        cmd_len = strlen(cmd_start);
        for (i = cmd_len - 1; i >= 0 && isspace(cmd_start[i]); i--) 
            cmd_start[i] = '\0';
        cmd_len = i + 1;

        // Command: exit
        if (strcmp(cmd_start, FACTO_CMD_EXIT) == 0) {
            printf(BOLD "Bye\n\n" BOLDEND);
            return 0;
        }

        // Command: help
        else if (strcmp(cmd_start, FACTO_CMD_HELP) == 0) {
            print_help_message();
        }

        // Command: mode
        else if (strcmp(cmd_start, FACTO_CMD_CURRENT_MODE) == 0) {
            printf("Facto is running in [%s] mode\n", facto_mode_name(current_mode));
        }

        // Command: version
        else if (strcmp(cmd_start, FACTO_CMD_VERSION) == 0) {
            printf(
                BOLD "Facto" BOLDEND " v%s\n"
                "Made by BrownBird Team <3\n", FACTO_VERSION
            );
        }

        // Command: normal (set mode to normal)
        else if (strcmp(cmd_start, FACTO_CMD_MODE_NORMAL) == 0) {
            current_mode = FACTO_MODE_NORMAL;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        // Command: precise (set mode to precise)
        else if (strcmp(cmd_start, FACTO_CMD_MODE_PRECISE) == 0) {
            current_mode = FACTO_MODE_PRECISE;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        // Command: stirling (set mode to stirling)
        else if (strcmp(cmd_start, FACTO_CMD_MODE_STIRLING) == 0) {
            current_mode = FACTO_MODE_STIRLING;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        // Command: <number>! (calculate factorial if the number)
        else if (isdigit(*cmd_start) && cmd_start[cmd_len - 1] == '!') {
            struct timeval start, stop, result;
            cmd_start[--cmd_len] = '\0';

            if (out_file != stdout) {
                freopen(out_file_name, "w", out_file);
                printf("Writing result to file \"%s\"\n", out_file_name);
            }

            gettimeofday(&start, NULL);
            
            switch (current_mode) {
                case FACTO_MODE_NORMAL:
                    factorial_calc_normal(cmd_start, out_file, stderr);
                    break;
                case FACTO_MODE_PRECISE:
                    factorial_calc_precise(cmd_start, out_file, stderr);
                    break;
                case FACTO_MODE_STIRLING:
                    factorial_calc_stirling(cmd_start, out_file, stderr);
                    break;
            }

            gettimeofday(&stop, NULL);
            timeval_subtract(&result, &stop, &start);

            fflush(out_file);
            printf(
                "Took %ld.%0.6lds to execute\n",
                result.tv_sec, result.tv_usec
            );
        }

        // Command: out [<file>] (set output file, where result is stored)
        else if (
            strncmp(cmd_start, FACTO_CMD_OUTPUT, (i = strlen(FACTO_CMD_OUTPUT))) == 0
            && (cmd_len == i || isspace(cmd_start[i]))
        ) {
            cmd_start += i;

            if (isspace(*cmd_start)) {
                
                while (isspace(*cmd_start))
                    ++cmd_start;

                if (strcmp(cmd_start, "STDOUT") == 0) {
                    if (out_file != stdout)
                        fclose(out_file);

                    out_file = stdout;
                    printf("Output file is now set to standard output (STDOUT)\n");
                } else {
                    FILE *tmp = fopen(cmd_start, "w");

                    if (!tmp) {
                        printf("facto error: unable to open specified file \"%s\" for writing\n", cmd_start);
                    } else {
                        if (out_file != stdout)
                            fclose(out_file);

                        out_file = tmp;
                        strncpy(out_file_name, cmd_start, FACTO_MAX_SAVED_FILENAME);
                        printf("Output file is now set to file \"%s\"\n", cmd_start);
                    }
                }

            } else {
                if (out_file == stdout) {
                    printf("Output file is set to standard output (STDOUT)\n");
                } else {
                    printf("Output file is set to file \"%s\"\n", out_file_name);
                }
            }
        }

        // Handle unknown command
        else {
            printf("facto error: Unknown command: %s\n", cmd_start);
        }

        printf("\n");
    }

    return 0;
}