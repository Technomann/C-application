#include "ujasztal.h"




void megtortent(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Az uj asztal nyitasa megtortent. Nyomj entert a visszalépéshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincstobb(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nincs tobb szabad asztal! Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsmeg(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nem nyitottal meg ki! Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}



void asztalnyit(Asztal* eleje){
    if(eleje == NULL) {
        nincsmeg();
        return;
    }
    bool vanmeg = false;
    Asztal* mozgo = eleje;
    while(mozgo != NULL)
    {
        if(mozgo->nyitva == false){
            vanmeg = true;
            mozgo->nyitva = true;
            break;
        }
        mozgo = mozgo->kovet;
    }
    if(vanmeg == false)
    {
        nincstobb();
        return;
    }
    megtortent();
}
