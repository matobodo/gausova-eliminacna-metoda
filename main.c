#include <stdio.h>

int main()
{while(0 == 0){
    printf("Zadaj pocet rovnic: ");
    int rovnic;
    scanf("%i", &rovnic);
    printf("Zadaj pocet premennych: ");
    int premennych;
    scanf("%i", &premennych);

    float matica[rovnic][premennych + 1];
    printf("Zadaj maticu:\n");
    for (int r = 0; r < rovnic; ++r) {
        for (int p = 0; p < premennych + 1; ++p) {
            scanf("%f", &matica[r][p]);
        }
    }


    int stlpec = 0;
    for (int r = 0; r < rovnic; ++r) { // na trojuholnik
        bool dalsiStlpec = false;
        float delitel = matica[r][stlpec]; // prvok na diagonale
        if (delitel != 1.0F && delitel != 0.0F) { // ak je rovny jednej alebo nulovy nema zmysel delit
            for (int p = stlpec; p < premennych + 1; ++p) { // ziskanie pivotnej jednotky a vydelenie ostatnych prvkov
                matica[r][p] /= delitel;
            }
        }
        for (int R = r + 1; R < rovnic; ++R) { // vynulovanie stlpca
            float nasobok = matica[R][stlpec]; // vzdy o riadok nizsie rovnaka premenna
            if (nasobok != 0.0F) { // ak je nulovy nema zmysel odpocitavat
                for (int P = stlpec; P < premennych + 1; ++P) {
                    matica[R][P] -= nasobok*matica[r][P];
                }
                dalsiStlpec = true;
            }
        }
        if (dalsiStlpec && stlpec + 1 < premennych) { // presun na dalsi stlpec len ak som dostal pivotnu jednotku
            stlpec++;
        }
    }

    stlpec = premennych - 1;
    for (int r = rovnic - 1; r >= 0; --r) { // nulovanie
        bool dalsiStlpec = false;
        for (int R = r - 1; R >= 0; --R) {
            if (matica[r][stlpec] != 0.0F) { // ak je pivotny prvok nulovy, vynecham ho
                float nasobok = matica[R][stlpec]; // o riadok vyssie rovnaka premenna
                if (nasobok != 0.0F) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = stlpec; P < premennych + 1; ++P) { // vynulovanie stlpca
                        matica[R][P] -= nasobok*matica[r][P];
                    }
                    dalsiStlpec = true;
                }
            }
        }
        if (dalsiStlpec && stlpec - 1 >= 0) { // presun na dalsi stlpec len ak je pivotny prvok nenulovy
            stlpec--;
        }
    }

    for (int r = 0; r < rovnic; ++r) { // vypis vyslednej matice
        for (int p = 0; p < premennych + 1; ++p) {
            printf("%f ", matica[r][p]);
        }
        printf("\n");
    }
}
    return 0;
}
