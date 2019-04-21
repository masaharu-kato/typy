#include "stream.hpp"
#include <iostream>
#include <fstream>
#include <memory>

using namespace typy;

int main(int argc, char *argv[]) {

    if(argc < 2) { std::cerr << "No input file.\n"; return -1; }

    std::ifstream ifs(argv[1]);
    if(ifs.fail()) { std::cerr << "Failed to open input file.\n"; return -1; }
    Stream stream(ifs);

    int i = 0;
    while(stream) {
        char c;
        stream >> c;
        std::cout << i << '\t' << c << "\n";
        i++;
    }

    return 0;
}