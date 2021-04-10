#include <iostream>
#include <algorithm>
#include "reader.h"

bool updateSeatMap(const SeatMap &seatmap_in, SeatMap &seatmap_out);
bool updateEmptySeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, size_t row, size_t col);
bool updateOccupiedSeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, size_t row, size_t col);
int countAdjacentOccupiedSeats(const SeatMap &seatmap, size_t row, size_t col);

int main()
{
    // file reading
    Reader day11_reader("../../day11/input.txt");
    SeatMap seatmap = day11_reader.readFile();
    SeatMap seatmap_copy = seatmap;

    bool updated = true;

    while (updated)
    {
        updated = updateSeatMap(seatmap, seatmap_copy);
        seatmap = seatmap_copy;
    }

    int num_occupied_seats = 0;
    for (auto &seatline : seatmap)
    {
        for (auto &seat : seatline)
        {
            if (seat == OCCUPIED)
                ++num_occupied_seats;
        }
    }
    std::cout << "\n occupied seats: " << num_occupied_seats;

    return 0;
}

bool updateSeatMap(const SeatMap &seatmap_in, SeatMap &seatmap_out)
{
    bool updated = false;
    size_t rows = seatmap_in.size();
    size_t cols = seatmap_in[0].size();

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            if (seatmap_in[row][col] == EMPTY)
            {
                updated |= updateEmptySeat(seatmap_in, seatmap_out, row, col);
            }
            else if (seatmap_in[row][col] == OCCUPIED)
            {
                updated |= updateOccupiedSeat(seatmap_in, seatmap_out, row, col);
            }
        }
    }
    return updated;
}

bool updateEmptySeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, size_t row, size_t col)
{
    bool updated = false;
    if (countAdjacentOccupiedSeats(seatmap_in, row, col) == 0)
    {
        seatmap_out[row][col] = OCCUPIED;
        updated = true;
    }
    return updated;
}

bool updateOccupiedSeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, size_t row, size_t col)
{
    bool updated = false;
    if (countAdjacentOccupiedSeats(seatmap_in, row, col) >= 4)
    {
        seatmap_out[row][col] = EMPTY;
        updated = true;
    }
    return updated;
}

int countAdjacentOccupiedSeats(const SeatMap &seatmap, size_t row, size_t col)
{
    int num_seats = 0;
    size_t row_start = row == 0 ? 0 : row - 1;
    size_t col_start = col == 0 ? 0 : col - 1;

    size_t row_end = std::min(row + 1, seatmap.size() - 1);
    size_t col_end = std::min(col + 1, seatmap[0].size() - 1);

    for (size_t row2 = row_start; row2 <= row_end; ++row2)
    {
        for (size_t col2 = col_start; col2 <= col_end; ++col2)
        {
            if (!(row == row2 && col == col2) &&
                seatmap[row2][col2] == OCCUPIED)
            {
                ++num_seats;
            }
        }
    }
    return num_seats;
}