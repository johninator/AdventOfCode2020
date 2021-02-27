#ifndef READER_H
#define READER_H

#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>

typedef long long myint;

class Reader
{
public:
    Reader(const std::string_view &filename_)
        : m_filename(filename_)
    {
        m_filestream.open(m_filename);
    }

    std::vector<myint> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<myint> vals;
        std::string line;

        while (std::getline(m_filestream, line))
        {
            vals.push_back(std::stoll(line));
        }
        return vals;
    }

private:
    std::string m_filename;
    std::ifstream m_filestream;
};

#endif // READER_H