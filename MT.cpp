#include "MT.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>

MT::MT(std::string stare_initiala, ListaTranzitie lista, std::vector<std::string> stari_finale) {
    this->stare_initiala = stare_initiala;
    this->lista = lista;
    this->stari_finale = stari_finale;
}

MT::MT(std::string numeFisier) {
    std::ifstream fisier(numeFisier);

    if (!fisier.is_open()) {
        throw std::runtime_error("Nu se poate deschide fisierul: " + numeFisier);
    }

    this->stare_initiala = citesteLinieUtila(fisier);

    std::string starif = citesteLinieUtila(fisier);
    this->stari_finale = split(starif);

    std::string tmp;

    while (std::getline(fisier, tmp)) {
        tmp = curataLinie(tmp);

        if (tmp.empty()) {
            continue;
        }

        std::vector<std::string> elemente = split(tmp);

        if (elemente.size() != 5) {
            throw std::runtime_error("Tranzitie invalida: " + tmp);
        }

        Tranzitie tr(
            elemente[0],
            elemente[1][0],
            elemente[2][0],
            elemente[3][0],
            elemente[4]
        );

        this->lista.addTranzitie(tr);
    }
}

bool MT::analizeazaCuvant(const std::string& cuvant) {
    return analizeazaCuvant(cuvant, false);
}

bool MT::analizeazaCuvant(const std::string& cuvant, bool afiseazaPasi) {
    std::unordered_map<int, char> banda = initializareBanda(cuvant);

    std::string stareCurenta = this->stare_initiala;
    int pozitieCap = 0;
    int pasi = 0;
    std::string motivOprire = "";

    if (afiseazaPasi) {
        std::cout << "===== MASINA TURING =====" << std::endl;
        std::cout << "Stare initiala: " << stare_initiala << std::endl;

        std::cout << "Stari finale: ";
        for (const std::string& stare : stari_finale) {
            std::cout << stare << " ";
        }

        std::cout << std::endl;
        std::cout << "Cuvant de intrare: " << afiseazaCuvant(cuvant) << std::endl;
        std::cout << std::endl;

        afiseazaConfiguratie(pasi, stareCurenta, banda, pozitieCap);
    }

    while (true) {
        if (esteStareFinala(stareCurenta)) {
            motivOprire = "s-a ajuns intr-o stare finala";
            break;
        }

        if (pasi >= limitaPasi) {
            motivOprire = "s-a depasit limita de pasi; posibila bucla infinita";
            break;
        }

        char simbolCitit = citeste(banda, pozitieCap);
        const Tranzitie* temp = lista.gasesteTranzitie(stareCurenta, simbolCitit);

        if (temp == nullptr) {
            motivOprire = "nu exista tranzitie pentru (" + stareCurenta + ", " + std::string(1, simbolCitit) + ")";
            break;
        }

        scrie(banda, pozitieCap, temp->getSimbolScris());

        if (temp->getDirectie() == 'R') {
            pozitieCap++;
        } else if (temp->getDirectie() == 'L') {
            pozitieCap--;
        } else if (temp->getDirectie() == 'S') {
            // Capul ramane pe aceeasi pozitie.
        } else {
            throw std::runtime_error("Directie invalida: " + std::string(1, temp->getDirectie()));
        }

        stareCurenta = temp->getStf();
        pasi++;

        if (afiseazaPasi) {
            std::cout << "Tranzitie aplicata: " << temp->toString() << std::endl;
            afiseazaConfiguratie(pasi, stareCurenta, banda, pozitieCap);
        }
    }

    bool acceptat = esteStareFinala(stareCurenta);

    std::cout << "----Rezultat----" << std::endl;
    std::cout << "Cuvant analizat: " << afiseazaCuvant(cuvant) << std::endl;
    std::cout << "Stare oprire: " << stareCurenta << std::endl;
    std::cout << "Pasi executati: " << pasi << std::endl;
    std::cout << "Motiv oprire: " << motivOprire << std::endl;
    std::cout << "Output banda fara blank-uri: " << continutUtil(banda) << std::endl;

    if (afiseazaPasi) {
        std::cout << "Banda finala:" << std::endl;
        std::cout << snapshot(banda, pozitieCap) << std::endl;
    }

    return acceptat;
}

