#include <stdio.h>

int main()
{//while(0 == 0){
    //FILE *f = fopen("C:/Programovanie/build-gausova-eliminacna-metoda-Desktop_Qt_5_7_0_MinGW_32bit-Debug/vstup.txt", "r");
    printf("Zadaj pocet rovnic: ");
    int rovnic;
    scanf("%i", &rovnic);
    //fscanf(f, "%i", &rovnic);
    printf("Zadaj pocet premennych: ");
    int premennych;
    scanf("%i", &premennych);
    //fscanf(f, "%i", &premennych);

    float matica[rovnic][premennych + 1];
    printf("Zadaj maticu:\n");
    for (int r = 0; r < rovnic; ++r) {
        for (int p = 0; p < premennych + 1; ++p) {
            scanf("%f", &matica[r][p]);
            //fscanf(f, "%f", &matica[r][p]);
        }
    }


    int stlpec = 0;
    for (int r = 0; r < rovnic; ++r) { // na trojuholnik
        float delitel = matica[r][stlpec]; // prvok na diagonale
        if (delitel != 1.0F && delitel != 0.0F) { // ak je rovny jednej alebo nulovy nema zmysel delit
            for (int p = stlpec; p < premennych + 1; ++p) { // ziskanie pivotnej jednotky a vydelenie ostatnych prvkov
                matica[r][p] /= delitel;
            }
        } else if (delitel == 0.0F) { //ak je nulovy prvok na diagonale tak vymen riadky aby bol nenulovy
            for (int R = r + 1; R < rovnic; ++R) {
                if (matica[R][stlpec] != 0.0F) { // ak som na nenulovom prvku tak vymenim riadky
                    for (int P = stlpec; P < premennych + 1; ++P) {
                        float m = matica[r][P];
                        matica[r][P] = matica[R][P];
                        matica[R][P] = m;
                    }
                    R = rovnic; // ukoncenie hladania po vymene
                }
            }
        }
        if (matica[r][stlpec] == 1.0F) { // nulujem len ak mam pivotnu jednotku
            for (int R = r + 1; R < rovnic; ++R) { // vynulovanie stlpca
                float nasobok = matica[R][stlpec]; // vzdy o riadok nizsie rovnaka premenna
                if (nasobok != 0.0F) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = stlpec; P < premennych + 1; ++P) {
                        matica[R][P] -= nasobok*matica[r][P];
                    }
                }
            }
        }
        if (matica[r][stlpec] == 1.0F && stlpec + 1 < premennych) { // presun na dalsi stlpec len ak som dostal pivotnu jednotk
            stlpec++;
        } else if (matica[r][stlpec] != 0.0F && matica[r][stlpec] != 1.0F) { // ak nemam pivotnu jednotku tak ju ziskaj
            r--;
        } else if (matica[r][stlpec] == 0.0F) {
            stlpec++;
            r--;
        }
    }

    stlpec = 0;
    for (int r = 0; r < rovnic; ++r) {
        for (int R = r - 1; R >= 0; --R) {
            if (matica[r][stlpec] != 0.0F) { // ak je pivotny prvok nulovy, vynecham ho
                float nasobok = matica[R][stlpec]; // o riadok vyssie rovnaka premenna
                if (nasobok != 0.0F) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = stlpec; P < premennych + 1; ++P) { // vynulovanie stlpca
                        matica[R][P] -= nasobok*matica[r][P];
                    }
                }
            }
        }
        if (matica[r][stlpec] == 0) { // ak som nemal pivotnu jednotku kontrolujem dalsiu neznamu
            r--;
        }
        stlpec++;
    }

    for (int r = 0; r < rovnic; ++r) { // vypis vyslednej matice
        for (int p = 0; p < premennych + 1; ++p) {
            printf("%f ", matica[r][p]);
        }
        printf("\n");
    }

    for (int r = 0; r < rovnic; ++r) { // vypis vyslednych rovnic
        for (int p = 0; p < premennych + 1; ++p) {
            if (p < premennych) {
                if (matica[r][p] != 0.0F)
                    printf("%c %.2fx%d ",matica[r][p] < 0 ? ' ' : '+' , matica[r][p], p + 1);
            } else {
                printf("= %.2f\n", matica[r][p]);
            }

        }
    }
//}
    return 0;
}
