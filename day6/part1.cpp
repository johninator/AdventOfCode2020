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
    for (const auto &seat_descriptor : seat_descriptors)
    {
        const auto &[row, col, id] = determine_row_col_id(seat_descriptor);
        id_max = id > id_max ? id : id_max;
        // std::cout << "\nrow: " << row << ", col: " << col << ", id: " << id;
    }
    std::cout << "\nid_max: " << id_max;

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