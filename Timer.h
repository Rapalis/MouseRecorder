#pragma once
#include <chrono>

class Timer
{
private:
	bool isCounting;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
public:
	void start();
	long long stop();
	bool isTimerCounting() const;
	Timer();
	~Timer();
};

