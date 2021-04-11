#include <iostream>
#include "shipstate.h"

void ShipState::move(const Command &cmd)
{
    switch (cmd.action)
    {
    case Action::NORTH:
        m_pos_north += cmd.value;
        break;
    case Action::SOUTH:
        m_pos_north -= cmd.value;
        break;
    case Action::WEST:
        m_pos_east -= cmd.value;
        break;
    case Action::EAST:
        m_pos_east += cmd.value;
        break;
    case Action::LEFT:
        moveHeading(cmd.value, Action::LEFT);
        break;
    case Action::RIGHT:
        moveHeading(cmd.value, Action::RIGHT);
        break;
    case Action::FORWARD:
        moveForward(cmd.value);
        break;
    default:
        std::cerr << "unknown action: " << cmd.action << std::endl;
    }
}

void ShipState::moveForward(const int value)
{
    switch (m_heading)
    {
    case Heading::HEAD_NORTH:
        m_pos_north += value;
        break;
    case Heading::HEAD_SOUTH:
        m_pos_north -= value;
        break;
    case Heading::HEAD_WEST:
        m_pos_east -= value;
        break;
    case Heading::HEAD_EAST:
        m_pos_east += value;
        break;
    }
}

void ShipState::moveHeading(const int value, const Action &action)
{
    int turns = (value / 90) % 4;
    int heading_int;
    if (action == Action::LEFT)
    {
        heading_int = ((int)m_heading + turns) % 4;
    }
    else
    {
        heading_int = ((int)m_heading - turns) % 4;
    }

    if (heading_int < 0)
    {
        heading_int += 4;
    }
    m_heading = (Heading)heading_int;
}

void ShipState::printStats()
{
    std::cout << "\n east: " << m_pos_east
              << ", north: " << m_pos_north
              << ", heading: " << m_heading;
}