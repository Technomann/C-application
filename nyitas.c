#include "nyitas.h"

void valaszokatment(void){
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("A valaszokat mentettem! Nyomj Entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 2);
        c = econio_getch();
    }
}

Asztal *asztaltnyit(int mennyit) {
    Asztal *lis = NULL;
    for(int i = 0; i<mennyit; i++)
    {
        Asztal *uj = (Asztal *) malloc(sizeof(Asztal));
        uj->sorszam = i + 1;
        uj->kovet = NULL;
        uj->nyitva = false;
        uj->rendelesek = NULL;
        if (lis == NULL) {
            lis = uj;
        } else {
            Asztal *mozgo = lis;
            while (mozgo->kovet != NULL)
                mozgo = mozgo->kovet;
            mozgo->kovet = uj;
        }
    }
        return lis;
}

Asztal* nyitas(void){
    econio_clrscr();
    econio_normalmode();
    int asztalokszama;
    econio_textcolor(COL_WHITE);
    printf("Hany asztallal szeretnel kinyitni?\n");
    scanf("%d", &asztalokszama);
    Asztal* eleje = asztaltnyit(asztalokszama);
    valaszokatment();
    return eleje;
}
