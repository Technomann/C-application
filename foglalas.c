#include "foglalas.h"


void foglalaskiir(int ptr) {
    char foglalasmenu[][30] = {"Foglalasok megtekintese\n",
                               "Foglalas torlese\n",
                               "Uj foglalas hozzaadasa\n",
                               "Vissza\n"};


    econio_clrscr();
    for (int i = 0; i < 4; i++) {
        if (i == ptr) {
            econio_textcolor(COL_BLACK);
            econio_textbackground(COL_WHITE);
            printf("%s", foglalasmenu[i]);
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        } else {
            econio_textcolor(COL_WHITE);
            printf("%s", foglalasmenu[i]);
            econio_textcolor(COL_RESET);
        }
    }
}

void valaszokatmentfoglalas(void){
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("A foglalast mentettem! Nyomj Entert a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsmegfog(void){
    econio_rawmode();
    econio_clrscr();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Nincs meg foglalas rogzitve! Nyomj Entert a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void foglalasmegtekint (Foglalas* eleje){
    if(eleje == NULL)
    {
        nincsmegfog();
        return;
    }

    econio_clrscr();
    printf("Nyomj ESC-et a visszalepeshez.\n");
    Foglalas* mozgo = eleje;
    while(mozgo != NULL)
    {
        printf("%d - %s - %s - %d fo\n", mozgo->sorszam, mozgo->nev, mozgo->idopont, mozgo->fo);
        mozgo = mozgo->kov;
    }
    econio_rawmode();
    int c = 11;
    while (c != KEY_ESCAPE){
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void foglalasfajlba(Foglalas* eleje){
    FILE*fp;
    fp = fopen("foglalasok.txt", "w");
    Foglalas* mozgo = eleje;
    while(mozgo != NULL){
        fprintf(fp, "%d-%s-%s-%d\n", mozgo->sorszam, mozgo->nev, mozgo->idopont, mozgo->fo);
        mozgo = mozgo->kov;
    }
    fclose(fp);
}

Foglalas* ujfoglalashozzaad (Foglalas*eleje){
    econio_clrscr();
    econio_normalmode();
    printf("Foglalo neve?\n");
    char nev[51];
    char idopont[20];
    int fo = 0;
    char
    scanf("%s", nev);

    printf("\nMilyen idopontra?\n\n");

    scanf("%s", idopont);

    printf("\nHany fore?\n\n");

    scanf("%d", &fo);

    Foglalas* uj = (Foglalas*) malloc(sizeof(Foglalas));
    strcpy(uj->nev, nev);
    strcpy(uj->idopont, idopont);
    uj->fo = fo;
    uj->kov = NULL;

    if(eleje == NULL) {
        uj->sorszam = 1;
        eleje = uj;
    }
    else{
        Foglalas*mozgo = eleje;
        while(mozgo->kov != NULL)
            mozgo = mozgo->kov;
        uj->sorszam = mozgo->sorszam+1;
        mozgo->kov = uj;
    }

    foglalasfajlba(eleje);
    valaszokatmentfoglalas();
    return eleje;
}

Foglalas* foglalastorles(Foglalas *eleje, int hanyast) {
    Foglalas *lemarado = NULL;
    Foglalas *mozgo = eleje;
    while (mozgo != NULL && mozgo->sorszam != hanyast) {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }
    if (mozgo == NULL) {}
    else if (lemarado == NULL) {
        Foglalas *ujeleje = mozgo->kov;
        free(mozgo);
        eleje = ujeleje;
    } else {
        lemarado->kov = mozgo->kov;
        free(mozgo);
    }
    int i = 1;
    mozgo = eleje;
    while(mozgo != NULL)
    {
        mozgo->sorszam = i;
        i++;
        mozgo = mozgo->kov;
    }

    return eleje;
}

Foglalas* foglalastorleskivalaszt(Foglalas* eleje){
    econio_clrscr();
    econio_normalmode();

    printf("Hanyas foglalast szeretned torolni?\n\n");


    Foglalas*mozgo = eleje;
    while(mozgo != NULL){
        printf("%d - %s - %s - %d fo\n", mozgo->sorszam, mozgo->nev, mozgo->idopont, mozgo->fo);
        mozgo = mozgo->kov;
    }
    printf("\n");

    int hanyast;
    scanf("%d", &hanyast);
    eleje = foglalastorles(eleje, hanyast);
    foglalasfajlba(eleje);
    valaszokatmentfoglalas();
    return eleje;
}

Foglalas* foglalasok(Foglalas *eleje) {
    int k = 11;
    int sorsz = 0;

    econio_clrscr();
    foglalaskiir(sorsz);
    econio_rawmode();
    econio_gotoxy(0, 0);

    while (!(sorsz == 3 && k == KEY_ENTER)) {
        foglalaskiir(sorsz);
        econio_rawmode();
        econio_gotoxy(0, sorsz);
        k = econio_getch();
        if (k == KEY_DOWN) {
            sorsz++;
            if (sorsz > 3)
                sorsz = 3;
            foglalaskiir(sorsz);
            econio_gotoxy(0, sorsz);
        } else if (k == KEY_UP) {
            sorsz--;
            if (sorsz < 0)
                sorsz = 0;
            foglalaskiir(sorsz);
            econio_gotoxy(0, sorsz);
        }

        switch(sorsz) {
            case 0:
                if (k == KEY_ENTER)
                    foglalasmegtekint(eleje);
                break;
            case 1:
                if (k == KEY_ENTER)
                    eleje = foglalastorleskivalaszt(eleje);
                break;
            case 2:
                if (k == KEY_ENTER)
                    eleje = ujfoglalashozzaad(eleje);
                break;
            case 3:
                if(k == KEY_ENTER)
                    return eleje;
                break;
            default:
                return eleje;
        }
    }
}
