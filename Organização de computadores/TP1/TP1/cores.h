#ifndef CORES_H
#define CORES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define ANSI_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"

#define RED(string) ANSI_COLOR_RED string ANSI_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_RESET

void printErr(char *);

void printWarning(char *);

void printSuccess(char *);


#endif