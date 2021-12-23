#ifndef PROG1_NAGYHAZI_ETTEREM_STRUCTS_H
#define PROG1_NAGYHAZI_ETTEREM_STRUCTS_H

#include <stdbool.h>

typedef struct Rendeles{
    int kod;
    char nev[51];
    int ar;
    struct Rendeles*kov;
}Rendeles;

typedef struct Asztal{
    int sorszam;
    bool nyitva;
    Rendeles * rendelesek;
    struct Asztal* kovet;
}Asztal;

typedef struct Foglalas{
    int sorszam;
    char nev[51];
    int fo;
    char idopont[20];
    struct Foglalas*kov;
}Foglalas;

#endif //PROG1_NAGYHAZI_ETTEREM_STRUCTS_H
