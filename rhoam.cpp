#include <iostream>
#include "interpreter.h"
using std::cout, std::cin, std::ifstream, std::ios;
#include <fstream>
#include <iterator>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "No file specified\n";
    } else if (argc > 2) {
        cout << "Too many arguments. \n";
    } else {
        ifstream filestream(argv[1], ios::in);
        if (!filestream) {
            cout << "No file. \n";
        } else {
            string code (std::istream_iterator<char>{filestream}, (std::istream_iterator<char>{}));
            interpreter rhoam{};
            rhoam.execute(code);
        }

    }
    return 0;
}


