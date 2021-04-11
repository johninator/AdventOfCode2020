#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct BusInput
{
    int timestamp;
    std::vector<int> bus_ids;
    std::vector<int> bus_positions;
};

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

    BusInput readFile()
    {
        std::cout << "\n** read file **";

        BusInput busInput;
        std::string line;
        std::istringstream lineStream;

        // 1st line: timestamp
        std::getline(m_inputstream, line);
        busInput.timestamp = std::atoi(line.c_str());
        // 2nd line: bus ids
        std::getline(m_inputstream, line);
        lineStream = std::istringstream(line);
        int bus_id;
        int bus_position{0};
        char ch;

        while (lineStream >> ch)
        {
            if (ch == ',')
            {
                continue;
            }
            else if (ch == 'x')
            {
                ++bus_position;
                continue;
            }
            lineStream.putback(ch);
            lineStream >> bus_id;
            busInput.bus_ids.push_back(bus_id);
            busInput.bus_positions.push_back(bus_position);
            ++bus_position;
        }

        return busInput;
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
};

#endif // READER_H