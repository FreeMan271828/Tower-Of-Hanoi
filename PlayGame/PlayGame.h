#pragma once

#ifndef _PLAYGAME_H
#define _PLAYGAME_H

#include "../MainMenu/MainMenu.h"
#include "../GameLog/GameLog.h"
#include "../Tower/Tower.h"
#include "../FileOper/FileOper.h"
#include <conio.h>
#include <cstdio>
class Game
{
public:
    void play();
    void playNewGame(MainMenu &menu);
    void continueGame();
    void demoGame();
    void getHistory(std::string path);

private:
    // 内部接口
    std::vector<std::string> splitStringBySpace(const std::string &str);
    void playGame(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate);
    // 输出提示语句
    void OutputPrompt();
    // 中途退出保存文件
    void HoldFile(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate);
    // 处理胜利时
    void Win(GameRecord gameRecord, int NumOfPlate);
    // 成功时保存文件
    void PreserveFile(GameRecord GameRecord, int NumOfPlate);
    // 输出最佳历史记录
    void outputBestHistory(int NumOfPlate);
    //  处理失败时
    void Fail();
    // 异常处理
    void noPlate(int towerIndex);
    void illegalInput();
    char wrongMove(int towerIndex);
};
#endif