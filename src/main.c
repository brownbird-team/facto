#include <stdio.h>
#include <sys/time.h>
#include <ctype.h>
#include <string.h>
#include <messages.h>
#include <helpers.h>
#include <factorial.h>
#include <constants.h>

#define FACTO_INPUT_BUFFER_SIZE 1000

int main() {

    FILE *out_file = stdout;
    int current_mode = FACTO_MODE_NORMAL;
    char input_buff[FACTO_INPUT_BUFFER_SIZE] = "";


    print_project_motd();

    // Main loop
    while (1) {

        int i, cmd_len = 0;
        char *cmd_start = input_buff;

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

        if (strcmp(cmd_start, FACTO_CMD_EXIT) == 0) {
            printf("Bye\n\n");
            return 0;
        }

        else if (strcmp(cmd_start, FACTO_CMD_HELP) == 0) {
            print_help_message();
        }

        else if (strcmp(cmd_start, FACTO_CMD_CURRENT_MODE) == 0) {
            printf("Facto is running in [%s] mode\n", facto_mode_name(current_mode));
        }

        else if (strcmp(cmd_start, FACTO_CMD_VERSION) == 0) {
            printf(
                "Facto v%s\n"
                "Made by BrownBird Team <3\n", FACTO_VERSION
            );
        }

        else if (strcmp(cmd_start, FACTO_CMD_MODE_NORMAL) == 0) {
            current_mode = FACTO_MODE_NORMAL;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        else if (strcmp(cmd_start, FACTO_CMD_MODE_PRECISE) == 0) {
            current_mode = FACTO_MODE_PRECISE;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        else if (strcmp(cmd_start, FACTO_CMD_MODE_STIRLING) == 0) {
            current_mode = FACTO_MODE_STIRLING;
            printf("Switching mode to [%s]\n", facto_mode_name(current_mode));
        }

        else if (isdigit(*cmd_start) && cmd_start[cmd_len - 1] == '!') {
            struct timeval start, stop, result;
            cmd_start[--cmd_len] = '\0';

            if (out_file != stdout) {
                printf("Writing result to this file");
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

            printf(
                "Took %ld.%0.6lds to execute\n", 
                result.tv_sec, result.tv_usec
            );
        }

        else {
            printf("facto error: Unknown command: %s\n", cmd_start);
        }

        out_file = stdout;
        printf("\n");
    }

    return 0;
}