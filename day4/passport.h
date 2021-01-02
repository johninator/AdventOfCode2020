#ifndef PASSPORT_H
#define PASSPORT_H

#include <string>

class Passport
{
private:
    int year_birth = -1;
    int year_issue = -1;
    int year_expiration = -1;
    int height = -1;
    int hair_color = -1;
    std::string eye_color = "";
    int passport_id = -1;
    int country_id = -1;

public:
    void map_key_value_pair(std::string key, std::string value);
    void process_line(std::string line);
    bool is_valid() const;
};

bool Passport::is_valid() const
{
    if (year_birth != -1 && year_issue != -1 && year_expiration != -1 && passport_id != -1 && height != -1 && hair_color != -1 && eye_color != "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Passport::process_line(std::string line)
{
    size_t found_pos(0);
    std::string key;
    std::string value;

    while (found_pos != std::string::npos)
    {
        found_pos = line.find(':', found_pos + 1);
        if (found_pos != std::string::npos)
        {
            key = line.substr(found_pos - 3, 3);
            // find next whitespace or null symbol
            size_t found_ws = line.find(' ', found_pos);
            if (found_ws != std::string::npos)
            {
                // std::cout << "\n found whitespace: " << found_ws;
                value = line.substr(found_pos + 1, found_ws - found_pos - 1);
            }
            else
            {
                value = line.substr(found_pos + 1);
            }
            // pass found key-value-pair
            // std::cout << "\nkey: " << key << " value: " << value;
            map_key_value_pair(key, value);
        }
    }
}

void Passport::map_key_value_pair(std::string key, std::string value)
{
    int value_int;

    if (key == "byr")
    {
        std::istringstream ss(value);
        ss >> value_int;
        if (value_int >= 1920 && value_int <= 2002 && value.size() == 4)
        {
            std::cout << "\nvalid year birth";
            year_birth = value_int;
        }
    }
    else if (key == "iyr")
    {
        std::istringstream ss(value);
        ss >> value_int;
        if (value_int >= 2010 && value_int <= 2020 && value.size() == 4)
        {
            std::cout << "\nvalid year issue";
            year_issue = value_int;
        }
    }
    else if (key == "eyr")
    {
        std::istringstream ss(value);
        ss >> value_int;
        if (value_int >= 2020 && value_int <= 2030 && value.size() == 4)
        {
            std::cout << "\nvalid year expiration";
            year_expiration = value_int;
        }
    }
    else if (key == "hgt")
    {
        std::istringstream ss(value);
        ss >> value_int;
        std::string unit;
        ss >> unit;
        if (unit == "cm")
        {
            if (value_int >= 150 && value_int <= 193)
                height = value_int;
        }
        else if (unit == "in")
        {
            if (value_int >= 59 && value_int <= 76)
                height = value_int;
        }
    }
    else if (key == "hcl")
    {
        // check preceding # symbol
        if (value[0] != '#')
            return;

        std::string value_substr = value.substr(1);
        if (value_substr.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos)
        {
            // only hex symbols in string
            value_int = (int)strtol(value_substr.c_str(), NULL, 16);
            std::cout << "\nvalid hair color";
            hair_color = value_int;
        }
    }
    else if (key == "ecl")
    {
        if (value == "amb" ||
            value == "blu" ||
            value == "brn" ||
            value == "gry" ||
            value == "grn" ||
            value == "hzl" ||
            value == "oth")
        {
            std::cout << "\nvalid eye color";
            eye_color = value;
        }
    }
    else if (key == "pid")
    {
        std::istringstream ss(value);
        ss >> value_int;
        if (value_int < 1000000000 && value.size() == 9)
        {
            std::cout << "\nvalid passport id";
            passport_id = value_int;
        }
    }
    else if (key == "cid")
    {
    }
}

#endif // PASSPORT_H