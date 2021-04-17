#include <iostream>
#include <vector>
#include <map>
#include "reader.h"

static int counter{0};
static int last_number;

void insertStartingNumbers(const std::vector<int> &starting_numbers,
                           std::map<int, std::vector<int>> &numbers);
void computeAndAddNewNumber(std::map<int, std::vector<int>> &numbers);
void insertNumber(const int number,
                  std::map<int, std::vector<int>> &numbers);

int main()
{
    // file reading
    Reader day15Reader("../../day15/input.txt");
    std::vector<int> starting_numbers = day15Reader.readFile();

    std::map<int, std::vector<int>> numbers;
    insertStartingNumbers(starting_numbers, numbers);

    while (counter < 30000000)
    {
        computeAndAddNewNumber(numbers);
    }

    std::cout << "last number: " << last_number;

    return 0;
}

void insertStartingNumbers(const std::vector<int> &starting_numbers,
                           std::map<int, std::vector<int>> &numbers)
{
    for (const int number : starting_numbers)
    {
        insertNumber(number, numbers);
    }
}

void computeAndAddNewNumber(std::map<int, std::vector<int>> &numbers)
{
    if (numbers[last_number].size() == 1) // first time -> 0
    {
        insertNumber(0, numbers);
    }
    else // not first time -> age
    {
        const int age = counter - *(numbers[last_number].end() - 2) - 1;
        insertNumber(age, numbers);
    }
}

void insertNumber(const int number,
                  std::map<int, std::vector<int>> &numbers)
{
    if (numbers.find(number) == numbers.end()) // not existing in the map
    {
        numbers.insert(std::pair<int, std::vector<int>>(number, {counter}));
    }
    else // already existing in the map -> only modify the vector
    {
        numbers[number].push_back(counter);
    }
    last_number = number;
    ++counter;
}
