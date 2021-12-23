#include "kilepes.h"



void kilepmenukiir(int ptr) {
    char kilep[][8] = {"IGEN\n", "NEM\n"};

    econio_clrscr();
    for (int i = 0; i < 2; i++) {
        if (i == ptr) {
            econio_textcolor(COL_BLACK);
            econio_textbackground(COL_WHITE);
            printf("%s", kilep[i]);
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        } else {
            econio_textcolor(COL_WHITE);
            printf("%s", kilep[i]);
            econio_textcolor(COL_RESET);
        }
    }
}

void felszabaditR(Rendeles*eleje){
    if(eleje == NULL)
        return;
    Rendeles*iter = eleje;
    while(iter != NULL){
        Rendeles*kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

void felszabaditA(Asztal*eleje){
    if(eleje == NULL)
        return;
    Asztal*iter = eleje;
    while(iter != NULL){
        Asztal*kov = iter->kovet;
        free(iter);
        iter = kov;
    }
}

void felszabaditF(Foglalas*eleje){
    if(eleje == NULL)
        return;
    Foglalas*iter = eleje;
    while(iter != NULL){
        Foglalas*kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

void kilepes(Rendeles*etlap, Asztal* asztal, Foglalas*foglalas){
    felszabaditF(foglalas);
    felszabaditR(etlap);
    if(asztal == NULL)
        return;
    Asztal* mozgo = asztal;
    while(mozgo != NULL ){
        if(mozgo->rendelesek == NULL){}
        else {
            felszabaditR(mozgo->rendelesek);
        }
        mozgo = mozgo->kovet;
    }
    felszabaditA(asztal);
}

bool biztoskilep(Rendeles*etlapeleje, Asztal*asztaleleje, Foglalas*foglalaseleje){
    int sorsz = 0;
    int k = 0;

    while (!(sorsz == 1 && k == KEY_ENTER) ) {
        kilepmenukiir(sorsz);
        econio_rawmode();
        econio_gotoxy(0, sorsz);
        k = econio_getch();
        if (k == KEY_DOWN) {
            sorsz++;
            if (sorsz > 1)
                sorsz = 1;
            kilepmenukiir(sorsz);
            econio_gotoxy(0, sorsz);
        } else if (k == KEY_UP) {
            sorsz--;
            if (sorsz < 0)
                sorsz = 0;
            kilepmenukiir(sorsz);
            econio_gotoxy(0, sorsz);
        }

        switch(sorsz) {
            case 0:
                if (k == KEY_ENTER) {
                    kilepes(etlapeleje, asztaleleje, foglalaseleje);
                    econio_clrscr();
                    return true;
                }
                break;
            case 1:
                if (k == KEY_ENTER)
                    return false;
                break;
            default:
                ;
        }
    }
}

