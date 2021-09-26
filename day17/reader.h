#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <functional>
#include <numeric>

enum State
{
    ACTIVE,
    INACTIVE
};

struct StateMap
{
public:
    StateMap(const int num_rows,
             const int num_cols,
             const int num_levels,
             const int num_hyperdims)
        : num_rows(num_rows), num_cols(num_cols), num_levels(num_levels), num_hyperdims(num_hyperdims)
    {
        states.resize(num_rows * num_cols * num_levels * num_hyperdims);
        std::fill(states.begin(), states.end(), INACTIVE);
    }

    State &getState(const int row,
                    const int col,
                    const int level,
                    const int hyperdim)
    {
        return states[col + row * num_cols + level * num_rows * num_cols + hyperdim * num_cols * num_rows * num_levels];
    }

    void print();

    int countActives();

    std::vector<State> states;
    int num_rows;
    int num_cols;
    int num_levels;
    int num_hyperdims;
};

void StateMap::print()
{
    for (int hyperdim = 0; hyperdim < num_hyperdims; ++hyperdim)
    {
        std::cout << "\n ---   hyperdim: " << hyperdim << " ---" << std::endl;

        for (int level = 0; level < num_levels; ++level)
        {
            std::cout << "\n ---   level: " << level << " ---" << std::endl;

            for (int row = 0; row < num_rows; ++row)
            {
                for (int col = 0; col < num_cols; ++col)
                {
                    if (getState(row, col, level, hyperdim) == ACTIVE)
                    {
                        std::cout << "#";
                    }
                    else
                    {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl;
            }
        }
    }
}

int StateMap::countActives()
{

    auto countLambda = [](int sum, State state)
    {
        return state == ACTIVE ? sum + 1 : sum;
    };
    return std::accumulate(states.begin(), states.end(), 0, countLambda);
}

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

    StateMap readFile()
    {
        std::cout << "\n** read file **";

        std::string line;
        std::vector<State> states;
        std::stringstream sstream;
        char ch;

        while (std::getline(m_inputstream, line))
        {
            sstream = std::stringstream(line);

            while (sstream >> ch)
            {
                if (ch == '#')
                {
                    states.push_back(ACTIVE);
                }
                else
                {
                    states.push_back(INACTIVE);
                }
            }
        }

        StateMap statemap(8, 8, 1, 1);
        statemap.states = std::move(states);

        return statemap;
    }

private:
    std::string m_filename;
    std::ifstream m_inputstream;
};

#endif // READER_H