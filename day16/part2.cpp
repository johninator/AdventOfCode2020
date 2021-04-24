#include <iostream>
#include <set>
#include <numeric>
#include <algorithm>
#include "reader.h"

typedef std::vector<std::vector<int>> Matrix;

std::set<int> convertRulesToSet(const Rules &rules);
std::vector<int> findInvalidTicketIds(const std::vector<TicketNumber> &tickets, const std::set<int> &rules_set);
std::vector<TicketNumber> filterTickets(const std::vector<TicketNumber> &tickets, const std::vector<int> &invalid_ids);
void eliminateWrongLocations(const std::vector<TicketNumber> &tickets, const Rules &rules, Matrix &matrix);
long long computeSumOfDeparture(const TicketNumber &your_ticket, const Matrix &matrix);

int main()
{
    // file reading
    Reader day16Reader("../../day16/input.txt");
    Input rules_and_tickets = day16Reader.readFile();

    std::set<int> rules_set = convertRulesToSet(rules_and_tickets.rules);
    std::vector<int> invalid_ticket_ids = findInvalidTicketIds(rules_and_tickets.nearby_numbers, rules_set);
    std::vector<TicketNumber> tickets_filtered = filterTickets(rules_and_tickets.nearby_numbers, invalid_ticket_ids);

    // create matrix to determine locations
    std::vector<int> init_vector(rules_and_tickets.rules.size() / 2, 1);
    Matrix matrix(rules_and_tickets.rules.size() / 2, init_vector); // initialise matrix with ones

    eliminateWrongLocations(tickets_filtered, rules_and_tickets.rules, matrix);
    long long result = computeSumOfDeparture(rules_and_tickets.your_number, matrix);

    std::cout << "result: " << result << std::endl;

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

std::vector<int> findInvalidTicketIds(const std::vector<TicketNumber> &tickets, const std::set<int> &rules_set)
{
    std::vector<int> invalid_ids;

    for (int id{0}; id < tickets.size(); ++id)
    {
        for (const int number : tickets[id])
        {
            if (rules_set.find(number) == rules_set.end())
            {
                invalid_ids.push_back(id);
                break;
            }
        }
    }
    return invalid_ids;
}

std::vector<TicketNumber> filterTickets(const std::vector<TicketNumber> &tickets, const std::vector<int> &invalid_ids)
{
    std::vector<TicketNumber> filtered_tickets;

    std::vector<int> valid_ids;
    for (int id = 0; id < tickets.size(); ++id)
    {
        if (std::find(invalid_ids.begin(), invalid_ids.end(), id) == invalid_ids.end())
        {
            valid_ids.push_back(id);
        }
    }

    for (int id : valid_ids)
    {
        filtered_tickets.push_back(tickets[id]);
    }
    return filtered_tickets;
}

void eliminateWrongLocations(const std::vector<TicketNumber> &tickets, const Rules &rules, Matrix &matrix)
{
    for (int position = 0; position < matrix.size(); ++position)
    {
        for (const auto &ticket : tickets)
        {
            const int number = ticket[position];

            for (int rule = 0; rule < matrix[position].size(); ++rule)
            {
                if (number < rules[2 * rule][0] ||
                    (number > rules[2 * rule][1] && number < rules[2 * rule + 1][0]) ||
                    number > rules[2 * rule + 1][1])
                {
                    matrix[position][rule] = 0;
                }
            }
        }
    }

    bool all_resolved = false;

    while (!all_resolved)
    {
        all_resolved = true;

        for (int position = 0; position < matrix.size(); ++position)
        {
            // check if position is already resolved
            if (std::accumulate(matrix[position].begin(), matrix[position].end(), 0) == 1)
            {
                auto rule_it = std::find(matrix[position].begin(), matrix[position].end(), 1);
                int rule = std::distance(matrix[position].begin(), rule_it);

                for (int pos = 0; pos < matrix.size(); ++pos)
                {
                    if (pos != position)
                    {
                        matrix[pos][rule] = 0;
                    }
                }
            }
            all_resolved = all_resolved && (std::accumulate(matrix[position].begin(), matrix[position].end(), 0) == 1);
        }
    }
}

long long computeSumOfDeparture(const TicketNumber &your_ticket, const Matrix &matrix)
{
    std::vector<int> departure_positions;

    for (int rule = 0; rule < 6; ++rule)
    {
        for (int position = 0; position < matrix.size(); ++position)
        {
            if (matrix[position][rule] == 1)
            {
                departure_positions.push_back(position);
            }
        }
    }

    long long result{1};
    std::for_each(departure_positions.begin(), departure_positions.end(),
                  [&](int position) {
                      result *= your_ticket[position];
                  });
    return result;
}
