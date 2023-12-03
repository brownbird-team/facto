/*
 * CONSTANTS
 *
 * This file contains some constants used across the whole project, feel free
 * to modify them as you wish
 * 
 * Made by rdobovic
 * 
 */

#ifndef _INCLUDE_CONSTANTS_H_
#define _INCLUDE_CONSTANTS_H_

// Mathematical constants
#define FACTO_E  2.71828182845904523536
#define FACTO_PI 3.14159265358979323846

// Current version
#define FACTO_VERSION "1.0.0"

// Command to print help message
#define FACTO_CMD_HELP "help"
// Command to exit the program
#define FACTO_CMD_EXIT "exit"
// Command to set output file, where results are stored
#define FACTO_CMD_OUTPUT "out"
// Command to print program version (defined above)
#define FACTO_CMD_VERSION "version"
// Command to print current mode
#define FACTO_CMD_CURRENT_MODE "mode"

// Command to set mode to normal
#define FACTO_CMD_MODE_NORMAL "normal"
// Command to set mode to precise (bigint)
#define FACTO_CMD_MODE_PRECISE "precise"
// Command to set mode to stirling (formula)
#define FACTO_CMD_MODE_STIRLING "stirling"

// Max size of command entered
#define FACTO_INPUT_BUFFER_SIZE 1500
// Max size of filename
// Greater size of the filename can cause unexpected behaviour
#define FACTO_MAX_SAVED_FILENAME 1000

// If this is unix-like system bold some things in the console,
// otherwise just print everithing normally (windows CMD doesn't
// support this escape codes, I think)
#ifdef __unix__
#define BOLD "\033[1m"
#define BOLDEND "\033[0m"
#else
#define BOLD ""
#define BOLDEND ""
#endif

// Available modes program can run in
enum facto_modes {
    FACTO_MODE_NORMAL,
    FACTO_MODE_PRECISE,
    FACTO_MODE_STIRLING,
};

#endif