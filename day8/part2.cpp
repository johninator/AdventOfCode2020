#include <iostream>
#include <vector>
#include <set>
#include "reader.h"

enum ReturnValue
{
    ONGOING,
    FAILED,
    SUCCESS
};

static int acc_val = 0;

std::set<int> instruction_observer;

void runSwappedCommands(const std::vector<Command> &commands);

bool runCommands(const std::vector<Command> &commands, std::vector<Command>::const_iterator &it_swap);

ReturnValue processCommand(const std::vector<Command> &commands,
                           std::vector<Command>::const_iterator &it,
                           std::vector<Command>::const_iterator &it_swap);
int main()
{
    // file reading
    Reader day8Reader("../../day8/input.txt");
    std::vector<Command> vals = day8Reader.readFile();

    runSwappedCommands(vals);

    std::cout << "\n acc: " << acc_val << std::endl;

    return 0;
}

void runSwappedCommands(const std::vector<Command> &commands)
{
    for (auto it = commands.begin(); it != commands.end(); ++it)
    {
        // reset
        acc_val = 0;
        instruction_observer.clear();

        if (runCommands(commands, it))
        {
            std::cout << "\n termination successful, acc: " << acc_val << std::endl;
        }
    }
}

bool runCommands(const std::vector<Command> &commands, std::vector<Command>::const_iterator &it_swap)
{
    auto it = commands.begin();
    ReturnValue rv = processCommand(commands, it, it_swap);
    while (rv == ONGOING)
    {
        rv = processCommand(commands, it, it_swap);
    }

    if (rv == SUCCESS)
    {
        return true;
    }
    return false;
}

ReturnValue processCommand(const std::vector<Command> &commands,
                           std::vector<Command>::const_iterator &it,
                           std::vector<Command>::const_iterator &it_swap)
{
    // check duplicate instruction
    if (!instruction_observer.insert(std::distance(commands.begin(), it)).second)
    {
        return FAILED;
    }

    CommandInstruction cmdInst = it->cmd;

    if (it == it_swap)
    {
        if (it_swap->cmd == CMD_JMP)
        {
            cmdInst = CMD_NOP;
        }
        else if (it_swap->cmd == CMD_NOP)
        {
            cmdInst = CMD_JMP;
        }
    }

    switch (cmdInst)
    {
    case CMD_ACC:
        acc_val += it->val;
        ++it;
        break;
    case CMD_JMP:
        it += it->val;
        break;
    case CMD_NOP:
        ++it;
        break;
    }

    if (it == commands.end())
    {
        // successful termination
        return SUCCESS;
    }
    return ONGOING;
}
