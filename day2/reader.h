#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

typedef std::tuple<int, int, char, std::string> resultType;

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

    std::vector<resultType> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<resultType> vals;
        std::string line;
        std::istringstream lineStream;

        while (std::getline(mInputStream, line))
        {
            lineStream = std::istringstream(line);

            int indices[2];
            char character;
            std::string password;

            lineStream >> indices[0];
            lineStream.ignore(1);
            lineStream >> indices[1];
            lineStream >> character;
            lineStream.ignore(1);
            lineStream >> password;

            resultType res = std::tuple(indices[0], indices[1], character, password);
            vals.push_back(res);
        }
        return vals;
    }

private:
    std::string mFileName;
    std::ifstream mInputStream;
};

#endif // READER_H