#include <string>
#include "interpreter.h"
#include <vector>
#include <iostream>
using std::vector;
using std::string;
using std::logic_error;
using std::cout, std::endl;
using namespace std::literals;


#define REGISTER_IF(name, index) \
    namespace{ insert_into_ins_func __##name##_register (index, &interpreter:: name); } \
    void interpreter:: name(std::function<string()> str)

namespace {
    using ins_func = std::function<void(interpreter&, std::function<string()>)>;
    vector<ins_func> ins_funcs;

    class insert_into_ins_func {
    public:
        insert_into_ins_func(int index, ins_func function) {
            ins_funcs.push_back(function);
        }
    };
}


interpreter::interpreter() {
    mpointer = 0;
    opcode = 0;
    ticket = 0;
    marr.push_back(0);
}

int interpreter::access(int index) {
    int len = marr.size();
    if (len < index) {
        marr.resize(index+1);
    }
    return marr.at(index);
}

void interpreter::change_marr(int val) {
    marr.at(mpointer) += val;
    if (marr.at(mpointer) < 0) {
        throw logic_error("Memory slots out of bounds");
    }
}

void interpreter::change_mpointer(int val) {
    mpointer += val;
    if (mpointer < 0) {
        throw logic_error("Memory pointer out of bounds");
    }
}

void interpreter::change_opcode(int val) {
    opcode += val;
    if (opcode < 0) {
        throw logic_error("Opcode out of bounds");
    }
    opcode = opcode % ins_funcs.size();
}

void interpreter::change_ticket(int val) {
    ticket += val;
    if (ticket < 0) {
        throw logic_error("Ticket out of bounds");
    }
}

void interpreter::execute(string pretty_code) {
    string code;
    for (const char &ca : pretty_code) {
        if ("[]:"s .find(ca) != string::npos) {
            code += ca;
        }
    }
    int c = 0;
    while (c < code.length()) {
        if (code[c] == ']') {
            change_opcode(1);
        } else if (code[c] == '[') {
            change_opcode(-1);
        } else if (code[c] == ':') {
            ins_funcs.at(opcode)(*this, [this, code, &c]() {
                string newstring = "";
                int strcount = 0;
                if (c+ticket >= code.size()) {
                    throw logic_error("Rhoam EOF: Check end of file. ");
                }
                while (strcount != ticket) {
                    newstring += code.at(c+strcount+1);
                    strcount++;
                }
                c += newstring.length() + 1;
                return newstring;
            });
        }
        // it's funny cause c++
        c++;
    }
}

REGISTER_IF(catalog, 0) {
    cout << "Welcome to this great esolang :)";
    /* cout << "BASIC DOCUMENTATION\n"
            "Typing ']' moves the instruction pointer up one instruction\n"
            "Typing '[' moves the instruction pointer down one instruction\n"
            "Typing ':' runs the instruction you are on.\n"
            "INSTRUCTIONS\n"
            "0. Opens the Catalog\n"
            "1. Increments the memory pointer by 1\n"
            "2. Decrements the memory pointer by 1\n"
            "3. Increments the memory pointer by the value in the ticket slot\n"
            "4. Decrements the memory pointer by the value in the ticket slot\n"
            "5. Increments the ticket slot by 1\n"
            "6. Decrements the ticket slot by 1\n"
            "7. Prints the ASCII value of the value that the memory pointer is on\n"
            "8. Prints the number that the memory pointer is on\n"
            "9. Increments the instruction pointer by 10\n"
            "10. Decrements the instruction pointer by 10\n"
            "11. Increments the memory slot by 1\n"
            "12. Decrements the memory slot by 1\n";
            */
}

REGISTER_IF(imp, 1) {
    change_mpointer(1);
}

REGISTER_IF(dmp, 2) {
    change_mpointer(-1);
}

REGISTER_IF(imptt, 3) {
    change_mpointer(ticket);
}

REGISTER_IF(dmptt, 4) {
    change_mpointer(-ticket);
}

REGISTER_IF(it, 5) {
    change_ticket(1);
}

REGISTER_IF(dt, 6) {
    change_ticket(-1);
}

REGISTER_IF(pcamp, 7) {
   access(mpointer);
   char letter = marr[mpointer];
   cout << letter;

}

REGISTER_IF(paamp, 8) {
    access(mpointer);
    int ascval = marr[mpointer];
    cout << ascval;
}

REGISTER_IF(j19, 9) {
    change_opcode(10);
}

REGISTER_IF(j0, 10) {
    change_opcode(-10);
}

REGISTER_IF(ims, 11) {
    access(mpointer);
    change_marr(1);
}

REGISTER_IF(dms, 12) {
    access(mpointer);
    change_marr(-1);
}

REGISTER_IF(imstt, 13) {
    access(mpointer);
    change_marr(ticket);
}

REGISTER_IF(dmstt, 14) {
    access(mpointer);
    change_marr(-ticket);
}

REGISTER_IF(pct, 15) {
    access(mpointer);
    char chr = ticket;
    cout << chr;
}

REGISTER_IF(pat, 16) {
    access(mpointer);
    int chr = ticket;
    cout << chr;
}

REGISTER_IF(pn, 17) {
    cout << "\n";
}
REGISTER_IF(ps, 18) {
    cout << " ";
}
REGISTER_IF(j29, 19) {
    change_opcode(10);
}

REGISTER_IF(j10, 20)  {
    change_opcode(-10);
}

REGISTER_IF(luzlt, 21) {
    access(mpointer);
    string iterated = str();
    while (marr[mpointer] != 0) {
        opcode = 0;
        mpointer = 0;
        execute(iterated);
    }
    opcode = 0;
    mpointer = 0;
}

REGISTER_IF(lunlt, 22) {
    access(mpointer + 1);
    string iterated = str();
    while (marr[mpointer] != marr[mpointer+1]) {
        opcode = 0;
        mpointer = 0;
        execute(iterated);
    }
    opcode = 0;
    mpointer = 0;
}

REGISTER_IF(cgnlt, 23) {
    access(mpointer + 1);
    string iterated = str();
    if (marr[mpointer] > marr[mpointer + 1]) {
        opcode = 0;
        mpointer = 0;
        execute(iterated);
    }
    opcode = 0;
    mpointer = 0;
}

REGISTER_IF(clnlt, 24) {
    access(mpointer + 1);
    string iterated = str();
    if (marr[mpointer] < marr[mpointer + 1]) {
        opcode = 0;
        mpointer = 0;
        execute(iterated);
    }
    opcode = 0;
    mpointer = 0;
}

REGISTER_IF(ceqlt, 25) {
    access(marr[mpointer + 1]);
    string iterated = str();
    if (marr[mpointer] == marr[mpointer + 1]) {
        opcode = 0;
        mpointer = 0;
        execute(iterated);
    }
    opcode = 0;
    mpointer = 0;
}

REGISTER_IF(pet, 26) {
    mpointer = ticket;
}

REGISTER_IF(cin, 27) {
    char c;
    std::cin >> c;
    access(mpointer);
    marr[mpointer] = c;
}

REGISTER_IF(tin, 28) {
    char c;
    access(mpointer + ticket);
    for (int i = 0; i < ticket; i++) {
        std::cin >> c;
        marr[mpointer + i] = c;
    }
}

REGISTER_IF(j8, 29) {
    change_opcode(10);
}

REGISTER_IF(j20, 30) {
    change_opcode(-10);
}