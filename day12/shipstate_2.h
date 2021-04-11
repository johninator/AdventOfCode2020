#ifndef H_SHIPSTATE_2
#define H_SHIPSTATE_2

enum Action
{
    NORTH,
    SOUTH,
    WEST,
    EAST,
    LEFT,
    RIGHT,
    FORWARD
};

struct Command
{
    Action action;
    int value;
};

class ShipState
{
public:
    ShipState(const int start_pos_east,
              const int start_pos_north)
        : m_pos_east(start_pos_east),
          m_pos_north(start_pos_north) {}
    ShipState() = default;

    void move(const Command &cmd);
    void moveForward(const int value);
    void moveHeading(const int value, const Action &action);
    int getManhattanDistance() const { return std::abs(m_pos_east) + std::abs(m_pos_north); };
    void printStats();

private:
    int m_pos_east{0};
    int m_pos_north{0};
    int m_waypoint_east{10};
    int m_waypoint_north{1};
};

#endif // H_SHIPSTATE_2