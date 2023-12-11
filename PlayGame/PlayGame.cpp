#include "PlayGame.h"
#include <unistd.h>
#include <windows.h>

void Game::play()
{
    while (true)
    {
        // 首先创建主菜单
        MainMenu menu;
        menu.showMainMunu();
        // 进行选择，并清除缓存
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice)
        {
        case '1':
            this->playNewGame(menu);
            break;
        case '2':
            this->continueGame();
            break;
        case '3':
            /* code */
            this->demoGame();
            break;
        case '4':
            this->getHistory(FileOper::historyPath);
            break;
        case '5':
            menu.showRuleMenu();
            // 检测任意键
            getch();
            break;
        case '6':
            exit(0);
            break;
        default:
            std::cout << "You have chosen a wrong number, please try again" << '\n';
            break;
        }
    }
}

void Game::playNewGame(MainMenu &menu)
{
    // 初始化新游戏页面
    menu.showNewGameMenu();
    GameRecord gameRecord;
    int NumOfPlate; // 铜板块数
    std::cin >> NumOfPlate;
    if (NumOfPlate == 0)
    {
        return;
    }
    std::vector<Tower> Towers = {Tower(NumOfPlate), Tower(0), Tower(0)};
    this->playGame(Towers, gameRecord, NumOfPlate);
}

void Game::continueGame()
{
    //! 清屏
    std::cout.flush();
    system("cls");
    // 从文件中读取数据
    std::vector<Tower> Towers;
    GameRecord gameRecord;
    int NumOfPlate = 0;
    int steps = 0;
    std::ifstream fin(FileOper::tempStorePath);
    // 打开文件失败
    if (fin.is_open() == false)
    {
        std::cout << "\033[31m"
                  << "Open the last game fail"
                  << "\033[0m" << '\n';
        for (int i = 2; i > 0; i--)
        {
            std::cout << "\033[32m"
                      << "\rReturn to main menu " << i;
            sleep(1);
        }
        std::cout << "\033[0m";
        return;
    }
    // 进行文件的数据处理
    int cnt = 0;
    std::string buffer;
    while (std::getline(fin, buffer))
    {
        if (cnt == 0)
        {
            NumOfPlate = std::stoi(buffer);
            cnt++;
            continue;
        }
        // 第一次读文件，读第一个塔的盘子数和长度
        // 第二次读文件，读第二个塔的盘子数和长度
        // 第三次读文件，读第三个塔的盘子数和长度
        if (cnt == 1)
        {
            for (; cnt <= 3; cnt++)
            {
                // 所有的盘子长度
                std::vector<int> platesLength;
                // 对源数据进行切割
                std::vector<std::string> strings = this->splitStringBySpace(buffer);
                for (int i = 0; i < strings.size(); i++)
                {

                    platesLength.push_back(std::stoi(strings[i]));
                }
                Tower tempTower(platesLength.size());
                tempTower.setPlatesLength(platesLength);
                Towers.push_back(tempTower);
                if (cnt < 3)
                {
                    std::getline(fin, buffer);
                }
            }
            continue;
        }
        // 第四次读文件，读上次用的时间
        else if (cnt == 4)
        {
            std::vector<std::string> strings = this->splitStringBySpace(buffer);
            int hour = std::stoi(strings[0]);
            int minute = std::stoi(strings[1]);
            int second = std::stoi(strings[2]);
            gameRecord.setTime(hour, minute, second);
            cnt++;
            continue;
        }
        // 第五次读文件，读上次用的步数
        else if (cnt == 5)
        {
            gameRecord.setSteps(std::stoi(buffer));
            cnt++;
            continue;
        }
    }
    this->playGame(Towers, gameRecord, NumOfPlate);
}

void Game::demoGame()
{
    system("cls");
    class Step
    {
    public:
        int begin;
        int end;
        Step(int begin, int end) : begin(begin), end(end){};
    };
    GameRecord gameRecord;
    int NumOfPlate = 3; // 铜板块数
    std::vector<Tower> Towers = {Tower(NumOfPlate), Tower(0), Tower(0)};
    std::vector<Step> steps =
        {Step(1, 3), Step(1, 2), Step(3, 2), Step(1, 3), Step(2, 1), Step(2, 3), Step(1, 3)};
    Tower::render(Towers, 2 * NumOfPlate + 1, NumOfPlate);
    // 获取开始时间
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < steps.size(); i++)
    {
        // 输出记录
        std::cout << "Record:" << '\n'
                  << gameRecord << '\n';
        sleep(1);
        int a, b;
        a = steps[i].begin;
        b = steps[i].end;
        a--;
        b--;
        bool ret = move(Towers[a], Towers[b]);
        //! 清屏
        std::cout.flush();
        system("cls");
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double seconds = elapsed.count();
        gameRecord.setTime(seconds);
        Tower::render(Towers, 2 * NumOfPlate + 1, NumOfPlate);
        gameRecord.addSteps();
    }
    sleep(1);
}

void Game::getHistory(std::string path)
{
    system("cls");
    std::vector<std::string> files;
    long hFile = 0;
    struct _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            std::string filePath = p.assign(path).append("\\\\").append(fileinfo.name);
            files.push_back(filePath);

            std::ifstream fin(filePath);
            if (fin.is_open())
            {
                std::string::size_type iPos = filePath.find_last_of('\\') + 1;
                std::string filename = filePath.substr(iPos, filePath.length() - iPos);
                std::cout << filename << "\n";
                std::string buffer;
                int cnt = 1;
                while (std::getline(fin, buffer))
                {
                    std::cout << "The " << cnt << " record is below:\n";
                    std::cout << "The time is: " << buffer[2] << ":" << buffer[4] << ":" << buffer[6] << "\n";
                    std::cout << "The steps is: " << buffer[8] << "\n\n";
                    cnt++;
                }
            }

        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    char c = fgetchar();
}

