#include "rendeles.h"

void rendelesment(void){
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("A rendelést mentettem! Nyomj Entert a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsmegR(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nem nyitottal meg ki! Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsmegetlap(void){
    econio_clrscr();
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Jelenleg nem rendelkezel meg etlappal. Hozz letre elobb egyet!  Nyomj entert a fomenube lepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}


void rendelesfelvetel(Asztal*asztaleleje, Rendeles*etlapeleje){
    if(etlapeleje == NULL){
        nincsmegetlap();
        return;
    }

    if(asztaleleje == NULL)
    {
        nincsmegR();
        return;
    }

    int asztalsorsz;
    int etelsorsz;
    


    econio_clrscr();
    econio_normalmode();
    econio_textcolor(COL_WHITE);
    printf("Hanyas asztalhoz szeretnel rendelest felvenni?\n");
    scanf("%d", &asztalsorsz);

    printf("Rendben!\n\nHanyas etelt szeretned felvenni?\n");
    Rendeles* mozgo = etlapeleje;
    while(mozgo != NULL){
        printf("%d - %s - %d\n", mozgo->kod, mozgo->nev, mozgo->ar);
        mozgo = mozgo->kov;
    }
    printf("\n");
    scanf("%d", &etelsorsz);


    mozgo = etlapeleje;
    while(mozgo->kod != etelsorsz){
        mozgo = mozgo->kov;
    }


    Rendeles* ujrend = (Rendeles*) malloc(sizeof(Rendeles));
    ujrend->ar = mozgo->ar;
    ujrend->kod = mozgo->kod;
    strcpy(ujrend->nev, mozgo->nev);
    ujrend->kov = NULL;

    Asztal* mozgoa = asztaleleje;
    while(mozgoa->sorszam != asztalsorsz)
        mozgoa = mozgoa->kovet;


    if(mozgoa->rendelesek == NULL) {
        mozgoa->rendelesek = ujrend;
    }
    else{
        Rendeles* mozgobelso = mozgoa->rendelesek;
            while (mozgobelso->kov != NULL) {
                mozgobelso = mozgobelso->kov;

            }
            mozgobelso->kov = ujrend;
    }
    rendelesment();
}
