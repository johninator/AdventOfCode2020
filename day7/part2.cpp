#include <iostream>
#include <set>
#include <map>
#include <algorithm>

#include "reader.h"

static std::vector<std::string> g_color_strings;

struct Rule
{
    int parent;
    int child;
    int num;
};

struct Bag;

struct Edge
{
    Bag *bag;
    int num;
};

struct Bag
{
    int id;
    std::vector<Bag *> parent;
    std::vector<Edge> children;
};

std::map<int, Bag *> g_id_observer;

int processRules(const std::vector<std::string> &set_of_rules);
void extractRules(const std::string &rule_string, std::vector<Rule> &rules);
size_t extractKeyword(const std::string &string_in, std::string &string_out, int &num, const std::string &keyword, const size_t pos);
int find_children(const Bag *bag);

int main()
{
    // file reading
    Reader day_7_reader("../../day7/input.txt");
    std::vector<std::string> set_of_rules = day_7_reader.readFile();

    int found_children = processRules(set_of_rules);

    std::cout << "\n no of found children: " << found_children;

    return 0;
}

int processRules(const std::vector<std::string> &set_of_rules)
{
    std::vector<Rule> rules;

    // setup rules
    for (const std::string &rule : set_of_rules)
    {
        // add new rules to existing rules
        extractRules(rule, rules);
    }

    // create graph from rules
    for (const auto &rule : rules)
    {
        // add new node if id is not known
        const auto &find_parent = g_id_observer.find(rule.parent);
        const auto &find_child = g_id_observer.find(rule.child);

        Bag *new_bag_parent;

        if (find_parent == g_id_observer.end())
        {
            new_bag_parent = new Bag;
            g_id_observer.insert(std::pair(rule.parent, new_bag_parent));
            new_bag_parent->id = rule.parent;
        }
        else
        {
            new_bag_parent = (*find_parent).second;
        }

        if (find_child == g_id_observer.end())
        {
            Bag *new_bag_child = new Bag;
            g_id_observer.insert(std::pair(rule.child, new_bag_child));
            new_bag_child->id = rule.child;
            new_bag_child->parent.push_back(new_bag_parent);
            new_bag_parent->children.push_back({new_bag_child, rule.num});
        }
        else
        {
            new_bag_parent->children.push_back({(*find_child).second, rule.num});
            find_child->second->parent.push_back(new_bag_parent);
        }
    }

    // search graph for specific bag
    std::string search_bag_name = "shiny gold";
    int id_search_bag = std::distance(g_color_strings.begin(), std::find(g_color_strings.begin(), g_color_strings.end(), search_bag_name));
    Bag *search_bag = g_id_observer[id_search_bag];

    int found_children = find_children(search_bag);

    return found_children - 1;
}

int find_children(const Bag *bag)
{
    std::vector<Edge> children = bag->children;

    int n_found_children = 0;

    if (!children.empty())
    {
        for (const Edge edge : children)
        {
            n_found_children += edge.num * find_children(edge.bag);
        }
    }

    return n_found_children + 1;
}

void extractRules(const std::string &rule_string, std::vector<Rule> &rules)
{
    // std::cout << "\n extractRules: " << rule_string;

    std::string color_string;
    int parent;
    int child;
    int num;

    size_t found_bag = extractKeyword(rule_string, color_string, num, "bag", 0);

    if (found_bag != std::string::npos)
    {
        auto &color_it = std::find(g_color_strings.begin(), g_color_strings.end(), color_string);
        // add found color to colors
        if (color_it == g_color_strings.end())
        {
            g_color_strings.push_back(color_string);
            parent = g_color_strings.size() - 1;
        }
        else
        {
            parent = std::distance(g_color_strings.begin(), color_it);
        }

        found_bag = extractKeyword(rule_string, color_string, num, "bag", found_bag + 3);

        while (found_bag != std::string::npos)
        {
            color_it = std::find(g_color_strings.begin(), g_color_strings.end(), color_string);
            // add found color to colors
            if (color_it == g_color_strings.end())
            {
                g_color_strings.push_back(color_string);
                child = g_color_strings.size() - 1;
            }
            else
            {
                child = std::distance(g_color_strings.begin(), color_it);
            }

            // add new rule
            if (num != -1)
            {
                Rule new_rule;
                new_rule.parent = parent;
                new_rule.child = child;
                new_rule.num = num;
                rules.push_back(new_rule);
            }

            // std::cout << "\n num: --" << num << "-- " << std::endl;
            // std::cout << "\n child color: --" << color_string << "-- " << std::endl;

            // continue search for next bag
            found_bag = extractKeyword(rule_string, color_string, num, "bag", found_bag + 3);
        }
    }
}

size_t extractKeyword(const std::string &string_in, std::string &string_out, int &num, const std::string &keyword, const size_t pos)
{
    size_t found_keyword = string_in.find(keyword, pos);

    if (found_keyword != std::string::npos)
    {
        // if keyword was found, extract the two preceding words
        size_t found_1st_whitespace = string_in.rfind(' ', found_keyword - 2);
        size_t found_2nd_whitespace = string_in.rfind(' ', found_1st_whitespace - 2);

        if (found_2nd_whitespace == std::string::npos)
        {
            found_2nd_whitespace = 0;
        }
        else
        {
            ++found_2nd_whitespace;
        }

        string_out = string_in.substr(found_2nd_whitespace, found_keyword - found_2nd_whitespace - 1);

        if (found_2nd_whitespace > 2 && string_out != "no other")
        {
            num = stoi(string_in.substr(found_2nd_whitespace - 2, 1));
        }
        else
        {
            num = -1;
        }
    }
    else
    {
        // std::cout << "\n could not find " << keyword << " keyword";
    }
    return found_keyword;
}