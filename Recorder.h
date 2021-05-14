#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Mouse.h"
#include <ctime>
#include "Actions.h"
#include "Buffer.h"
#include <chrono>
#include "Timer.h"

class Recorder
{
private:
	Buffer buffer;
	Mouse mouse;
	long lastX;
	long lastY;
	bool lastState;
	Timer clock;
public:
	bool saveData(const std::string  &fileName);
	void recordLine();
	bool continueRec(const std::string  &fileName);
	void stop();
	Recorder();
	~Recorder();
};

