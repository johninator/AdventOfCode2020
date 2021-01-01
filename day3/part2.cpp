#include <iostream>
#include <array>
#include <iomanip>
#include "reader.h"

typedef std::array<int, 2> slopeType;

size_t count_trees_with_slope(std::vector<std::string> map, slopeType slope);

int main()
{
    // file reading
    Reader day3Reader("../../day3/input.txt");
    std::vector<std::string> lines = day3Reader.readFile();

    // data processing
    std::array<slopeType, 5> slopes;
    slopes[0] = {1, 1};
    slopes[1] = {1, 3};
    slopes[2] = {1, 5};
    slopes[3] = {1, 7};
    slopes[4] = {2, 1};
    std::vector<int> ntrees;

    for (const auto &slope : slopes)
    {
        int ntree = count_trees_with_slope(lines, slope);
        ntrees.push_back(ntree);
    }

    unsigned long long int ntotal = 1;
    for (const auto &ntree : ntrees)
    {
        ntotal *= ntree;
    }

    std::cout << "\nntotal: " << ntotal;

    return 0;
}

size_t count_trees_with_slope(std::vector<std::string> map, slopeType slope)
{
    // traverse map from origin to end and count trees
    size_t ntrees = 0;
    size_t nrows = map.size();
    size_t ncols = map[0].size();
    size_t row(0), col(0);

    while (row < nrows)
    {
        // check for tree
        if (map[row][col] == '#')
        {
            ntrees++;
        }
        row += slope[0];
        col += slope[1];
        col = col % (ncols);
    }
    return ntrees;
}