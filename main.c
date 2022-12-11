#include <stdio.h>
#include <malloc.h>

#define EXIT 6
struct element_drzewa{ //binary tree
    double wartosc;
    struct element_drzewa *lewy, *prawy;
};

//ok
void wstaw(struct element_drzewa **poczatkowy, double dana){
    struct element_drzewa *nowy, *wskaznik, *nastepny;
    wskaznik=*poczatkowy;
    nowy=malloc(sizeof(struct element_drzewa));
    nowy->wartosc=dana;
    nowy->lewy=nowy->prawy=0;
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
                wstaw(&drzewko, wartosc);
                break;
            case 1:
                wypisz(drzewko);
                break;
            case 2:
                printf("2\n");
                break;
            case 3:
                printf("3\n");
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
