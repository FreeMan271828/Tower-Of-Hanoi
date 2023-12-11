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
    // Getter
    int getWidth() const;
    int getHeight() const;

public:
    // Constructor
    MainMenu(int width = 52, int height = 10);

private:
    // 设置主页面和新游戏页面，在外部无法调用
    void initMenu();
    // TODO:该页面需要优化
    void setMainMenu();
    // TODO:该页面需要优化
    void setNewGameMenu();
    void setRuleMenu();

public:
    // 展示页面
    void showMenu();
    void showMainMunu();
    void showNewGameMenu();
    void showRuleMenu();
};

#endif