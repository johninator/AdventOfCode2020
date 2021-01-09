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
    bool init;

    for (const auto &answerBlock : answerBlocks)
    {
        letters.clear();
        init = false;

        for (const auto &line : answerBlock)
        {
            std::vector<char> lettersToBeErased;
            if (!init)
            {
                for (const auto &letter : line)
                {
                    letters.insert(letter);
                }
            }
            else
            {
                // find letters that are not existing
                for (const auto &letter : letters)
                {
                    if (line.find(letter) == std::string::npos)
                    {
                        lettersToBeErased.push_back(letter);
                    }
                }
                // remove letters that are not existing
                for (const auto &letterErase : lettersToBeErased)
                {
                    letters.erase(letterErase);
                }
            }
            init = true;
        }
        numLetters += letters.size();
    }

    std::cout << "\nno of indiviudal letters: " << numLetters;

    return 0;
}