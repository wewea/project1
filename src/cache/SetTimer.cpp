#ifndef _SETTIMER_HPP_
#define _SETTIMER_HPP_	
#include <sys/time.h>



class SetTimer
{
public:
	SetTimer();
	~SetTimer();
	SetTime(struct timval &tv, time_t sec);	
	CheckTime(struct timval &tv, time_t sec);
};

int SetTimer::SetTime(struct timval &tv, time_t sec)
{
	gettimeofday(&tv, NULL);
	tv.sec += sec;
	return 1;
}

int SetTimer::CheckTime(struct timval &tv, time_t sec)
{
	struct timeval ctv;	
	gettimeofday(&ctv, NULL);

	if(ctv.sec == tv.sec)
	{
		gettimeofday(&tv, NULL);		
		tv.sec += sec;
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif
