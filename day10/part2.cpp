#include <iostream>
#include <algorithm>
#include "reader.h"

struct NextVal
{
    int joltage;
    int difference;
};

struct AdapterGroup
{
    std::vector<myint>::const_iterator it;
    int size;
};

myint countAdapterCombinations(const std::vector<AdapterGroup> &adapter_groups);
myint tryAllCombinations(const AdapterGroup &group);
bool checkIfWorking(const std::vector<myint>::const_iterator it);
std::vector<AdapterGroup> findAdapterGroups(const std::vector<myint> &adapters);
bool checkIfCanBeLeftOut(const std::vector<myint>::const_iterator it);
std::vector<myint> findAdapters(const std::vector<myint> &vals);
NextVal findNextVal(const int joltage, const std::vector<myint> &vals);

int main()
{
    // file reading
    Reader day10_reader("../../day10/input.txt");
    std::vector<myint> vals = day10_reader.readFile();
    std::vector<myint> adapters = findAdapters(vals);
    std::vector<AdapterGroup> adapter_groups = findAdapterGroups(adapters);
    myint num_combinations = countAdapterCombinations(adapter_groups);

    std::cout << "\n combos: " << num_combinations;

    return 0;
}

myint countAdapterCombinations(const std::vector<AdapterGroup> &adapter_groups)
{
    myint num_combinations{1};
    for (const auto &group : adapter_groups)
    {
        if (group.size == 1)
        {
            // find all groups wih size 1 because combination is simple here
            num_combinations *= 2;
        }
        else
        {
            num_combinations *= tryAllCombinations(group);
        }
    }
    return num_combinations;
}

myint tryAllCombinations(const AdapterGroup &group)
{
    std::vector<myint> groups_vals;
    myint num_combinations{0};

    // try all possible combinations
    for (int n = 0; n < pow(2, group.size); ++n)
    {
        groups_vals.clear();
        groups_vals.push_back(*(group.it - 1));

        for (int bit = 0; bit < group.size; ++bit)
        {
            // read bit at defined location
            if (n & (1 << bit))
            {
                groups_vals.push_back(*(group.it + bit));
            }
        }
        groups_vals.push_back(*(group.it + group.size));

        // check values
        bool combination_works = true;
        for (auto it = groups_vals.begin(); it < groups_vals.end() - 1; ++it)
        {
            if (!checkIfWorking(it))
            {
                combination_works = false;
                break;
            }
        }

        if (combination_works)
        {
            num_combinations++;
        }
    }
    return num_combinations;
}

bool checkIfWorking(const std::vector<myint>::const_iterator it)
{
    if (*(it + 1) - *it < 4)
    {
        return true;
    }
    return false;
}

std::vector<AdapterGroup> findAdapterGroups(const std::vector<myint> &adapters)
{
    std::vector<AdapterGroup> adapter_groups;
    AdapterGroup group;
    bool new_group = true;

    for (auto it = adapters.begin() + 1; it < adapters.end() - 1; ++it)
    {
        if (checkIfCanBeLeftOut(it))
        {
            if (new_group)
            {
                group.size = 1;
                group.it = it;
                new_group = false;
            }
            else
            {
                group.size++;
            }
        }
        else
        {
            if (!new_group)
            {
                adapter_groups.push_back(group);
            }
            new_group = true;
        }
    }
    return adapter_groups;
}

bool checkIfCanBeLeftOut(const std::vector<myint>::const_iterator it)
{
    if (*it - *(it - 1) < 2 && *(it + 1) - *it < 2)
    {
        return true;
    }
    return false;
}

std::vector<myint> findAdapters(const std::vector<myint> &vals)
{
    std::vector<myint> adapters;
    int diff{0};
    int joltage{0};

    adapters.push_back(joltage);

    while (diff >= 0)
    {
        NextVal next_val = findNextVal(joltage, vals);
        joltage = next_val.joltage;
        diff = next_val.difference;
        if (diff > 0)
        {
            adapters.push_back(joltage);
        }
    }

    adapters.push_back(adapters.back() + 3);

    return adapters;
}

NextVal findNextVal(const int joltage, const std::vector<myint> &vals)
{
    int diff{-1};
    int joltage_out;

    std::for_each(vals.begin(), vals.end(), [&diff, joltage, &joltage_out](const int val) {
        int diff_local = val - joltage;
        if (diff_local > 0 && diff_local < 4)
        {
            if (diff == -1 || diff_local < diff)
            {
                diff = diff_local;
                joltage_out = val;
            }
        }
    });
    return {joltage_out, diff};
}
