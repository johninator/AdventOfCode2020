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
    std::map<long long, long long> memory;

    for (const auto &assignmentpack : assignmentpacks)
    {
        for (const auto &assignment : assignmentpack.assignments)
        {
            const Mask &mask = assignmentpack.mask;
            long long pos = assignment.pos;
            // set ones
            pos |= mask.mask_one;
            // set floating 'x'
            size_t N = mask.floating_positions.size();
            size_t N_pow = pow(2, N);

            for (size_t id = 0; id < N_pow; ++id)
            {
                long long pos_copy = pos;

                for (size_t i = 0; i < N; ++i)
                {
                    if (id % (int)(pow(2, N - i)) >= (int)(pow(2, N - i - 1)))
                    {
                        pos_copy |= (1ULL << mask.floating_positions[i]);
                    }
                    else
                    {
                        pos_copy &= ~(1ULL << mask.floating_positions[i]);
                    }
                }

                if (memory.find(pos_copy) == memory.end())
                {
                    memory.insert(std::pair(pos_copy, assignment.value));
                }
                else
                {
                    memory[pos_copy] = assignment.value;
                }
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
