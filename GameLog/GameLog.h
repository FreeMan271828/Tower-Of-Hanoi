#pragma once

#ifndef _GAMELOG_H
#define _GAMELOG_H

#include <bits/stdc++.h>
#include <ostream>

class Time
{
private:
    int hour;
    int minute;
    int second;

public:
    // Constructor
    Time();
    Time(int h, int m, int s);
    // 初始化时间为0
    void initTime();
    // 后置++重载，使(class)Time++成功
    Time &operator++(int);
    // 根据传入秒数格式化时间
    Time &setTime(int num);
    void setTime(int hour, int minute, int second);
    // 展示时间
    void showTime() const;
    // 左移运算重载可以使用cout<<(class)Time
    friend std::ostream &operator<<(std::ostream &cout, const Time &time);
    // 获取时分秒
    int getHour() const;
    int getMimute() const;
    int getSecond() const;
};
std::ostream &operator<<(std::ostream &out, const Time &time);

class GameRecord : public Time
{
private:
    // 使用的步数
    int steps;
    // 使用的时间
    Time time;

public:
    // 还可以使用
    // showTime()
    // getTime()
    // addTime()
    // cout<<(class)Time
    //(class)Time++
    GameRecord();
    void init();
    int getSteps() const;
    void setSteps(const int steps);
    void addSteps();
    void reduceSteps();
    friend std::ostream &operator<<(std::ostream &out, const GameRecord &gameRecord);
};
std::ostream &operator<<(std::ostream &out, const GameRecord &gameRecord);
#endif