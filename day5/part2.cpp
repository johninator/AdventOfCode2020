#include <iostream>
#include "reader.h"

typedef std::tuple<int, int, int> rowColIdType;

rowColIdType determine_row_col_id(const std::string &seat_descriptor);
int determine_row_or_col(const std::string &seat_descriptor, const char bit_symbol, const int bit_max);

int main()
{
    // file reading
    Reader day5Reader("../../day5/input.txt");
    std::vector<std::string> seat_descriptors = day5Reader.readFile();

    int id_max = 0;
    std::vector<int> ids;
    for (const auto &seat_descriptor : seat_descriptors)
    {
        const auto &[row, col, id] = determine_row_col_id(seat_descriptor);
        id_max = id > id_max ? id : id_max;
        ids.push_back(id);
    }

    bool *seats = new bool[id_max + 1];
    memset(seats, false, id_max + 1);

    // determine seat ids
    for (const auto &id : ids)
    {
        seats[id] = true;
    }

    // find my seat id
    for (int id = 6; id < id_max - 6; ++id)
    {
        std::cout << "\nseat id: " << id << " occupied? " << seats[id];

        if (seats[id] == false && seats[id - 1] == true && seats[id + 1] == true)
        {
            std::cout << "\nfound my seat id: " << id;
        }
    }
    return 0;
}

rowColIdType determine_row_col_id(const std::string &seat_descriptor)
{

    int row, col, id;
    row = determine_row_or_col(seat_descriptor.substr(0, 7), 'B', 7);
    col = determine_row_or_col(seat_descriptor.substr(7, 3), 'R', 3);

    id = row * 8 + col;
    return std::tuple(row, col, id);
}

int determine_row_or_col(const std::string &seat_descriptor, const char bit_symbol, const int bit_max)
{
    int val = pow(2, bit_max - 1);
    int row = 0;

    for (int bit = 0; bit < bit_max; ++bit)
    {
        if (seat_descriptor[bit] == bit_symbol)
        {
            row += val;
        }
        val *= 0.5;
    }
    return row;
}