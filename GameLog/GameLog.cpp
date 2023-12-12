#include "GameLog.h"
GameRecord::GameRecord()
{
    this->steps = 0;
    this->time.initTime();
}

void GameRecord::init()
{
    this->steps = 0;
    this->time.initTime();
}

int GameRecord::getSteps() const
{
    return this->steps;
}

void GameRecord::setSteps(const int steps)
{
    this->steps = steps;
}

void GameRecord::addSteps()
{
    this->steps++;
}

void GameRecord::reduceSteps()
{
    this->steps--;
}

Time::Time() : hour(0), minute(0), second(0) {}

Time::Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

void Time::initTime()
{
    this->hour = 0;
    this->second = 0;
    this->minute = 0;
}

Time &Time::operator++(int)
{
    Time *copyTime = new Time(this->hour, this->minute, this->second);
    this->second++;
    if (this->second >= 60)
    {
        this->second %= 60;
        this->minute++;
    }
    if (this->minute >= 60)
    {
        this->minute %= 60;
        this->hour++;
    }
    return *copyTime;
}

Time &Time::setTime(int num)
{
    this->second = num;
    if (this->second >= 60)
    {
        this->second %= 60;
        this->minute++;
    }
    if (this->minute >= 60)
    {
        this->minute %= 60;
        this->hour++;
    }
    return *this;
}

void Time::setTime(int hour, int minute, int second)
{
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

void Time::showTime() const
{
    std::cout << hour << ":" << minute << ":" << second;
}

int Time::getHour() const
{
    return this->hour;
}

int Time::getMimute() const
{
    return this->minute;
}

int Time::getSecond() const
{
    return this->second;
}

int Time::toSeconds() const
{
    return this->hour * 3600 + this->minute * 60 + this->second;
}

std::ostream &operator<<(std::ostream &out, const Time &time)
{
    out << '\r' << time.hour << ":" << time.minute << ":" << time.second;
    return out;
}

std::ostream &operator<<(std::ostream &out, const GameRecord &gameRecord)
{
    out << "\033[36m";
    out << "你的步数是 " << gameRecord.getSteps() << '\n';
    out << "你的时间是" << gameRecord.getHour() << ":" << gameRecord.getMimute() << ":" << gameRecord.getSecond();
    out << "\033[0m";
    return out;
}
