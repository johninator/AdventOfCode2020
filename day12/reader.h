#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "shipstate_2.h"

class Reader
{
public:
    Reader(const std::string &filename_)
        : m_filename(filename_)
    {
        m_inputstream.open(m_filename);

        if (!m_inputstream.is_open())
        {
            std::cout << "\nerror opening file: " << m_filename;
        }
    }

    std::vector<Command> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<Command> vals;
        std::string line;
        std::istringstream lineStream;

        while (std::getline(m_inputstream, line))
        {
            lineStream = std::istringstream(line);

            Command cmd;
            char action;
            int value;

            lineStream >> action;
            lineStream >> value;

            cmd.value = value;

            switch (action)
            {
            case 'N':
                cmd.action = Action::NORTH;
                break;
            case 'S':
                cmd.action = Action::SOUTH;
                break;
            case 'W':
                cmd.action = Action::WEST;
                break;
            case 'E':
                cmd.action = Action::EAST;
                break;
            case 'L':
                cmd.action = Action::LEFT;
                break;
            case 'R':
                cmd.action = Action::RIGHT;
                break;
            case 'F':
                cmd.action = Action::FORWARD;
                break;
            default:
                std::cerr << "unrecognized character: " << action << std::endl;
                break;
            }

            vals.push_back(cmd);
        }
        return vals;
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
};

#endif // READER_H