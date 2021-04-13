#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "reader.h"

long long processAssignmentPacks(const AssignmentPacks &);

int main()
{
    // file reading
    Reader day14Reader("../../day14/input.txt");
    AssignmentPacks assignmentpacks = day14Reader.readFile();
    long long sum = processAssignmentPacks(assignmentpacks);

    std::cout << "sum: " << sum;

    return 0;
}

long long processAssignmentPacks(const AssignmentPacks &assignmentpacks)
{
    std::map<int, long long> memory;

    for (const auto &assignmentpack : assignmentpacks)
    {
        for (const auto &assignment : assignmentpack.assignments)
        {
            long long value = assignment.value;
            // set ones
            value |= assignmentpack.mask.mask_one;
            // set zeros
            value &= ~(assignmentpack.mask.mask_zero);

            if (memory.find(assignment.pos) == memory.end())
            {
                memory.insert(std::pair(assignment.pos, value));
            }
            else
            {
                memory[assignment.pos] = value;
            }
        }
    }

    long long sum{0};
    for (const auto [pos, value] : memory)
    {
        sum += value;
    }
    return sum;
}
