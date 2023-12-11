#pragma once

#ifndef _Tower_H
#define _Tower_H

#include <bits/stdc++.h>

class Plate
{
private:
    int length; // 盘子的长度
public:
    // Getter and Setter
    void setLength(const int l);
    int getLength() const;
};

class Tower : public Plate
{
private:
    int num;            // 盘子数
    int maxPlateLength; // 最大盘子长度
    std::vector<Plate> plates;

public:
    // Constractor
    Tower();
    Tower(int num);
    // Getter and Setter
    void setNum(const int n);
    int getNum() const;
    int getMaxPlateLength() const;
    // 设置塔的盘子长度
    void setPlatesLength(std::vector<int> &platesLength);
    // 返回该塔所有盘子长度
    std::vector<int> getPlatesLength() const;
    // 判断当前塔是否正确
    bool isRight();
    // a移动到b，返回true表示移动成功，否则失败
    friend bool move(Tower &a, Tower &b);

    // 左移运算重载，逻辑化输出
    friend std::ostream &operator<<(std::ostream &out, const Tower &hanoi);
    // 渲染多个塔输出
    static void render(std::vector<Tower> Hanios, int maxLength, int maxPlateNum);
};
bool move(Tower &a, Tower &b);
std::ostream &operator<<(std::ostream &out, const Tower &hanoi);

#endif