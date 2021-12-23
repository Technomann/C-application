#include "menu.h"


void mentett(void) {
    econio_rawmode();
    econio_clrscr();
    int bill = 11;
    while (bill != KEY_ENTER) {
        printf("Az etlapot es a fogalalsokat mentettem! Nyomj entert a visszalepeshez!\n");
        econio_gotoxy(0, 0);
        bill = econio_getch();
    }
}

void foglalasmentes(Foglalas *eleje) {
    if (eleje == NULL)
        return;
    FILE *fp;
    fp = fopen("foglalasok.txt", "w");
    Foglalas *mozgo = eleje;
    while (mozgo->kov != NULL) {
        fprintf(fp, "%d-%s-%s-%d\n", mozgo->sorszam, mozgo->nev, mozgo->idopont, mozgo->fo);
        mozgo = mozgo->kov;
    }
    fclose(fp);
}

void etlapmentes(Rendeles *eleje) {
    if (eleje == NULL)
        return;

    FILE *fp;
    fp = fopen("etlap.txt", "w");
    Rendeles *mozgo = eleje;
    while (mozgo->kov != NULL) {
        fprintf(fp, "%d-%s-%d\n", mozgo->kod, mozgo->nev, mozgo->ar);
        mozgo = mozgo->kov;
    }
    fclose(fp);
}

void mentes(Foglalas *foglalaseleje, Rendeles *etlapeleje) {

    foglalasmentes(foglalaseleje);
    etlapmentes(etlapeleje);

    mentett();

}

void menukiir(int ptr) {
    char szoveg[][35] = {"Nyitas\n",
                         "Etlap\n",
                         "Uj asztal nyitasa\n",
                         "Rendeles felvetele\n",
                         "Asztal fizettetese\n",
                         "Asztalfoglalasok kezelese\n",
                         "Mentes\n",
                         "Kilepes\n"};

    econio_clrscr();
    for (int i = 0; i < 8; i++) {
        if (i == ptr) {
            econio_textcolor(COL_BLACK);
            econio_textbackground(COL_WHITE);
            printf("%s", szoveg[i]);
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        } else {
            econio_textcolor(COL_WHITE);
            printf("%s", szoveg[i]);
            econio_textcolor(COL_RESET);
        }
    }
}

Rendeles *etlapletrehoz(void) {
    Rendeles *lis = NULL;

    char defetlapnev[5][20] = {"elso etel", "masodik etel", "harmadik etel", "negyedik etel", "otodik etel"};
    int defetlapar[5] = {1400, 1900, 2300, 4000, 950};


    FILE *fp;
    fp = fopen("etlap.txt", "w");
    for (int i = 0; i < 5; i++) {
        Rendeles *uj = (Rendeles *) malloc(sizeof(Rendeles));
        uj->kod = i + 1;
        uj->ar = defetlapar[i];
        uj->kov = NULL;
        strcpy(uj->nev, defetlapnev[i]);
        if (lis == NULL) {
            lis = uj;
        } else {
            Rendeles *mozgo = lis;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
        }
        fprintf(fp, "%d-%s-%d\n", i + 1, defetlapnev[i], defetlapar[i]);
    }
    fclose(fp);
    return lis;
}

Rendeles *etlaplistaba(void) {
    Rendeles *lis = NULL;
    int kod, ar;
    char nev[51];
    FILE *fp;
    fp = fopen("etlap.txt", "r");
    while (fscanf(fp, "%d-%[^-]-%d", &kod, nev, &ar) != EOF) {
        Rendeles *uj = (Rendeles *) malloc(sizeof(Rendeles));
        uj->ar = ar;
        uj->kod = kod;
        uj->kov = NULL;
        strcpy(uj->nev, nev);
        if (lis == NULL) {
            lis = uj;
        } else {
            Rendeles *mozgo = lis;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
        }
    }
    return lis;
}

