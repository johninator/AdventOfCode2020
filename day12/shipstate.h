#ifndef H_SHIPSTATE
#define H_SHIPSTATE

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

enum Heading
{
    HEAD_NORTH,
    HEAD_WEST,
    HEAD_SOUTH,
    HEAD_EAST
};

class ShipState
{
public:
    ShipState(const int start_pos_east,
              const int start_pos_north,
              const Heading start_heading)
        : m_pos_east(start_pos_east),
          m_pos_north(start_pos_north),
          m_heading(start_heading) {}
    ShipState() = default;

    void move(const Command &cmd);
    void moveForward(const int value);
    void moveHeading(const int value, const Action &action);
    int getManhattanDistance() const { return std::abs(m_pos_east) + std::abs(m_pos_north); };
    void printStats();

private:
    int m_pos_east{0};
    int m_pos_north{0};
    Heading m_heading{Heading::HEAD_EAST};
};

#endif