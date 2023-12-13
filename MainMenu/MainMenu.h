#pragma once

#ifndef _MAINMENU_H
#define _MAINMENU_H

#include <bits/stdc++.h>

// 主菜单，不允许在游戏中改变边框大小
// 默认可用范围width[1,80]，height[1,25]
class MainMenu
{
private:
    int width;
    int height;
    std::vector<std::vector<char>> storage;

public:
    MainMenu(int width = 52, int height = 10);
    void showMainMunu();
    void showNewGameMenu();
    void showRuleMenu();

private:
    int getWidth() const;
    int getHeight() const;
    void showMenu();
    void initMenu();
    void setMainMenu();
    void setNewGameMenu();
    void setRuleMenu();
};

#endif