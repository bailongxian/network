#ifndef _ERROR_H
#define _ERROR_H
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>

static void unix_error(char *strMsg );
static void posix_error( int nCode, char* strMsg);
static void dns_error( char *strMsg);
static void app_error( char *strMsg);
#endif
