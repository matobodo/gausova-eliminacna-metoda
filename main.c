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

    for (int r = 0; r < rovnic; ++r) { // na trojuholnik
        float delitel = matica[r][r]; // prvok na diagonale
        if (delitel != 1.0F && delitel != 0.0F) { // ak je rovny jednej alebo nulovy nema zmysel delit
            for (int p = r; p < premennych + 1; ++p) { // ziskanie pivotnej jednotky a vydelenie ostatnych prvkov
                matica[r][p] /= delitel;
            }
        }
        for (int R = r + 1; R < rovnic; ++R) { // vynulovanie stlpca
            float nasobok = matica[R][r]; // vzdy o riadok nizsie rovnaka premenna
            if (nasobok == 0.0F) { // ak je nulovy nema zmysel odpocitavat
                for (int P = r; P < premennych + 1; ++P) {
                    matica[R][P] -= nasobok*matica[r][P];
                }
            }
        }
    }

    for (int r = rovnic - 1; r >= 0; --r) { // nulovanie
        for (int R = r - 1; R >= 0; --R) {
            if (matica[r][r] != 0.0F) { // ak je pivotny prvok nulovy, vynecham ho
                float nasobok = matica[R][r];
                if (nasobok == 0.0F) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = r; P < premennych + 1; ++P) { // vynulovanie stlpca
                        matica[R][P] -= nasobok*matica[r][P];
                    }
                }
            }
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
