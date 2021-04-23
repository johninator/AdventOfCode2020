#include <iostream>
#include <set>
#include <thread>
#include <mutex>
#include "reader.h"

#define NUM_THREADS 4

std::set<int> convertRulesToSet(const Rules &rules);
void computeSumOfInvalidTicketNumbers(const std::vector<TicketNumber> &tickets, const std::set<int> &rules_set);

std::atomic<int> total_sum{0}, ticket_id{0};
std::mutex mymutex;

int main()
{
    // file reading
    Reader day16Reader("../../day16/input.txt");
    Input rules_and_tickets = day16Reader.readFile();

    std::set<int> rules_set = convertRulesToSet(rules_and_tickets.rules);

    std::vector<std::thread> threads(NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads[i] = std::thread(&computeSumOfInvalidTicketNumbers, rules_and_tickets.nearby_numbers, rules_set);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads[i].join();
    }

    std::cout << "total sum: " << total_sum;

    return 0;
}

std::set<int> convertRulesToSet(const Rules &rules)
{
    std::set<int> allowed_values;

    for (const auto &rule : rules)
    {
        for (int i = rule[0]; i <= rule[1]; ++i)
        {
            allowed_values.insert(i);
        }
    }

    return allowed_values;
}

void computeSumOfInvalidTicketNumbers(const std::vector<TicketNumber> &tickets, const std::set<int> &rules_set)
{
    TicketNumber ticket;

    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(mymutex);
            if (ticket_id < tickets.size())
            {
                ticket = tickets[ticket_id];
                ++ticket_id;
            }
            else
            {
                break;
            }
        }

        int sum{0};

        for (const int number : ticket)
        {
            if (rules_set.find(number) == rules_set.end())
            {
                sum += number;
            }
        }

        total_sum += sum;
    }
}
