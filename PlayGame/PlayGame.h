#pragma once

#ifndef _PLAYGAME_H
#define _PLAYGAME_H

#include "../MainMenu/MainMenu.h"
#include "../GameLog/GameLog.h"
#include "../Tower/Tower.h"
#include "../FileOper/FileOper.h"
#include <conio.h>
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
    void OutputPrompt();
    // 中途退出保存文件
    void HoldFile(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate);
    void Win(GameRecord gameRecord, int NumOfPlate);
    // 成功时保存文件
    void PreserveFile(GameRecord GameRecord, int NumOfPlate);
    void Fail();
    void noPlate(int towerIndex);
    void illegalInput();
    char wrongMove(int towerIndex);
};
#endif