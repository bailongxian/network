#include "error.h"

static unix_error(char *strMsg)
{  
	fprintf(stderr, "%s: %s\n", strMsg, strerror(errno));
	exit(0);
} 

static posix_error(int nCode, char *strMsg)
{ 
	fprintf(stderr, "%s: %s\n", strMsg, strerror(  nCode));
	exit(  0);
}

static dns_error(  char *strMsg)
{ 
	fprintf( stderr, "%s: %d\n", strMsg, h_errno);
	exit( 0);
}

static app_error( char *strMsg)
{ 
	fprintf(stderr, "%s\n", strMsg);
	exit(0);
}
