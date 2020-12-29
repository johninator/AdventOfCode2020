#include <iostream>
#include <tuple>
#include "reader.h"

std::tuple<int, int, int> findNumbers(std::vector<int> vals, int sum);

int main()
{
    // file reading
    Reader csvReader("../../day1/input.txt");
    std::vector<int> vals = csvReader.readFile();

    // data processing
    std::tuple<int, int, int> sumVals = findNumbers(vals, 2020);
    // use structured binding to extract values
    const auto &[val1, val2, val3] = sumVals;
    std::cout << "val1: " << val1 << " val2: " << val2 << " val3: " << val3
              << " mul: " << val1 * val2 * val3;

    return 0;
}

std::tuple<int, int, int> findNumbers(std::vector<int> vals, int sum)
{
    for (size_t id1 = 0; id1 < vals.size() - 2; ++id1)
    {
        for (size_t id2 = id1 + 1; id2 < vals.size() - 1; ++id2)
        {
            for (size_t id3 = id2 + 1; id3 < vals.size(); ++id3)
            {
                if (vals[id1] + vals[id2] + vals[id3] == sum)
                {
                    return std::tuple(vals[id1], vals[id2], vals[id3]);
                }
            }
        }
    }
    return std::tuple(0, 0, 0);
}