Rendeles *defetlap(void) {
    Rendeles *uj;
    if (access("etlap.txt", F_OK) != -1) {
        uj = etlaplistaba();
    } else {
        uj = etlapletrehoz();
    }
    return uj;
}

Foglalas *foglalasletrehoz(void) {
    Foglalas *uj = (Foglalas *) malloc(sizeof(Foglalas));
    uj->sorszam = 0;
    uj->kov = NULL;
    strcpy(uj->idopont, "2019.12.01. 0:00");
    strcpy(uj->nev, "MINTA");
    uj->fo = 4;
    FILE *fp;
    fp = fopen("foglalasok.txt", "w");
    fprintf(fp, "%d-%s-%s-%d\n", uj->sorszam, uj->nev, uj->idopont, uj->fo);
    fclose(fp);
    return uj;
}

Foglalas *foglalaslistaba(void) {
    Foglalas *lis = NULL;
    int sorszam, fo;
    char nev[51];
    char idopont[20];
    FILE *fp;
    fp = fopen("foglalasok.txt", "r");
    while (fscanf(fp, "%d-%[^-]-%[^-]-%d", &sorszam, nev, idopont, &fo) != EOF) {
        Foglalas *uj = (Foglalas *) malloc(sizeof(Foglalas));
        uj->sorszam = sorszam;
        uj->fo = fo;
        strcpy(uj->nev, nev);
        strcpy(uj->idopont, idopont);
        uj->kov = NULL;
        if (lis == NULL)
            lis = uj;
        else {
            Foglalas *mozgo = lis;
            while (mozgo->kov != NULL)
                mozgo = mozgo->kov;
            mozgo->kov = uj;
        }
    }
    return lis;
}

Foglalas *deffoglalas(void) {
    Foglalas *uj;
    if (access("foglalasok.txt", F_OK) != -1) {
        uj = foglalaslistaba();
    } else {
        uj = foglalasletrehoz();
    }
    return uj;
}


void menu(void) {
    Asztal *asztaleleje = NULL;
    Rendeles *etlapeleje = defetlap();
    Foglalas *foglalaseleje = deffoglalas();
    int c;
    int sorsz = 0;
    bool kilep = false;
    econio_clrscr();
    menukiir(sorsz);
    econio_rawmode();
    econio_gotoxy(0, 0);
    while (!kilep) {
        menukiir(sorsz);
        econio_rawmode();
        econio_gotoxy(0, sorsz);
        c = econio_getch();
        if (c == KEY_DOWN) {
            sorsz++;
            if (sorsz > 7)
                sorsz = 7;
            menukiir(sorsz);
            econio_gotoxy(0, sorsz);
        } else if (c == KEY_UP) {
            sorsz--;
            if (sorsz < 0)
                sorsz = 0;
            menukiir(sorsz);
            econio_gotoxy(0, sorsz);
        }
        switch (sorsz) {
            case 0:
                if (c == KEY_ENTER)
                    asztaleleje = nyitas();
                break;
            case 1:
                if (c == KEY_ENTER)
                    etlapeleje = etlap(etlapeleje);
                break;
            case 2:
                if (c == KEY_ENTER)
                    asztalnyit(asztaleleje);
                break;
            case 3:
                if (c == KEY_ENTER)
                    rendelesfelvetel(asztaleleje, etlapeleje);
                break;
            case 4:
                if (c == KEY_ENTER)
                    fizettet(asztaleleje);
                break;
            case 5:
                if (c == KEY_ENTER)
                    foglalaseleje = foglalasok(foglalaseleje);
                break;
            case 6:
                if (c == KEY_ENTER)
                    mentes(foglalaseleje, etlapeleje);
                break;
            case 7:
                if (c == KEY_ENTER) {
                    kilep = biztoskilep(etlapeleje, asztaleleje, foglalaseleje);
                }
                break;
            default:
                return;
        }
    }

}
