#include <iostream>
#include <algorithm>
#include "reader.h"

struct NextVal
{
    int joltage;
    int difference;
};

void findAdapters(const std::vector<int> &vals);
NextVal findNextVal(const int joltage, const std::vector<int> &vals);

int main()
{
    // file reading
    Reader day10_reader("../../day10/input.txt");
    std::vector<myint> vals = day10_reader.readFile();
    findAdapters(vals);

    return 0;
}

void findAdapters(const std::vector<int> &vals)
{
    int count_1_diff{0};
    int count_3_diff{1};
    int diff{0};
    int joltage{0};

    while (diff >= 0)
    {
        NextVal next_val = findNextVal(joltage, vals);
        joltage = next_val.joltage;
        diff = next_val.difference;
        std::cout << "\n diff: " << diff;

        if (diff == 1)
            ++count_1_diff;
        if (diff == 3)
            ++count_3_diff;
    }
    std::cout << "\n val: " << count_1_diff * count_3_diff;
}

NextVal findNextVal(const int joltage, const std::vector<int> &vals)
{
    int diff{-1};
    int joltage_out;

    std::for_each(vals.begin(), vals.end(), [&diff, joltage, &joltage_out](const int val) {
        int diff_local = val - joltage;
        if (diff_local > 0 && diff_local < 4)
        {
            if (diff == -1 || diff_local < diff)
            {
                diff = diff_local;
                joltage_out = val;
            }
        }
    });
    return {joltage_out, diff};
}