std::unordered_map<int, char> MT::initializareBanda(const std::string& cuvant) const {
    std::unordered_map<int, char> banda;

    // Pozitia 0 este blank.
    // Cuvantul incepe de la pozitia 1.
    // Astfel, tranzitia q0 B B R q1 duce capul pe primul simbol al cuvantului.
    for (int i = 0; i < static_cast<int>(cuvant.length()); i++) {
        banda[i + 1] = cuvant[i];
    }

    return banda;
}

char MT::citeste(const std::unordered_map<int, char>& banda, int pozitie) const {
    auto it = banda.find(pozitie);

    if (it != banda.end()) {
        return it->second;
    }

    return blank;
}

void MT::scrie(std::unordered_map<int, char>& banda, int pozitie, char simbol) const {
    if (simbol == blank) {
        banda.erase(pozitie);
    } else {
        banda[pozitie] = simbol;
    }
}

bool MT::esteStareFinala(const std::string& stare) const {
    for (const std::string& s : stari_finale) {
        if (s == stare) {
            return true;
        }
    }

    return false;
}

void MT::afiseazaConfiguratie(
        int pas,
        const std::string& stareCurenta,
        const std::unordered_map<int, char>& banda,
        int pozitieCap
) const {
    std::cout << "Pas " << pas << " | stare curenta = " << stareCurenta
              << " | pozitie cap = " << pozitieCap << std::endl;
    std::cout << snapshot(banda, pozitieCap) << std::endl;
}

std::string MT::snapshot(const std::unordered_map<int, char>& banda, int pozitieCap) const {
    int minPoz = pozitieCap;
    int maxPoz = pozitieCap;

    for (const auto& element : banda) {
        if (element.first < minPoz) {
            minPoz = element.first;
        }

        if (element.first > maxPoz) {
            maxPoz = element.first;
        }
    }

    minPoz--;
    maxPoz++;

    std::ostringstream linieBanda;
    std::ostringstream linieCap;

    for (int i = minPoz; i <= maxPoz; i++) {
        linieBanda << citeste(banda, i) << ' ';

        if (i == pozitieCap) {
            linieCap << "^ ";
        } else {
            linieCap << "  ";
        }
    }

    return linieBanda.str() + "\n" + linieCap.str();
}

std::string MT::continutUtil(const std::unordered_map<int, char>& banda) const {
    if (banda.empty()) {
        return "#";
    }

    int minPoz = INT_MAX;
    int maxPoz = INT_MIN;

    for (const auto& element : banda) {
        if (element.first < minPoz) {
            minPoz = element.first;
        }

        if (element.first > maxPoz) {
            maxPoz = element.first;
        }
    }

    std::string rezultat;

    for (int i = minPoz; i <= maxPoz; i++) {
        char simbol = citeste(banda, i);

        if (simbol != blank) {
            rezultat += simbol;
        }
    }

    if (rezultat.empty()) {
        return "#";
    }

    return rezultat;
}

std::string MT::afiseazaCuvant(const std::string& cuvant) const {
    if (cuvant.empty()) {
        return "#";
    }

    return cuvant;
}

std::string MT::citesteLinieUtila(std::ifstream& fisier) const {
    std::string linie;

    while (std::getline(fisier, linie)) {
        linie = curataLinie(linie);

        if (!linie.empty()) {
            return linie;
        }
    }

    throw std::runtime_error("Fisierul de tranzitii nu are suficiente linii utile.");
}

std::string MT::curataLinie(std::string linie) const {
    std::size_t pozComentariu = linie.find(';');

    if (pozComentariu != std::string::npos) {
        linie = linie.substr(0, pozComentariu);
    }

    pozComentariu = linie.find("//");

    if (pozComentariu != std::string::npos) {
        linie = linie.substr(0, pozComentariu);
    }

    std::size_t start = linie.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    std::size_t end = linie.find_last_not_of(" \t\r\n");
    return linie.substr(start, end - start + 1);
}

std::vector<std::string> MT::split(const std::string& linie) const {
    std::vector<std::string> elemente;
    std::istringstream input(linie);
    std::string element;

    while (input >> element) {
        elemente.push_back(element);
    }

    return elemente;
}