std::vector<std::string> Game::splitStringBySpace(const std::string &str)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}

void Game::playGame(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate)
{
    // 第一次渲染
    //! 清屏
    std::cout.flush();
    system("cls");
    Tower::render(Towers, 2 * NumOfPlate + 1, NumOfPlate);
    std::cout << "Record:" << '\n'
              << gameRecord << '\n';
    // 进行游戏
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        // 如果最后一个塔有NumOfPlate块板并且符合条件，则成功
        if (Towers[2].getNum() == NumOfPlate && Towers[2].isRight() == true ||
            Towers[1].getNum() == NumOfPlate && Towers[1].isRight() == true)
        {
            // 成功处理
            this->Win(gameRecord, NumOfPlate);
            break;
        }

        // 进行移动
        // 塔的编号从1开始计数
        int a, b;
        this->OutputPrompt();
        while (std::cin >> a >> b)
        {
            // 输入时各种异常处理
            // 选择返回处理
            if (a == 0 && b == 0)
            {
                break;
            }
            // 输入合规
            if (a >= 1 && a <= 3 && b <= 3 && b >= 1)
            {
                // 塔a不存在盘子处理
                // 在物理存储上塔a是Towers[a-1]
                if (Towers[a - 1].getNum() == 0)
                {
                    this->noPlate(a);
                    continue;
                }
                // 直接跳出
                break;
            }

            // 其余非法输入
            else
            {
                this->illegalInput();
                continue;
            }
        }
        // 暂时退出游戏
        if (a == 0 && b == 0)
        {
            // 进行是否保存文件
            this->HoldFile(Towers, gameRecord, NumOfPlate);
            break;
        }
        // 输入合法的后续处理
        a--;
        b--;
        bool ret = move(Towers[a], Towers[b]);
        //! 清屏
        std::cout.flush();
        system("cls");
        // 渲染输出后的塔
        Tower::render(Towers, 2 * NumOfPlate + 1, NumOfPlate);
        // 增加步数
        gameRecord.addSteps();
        // 获取一次运行时间
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double seconds = elapsed.count();
        // 设置运行时间
        gameRecord.setTime(seconds);
        // 输出记录
        std::cout << gameRecord << '\n';
        // 该次移动失败，即把大的盘子放在小的盘子上
        if (ret == false)
        {
            char c = this->wrongMove(b);
            if (c == 'Y' || c == 'y')
            {
                move(Towers[b], Towers[a]);
                gameRecord.reduceSteps();
            }
            else
            {
                this->Fail();
                break;
            }
        }
    }
}

void Game::OutputPrompt()
{
    // 该句输出为绿色
    std::cout << "\033[32m"
              << "If you want to quit, press double zero"
              << "\033[0m" << '\n';
    std::cout << "Please move from tower A to tower B: ";
}

void Game::HoldFile(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate)
{
    std::cout << "\033[32m"
              << "是否保存当前游戏进度[Y/N]"
              << "\033[0m" << '\n';
    char choice;
    std::cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        FileOper::preserveInQuit(Towers, gameRecord, NumOfPlate);
    }
    // 该输出为绿色
    for (int i = 2; i > 0; i--)
    {
        std::cout << "\033[32m"
                  << "\rReturn to main menu " << i;
        sleep(1);
    }
    std::cout << "\033[0m";
    return;
}

void Game::Win(GameRecord gameRecord, int NumOfPlate)
{
    //! 清屏
    std::cout.flush();
    system("cls");
    this->PreserveFile(gameRecord, NumOfPlate);
    std::cout << "\n"
              << "\033[33m"
              << "Congratulation,You Win" << '\n'
              << '\n'
              << "Your record is: " << '\n'
              << gameRecord;

    for (int i = 3; i > 0; i--)
    {
        std::cout << "\rReturn to main menu " << i;
        sleep(1);
    }
    std::cout << "\033[0m";
}

void Game::PreserveFile(GameRecord gameRecord, int NumOfPlate)
{
    FileOper::preserveInWin(gameRecord, NumOfPlate);
}

void Game::Fail()
{
    // 该句输出为红色
    std::cout << "\033[31m"
              << "You Fail" << '\n'
              << "\033[0m";
    for (int i = 2; i > 0; i--)
    {
        std::cout << "\rReturn to main menu " << i;
        sleep(1);
    }
}

void Game::noPlate(int a)
{
    // 该句为红色
    std::cout << "\033[31m"
              << "The tower" << a << " has no plate, press again"
              << "\033[0m" << '\n';
    std::cout << "Please move from tower A to tower B: ";
}

void Game::illegalInput()
{
    std::cout << '\n';
    // 该句为红色
    std::cout << "\033[31m"
              << "Your input is illegal, press again"
              << "\033[0m" << '\n';
    std::cout << "Please move from tower A to tower B: ";
}

char Game::wrongMove(int b)
{ // 该句输出为红色
    std::cout << "\033[31m"
              << "You're putting a big plate on a small plate in tower " << b << '\n'
              << '\n'
              << "Try Again[Y/N]" << '\n'
              << "If you press N, you will fail and return to main menu" << '\n'
              << "\033[0m";
    char c; // 输入Y/N
    std::cin >> c;
    return c;
}
