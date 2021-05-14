#pragma once
#include "Mouse.h"
#include <string>
#include <fstream>
#include "Actions.h"
#include "Buffer.h"

class Player
{
private:
	Buffer buffer;
	double speed;
	Mouse mouse;
public:
	bool openRecord(const std::string& fileName);
	void restRecord();
	void setSpeed(const double & s);
	void stop();
	double getSpeed() const { return speed; }
	//unsigned char getRepeatTimes() const { return repeatTimes; }
	bool canPlay();
	void playLine();
	Player();
	~Player();
};

