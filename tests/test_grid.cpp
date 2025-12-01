#include <iostream>
#include "../src/Grid.h"
#include "../src/ConwayRule.h"
#include <cassert>

int main() {
    // Exemple: 3x3 "blinker" horizontal -> vertical après 1 it.
    std::vector<int> init = {
        0,0,0,
        1,1,1,
        0,0,0
    };
    Grid g(3,3,init);
    ConwayRule rule;
    Grid next = g.computeNextGrid(rule);
    std::vector<int> expect = {
        0,1,0,
        0,1,0,
        0,1,0
    };
    Grid expected(3,3,expect);
    assert(next == expected);
    std::cout << "Test blinker passed\n";
    return 0;
}
