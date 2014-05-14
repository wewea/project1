#ifndef _SETTIMER_HPP_
#define _SETTIMER_HPP_	
#include <sys/time.h>
#include <stdio.h>


class SetTimer
{
public:
	int SetTime(struct timeval &tv, time_t sec);	
	int CheckTime(struct timeval &tv, time_t sec);
};

int SetTimer::SetTime(struct timeval &tv, time_t sec)
{
	gettimeofday(&tv, NULL);
	tv.tv_sec += sec;
	return 1;
}

int SetTimer::CheckTime(struct timeval &tv, time_t sec)
{
	struct timeval ctv;	
	gettimeofday(&ctv, NULL);

	if(ctv.tv_sec == tv.tv_sec)
	{
		gettimeofday(&tv, NULL);		
		tv.tv_sec += sec;
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif
