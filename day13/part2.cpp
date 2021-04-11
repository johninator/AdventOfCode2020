#include <iostream>
#include <vector>
#include <algorithm>
#include "reader.h"

long long computeTimestamp(const BusInput &input);
bool checkTimestamp(const long long timestamp, const BusInput &input);

int main()
{
    // file reading
    Reader day13Reader("../../day13/input.txt");
    BusInput busInput = day13Reader.readFile();
    long long timestamp = computeTimestamp(busInput);

    std::cout << "\n timestamp: " << timestamp;

    return 0;
}

long long computeTimestamp(const BusInput &input)
{
    // manually determined solution for slice of the input
    long long timestamp{10494562};
    // primefactorial of the slice
    long long add_val = 12996139;

    while (!checkTimestamp(timestamp, input))
    {
        timestamp += add_val;
    }

    return timestamp;
}

bool checkTimestamp(const long long timestamp, const BusInput &input)
{
    int id_pos{0};

    for (const auto bus_id : input.bus_ids)
    {
        if (((timestamp + input.bus_positions[id_pos]) % bus_id) != 0)
        {
            return false;
        }
        ++id_pos;
    }

    return true;
}
