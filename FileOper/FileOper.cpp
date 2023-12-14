#include "FileOper.h"
#include <fstream>

std::string FileOper::tempStorePath =
    R"(D:\\DevelopTools\\Code\\Cpp\\Tower-Of-Hanoi\\Data\\Last(Monent))";
std::string FileOper::historyPath =
    R"(D:\\DevelopTools\\Code\\Cpp\\Tower-Of-Hanoi\\Data\\History)";
std::string FileOper::bestDataPath =
    R"(D:\\DevelopTools\\Code\\Cpp\\Tower-Of-Hanoi\\Data\\BestRecord)";
/*Last(Moment)的存储方式
    1. 最大盘子数
    2. 塔1的各个盘子长度
    3. 塔2的各个盘子长度
    4. 塔3的各个盘子长度
    5. 时间(时 分 秒)
    6. 步数
*/
/*History的存储方式
    1. 盘子数
    2. 时 分 秒
    3. 步数
*/
void FileOper::preserveInQuit(std::vector<Tower> Towers, GameRecord gameRecord, int NumOfPlate)
{
    std::ofstream fout(tempStorePath);
    if (fout.is_open() == false)
    {
        std::cout << "打开 " << tempStorePath << " 失败" << '\n';
    }
    else
    {
        fout << NumOfPlate << '\n';
        for (int i = 0; i < Towers.size(); i++)
        {
            std::vector<int> platesLength = Towers[i].getPlatesLength();
            for (int j = 0; j < platesLength.size(); j++)
            {
                fout << platesLength[j] << ' ';
            }
            fout << '\n';
        }
        fout << gameRecord.getHour() << ' ' << gameRecord.getMimute() << ' ' << gameRecord.getSecond() << '\n'
             << gameRecord.getSteps() << '\n';
    }
}

void FileOper::preserveInWin(GameRecord gameRecord, int NumOfPlate)
{
    // 根据NumOfPlate打开对应的文件
    std::string nowHistoryPath = historyPath + "/" + std::to_string(NumOfPlate);
    std::ofstream fout(nowHistoryPath, std::ios::app);
    if (fout.is_open() == false)
    {
        std::cout << "打开 " << nowHistoryPath << " 失败" << '\n';
    }
    else
    {
        std::ifstream file(nowHistoryPath);
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            // The file is empty
            fout << NumOfPlate << " " << gameRecord.getHour() << ' ' << gameRecord.getMimute() << ' ' << gameRecord.getSecond() << ' ' << gameRecord.getSteps();
        }
        else
        {
            fout << '\n';
            fout << NumOfPlate << " " << gameRecord.getHour() << ' ' << gameRecord.getMimute() << ' ' << gameRecord.getSecond() << ' ' << gameRecord.getSteps();
        }
    }
}

void FileOper::preserveInBest(GameRecord gameRecord, int NumOfPlate)
{
    std::string nowHistoryPath = bestDataPath + "/" + std::to_string(NumOfPlate);
    std::ofstream fout(nowHistoryPath);
    if (fout.is_open() == false)
    {
        std::cout << "打开 " << nowHistoryPath << " 失败" << '\n';
    }
    else
    {
        fout << NumOfPlate << " " << gameRecord.getHour() << ' ' << gameRecord.getMimute() << ' ' << gameRecord.getSecond() << ' ' << gameRecord.getSteps();
    }
}
