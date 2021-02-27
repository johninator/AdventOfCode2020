#include <iostream>
#include <numeric>
#include <algorithm>
#include "reader.h"

bool findContiguousVals(const std::vector<myint>::iterator &val_it,
                        const myint goal,
                        myint &weakness);

int main()
{
    // file reading
    Reader day9_reader("../../day9/input.txt");
    std::vector<myint> vals = day9_reader.readFile();

    const myint goal = 15690279;
    myint weakness;

    for (auto val_it = vals.begin(); val_it != vals.end(); ++val_it)
    {
        if (*val_it < goal &&
            findContiguousVals(val_it, goal, weakness))
        {
            std::cout << "\n weakness: " << weakness;
            break;
        }
    }

    return 0;
}

bool findContiguousVals(const std::vector<myint>::iterator &val_it,
                        const myint goal,
                        myint &weakness)
{
    std::vector<myint> vals;
    myint sum = {0};

    for (auto my_it = val_it; sum < goal; ++my_it)
    {
        vals.push_back(*my_it);
        sum = std::accumulate(val_it, my_it, 0);

        if (sum == goal)
        {
            weakness = *std::max_element(val_it, my_it) + *std::min_element(val_it, my_it);
            return true;
        }
    }
    return false;
}
