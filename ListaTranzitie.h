#ifndef LISTA_TRANZITIE_H
#define LISTA_TRANZITIE_H

#include "Tranzitie.h"

#include <vector>
#include <string>

class ListaTranzitie {
private:
    std::vector<Tranzitie> lista;

public:
    void addTranzitie(const Tranzitie& tr);
    const Tranzitie* gasesteTranzitie(const std::string& stare, char simbolGasit) const;
};

#endif
