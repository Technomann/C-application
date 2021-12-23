#include "fizetes.h"

void fizetvekiir(Rendeles*lista){
    int osszeg = 0;
    econio_clrscr();
    printf("*****************  SZAMLA  *****************\n");
    printf("Tetel:           Egysegar:\n");
    Rendeles*mozgo;
    for(mozgo = lista; mozgo != NULL; mozgo = mozgo->kov){
        printf("%s - %dFt\n", mozgo->nev, mozgo->ar);
        osszeg += mozgo->ar;
    }
    printf("\n\nTOTAL:      %dFt\n\n\n", osszeg);

    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nyomj Entert a befejezeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void listafelszabadit(Rendeles* lista){
    Rendeles*iter = lista;
    while(iter != NULL){
        Rendeles*kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

void nincsmegF(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nem nyitottal meg ki! Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsmegE(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nem vettel meg fel rendelest ehhez az asztalhoz! Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void fizettet (Asztal* eleje){
    if(eleje == NULL)
    {
        nincsmegF();
        return;
    }
    econio_clrscr();
    printf("Hanyas asztalt szeretned fizettetni?\n");
    econio_normalmode();
    int sorszam;
    scanf("%d", &sorszam);
    Asztal* mozgo = eleje;
    while(mozgo->sorszam != sorszam)
        mozgo = mozgo->kovet;
    if(mozgo->rendelesek == NULL)
    {
        nincsmegE();
        return;
    }
    fizetvekiir(mozgo->rendelesek);
    listafelszabadit(mozgo->rendelesek);
    mozgo->rendelesek =NULL;
    mozgo->nyitva = false;
}



