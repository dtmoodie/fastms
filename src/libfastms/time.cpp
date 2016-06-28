#include <SysTime.h>


#ifdef _MSC_VER

int gettimeofday(struct timeval2 *tv/*in*/, struct timezone2 *tz/*in*/)
{
    FILETIME ft;
    __int64 tmpres = 0;
    TIME_ZONE_INFORMATION tz_winapi;
    int rez = 0;

    ZeroMemory(&ft, sizeof(ft));
    ZeroMemory(&tz_winapi, sizeof(tz_winapi));

    GetSystemTimeAsFileTime(&ft);

    tmpres = ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    /*converting file time to unix epoch*/
    tmpres /= 10;  /*convert into microseconds*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
    if (tv)
    {
        tv->tv_sec = (__int32)(tmpres*0.000001);
        tv->tv_usec = (tmpres % 1000000);
    }
    


    //_tzset(),don't work properly, so we use GetTimeZoneInformation
    
    rez = GetTimeZoneInformation(&tz_winapi);
    if (tz)
    {
        tz->tz_dsttime = (rez == 2) ? true : false;
        tz->tz_minuteswest = tz_winapi.Bias + ((rez == 2) ? tz_winapi.DaylightBias : 0);
    }
    

    return 0;
}
#else




#endif