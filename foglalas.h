#ifndef PROG1_NAGYHAZI_ETTEREM_FOGLALAS_H
#define PROG1_NAGYHAZI_ETTEREM_FOGLALAS_H

#include <stdio.h>
#include "econio.h"
#include "structs.h"
#include <string.h>
#include "debugmalloc.h"
#include "debugmalloc-impl.h"

void foglalaskiir(int ptr);

Foglalas* foglalasok(Foglalas*eleje);

void valaszokatmentfoglalas(void);

void nincsmegfog(void);

void foglalasmegtekint (Foglalas* eleje);

void foglalasfajlba(Foglalas* eleje);

Foglalas* ujfoglalashozzaad (Foglalas*eleje);

Foglalas* foglalastorles(Foglalas *eleje, int hanyast);

Foglalas* foglalastorleskivalaszt(Foglalas* eleje);

#endif //PROG1_NAGYHAZI_ETTEREM_FOGLALAS_H
