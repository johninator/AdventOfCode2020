#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <vector>

typedef std::vector<std::string> answerBlockType;

class Reader
{
public:
    Reader(const std::string &fileName_)
        : mFileName(fileName_)
    {
        mInputStream.open(mFileName);

        if (!mInputStream.is_open())
        {
            std::cout << "\nerror opening file: " << mFileName;
        }
    }

    std::vector<answerBlockType> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<answerBlockType> vals;
        answerBlockType val;
        std::string line;

        while (std::getline(mInputStream, line))
        {
            if (!line.empty())
            {
                val.clear();
                val.push_back(line);
                // continue with rest of the block
                while (std::getline(mInputStream, line) && !line.empty())
                {
                    val.push_back(line);
                }
                // save block and resume work
                vals.push_back(val);
            }
        }
        return vals;
    }

private:
    std::string mFileName;
    std::ifstream mInputStream;
};

#endif // READER_H
