#ifndef MT_H
#define MT_H

#include "ListaTranzitie.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

class MT {
private:
    std::string stare_initiala;
    ListaTranzitie lista;
    std::vector<std::string> stari_finale;

    const char blank = 'B';
    const int limitaPasi = 10000;

public:
    MT(std::string stare_initiala, ListaTranzitie lista, std::vector<std::string> stari_finale);
    MT(std::string numeFisier);

    bool analizeazaCuvant(const std::string& cuvant);
    bool analizeazaCuvant(const std::string& cuvant, bool afiseazaPasi);

private:
    std::unordered_map<int, char> initializareBanda(const std::string& cuvant) const;
    char citeste(const std::unordered_map<int, char>& banda, int pozitie) const;
    void scrie(std::unordered_map<int, char>& banda, int pozitie, char simbol) const;
    bool esteStareFinala(const std::string& stare) const;

    void afiseazaConfiguratie(
        int pas,
        const std::string& stareCurenta,
        const std::unordered_map<int, char>& banda,
        int pozitieCap
    ) const;

    std::string snapshot(const std::unordered_map<int, char>& banda, int pozitieCap) const;
    std::string continutUtil(const std::unordered_map<int, char>& banda) const;
    std::string afiseazaCuvant(const std::string& cuvant) const;

    std::string citesteLinieUtila(std::ifstream& fisier) const;
    std::string curataLinie(std::string linie) const;
    std::vector<std::string> split(const std::string& linie) const;
};

#endif
