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
};

struct Bag
{
    int id;
    std::vector<Bag *> parent;
    std::vector<Bag *> children;

    Bag()
    {
    }
};

std::map<int, Bag *> g_id_observer;

int processRules(const std::vector<std::string> &set_of_rules);
void extractRules(const std::string &rule_string, std::vector<Rule> &rules);
size_t extractKeyword(const std::string &string_in,
                      std::string &string_out,
                      const std::string &keyword,
                      const size_t pos);
void find_parents(const Bag *bag, std::set<int> &found_parent_ids);

int main()
{
    // file reading
    Reader day_7_reader("../../day7/input.txt");
    std::vector<std::string> set_of_rules = day_7_reader.readFile();

    int found_parents = processRules(set_of_rules);

    std::cout << "\n no of found parents: " << found_parents;

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
            new_bag_parent->children.push_back(new_bag_parent);
        }
        else
        {
            new_bag_parent->children.push_back((*find_child).second);
            find_child->second->parent.push_back(new_bag_parent);
        }
    }

    // search graph for specific bag
    std::string search_bag_name = "shiny gold";
    int id_search_bag = std::distance(g_color_strings.begin(), std::find(g_color_strings.begin(), g_color_strings.end(), search_bag_name));
    std::set<int> found_parent_ids;
    Bag *search_bag = g_id_observer[id_search_bag];

    find_parents(search_bag, found_parent_ids);

    return found_parent_ids.size();
}

void find_parents(const Bag *bag, std::set<int> &found_parent_ids)
{
    std::vector<Bag *> parents = bag->parent;

    if (parents.empty())
    {
        return;
    }
    else
    {

        for (const Bag *bag : parents)
        {
            found_parent_ids.insert(bag->id);
            find_parents(bag, found_parent_ids);
        }
    }
}

void extractRules(const std::string &rule_string, std::vector<Rule> &rules)
{
    // std::cout << "\n extractRules: " << rule_string;

    std::string color_string;
    int parent;
    int child;

    size_t found_bag = extractKeyword(rule_string, color_string, "bag", 0);

    // std::cout << "\n parent color: --" << color_string << "-- " << std::endl;

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

        found_bag = extractKeyword(rule_string, color_string, "bag", found_bag + 3);

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
            Rule new_rule;
            new_rule.parent = parent;
            new_rule.child = child;
            rules.push_back(new_rule);

            // std::cout << "\n child color: --" << color_string << "-- " << std::endl;

            // continue search for next bag
            found_bag = extractKeyword(rule_string, color_string, "bag", found_bag + 3);
        }
    }
}

size_t extractKeyword(const std::string &string_in, std::string &string_out, const std::string &keyword, const size_t pos)
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
    }
    else
    {
        // std::cout << "\n could not find " << keyword << " keyword";
    }
    return found_keyword;
}