#include "MainMenu.h"

// 主菜单的实现
int MainMenu::getWidth() const
{
    return this->width;
}

int MainMenu::getHeight() const
{
    return this->height;
}

MainMenu::MainMenu(int width, int height)
{
    this->width = width;
    this->height = height;
    for (int i = 0; i < height; i++)
    {
        std::vector<char> vec(width, ' ');
        this->storage.push_back(vec);
    }
}

void MainMenu::initMenu()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            this->storage[j][i] = ' ';
        }
    }
    for (int i = 0; i < width; i++)
    {
        this->storage[0][i] = '*';
    }
    for (int i = 0; i < width; i++)
    {
        this->storage[this->height - 1][i] = '*';
    }
    for (int i = 0; i < height; i++)
    {
        this->storage[i][0] = '*';
    }
    for (int i = 0; i < height; i++)
    {
        this->storage[i][this->width - 1] = '*';
    }
}

void MainMenu::showMenu()
{
    //! 刷新缓冲区
    std::cout.flush();
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << this->storage[i][j];
        }
        std::cout << '\n';
    }
}

void MainMenu::setMainMenu()
{
    this->initMenu();
    std::string str1 = "Tower of Hanoi";
    std::string str2 = "1: New Game";
    std::string str3 = "2: Continue";
    std::string str4 = "3: Demo";
    std::string str5 = "4: History";
    std::string str6 = "5: Rules";
    std::string str7 = "6: Exit";
    std::string str8 = "Please choose";
    std::vector<std::string> vec = {str1, str2, str3, str4, str5, str6, str7, str8};
    for (int i = 0; i < vec.size(); i++)
    {

        for (int j = 0; j < vec[i].length(); j++)
        {
            int tapNum = (this->width - vec[i].length()) / 2;
            for (int k = 0; k < tapNum; k++)
            {
                this->storage[i + 1][k + 1] = ' ';
            }
            this->storage[i + 1][j + tapNum + 1] = vec[i][j];
        }
    }
}

void MainMenu::showMainMunu()
{
    this->setMainMenu();
    this->showMenu();
}

void MainMenu::setNewGameMenu()
{
    this->initMenu();
    std::string str = "";
    std::string str1 = "Tower of Hanoi";
    std::string str2 = "New Game";
    std::string str3 = "Please input the plates you want to have";
    std::string str4 = "If you want to back, press 0";
    std::vector<std::string> vec = {str1, str2, str, str, str3, str4};
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].length(); j++)
        {
            int tapNum = (this->width - vec[i].length()) / 2;
            for (int k = 0; k < tapNum; k++)
            {
                this->storage[i + 1][k + 1] = ' ';
            }
            this->storage[i + 1][j + tapNum + 1] = vec[i][j];
        }
    }
}

void MainMenu::setRuleMenu()
{
    this->initMenu();
    std::string str = "";
    std::string str1 = "Tower of Hanoi";
    std::string str2 = "There are three towers";
    std::string str3 = "Choose the plates number in tower1";
    std::string str4 = "Try your best to move the plates to another tower";
    std::string str5 = "Do not put a big plate on a small plate";
    std::string str6 = "Press any key to return to main menu";
    std::vector<std::string> vec = {str1, str, str2, str3, str4, str5, str, str6};
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].length(); j++)
        {
            // 第一行居中处理
            if (i == 0)
            {
                int tapNum = (this->width - vec[i].length()) / 2;
                for (int k = 0; k < tapNum; k++)
                {
                    this->storage[i + 1][k + 1] = ' ';
                }
                this->storage[i + 1][j + tapNum + 1] = vec[i][j];
            }
            else
            {
                this->storage[i + 1][j + 1] = vec[i][j];
            }
        }
    }
}
void MainMenu::showNewGameMenu()
{
    this->setNewGameMenu();
    this->showMenu();
}

void MainMenu::showRuleMenu()
{
    this->setRuleMenu();
    this->showMenu();
}