#include <iostream>
#include "reader.h"

bool checkIfSum(const std::vector<myint>::iterator &val_it,
                const int preambel_length);

int main()
{
    // file reading
    constexpr int preambel_length = 25;
    Reader day9_reader("../../day9/input.txt");
    std::vector<myint> vals = day9_reader.readFile();

    for (auto val_it = vals.begin() + preambel_length; val_it != vals.end(); ++val_it)
    {
        if (!checkIfSum(val_it, preambel_length))
        {
            std::cout << "\n not working val: " << *val_it;
            break;
        }
    }

    return 0;
}

bool checkIfSum(const std::vector<myint>::iterator &val_it,
                const int preambel_length)
{
    bool is_sum = false;
    for (auto val_it_temp1 = val_it - preambel_length; val_it_temp1 < val_it - 1; ++val_it_temp1)
    {
        for (auto val_it_temp2 = val_it_temp1 + 1; val_it_temp2 < val_it; ++val_it_temp2)
        {
            if (*val_it_temp1 != *val_it_temp2 &&
                *val_it_temp1 + *val_it_temp2 == *val_it)
            {
                is_sum = true;
                return is_sum;
            }
        }
    }
    return is_sum;
}
