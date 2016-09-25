#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int gcd(int _a, int _b)
{
    _a < 0 ? _a = -_a :0;
    _b < 0 ? _b = -_b :0;
    int a = max(_a, _b);
    int b = min(_a, _b);
    int x;
    x = b != 0 ? a - (a / b) * b :  a != 0 ? -2 : -1;
    switch (x) {
    case -2:
        return a;
        break;
    case -1:
        return 1;
        break;
    case 0:
        return b;
        break;
    default:
        return gcd(b, x);
        break;
    }
}

int main()
{//while(0 == 0){
    FILE *f = fopen("C:/Programovanie/build-gausova-eliminacna-metoda-Desktop_Qt_5_7_0_MinGW_32bit-Debug/vstup.txt", "r");
    //printf("Zadaj pocet rovnic: ");
    int rovnic;
    //scanf("%d", &rovnic);
    fscanf(f, "%d", &rovnic);
    //printf("Zadaj pocet premennych: ");
    int premennych;
    //scanf("%d", &premennych);
    fscanf(f, "%d", &premennych);

    int citatel[rovnic][premennych + 1];
    int menovatel[rovnic][premennych + 1];
    //printf("Zadaj maticu:\n");
    for (int r = 0; r < rovnic; ++r) {
        for (int p = 0; p < premennych + 1; ++p) {
            //scanf("%d", &citatel[r][p]);
            fscanf(f, "%d", &citatel[r][p]);
            menovatel[r][p] = 1;
        }
    }


    int stlpec = 0;
    for (int r = 0; r < rovnic; ++r) { // na trojuholnik
        int nasobokC = citatel[r][stlpec]; // prvok na diagonale
        int nasobokM = menovatel[r][stlpec]; // prvok na diagonale
        if (nasobokC != nasobokM && nasobokC != 0) { // ak je rovny jednej alebo nulovy nema zmysel delit
            for (int p = stlpec; p < premennych + 1; ++p) { // ziskanie pivotnej jednotky a vydelenie ostatnych prvkov
                citatel[r][p] *= nasobokM;
                menovatel[r][p] *= nasobokC;
                int g = gcd(citatel[r][p], menovatel[r][p]); // vykratenie zlomku
                if (g > 1) {
                    citatel[r][p] /= g;
                    menovatel[r][p] /= g;
                }
            }
        } else if (nasobokC == 0) { //ak je nulovy prvok na diagonale tak vymen riadky aby bol nenulovy
            for (int R = r + 1; R < rovnic; ++R) {
                if (citatel[R][stlpec] != 0) { // ak som na nenulovom prvku tak vymenim riadky
                    for (int P = stlpec; P < premennych + 1; ++P) {
                        int c = citatel[r][P];
                        int m = menovatel[r][P];
                        citatel[r][P] = citatel[R][P];
                        menovatel[r][P] = menovatel[R][P];
                        citatel[R][P] = c;
                        menovatel[R][P] = m;
                    }
                    R = rovnic; // ukoncenie hladania po vymene
                }
            }
        }
        if (citatel[r][stlpec] == menovatel[r][stlpec]) { // nulujem len ak mam pivotnu jednotku
            for (int R = r + 1; R < rovnic; ++R) { // vynulovanie stlpca
                int c = citatel[R][stlpec]; // vzdy o riadok nizsie rovnaka premenna
                int m = menovatel[R][stlpec]; // vzdy o riadok nizsie rovnaka premenna
                if (nasobokC != 0) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = stlpec; P < premennych + 1; ++P) {
                        int citatelR = c * citatel[r][P];
                        int menovatelR = m * menovatel[r][P];
                        int g = gcd(citatelR, menovatelR); // vykratenie zlomku
                        if (g > 1) {
                            citatelR /= g;
                            menovatelR /= g;
                        }
                        citatel[R][P] = citatel[R][P]*menovatelR - citatelR*menovatel[R][P];
                        menovatel[R][P] *= menovatelR;
                        g = gcd(citatel[R][P], menovatel[R][P]); // vykratenie zlomku
                        if (g > 1) {
                            citatel[R][P] /= g;
                            menovatel[R][P] /= g;
                        }
                    }
                }
            }
        }
        if (citatel[r][stlpec] == menovatel[r][stlpec] && stlpec + 1 < premennych) { // presun na dalsi stlpec len ak som dostal pivotnu jednotk
            stlpec++;
        } else if (citatel[r][stlpec] != 0 && citatel[r][stlpec] != menovatel[r][stlpec]) { // ak nemam pivotnu jednotku tak ju ziskaj
            r--;
        } else if (citatel[r][stlpec] == 0) { // upravit!! pri viacriadkovych rovniciach sa nemusel dostat nulovy riadok uplne dolu a moze sa hladat na zlom stlpci lebo na nulovom riadku sa dostane na posledny stlpec aj ked su pod nim dalsie riadky ktore mozno vyhovuju
            stlpec++;
            r--;
        }
    }

    stlpec = 0;
    for (int r = 0; r < rovnic; ++r) {
        for (int R = r - 1; R >= 0; --R) {
            if (citatel[r][stlpec] != 0) { // ak je pivotny prvok nulovy, vynecham ho
                int c = citatel[R][stlpec]; // o riadok vyssie rovnaka premenna
                int m = menovatel[R][stlpec]; // o riadok vyssie rovnaka premenna
                if (c != 0) { // ak je nulovy nema zmysel odpocitavat
                    for (int P = stlpec; P < premennych + 1; ++P) { // vynulovanie stlpca
                        int citatelR = c * citatel[r][P];
                        int menovatelR = m * menovatel[r][P];
                        int g = gcd(citatelR, menovatelR); // vykratenie zlomku
                        if (g > 1) {
                            citatelR /= g;
                            menovatelR /= g;
                        }
                        citatel[R][P] = citatel[R][P]*menovatelR - citatelR*menovatel[R][P];
                        menovatel[R][P] *= menovatelR;
                    }
                }
            }
        }
        if (citatel[r][stlpec] == 0) { // ak som nemal pivotnu jednotku kontrolujem dalsiu neznamu
            r--;
        }
        stlpec++;
    }

    for (int r = 0; r < rovnic; ++r) { // vypis vyslednej matice
        for (int p = 0; p < premennych + 1; ++p) {
            if (p < premennych) {
                printf("%.4f ", (float)citatel[r][p]/menovatel[r][p]);
            } else {
                printf("%.4f = %d / %d\n", (float)citatel[r][p]/menovatel[r][p], citatel[r][p], menovatel[r][p]);
            }
        }
    }

    for (int r = 0; r < rovnic; ++r) { // vypis vyslednych rovnic
        for (int p = 0; p < premennych + 1; ++p) {
            if (p < premennych) {
                if (citatel[r][p] != 0)
                    printf("%c %.4fx%d ",(float)citatel[r][p]/menovatel[r][p] < 0 ? ' ' : '+' , (float)citatel[r][p]/menovatel[r][p], p + 1);
            } else {
                printf("= %.4f = %d / %d\n", (float)citatel[r][p]/menovatel[r][p], citatel[r][p], menovatel[r][p]);
            }
        }
    }
//}
    return 0;
}
