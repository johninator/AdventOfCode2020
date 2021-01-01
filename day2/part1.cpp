#include <iostream>
#include "reader.h"

int main()
{
    // file reading
    Reader day2Reader("../../day2/input.txt");
    std::vector<resultType> vals = day2Reader.readFile();

    size_t nValidsPws = 0;
    // data processing
    for (const auto &val : vals)
    {
        const auto &[index1, index2, character, password] = val;

        int ncounts = std::count(password.begin(), password.end(), character);

        if (ncounts >= index1 && ncounts <= index2)
        {
            nValidsPws++;
        }
    }
    std::cout << "\nvalid passwords: " << nValidsPws;

    return 0;
}
