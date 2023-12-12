#pragma once
#ifndef _FILEOPER_H
#define _FILEOPER_H

#include <bits/stdc++.h>
#include "../Tower/Tower.h"
#include "../GameLog/GameLog.h"

class FileOper
{
public:
    // 上一把数据的存储地址，用于continue，存储时间，步数以及每个塔的盘子数
    static std::string tempStorePath;
    // 历史胜利数据的存储地址，存储时间，步数
    static std::string historyPath;
    // 最佳记录地址
    static std::string bestDataPath;

public:
    // 要退出时保存当前游戏记录
    static void preserveInQuit(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate);
    // 胜利时保存游戏记录
    static void preserveInWin(GameRecord gameRecord, int NumOfPlate);
    // 存储最佳历史记录
    static void preserveInBest(GameRecord gameRecord, int NumOfPlate);
};
#endif