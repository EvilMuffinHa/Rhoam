#include <vector>
#include <string>
using std::vector;
using std::string;

#ifndef RHOAMC_INTERPRETER_H
#define RHOAMC_INTERPRETER_H


class interpreter {

public:
    interpreter(interpreter&) = delete;
    interpreter();
    void execute(string code);
    void catalog(std::function<string()> str);
    void imp(std::function<string()> str);
    void dmp(std::function<string()> str);
    void imptt(std::function<string()> str);
    void dmptt(std::function<string()> str);
    void it(std::function<string()> str);
    void dt(std::function<string()> str);
    void pcamp(std::function<string()> str);
    void paamp(std::function<string()> str);
    void j19(std::function<string()> str);
    void j0(std::function<string()> str);
    void ims(std::function<string()> str);
    void dms(std::function<string()> str);
    void imstt(std::function<string()> str);
    void dmstt(std::function<string()> str);
    void pct(std::function<string()> str);
    void pat(std::function<string()> str);
    void pn(std::function<string()> str);
    void ps(std::function<string()> str);
    void j29(std::function<string()> str);
    void j10(std::function<string()> str);
    void luzlt(std::function<string()> str);
    void lunlt(std::function<string()> str);
    void cgnlt(std::function<string()> str);
    void clnlt(std::function<string()> str);
    void ceqlt(std::function<string()> str);
    void pet(std::function<string()> str);
    void cin(std::function<string()> str);
    void tin(std::function<string()> str);
    void j8(std::function<string()> str);
    void j20(std::function<string()> str);
protected:

    int mpointer;
    int opcode;
    vector<int> marr;
    int ticket;


    int access(int index);

    void change_mpointer(int val);

    void change_marr(int val);

    void change_opcode(int val);

    void change_ticket(int val);
};


#endif // RHOAMC_INTERPRETER_H
