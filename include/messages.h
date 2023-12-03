/*
 * PROJECT MESSAGES
 *
 * This file contains simple functions used to print large text messages used
 * in this project. There are no comments since functions just print stuff.
 * 
 * Made by rdobovic
 * 
 */

#ifndef _INCLUDE_MESSAGES_H_
#define _INCLUDE_MESSAGES_H_

#include <stdio.h>
#include <factorial.h>
#include <constants.h>

void print_project_motd(void) {
    printf(
        " _____          _        \n"
        "|  ___|_ _  ___| |_ ___  \n"
        "| |_ / _` |/ __| __/ _ \\ \n"
        "|  _| (_| | (__| || (_) |\n"
        "|_|  \\__,_|\\___|\\__\\___/ \n\n"

        "A simple factorial calculator\n"
        "Made by BrownBird Team <3\n\n"

        "Type help for the list of commands and program description\n\n"
    );
}

void print_help_message(void) {
    printf(
        BOLD "Facto" BOLDEND " is a simple factorial calculator. It can be used to calculate\n"
        "factorials in 3 different ways, each with it's own way and precision.\n"
        "Following commands are supported:\n\n"

        BOLD FACTO_CMD_HELP "\n" BOLDEND
        "    Prints this help message\n\n"

        BOLD "<number>!\n" BOLDEND
        "    Calculates factorial of given <number> in current mode\n\n"

        BOLD FACTO_CMD_CURRENT_MODE "\n" BOLDEND
        "    Displays in which mode program is operating in\n\n"

        BOLD FACTO_CMD_MODE_NORMAL "\n" BOLDEND
        "    Switches to normal mode, this mode uses double variables to store\n"
        "    result of factorial and thus can calculate up to %s!\n\n"

        BOLD FACTO_CMD_MODE_PRECISE "\n" BOLDEND
        "    Switches to precise mode, this mode uses big integers to calculate\n"
        "    factorial and should be able to calculate factorial of any number,\n"
        "    but because of hardware limitations this mode is limited to %s!\n\n"

        BOLD FACTO_CMD_MODE_STIRLING "\n" BOLDEND
        "    Switches to stirling mode, this mode approximates value of factorial\n"
        "    using stirling's formula, it also uses doubles like the normal mode and\n"
        "    is limited to %s!\n\n"

        BOLD FACTO_CMD_OUTPUT " <path>\n" BOLDEND
        "    Saves result of factorial calculation into specified file, if called\n"
        "    without an argument prints current output file. If you wish to reset\n"
        "    output back to standard output, type "BOLD"STDOUT"BOLDEND" as filename\n\n"

        BOLD FACTO_CMD_VERSION "\n" BOLDEND
        "    Prints current program version\n\n"

        BOLD FACTO_CMD_EXIT "\n" BOLDEND
        "    Finishes the execution of the program\n\n"

        "good luck :)\n",

        FACTORIAL_MAX_NORMAL, FACTORIAL_MAX_PRECISE, FACTORIAL_MAX_STIRLING
    );
}

#endif
