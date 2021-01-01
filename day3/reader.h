#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

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

    std::vector<std::string> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<std::string> vals;
        std::string line;

        while (std::getline(mInputStream, line))
        {
            vals.push_back(line);
        }
        return vals;
    }

private:
    std::string mFileName;
    std::ifstream mInputStream;
};

#endif // READER_H