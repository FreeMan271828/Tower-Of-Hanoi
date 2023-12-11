#include "Tower.h"

void Plate::setLength(const int l)
{
    this->length = l;
}

int Plate::getLength() const
{
    return this->length;
}

Tower::Tower() : num(0), maxPlateLength(0) {}

Tower::Tower(int num)
{
    this->num = num;
    for (int i = 1; i <= num; i++)
    {
        Plate plate;
        plate.setLength(2 * i + 1);
        plates.push_back(plate);
    }
    this->maxPlateLength = 2 * num + 1;
}

void Tower::setNum(const int num)
{
    this->num = num;
    this->plates.clear();
    for (int i = 1; i <= num; i++)
    {
        Plate plate;
        plate.setLength(2 * i + 1);
        plates.push_back(plate);
    }
    this->maxPlateLength = 2 * num + 1;
}

int Tower::getNum() const
{
    return this->num;
}

int Tower::getMaxPlateLength() const
{
    return this->maxPlateLength;
}

void Tower::setPlatesLength(std::vector<int> &platesLength)
{
    this->num = platesLength.size();
    for (int i = 0; i < this->num; i++)
    {
        this->plates[i].setLength(platesLength[i]);
    }
}

std::vector<int> Tower::getPlatesLength() const
{
    std::vector<int> ret;
    for (int i = 0; i < this->getNum(); i++)
    {
        ret.push_back(this->plates[i].getLength());
    }
    return ret;
}

bool Tower::isRight()
{
    int firstLength = plates[0].getLength();
    for (int i = 1; i < plates.size(); i++)
    {
        if (plates[i].getLength() <= firstLength)
        {
            return false;
        }
    }
    return true;
}

void Tower::render(std::vector<Tower> Hanios, int maxLength, int maxPlateNum)
{
    // maxLength是所有塔的最大盘子长度的最大值，为了确定每个塔的宽度为maxLength
    // 奇数化和最小化处理，保证居中输出和正常输出
    if (maxLength < 11)
    {
        maxLength = 11;
    }
    if (maxLength % 2 == 0)
    {
        maxLength++;
    }
    // 为了有空格，更好辨认
    maxLength += 4;
    // 第一行输出塔名
    for (int i = 1; i <= 3; i++)
    {
        std::string str = "Tower " + std::to_string(i);
        int tapNum = (maxLength - str.length()) / 2;
        for (int i = 0; i < tapNum; i++)
        {
            std::cout << ' ';
        }
        for (auto &elm : str)
        {
            std::cout << elm;
        }
        for (int i = 0; i < tapNum; i++)
        {
            std::cout << ' ';
        }
    }
    std::cout << '\n';
    // 下面打印盘子
    // 设置空白行数
    int blankLine[3];
    for (int i = 0; i < 3; i++)
    {
        blankLine[i] = maxPlateNum - Hanios[i].getNum();
    }
    // 开始打印盘子,一共有maxPlateNum行
    for (int row = 0; row < maxPlateNum; row++)
    {
        // 3个塔
        for (int index = 0; index < 3; index++)
        {
            // 当该行为空白行
            if (row < blankLine[index])
            {
                // 输出一个塔的宽度的空格
                for (int i = 0; i < maxLength; i++)
                {
                    std::cout << ' ';
                }
            }
            else
            {
                // row-blankLine[i]row-blankLine[i]是为了修正maxPlateNum带来的影响
                // Hanios[index]是选择第i个塔
                // Hanios[index].plates[row-blankLine[i]]是选择当前塔的行数
                int nowLength = Hanios[index].plates[row - blankLine[index]].getLength();
                double tapNum = (maxLength - nowLength) / 2;
                for (int i = 0; i < tapNum; i++)
                {
                    std::cout << ' ';
                }
                for (int i = 0; i < nowLength; i++)
                {
                    std::cout << '-';
                }
                // 还要加间隔
                for (int i = 0; i < tapNum; i++)
                {
                    std::cout << ' ';
                }
            }
        }
        std::cout << '\n';
    }
}

bool move(Tower &a, Tower &b)
{
    if (a.plates.size() == 0)
    {
        std::cout << "a中没有盘子" << '\n';
        return false;
    }
    else
    {
        // 其余情况不需要考虑最大长度的改变
        Plate plate = a.plates[0];
        // a原本只有一个盘子，再减少就没盘子了
        if (a.plates.size() == 1)
        {
            a.maxPlateLength = 0;
        }
        // b原本没有盘子，新的盘子就是它的最大长度
        if (b.plates.size() == 0)
        {
            b.maxPlateLength = plate.getLength();
        }
        a.plates.erase(a.plates.begin());
        b.plates.insert(b.plates.begin(), plate);
        a.num -= 1;
        b.num += 1;
        if (b.isRight() == false)
        {
            std::cout << "Wrong result after moving" << '\n';
            return false;
        }
        return true;
    }
}

std::ostream &operator<<(std::ostream &out, const Tower &hanoi)
{
    if (hanoi.plates.size() == 0)
    {
        std::cout << "No Plate";
    }
    else
    {
        for (int i = 0; i < hanoi.plates.size(); i++)
        {
            std::cout << hanoi.plates[i].getLength() << " ";
        }
    }
    std::cout << '\n';
    return out;
}
