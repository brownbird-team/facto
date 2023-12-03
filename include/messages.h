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
        "Facto is a simple factorial calculator. It can be used to calculate\n"
        "factorials in 3 different ways, each with it's own way and precision.\n"
        "Following modes (ways) are supported, you can enter each mode by\n"
        "typing its name\n\n"

        ">> normal <<\n"
        "This mode uses double variables to store result of factorial and thus\n"
        "can calculate up to %s!\n\n"

        ">> precise <<\n"
        "This mode uses big integers to calculate factorial and should be able\n"
        "to calculate factorial of any number, but because of hardware\n"
        "limitations this mode is limited to %s!\n\n"

        ">> stirling <<\n"
        "This mode approximates value of factorial using stirling's formula, it\n"
        "also uses doubles like the normal mode and is limited to %s!\n\n"

        "To calculate factorial you simply type <number>!\n"
        "And of course command help prints this message, good luck :)\n\n",

        FACTORIAL_MAX_NORMAL, FACTORIAL_MAX_PRECISE, FACTORIAL_MAX_STIRLING
    );
}

#endif
