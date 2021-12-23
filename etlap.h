#ifndef PROG1_NAGYHAZI_ETTEREM_ETLAP_H
#define PROG1_NAGYHAZI_ETTEREM_ETLAP_H

#include <stdio.h>
#include "econio.h"
#include <string.h>
#include "structs.h"
#include "debugmalloc.h"
#include "debugmalloc-impl.h"

void valaszokatmentetlap (void);

void nincsetlap(void);

void etlapmenukiir (int ptr);

Rendeles* etlap (Rendeles*);

void etlapmegtekint(Rendeles*);

Rendeles* etlapelemhozzaad(Rendeles*);

void etlapfajlba(Rendeles*);

Rendeles* etlaptorleskivalaszt(Rendeles* eleje);

Rendeles* etlapelemtorles(Rendeles* eleje, int hanyast);

#endif //PROG1_NAGYHAZI_ETTEREM_ETLAP_H
