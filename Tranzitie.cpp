#include "Tranzitie.h"

#include <cctype>
#include <stdexcept>

Tranzitie::Tranzitie() {
    this->sti = "";
    this->simbolGasit = 'B';
    this->simbolScris = 'B';
    this->directie = 'S';
    this->stf = "";
}

Tranzitie::Tranzitie(std::string sti, char simbolGasit, char simbolScris, char directie, std::string stf) {
    directie = static_cast<char>(std::toupper(static_cast<unsigned char>(directie)));

    if (directie != 'L' && directie != 'R' && directie != 'S') {
        throw std::runtime_error("Directia trebuie sa fie L, R sau S.");
    }

    this->sti = sti;
    this->simbolGasit = simbolGasit;
    this->simbolScris = simbolScris;
    this->directie = directie;
    this->stf = stf;
}

std::string Tranzitie::getSti() const {
    return this->sti;
}

char Tranzitie::getSimbolGasit() const {
    return this->simbolGasit;
}

char Tranzitie::getSimbolScris() const {
    return this->simbolScris;
}

char Tranzitie::getDirectie() const {
    return this->directie;
}

std::string Tranzitie::getStf() const {
    return this->stf;
}

std::string Tranzitie::toString() const {
    return "(" + sti + ", " + std::string(1, simbolGasit) + ") -> (" + stf + ", "
        + std::string(1, simbolScris) + ", " + std::string(1, directie) + ")";
}
