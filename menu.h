#ifndef PROG1_NAGYHAZI_ETTEREM_MENU_H
#define PROG1_NAGYHAZI_ETTEREM_MENU_H

#include <stdio.h>
#include "econio.h"
#include "debugmalloc.h"
#include "debugmalloc-impl.h"
#include "etlap.h"
#include "nyitas.h"
#include "ujasztal.h"
#include "rendeles.h"
#include "structs.h"
#include <string.h>
#include <unistd.h>
#include "fizetes.h"
#include "foglalas.h"
#include "kilepes.h"

void menukiir(int ptr);

void menu(void);

void mentett(void);

void mentes(Foglalas*, Rendeles*);

Rendeles* etlapletrehoz(void);

Rendeles* defetlap(void);

Rendeles *etlaplistaba(void);

Foglalas* foglalasletrehoz(void);

Foglalas* foglalaslistaba(void);

Foglalas* deffoglalas(void);

#endif //PROG1_NAGYHAZI_ETTEREM_MENU_H
