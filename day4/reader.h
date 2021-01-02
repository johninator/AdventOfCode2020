#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include "passport.h"

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

    std::vector<Passport> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<Passport> vals;
        std::string line;

        while (std::getline(mInputStream, line))
        {
            if (line.empty())
            {
                continue;
            }
            Passport passport;
            while (!line.empty() && !mInputStream.eof())
            {
                std::cout << "\nprocess line: " << line;
                passport.process_line(line);
                std::getline(mInputStream, line);
            }
            vals.push_back(passport);
        }
        return vals;
    }

private:
    std::string mFileName;
    std::ifstream mInputStream;
};

#endif // READER_H