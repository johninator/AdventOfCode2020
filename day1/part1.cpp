#include <iostream>
#include "reader.h"

std::pair<int, int> findNumbers(std::vector<int> vals, int sum);

int main()
{
    // file reading
    Reader csvReader("../../day1/input.txt");
    std::vector<int> vals = csvReader.readFile();

    // data processing
    std::pair<int, int> sumVals = findNumbers(vals, 2020);
    std::cout << "val1: " << sumVals.first << " val2: " << sumVals.second
              << " mul: " << sumVals.first * sumVals.second;

    return 0;
}

std::pair<int, int> findNumbers(std::vector<int> vals, int sum)
{
    for (size_t id1 = 0; id1 < vals.size() - 1; ++id1)
    {
        for (size_t id2 = id1 + 1; id2 < vals.size(); ++id2)
        {
            if (vals[id1] + vals[id2] == sum)
            {
                return std::make_pair(vals[id1], vals[id2]);
            }
        }
    }
    return std::make_pair(-1, -1);
}
