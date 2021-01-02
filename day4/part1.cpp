#include <iostream>
#include "reader.h"

int main()
{
    // file reading
    Reader day4Reader("../../day4/input.txt");
    std::vector<Passport> passports = day4Reader.readFile();

    std::cout << "\nno of passports: " << passports.size();

    size_t n_valid_passports = 0;
    for (const auto &passport : passports)
    {
        if (passport.is_valid())
        {
            n_valid_passports++;
        }
    }
    std::cout << "\nno of valid passports: " << n_valid_passports;

    return 0;
}