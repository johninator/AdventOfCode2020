#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

typedef std::vector<std::array<int, 2>> Rules;
typedef std::vector<int> TicketNumber;

struct Input
{
    Rules rules;
    TicketNumber your_number;
    std::vector<TicketNumber> nearby_numbers;
};

enum ReaderState
{
    RULES,
    YOUR_TICKET,
    NEARBY_TICKETS
};

class Reader
{
public:
    Reader(const std::string &filename_)
        : m_filename(filename_), m_state(RULES)
    {
        m_inputstream.open(m_filename);

        if (!m_inputstream.is_open())
        {
            std::cout << "\nerror opening file: " << m_filename;
        }
    }

    Input readFile()
    {
        std::cout << "\n** read file **";

        std::string line;
        Rules rules;
        TicketNumber your_number;
        std::vector<TicketNumber> nearby_numbers;

        while (std::getline(m_inputstream, line))
        {
            if (line == "")
            {
                continue;
            }
            else if (line == "your ticket:")
            {
                m_state = YOUR_TICKET;
                continue;
            }
            else if (line == "nearby tickets:")
            {
                m_state = NEARBY_TICKETS;
                continue;
            }

            if (m_state == RULES)
            {
                std::string rule1 = line.substr(line.find(':') + 1, line.find(" or ") - line.find(':'));
                std::string rule2 = line.substr(line.find(" or ") + 3);
                std::istringstream sstream1 = std::istringstream(rule1);
                std::istringstream sstream2 = std::istringstream(rule2);
                int val1, val2;

                // rule1
                sstream1 >> val1;
                sstream1.ignore(1);
                sstream1 >> val2;
                rules.push_back({val1, val2});

                // rule2
                sstream2 >> val1;
                sstream2.ignore(1);
                sstream2 >> val2;
                rules.push_back({val1, val2});
            }
            else if (m_state == YOUR_TICKET)
            {
                std::istringstream linestream = std::istringstream(line);
                int val;
                while (linestream >> val)
                {
                    your_number.push_back(val);
                    linestream.ignore(1);
                }
            }
            else // NEARBY_TICKETS
            {
                std::istringstream linestream = std::istringstream(line);
                int val;
                TicketNumber ticket_number;

                while (linestream >> val)
                {
                    ticket_number.push_back(val);
                    linestream.ignore(1);
                }
                nearby_numbers.push_back(ticket_number);
            }
        }
        return {rules, your_number, nearby_numbers};
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
    ReaderState m_state;
};

#endif // READER_H