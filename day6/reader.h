#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

typedef std::vector<std::string> answerBlock;

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

    std::vector<answerBlock> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<answerBlock> vals;
        answerBlock val;
        std::string line;

        while (std::getline(mInputStream, line))
        {
            if(!line.empty())
            {
              val.clear();
              val.push_back(line);
              // continue with rest of the block
              while (std::getline(mInputStream, line))
              {
                if(!line.empty())
                {
                  val.push_back(line);
                }
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
