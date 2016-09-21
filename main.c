#include <stdio.h>

int main()
{while(0 == 0){
    printf("Zadaj pocet rovnic: ");
    int rovnic;
    scanf("%i", &rovnic);
    //printf("Zadaj pocet premennych: ");
    int premennych;
    //scanf("%i", &premennych);
    premennych = rovnic;

    float matica[rovnic][premennych + 1];
    printf("Zadaj maticu:\n");
    for (int r = 0; r < rovnic; ++r) {
        for (int p = 0; p < premennych + 1; ++p) {
            scanf("%f", &matica[r][p]);
        }
    }

    for (int r = 0; r < rovnic; ++r) { // na trojuholnik
        float delitel = matica[r][r];
        if (delitel != 1.0F && delitel != 0.0F) {
            for (int p = r; p < premennych + 1; ++p) { // ziskanie pivotnej jednotky
                matica[r][p] /= delitel;
            }
        }
        for (int R = r + 1; R < rovnic; ++R) { // vynulovanie stlpca
            float nasobok = matica[R][r];
            for (int P = r; P < premennych + 1; ++P) {
                matica[R][P] -= nasobok*matica[r][P];
            }
        }
    }

    for (int r = rovnic - 1; r >= 0; --r) { // nulovanie
        for (int R = r - 1; R >= 0; --R) {
            if (matica[r][r] != 0.0F) {
                float nasobok = matica[R][r];
                for (int P = r; P < premennych + 1; ++P) { // vynulovanie stlpca
                    matica[R][P] -= nasobok*matica[r][P];
                }
            }
        }
    }

    for (int r = 0; r < rovnic; ++r) {
        for (int p = 0; p < premennych + 1; ++p) {
            printf("%f ", matica[r][p]);
        }
        printf("\n");
    }
}
    return 0;
}
