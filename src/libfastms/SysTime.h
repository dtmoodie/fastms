#ifdef _MSC_VER
#include <time.h>
#include <windows.h> 

#define timeval timeval2
#define timezone timezone2
const __int64 DELTA_EPOCH_IN_MICROSECS = 11644473600000000;

/* IN UNIX the use of the timezone struct is obsolete;
I don't know why you use it. See http://linux.about.com/od/commands/l/blcmdl2_gettime.htm
But if you want to use this structure to know about GMT(UTC) diffrence from your local time
it will be next: tz_minuteswest is the real diffrence in minutes from GMT(UTC) and a tz_dsttime is a flag
indicates whether daylight is now in use
*/
struct timezone2
{
    __int32  tz_minuteswest; /* minutes W of Greenwich */
    bool  tz_dsttime;     /* type of dst correction */
};

struct timeval2 {
    __int32    tv_sec;         /* seconds */
    __int32    tv_usec;        /* microseconds */
};
int gettimeofday(struct timeval2 *tv/*in*/, struct timezone2 *tz/*in*/);
#else
#include <sys/time.h>
#endif