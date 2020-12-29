#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Reader
{
public:
    Reader(const std::string &fileName_)
        : mFileName(fileName_)
    {
        mInputStream.open(mFileName);
    }

    std::vector<int> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<int> vals;
        std::string line;
        std::istringstream lineStream;

        while (std::getline(mInputStream, line))
        {
            lineStream = std::istringstream(line);
            int val;
            while (lineStream >> val)
            {
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