#include <iostream>
#include "reader.h"

StateMap updateStateMap(StateMap &statemap);

State calcNewState(StateMap &statemap,
                   const int row,
                   const int col,
                   const int level);

int main()
{
    // file reading
    Reader day17Reader("../../day17/input.txt");
    StateMap statemap_old = day17Reader.readFile();

    // statemap_old.print();

    for (int counter = 0; counter < 6; ++counter)
    {
        auto statemap_new = updateStateMap(statemap_old);
        statemap_old = statemap_new;

        // std::cout << "\n ***** round: " << counter << " *****" << std::endl;
        // statemap_old.print();
    }

    std::cout << "\n active states: " << statemap_old.countActives() << std::endl;

    return 0;
}

StateMap updateStateMap(StateMap &statemap)
{
    StateMap statemap_tmp(statemap.num_rows + 2,
                          statemap.num_cols + 2,
                          statemap.num_levels + 2);
    StateMap statemap_new = statemap_tmp;

    for (int row = 0; row < statemap.num_rows; ++row)
    {
        for (int col = 0; col < statemap.num_cols; ++col)
        {
            for (int level = 0; level < statemap.num_levels; ++level)
            {
                statemap_tmp.getState(row + 1, col + 1, level + 1) = statemap.getState(row, col, level);
            }
        }
    }

    for (int row = 0; row < statemap_tmp.num_rows; ++row)
    {
        for (int col = 0; col < statemap_tmp.num_cols; ++col)
        {
            for (int level = 0; level < statemap_tmp.num_levels; ++level)
            {
                statemap_new.getState(row, col, level) = calcNewState(statemap_tmp, row, col, level);
            }
        }
    }

    return statemap_new;
}

State calcNewState(StateMap &statemap,
                   const int row_orig,
                   const int col_orig,
                   const int level_orig)
{
    int counter_active = 0;
    int row_orig_min = std::max(row_orig - 1, 0);
    int row_orig_max = std::min(row_orig + 1, statemap.num_rows - 1);
    int col_orig_min = std::max(col_orig - 1, 0);
    int col_orig_max = std::min(col_orig + 1, statemap.num_cols - 1);
    int level_orig_min = std::max(level_orig - 1, 0);
    int level_orig_max = std::min(level_orig + 1, statemap.num_levels - 1);

    for (int row = row_orig_min; row <= row_orig_max; ++row)
    {
        for (int col = col_orig_min; col <= col_orig_max; ++col)
        {
            for (int level = level_orig_min; level <= level_orig_max; ++level)
            {
                if ((row != row_orig || col != col_orig || level != level_orig) &&
                    statemap.getState(row, col, level) == ACTIVE)
                {
                    ++counter_active;
                }
            }
        }
    }

    if (statemap.getState(row_orig, col_orig, level_orig) == ACTIVE)
    {
        if (counter_active == 2 ||
            counter_active == 3)
        {
            return ACTIVE;
        }
        return INACTIVE;
    }
    else
    {
        if (counter_active == 3)
        {
            return ACTIVE;
        }
        return INACTIVE;
    }
}
