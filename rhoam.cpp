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

/*
 * -d: debugging
 *      if it is run without any args or other flags, interpreter in debug mode
 *      otherwise, it can be debugging a file in a mode, for example,
 *      `rhoam -dw hello_world.rhm` will debug hello_world.rhm in rhoam wrap mode.
 *
 *      File debugger:
 *          insert breakpoints manually with b l3c4 (line 3 char 4). If no line is specified,
 *          it will continue as characters in file. If chars go off the line, it will error.
 *
 *          Memory / Instruction panes show up, you can scroll them with mma (move mem arr) and
 *          mia. For example mia 10 will scroll it forward by 10, and mma -3 will scroll it back by 3
 *
 *          Getting values can be done with gt (get ticket) gma (get memory at) gmap (get memory at pointer),
 *          gia (get instruction at), and giap (get instruction at pointer).
 *
 *          You can do `s` to step through program after breakpoint, `c` to continue normal execution, and
 *          `exit` to exit the debugger.
 *
 * -n / -w / -u: modes
 *      runs a file in a mode. -u wont work for debugger and interpreter, but -w and
 *      -n will. wrap and normal are able to be debugged, interpreted, debugged in file, and
 *      interpreted in file. -u is only able to be interpreted in file.
 * -h: help
 *      gives output on everything e.z
 */
