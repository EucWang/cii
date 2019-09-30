#include <string.h>
#include <stdio.h>
#include "str.h"
/*lint -e613
strerror is defined here because some vendors don't provide it.
*/
char *my_strerror(int errnum) {
	extern int sys_nerr;
    //warning: `sys_nerr' is deprecated; use `strerror' or `strerror_r' instead
//	extern char *sys_errlist[];
    extern const char *const sys_errlist[];
// warning: `sys_errlist' is deprecated; use `strerror' or `strerror_r' instead
	static char null[1] = { 0 };

	if (errnum <= 0)
		return null;
	else if (errnum >= sys_nerr) {
		static char errmsg[50];
		sprintf(errmsg, "error %d", errnum);
		return errmsg;
	} else
		return sys_errlist[errnum];
}
