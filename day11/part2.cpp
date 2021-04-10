#include <iostream>
#include <algorithm>
#include "reader.h"

bool updateSeatMap(const SeatMap &seatmap_in, SeatMap &seatmap_out);
bool updateEmptySeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, int row, int col);
bool updateOccupiedSeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, int row, int col);
int countOccupiedSeats(const SeatMap &seatmap, int row, int col);
bool checkForOccupiedSeatForDirection(const SeatMap &seatmap,
                                      int row, int col,
                                      int row_end, int col_end,
                                      const int dir_row, const int dir_col);
void printMap(const SeatMap &seatmap);

int main()
{
    // file reading
    Reader day11_reader("../../day11/input.txt");
    SeatMap seatmap = day11_reader.readFile();
    SeatMap seatmap_copy = seatmap;

    bool updated = true;

    while (updated)
    {
        // printMap(seatmap);
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
    int rows = seatmap_in.size();
    int cols = seatmap_in[0].size();

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
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

bool updateEmptySeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, int row, int col)
{
    bool updated = false;
    if (countOccupiedSeats(seatmap_in, row, col) == 0)
    {
        seatmap_out[row][col] = OCCUPIED;
        updated = true;
    }
    return updated;
}

bool updateOccupiedSeat(const SeatMap &seatmap_in, SeatMap &seatmap_out, int row, int col)
{
    bool updated = false;
    if (countOccupiedSeats(seatmap_in, row, col) >= 5)
    {
        seatmap_out[row][col] = EMPTY;
        updated = true;
    }
    return updated;
}

int countOccupiedSeats(const SeatMap &seatmap, int row, int col)
{
    int num_seats = 0;
    int row_end = static_cast<int>(seatmap.size()) - 1;
    int col_end = static_cast<int>(seatmap[0].size()) - 1;

    for (int dir_row = -1; dir_row <= 1; ++dir_row)
    {
        for (int dir_col = -1; dir_col <= 1; ++dir_col)
        {
            if ((dir_row != 0 || dir_col != 0) &&
                checkForOccupiedSeatForDirection(seatmap, row, col, row_end, col_end, dir_row, dir_col))
            {
                ++num_seats;
            }
        }
    }
    return num_seats;
}

bool checkForOccupiedSeatForDirection(const SeatMap &seatmap,
                                      int row, int col,
                                      int row_end, int col_end,
                                      const int dir_row, const int dir_col)
{
    int row_t = row + dir_row;
    int col_t = col + dir_col;

    if ((row_t > row_end) || (col_t > col_end) ||
        (row_t < 0) || (col_t < 0))
    {
        return false;
    }

    while (seatmap[row_t][col_t] == FLOOR)
    {
        row_t += dir_row;
        col_t += dir_col;

        if ((row_t > row_end) || (col_t > col_end) ||
            (row_t < 0) || (col_t < 0))
        {
            return false;
        }
    }

    if (seatmap[row_t][col_t] == OCCUPIED)
    {
        return true;
    }
    return false;
}

void printMap(const SeatMap &seatmap)
{
    std::cout << std::endl;

    for (auto &seatline : seatmap)
    {
        std::cout << std::endl;
        for (auto &seat : seatline)
        {
            switch (seat)
            {
            case EMPTY:
                std::cout << "L";
                break;
            case OCCUPIED:
                std::cout << "#";
                break;
            case FLOOR:
                std::cout << ".";
                break;
            }
        }
    }
}