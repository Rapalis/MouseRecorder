#include "Timer.h"



void Timer::start()
{
	begin = std::chrono::steady_clock::now();
	isCounting = true;
}

long long Timer::stop()
{
	if (isCounting)
	{
		end = std::chrono::steady_clock::now();
		isCounting = false;
		return std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	}
	else
		return -1;
}

bool Timer::isTimerCounting() const
{
	return isCounting;
}

Timer::Timer(): isCounting(false)
{
}


Timer::~Timer()
{
}
