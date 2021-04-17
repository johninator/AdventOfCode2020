#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

    std::vector<int> readFile()
    {
        std::cout << "\n** read file **";

        std::string line;
        std::istringstream lineStream;
        std::vector<int> vals;
        int val;

        std::getline(m_inputstream, line);
        lineStream = std::istringstream(line);

        while (lineStream >> val)
        {
            vals.push_back(val);
            lineStream.ignore(1);
        }

        return vals;
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
};

#endif // READER_H