#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct Mask
{
    long long mask_one;
    long long mask_zero;
    std::vector<int> floating_positions;
};

struct Assignment
{
    int pos;
    long long value;
};

struct AssignmentPack
{
    Mask mask;
    std::vector<Assignment> assignments;
};

typedef std::vector<AssignmentPack> AssignmentPacks;

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

    AssignmentPacks readFile()
    {
        std::cout << "\n** read file **";

        AssignmentPacks assignmentpacks;
        AssignmentPack assignmentpack;
        std::string line;
        std::string word;
        std::istringstream lineStream;

        while (std::getline(m_inputstream, line))
        {
            lineStream = std::istringstream(line);

            lineStream >> word;

            if (word == "mask")
            {
                // add previous pack and clear it
                if (!assignmentpack.assignments.empty())
                {
                    assignmentpacks.push_back(assignmentpack);
                    assignmentpack.assignments.clear();
                }
                // add new pack
                Mask mask{0, 0};
                lineStream >> word; // skip '=' sign
                lineStream >> word;

                int pos = 35;
                for (char ch : word)
                {
                    if (ch == '0')
                    {
                        mask.mask_zero |= (1ULL << pos);
                    }
                    else if (ch == '1')
                    {
                        mask.mask_one |= (1ULL << pos);
                    }
                    else if (ch == 'X')
                    {
                        mask.floating_positions.push_back(pos);
                    }
                    --pos;
                }
                assignmentpack.mask = mask;
            }
            else
            {
                Assignment assignment;
                assignment.pos = std::stoi(word.substr(4, word.length()));

                lineStream >> word; // skip '=' sign
                lineStream >> word;

                assignment.value = std::stoll(word);
                assignmentpack.assignments.push_back(assignment);
            }
        }

        // add previous pack and clear it
        if (!assignmentpack.assignments.empty())
        {
            assignmentpacks.push_back(assignmentpack);
        }

        return assignmentpacks;
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
};

#endif // READER_H