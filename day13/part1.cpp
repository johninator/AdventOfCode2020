#include <iostream>
#include <vector>
#include <algorithm>
#include "reader.h"

struct BusOutput
{
    int timestamp;
    int bus_id;
};

BusOutput computeBusOutput(const BusInput &input);

int main()
{
    // file reading
    Reader day13Reader("../../day13/input.txt");
    BusInput busInput = day13Reader.readFile();
    BusOutput busOutput = computeBusOutput(busInput);

    std::cout << "\n timediff: " << busOutput.timestamp << ", bus_id: " << busOutput.bus_id << ", mul: " << busOutput.timestamp * busOutput.bus_id;

    return 0;
}

BusOutput computeBusOutput(const BusInput &input)
{
    // compute vector of modulos
    std::vector<int> modulos;
    std::for_each(input.bus_ids.begin(),
                  input.bus_ids.end(),
                  [&modulos, &input](const int bus_id) {
                      modulos.push_back(bus_id - input.timestamp % bus_id);
                  });

    std::cout << "\n modulos";
    for (auto modulo : modulos)
    {
        std::cout << "\n " << modulo;
    }

    std::cout << "\n busids";
    for (auto id : input.bus_ids)
    {
        std::cout << "\n " << id;
    }

    auto timediff_it = std::min_element(modulos.begin(), modulos.end());
    int bus_id = input.bus_ids[std::distance(modulos.begin(), timediff_it)];
    return {*timediff_it, bus_id};
}
