#ifndef PROG1_NAGYHAZI_ETTEREM_KILEPES_H
#define PROG1_NAGYHAZI_ETTEREM_KILEPES_H

#include <stdio.h>
#include "econio.h"
#include "structs.h"
#include "debugmalloc.h"
#include "debugmalloc-impl.h"

void kilepes(Rendeles*, Asztal*, Foglalas*);

bool biztoskilep(Rendeles*etlapeleje, Asztal*asztaleleje, Foglalas*foglalaseleje);

void felszabaditF(Foglalas*eleje);

void felszabaditA(Asztal*eleje);

void felszabaditR(Rendeles*eleje);

void kilepmenukiir(int ptr);

#endif //PROG1_NAGYHAZI_ETTEREM_KILEPES_H
