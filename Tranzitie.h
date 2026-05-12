#ifndef TRANZITIE_H
#define TRANZITIE_H

#include <string>

class Tranzitie {
private:
    std::string sti;
    char simbolGasit;
    char simbolScris;
    char directie;
    std::string stf;

public:
    Tranzitie();
    Tranzitie(std::string sti, char simbolGasit, char simbolScris, char directie, std::string stf);

    std::string getSti() const;
    char getSimbolGasit() const;
    char getSimbolScris() const;
    char getDirectie() const;
    std::string getStf() const;

    std::string toString() const;
};

#endif
