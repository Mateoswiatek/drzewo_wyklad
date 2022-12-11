#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define EXIT 6



/*
 *              wstaw do drzewa  // pierwsze nie moze byc 0;
 *              wyswietl
 *              znajdz
 *  usun   // wstawianie pozniej te usuniete,
 *  skopiuj drzewo
 *  doda jdrzewa
 */
struct element_drzewa{ //binary tree
    double wartosc;
    struct element_drzewa *lewy, *prawy;
};

//ok
void wstaw(struct element_drzewa **poczatkowy, double dana, int tryb){ // 0-wstawianie nowego, 1- wstawianie elementow
    struct element_drzewa *nowy, *wskaznik;
    wskaznik=*poczatkowy;
    if(tryb==0) {
        nowy = malloc(sizeof(struct element_drzewa));
        nowy->wartosc = dana;
        nowy->lewy = nowy->prawy = 0;
    }
    if(tryb==1){

    }
    if(!wskaznik) *poczatkowy=nowy; // jeśli nie ma żadnego elementu, no to nowo utworzony bedzie korzeniem
    else{
        while(1){
            if(dana < wskaznik->wartosc){ // jesli dana jest mniejsza od tego co jest w danym elemencie
                if(wskaznik->lewy==0){
                    wskaznik->lewy=nowy;
                    break;
                }
                else{
                    wskaznik=wskaznik->lewy; // jesli jest kolejny lewy element, to przechodzimy
                }
            }
            else{
                if(wskaznik->prawy==0){ // jesli prawe sie konczy
                    wskaznik->prawy=nowy; // to dopisujemy tu na koncu
                    break;
                }
                else{
                    wskaznik=wskaznik->prawy;
                }
            }
        }
    }
}
//ok
void wypisz(struct element_drzewa *root){
    if(root==0) return;
    wypisz(root->lewy); // wchodzimy do lewego, i od nowa sprawdzamy, jak juz dojdziemy do konca to wypisujemy lewy
    printf("%0.2lf\n", root->wartosc); // jak wypisalismy to sprawdzamy prawa czesc
    wypisz(root->prawy);
}
//ok
struct element_drzewa *znajdz(struct element_drzewa *root, double szukana){ // niby wiem jak dziala, ale buja
    if(root==0){
        printf("nie ma elementu w drzewie\n");
        return 0;
    }
    if (szukana == root->wartosc) {
        printf("%0.2lf\n", root->wartosc);
        return root;
    } else if (szukana < root->wartosc) {
        znajdz(root->lewy, szukana);
    } else {
        znajdz(root->prawy, szukana);
    }
}

void usun(struct element_drzewa *root, double szukana_do_usuniecia){
    struct element_drzewa *do_usuniecia, *prawe, *lewe;
    if(szukana_do_usuniecia==root->wartosc){
        printf("nie mozna usunac pierwszej wartosci\n");
        return;
    }
    do_usuniecia = znajdz(root, szukana_do_usuniecia);
    if(do_usuniecia==0) return; // bo znajdz nam juz pisze ze nie ma
    lewe=do_usuniecia->lewy;
    prawe=do_usuniecia->prawy;
    // usunac do_usuniecia;
    if(lewe!=0){
        wstaw(&lewe, lewe->wartosc, 1);
    }
    if(prawe!=0){
        wstaw(&prawe, prawe->wartosc, 1);
    }

}

int main() {
    struct element_drzewa *drzewko;
    int wybor;
    double wartosc;

    while(1){
        printf("co cheesz zrobic:\n0 - wstawic do drzewa\n1 - wyswietlic\n2 - znalezc\n3 - usunac\n4 - skopiowac drzezwo\n5 - dodac drzewo\n%d - wyjscie", EXIT);
        scanf("%d", &wybor);

        switch(wybor) {
            case 0:
                printf("podaj wartosc: \n");
                scanf("%lf", &wartosc);

                wstaw(&drzewko, wartosc, 0);
                break;

            case 1:
                if(!drzewko) {
                    printf("nie ma zadnego elementu\n");
                    break;
                }
                wypisz(drzewko);
                break;

            case 2:
                printf("podaj wartosc:\n");
                scanf("%lf", &wartosc);
                znajdz(drzewko, wartosc);
                break;

            case 3:
                printf("podaj wartosc:\n");
                scanf("%lf", &wartosc);
                usun(drzewko, wartosc);
                break;

            case 4:
                printf("4\n");
                break;

            case 5:

                break;
            case EXIT:
                printf("Wyjscie");
                return 0;
        }
    }

    return 0;
}
