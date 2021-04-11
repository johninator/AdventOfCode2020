#include <iostream>
#include "shipState_2.h"

void ShipState::move(const Command &cmd)
{
    switch (cmd.action)
    {
    case Action::NORTH:
        m_waypoint_north += cmd.value;
        break;
    case Action::SOUTH:
        m_waypoint_north -= cmd.value;
        break;
    case Action::WEST:
        m_waypoint_east -= cmd.value;
        break;
    case Action::EAST:
        m_waypoint_east += cmd.value;
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
    m_pos_north += m_waypoint_north * value;
    m_pos_east += m_waypoint_east * value;
}

void ShipState::moveHeading(const int value, const Action &action)
{
    float angle_rad = value * 3.1415f / 180.0f;

    if (action == RIGHT)
    {
        angle_rad *= -1.0f;
    }

    // rotate with rotation matrix
    int east_orig = m_waypoint_east;
    int north_orig = m_waypoint_north;
    m_waypoint_east = std::round(east_orig * cos(angle_rad) - north_orig * sin(angle_rad));
    m_waypoint_north = std::round(east_orig * sin(angle_rad) + north_orig * cos(angle_rad));
}

void ShipState::printStats()
{
    std::cout << "\n east: " << m_pos_east
              << ", north: " << m_pos_north
              << ", waypoint east: " << m_waypoint_east
              << ", waypoint north: " << m_waypoint_north;
}