#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <vector>

class Reader
{
public:
    Reader(const std::string &filename_)
        : m_filename(filename_)
    {
        m_input_stream.open(m_filename);

        if (!m_input_stream.is_open())
        {
            std::cout << "\nerror opening file: " << m_filename;
        }
    }

    std::vector<std::string> readFile()
    {
        std::cout << "\n** read file **";

        std::vector<std::string> set_of_rules;
        std::string line;

        while (std::getline(m_input_stream, line))
        {
            set_of_rules.push_back(line);
        }
        return set_of_rules;
    }

private:
    std::string m_filename;
    std::ifstream m_input_stream;
};

#endif // READER_H
