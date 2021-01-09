#include <iostream>
#include <set>

#include "reader.h"

int main()
{
    // file reading
    Reader day6Reader("../../day6/input.txt");
    std::vector<answerBlockType> answerBlocks = day6Reader.readFile();
    std::set<char> letters;
    int numLetters = 0;

    for (const auto &answerBlock : answerBlocks)
    {
        // std::cout << "\n size of answer block: " << answerBlock.size();
        letters.clear();
        for (const auto &line : answerBlock)
        {
            // std::cout << std::endl;
            for (const auto &letter : line)
            {
                // std::cout << " " << letter;
                letters.insert(letter);
            }
        }
        numLetters += letters.size();
    }

    std::cout << "\nno of indiviudal letters: " << numLetters;

    return 0;
}