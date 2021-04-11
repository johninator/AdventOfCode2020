#include <iostream>
#include <vector>
#include <set>
#include "reader.h"

int main()
{
    // file reading
    Reader day12Reader("../../day12/input.txt");
    std::vector<Command> cmds = day12Reader.readFile();

    ShipState shipState;
    for (const auto &cmd : cmds)
    {
        shipState.move(cmd);
        //shipState.printStats();
    }

    std::cout << "\n Manhattan distance: " << shipState.getManhattanDistance();

    return 0;
}
