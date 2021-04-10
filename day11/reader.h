#ifndef READER_H
#define READER_H

#include <string>
#include <string_view>
#include <fstream>
#include <vector>
#include <algorithm>

enum SeatState
{
    FLOOR,
    EMPTY,
    OCCUPIED
};

typedef std::vector<SeatState> SeatLine;
typedef std::vector<SeatLine> SeatMap;

class Reader
{
public:
    Reader(const std::string_view &filename_)
        : m_filename(filename_)
    {
        m_filestream.open(m_filename);
    }

    SeatMap readFile()
    {
        std::cout << "\n** read file **";

        SeatMap seatmap;
        std::string line;

        while (std::getline(m_filestream, line))
        {
            SeatLine seatline;
            std::for_each(line.begin(), line.end(), [&seatline](const char &ch) {
                switch (ch)
                {
                case '.':
                    seatline.push_back(SeatState::FLOOR);
                    break;
                case 'L':
                    seatline.push_back(SeatState::EMPTY);
                    break;
                case '#':
                    seatline.push_back(SeatState::OCCUPIED);
                    break;
                }
            });
            seatmap.push_back(seatline);
        }
        return seatmap;
    }

private:
    std::string m_filename;
    std::ifstream m_filestream;
};

#endif // READER_H