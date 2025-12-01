#include <iostream>
#include <memory>
#include "Grid.h"
#include "ConwayRule.h"
#include "ConsoleRenderer.h"
#include "Game.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input-file> [iterations]\n";
        return 1;
    }
    std::string path = argv[1];
    int iterations = 10;
    if (argc >= 3) iterations = std::stoi(argv[2]);


    return 0;
}
