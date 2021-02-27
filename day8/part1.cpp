#include <iostream>
#include <vector>
#include <set>
#include "reader.h"

static int acc_val = 0;

std::set<int> instruction_observer;

void runCommands(const std::vector<Command> &commands);

bool processCommand(const std::vector<Command> &commands, std::vector<Command>::const_iterator &it);

int main()
{
    // file reading
    Reader day8Reader("../../day8/input.txt");
    std::vector<Command> vals = day8Reader.readFile();

    runCommands(vals);

    std::cout << "\n acc: " << acc_val << std::endl;

    return 0;
}

void runCommands(const std::vector<Command> &commands)
{
    auto it = commands.begin();
    while (processCommand(commands, it))
    {
    }
}

bool processCommand(const std::vector<Command> &commands, std::vector<Command>::const_iterator &it)
{
    // check duplicate instruction
    if (!instruction_observer.insert(std::distance(commands.begin(), it)).second)
    {
        return false;
    }

    switch (it->cmd)
    {
    case CMD_ACC:
        acc_val += it->val;
        ++it;
        return true;
        break;
    case CMD_JMP:
        it += it->val;
        return true;
        break;
    case CMD_NOP:
        ++it;
        return true;
        break;
    default:
        return false;
    }
}
