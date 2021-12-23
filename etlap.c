#include "etlap.h"


void valaszokatmentetlap(void){
    econio_rawmode();
    int c = 11;
    while (c != KEY_ENTER){
        printf("Az etlapot mentettem! Nyomj Entert a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void nincsetlap(void){
    econio_rawmode();
    econio_clrscr();
    int c = 11;
    while (c != KEY_ESCAPE){
        printf("Jelenleg nem rendelkezel etlappal! Nyomj ESC-et a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void etlapmenukiir(int ptr) {
    char etlapmenu[][20] = {"Etlap megtekintese\n",
                            "Etel torlese\n",
                            "Etel hozzaadasa\n",
                            "Vissza\n"};

    econio_clrscr();
    for (int i = 0; i < 4; i++) {
        if (i == ptr) {
            econio_textcolor(COL_BLACK);
            econio_textbackground(COL_WHITE);
            printf("%s", etlapmenu[i]);
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        } else {
            econio_textcolor(COL_WHITE);
            printf("%s", etlapmenu[i]);
            econio_textcolor(COL_RESET);
        }
    }
}

void etlapmegtekint (Rendeles* eleje){
    econio_clrscr();
    printf("Nyomj ESC-et a visszalepeshez.\n");
    if(eleje == NULL){
        nincsetlap();
        return;
    }
    Rendeles* mozgo = eleje;
    while(mozgo != NULL)
    {
        printf("%d - %s - %dFt\n", mozgo->kod, mozgo->nev, mozgo->ar);
        mozgo = mozgo->kov;
    }
    econio_rawmode();
    int c = 11;
    while (c != KEY_ESCAPE){
        econio_gotoxy(0, 0);
        c = econio_getch();
    }
}

void etlapfajlba(Rendeles* eleje){
    FILE*fp;
    fp = fopen("etlap.txt", "w");
    Rendeles* mozgo = eleje;
    while(mozgo != NULL){
        fprintf(fp, "%d-%s-%d\n", mozgo->kod, mozgo->nev, mozgo->ar);
        mozgo = mozgo->kov;
    }
    fclose(fp);
}

Rendeles* etlapelemhozzaad (Rendeles*eleje){
    econio_clrscr();
    econio_normalmode();
    printf("Mit szeretnel hozzaadni az etlaphoz?  (Nev)\n");
    char szo[51];
    int ar;
    scanf("%s", szo);

    printf("\nAr?\n\n");
    scanf("%d", &ar);

    Rendeles* uj = (Rendeles*) malloc(sizeof(Rendeles));
    strcpy(uj->nev, szo);
    uj->ar = ar;
    uj->kov = NULL;

    if(eleje == NULL) {
        uj->kod = 1;
        eleje = uj;
    }
    else{
        Rendeles*mozgo = eleje;
        while(mozgo->kov != NULL)
            mozgo = mozgo->kov;
        uj->kod = mozgo->kod+1;
        mozgo->kov = uj;
    }

    etlapfajlba(eleje);
    valaszokatmentetlap();
    return eleje;
}

Rendeles* etlapelemtorles(Rendeles *eleje, int hanyast) {
    Rendeles *lemarado = NULL;
    Rendeles *mozgo = eleje;
    while (mozgo != NULL && mozgo->kod != hanyast) {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }
    if (mozgo == NULL) {}
    else if (lemarado == NULL) {
        Rendeles *ujeleje = mozgo->kov;
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
        mozgo->kod = i;
        i++;
        mozgo = mozgo->kov;
    }

    return eleje;
}

Rendeles* etlaptorleskivalaszt(Rendeles* eleje){
    econio_clrscr();
    econio_normalmode();

    printf("Hanyas tetelt szeretned torolni az etlapbol??\n\n");


    Rendeles*mozgo = eleje;
    while(mozgo != NULL){
        printf("%d - %s - %dFt\n", mozgo->kod, mozgo->nev, mozgo->ar);
        mozgo = mozgo->kov;
    }
    printf("\n");

    int hanyast;
    scanf("%d", &hanyast);
    eleje = etlapelemtorles(eleje, hanyast);
    etlapfajlba(eleje);
    valaszokatmentetlap();
    return eleje;
}

Rendeles* etlap(Rendeles *eleje) {
    int k = 11;
    int sorsz = 0;

    econio_clrscr();
    etlapmenukiir(sorsz);
    econio_rawmode();
    econio_gotoxy(0, 0);

    while (!(sorsz == 3 && k == KEY_ENTER)) {
        etlapmenukiir(sorsz);
        econio_rawmode();
        econio_gotoxy(0, sorsz);
        k = econio_getch();
        if (k == KEY_DOWN) {
            sorsz++;
            if (sorsz > 3)
                sorsz = 3;
            etlapmenukiir(sorsz);
            econio_gotoxy(0, sorsz);
        } else if (k == KEY_UP) {
            sorsz--;
            if (sorsz < 0)
                sorsz = 0;
            etlapmenukiir(sorsz);
            econio_gotoxy(0, sorsz);
        }

        switch(sorsz) {
            case 0:
                if (k == KEY_ENTER)
                   etlapmegtekint(eleje);
                break;
            case 1:
                if (k == KEY_ENTER)
                    eleje = etlaptorleskivalaszt(eleje);
                break;
            case 2:
                if (k == KEY_ENTER)
                    eleje = etlapelemhozzaad(eleje);
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
