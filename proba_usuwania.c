#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define EXIT 6

int k =0;

/*
 *              wstaw do drzewa  // pierwsze nie moze byc 0;
 *              wyswietl
 *              znajdz
 *       usun       // plan byl by zamieszac dosc grubo, aby dzieci usunietej matki dodawac do matki usunietej matki XD
 *  skopiuj drzewo
 *  doda jdrzewa
 */
struct element_drzewa{ //binary tree
    double wartosc;
    struct element_drzewa *lewy, *prawy;
};

struct element_drzewa *poprzedni_u;

//ok
void wstaw(struct element_drzewa **poczatkowy, double dana){
    struct element_drzewa *nowy, *wskaznik;
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
void wypisz(struct element_drzewa *root, int tryb){ // 1 - do usuwania

    if(root==0) return;
    wypisz(root->lewy, tryb); // wchodzimy do lewego, i od nowa sprawdzamy, jak juz dojdziemy do konca to wypisujemy lewy
    printf("%0.2lf\n", root->wartosc); // jak wypisalismy to sprawdzamy prawa czesc
    if (tryb==1){
        poprzedni_u->lewy=0;
        wstaw(poprzedni_u, root->wartosc);
    }
    wypisz(root->prawy, tryb);
    if (tryb==1){
        poprzedni_u->prawy=0;
        wstaw(poprzedni_u, root->wartosc);
    }
}
//ok
struct element_drzewa *znajdz(struct element_drzewa *root, double szukana){ // niby wiem jak dziala, ale buja
    if(root==0){
        printf("nie ma elementu w drzewie\n");
        return 0;
    }
    if (szukana == root->wartosc) {
        printf("znaleziony to %u\n", root);
        printf("%0.2lf\n", root->wartosc);
        return root;
    } else if (szukana < root->wartosc) {
        poprzedni_u=root;
        printf("poprzedni root to niby %u\n", poprzedni_u);
        znajdz(root->lewy, szukana);
    } else {
        poprzedni_u=root;
        printf("poprzedni root to niby %u\n", poprzedni_u);
        znajdz(root->prawy, szukana);
    }
}

void usun(struct element_drzewa *root, double szukana_do_usuniecia){
    struct element_drzewa *do_usuniecia;
    do_usuniecia = znajdz(root, szukana_do_usuniecia);
    if(do_usuniecia==0) return; // bo znajdz nam juz pisze ze nie ma
    //zwolnic miejsce
    wypisz(do_usuniecia->lewy, 1);

    wypisz(do_usuniecia->prawy, 1);

    printf("%.02lf\n", do_usuniecia->wartosc);
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
                if(!drzewko) {
                    printf("nie ma zadnego elementu\n");
                    break;
                }
                wypisz(drzewko,0);
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
