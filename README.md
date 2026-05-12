# Masina Turing in C++

Proiect C++ rescris dupa cele doua variante Java:

- varianta simpla initiala: clasele `Tranzitie`, `ListaTranzitie`, `MT`, `Test`;
- varianta imbunatatita: banda simulata cu memorie nelimitata, afisare pasi, verificare determinism, input din linia de comanda.

## Compilare Linux / macOS / Git Bash

```bash
g++ -std=c++17 Test.cpp Tranzitie.cpp ListaTranzitie.cpp MT.cpp -o masina_turing
./masina_turing
./masina_turing aaabbb --pasi
./masina_turing aabb
./masina_turing epsilon
```

## Compilare Windows PowerShell

```powershell
g++ -std=c++17 Test.cpp Tranzitie.cpp ListaTranzitie.cpp MT.cpp -o masina_turing.exe
.\masina_turing.exe
.\masina_turing.exe aaabbb --pasi
.\masina_turing.exe aabb
.\masina_turing.exe epsilon
```

## Format fisier tranzitii

```txt
stare_initiala
stari_finale
stare_curenta simbol_citit simbol_scris directie stare_urmatoare
```

Directia poate fi:

- `L` = stanga
- `R` = dreapta
- `S` = sta pe loc

Exemplu:

```txt
q0 B B R q1
```

Inseamna: daca masina este in `q0` si citeste `B`, scrie `B`, muta capul la dreapta si trece in `q1`.
