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
    std::string str1 = "汉 诺 塔";
    std::string str2 = "1: 新游戏";
    std::string str3 = "2: 继续游戏";
    std::string str4 = "3: 游戏演示";
    std::string str5 = "4: 历史记录";
    std::string str6 = "5: 游戏规则";
    std::string str7 = "6: 退出游戏";
    std::string str8 = "请从1到6中选择一项";
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
    std::string str1 = "汉诺塔";
    std::string str2 = "现在是新游戏";
    std::string str3 = "请输入你想要的盘子数（难度）";
    std::string str4 = "如果想返回主菜单，请按0";
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
    std::string str1 = "汉 诺 塔";
    std::string str2 = "这儿有三个塔，你先选择在塔1上的盘子数";
    std::string str3 = "你每次都可以移动塔最上方的盘子到另一个塔";
    std::string str4 = "但是不要把大盘子移动到小盘子上";
    std::string str5 = "按任意键返回";
    std::vector<std::string> vec = {str1, str, str2, str3, str4, str, str5, str};
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].length(); j++)
        {
            // 第一行居中处理
            if (i == 0 || i == vec.size() - 2)
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