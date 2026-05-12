#include "ListaTranzitie.h"

#include <stdexcept>

void ListaTranzitie::addTranzitie(const Tranzitie& tr) {
    for (const Tranzitie& tranzitie : lista) {
        if (tranzitie.getSti() == tr.getSti()
                && tranzitie.getSimbolGasit() == tr.getSimbolGasit()) {
            throw std::runtime_error(
                "Masina Turing nu este determinista. Exista doua tranzitii pentru ("
                + tr.getSti() + ", " + std::string(1, tr.getSimbolGasit()) + ")."
            );
        }
    }

    this->lista.push_back(tr);
}

const Tranzitie* ListaTranzitie::gasesteTranzitie(const std::string& stare, char simbolGasit) const {
    for (const Tranzitie& tranzitie : lista) {
        if (tranzitie.getSti() == stare && tranzitie.getSimbolGasit() == simbolGasit) {
            return &tranzitie;
        }
    }

    return nullptr;
}
