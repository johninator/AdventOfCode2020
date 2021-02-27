#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

enum CommandInstruction
{
    CMD_ACC,
    CMD_JMP,
    CMD_NOP
};

struct Command
{
    CommandInstruction cmd;
    int val;
};

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

    std::vector<Command> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<Command> vals;
        std::string line;
        std::istringstream lineStream;

        while (std::getline(mInputStream, line))
        {
            lineStream = std::istringstream(line);

            std::string cmd;
            int val;

            lineStream >> cmd;
            lineStream >> val;

            CommandInstruction cmdIns = CMD_NOP;
            if (cmd == "acc")
            {
                cmdIns = CMD_ACC;
            }
            else if (cmd == "jmp")
            {
                cmdIns = CMD_JMP;
            }

            vals.push_back({cmdIns, val});
        }
        return vals;
    }

private:
    std::string mFileName;
    std::ifstream mInputStream;
};

#endif // READER_H