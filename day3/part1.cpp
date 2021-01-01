#include <iostream>
#include "reader.h"

size_t count_trees_with_slope(std::vector<std::string> map, std::pair<int, int> slope);

int main()
{
    // file reading
    Reader day3Reader("../../day3/input.txt");
    std::vector<std::string> lines = day3Reader.readFile();

    // data processing
    size_t ntrees = count_trees_with_slope(lines, std::make_pair(1, 3));
    std::cout << "\nntrees: " << ntrees;

    return 0;
}

size_t count_trees_with_slope(std::vector<std::string> map, std::pair<int, int> slope)
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
        row += slope.first;
        col += slope.second;
        col = col % (ncols);
    }
    return ntrees;
}