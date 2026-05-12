#include "MT.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

static std::string afiseazaCuvant(const std::string& cuvant) {
    if (cuvant.empty()) {
        return "#";
    }

    return cuvant;
}

static std::string lower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });

    return text;
}

int main(int argc, char* argv[]) {
    try {
        MT M("tranzitii.txt");

        std::string cuvant = "aaabbb";
        bool afiseazaPasi = false;

        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if (arg == "--pasi") {
                afiseazaPasi = true;
            } else {
                cuvant = arg;
            }
        }

        if (cuvant == "#" || lower(cuvant) == "epsilon") {
            cuvant = "";
        }

        bool acceptat = M.analizeazaCuvant(cuvant, afiseazaPasi);

        std::cout << "----------------" << std::endl;

        if (acceptat) {
            std::cout << "Cuvantul '" << afiseazaCuvant(cuvant) << "' este ACCEPTAT de MT." << std::endl;
        } else {
            std::cout << "Cuvantul '" << afiseazaCuvant(cuvant) << "' este RESPINS de MT." << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Eroare: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
