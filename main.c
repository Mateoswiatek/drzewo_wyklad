#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define EXIT 6

struct element_drzewa *drzewko, *poprzedni_u, *kopiowane;
int a;

/*
 *              wstaw do drzewa  // pierwsze nie moze byc 0;
 *              wyswietl
 *              znajdz
 *              usun   // wstawianie pozniej te usuniete przekazujemy wartosc, jako od kotrej zaczynamy, a zamiast nowo utworzonego, mamy wskaznik do "poczaktu" jednego z dziecka z tego usunietego,
 *              skopiuj drzewo
 *              dodaj drzewa
 */
struct element_drzewa{ //binary tree
    double wartosc;
    struct element_drzewa *lewy, *prawy;
};
//ok
void wstaw(struct element_drzewa **poczatkowy, double dana, int tryb, struct element_drzewa *ws_dziecka){ // 0-wstawianie nowego, 1- wstawianie elementow
    struct element_drzewa *nowy, *wskaznik;
    wskaznik=*poczatkowy;
    if(tryb) {
        nowy=ws_dziecka;
    }else{
        nowy = malloc(sizeof(struct element_drzewa));
        nowy->wartosc = dana;
        nowy->lewy = nowy->prawy = 0;
    }

    if(tryb==0 && !wskaznik) *poczatkowy=nowy; // jeśli nie ma żadnego elementu, no to nowo utworzony bedzie korzeniem
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
void wypisz(struct element_drzewa *root, int tryb){ //0 - wypisz, 1 - skopiuj 2 - usuwanie
    if(root==0) return;
    wypisz(root->lewy, tryb); // wchodzimy do lewego, i od nowa sprawdzamy, jak juz dojdziemy do konca to wypisujemy lewy
    if(tryb==1){
        wstaw(&kopiowane, root->wartosc, 0, 0);
    }
    else if(tryb==0){
        printf("%0.2lf\n", root->wartosc); // jak wypisalismy to sprawdzamy prawa czesc
    }
    if(tryb==2){
        free(root);
    }
    wypisz(root->prawy, tryb);
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
        poprzedni_u=root;
        a=0;
        //printf("poprzedni root to niby %u\n", poprzedni_u);
        znajdz(root->lewy, szukana);
    } else {
        poprzedni_u=root;
        a=1;
        //printf("poprzedni root to niby %u\n", poprzedni_u);
        znajdz(root->prawy, szukana);
    }
}
//ok
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
    if(a){
        poprzedni_u->prawy=0;
    }
    else{
        poprzedni_u->lewy=0;
    }

    free(do_usuniecia);
    if(lewe!=0){
        wstaw(&drzewko, lewe->wartosc, 1, lewe);
    }
    if(prawe!=0){
        wstaw(&drzewko, prawe->wartosc, 1, prawe);
    }
}
//ok
void skopiuj(struct element_drzewa *zrodlo){ // tak jakby wypisujemy wszystkie, ale nie wypisujemy tylko dodajemy je do "kopiowanego drzewaa"
    wypisz(zrodlo, 1);
    return;
}
//ok
void dodaj_drzewa(struct element_drzewa *do_ktorego, struct element_drzewa *jakie_drzewo){
    wstaw(&do_ktorego, jakie_drzewo->wartosc, 1, jakie_drzewo);
}

int main() {
    int wybor;
    double wartosc;

    while(1){
        //printf("co cheesz zrobic: 0 - wstawic do drzewa 1 - wyswietlic 2 - znalezc 3 - usunac 4 - skopiowac drzezwo 5 - dodac drzewo %d - wyjscie", EXIT);
        printf("co cheesz zrobic:\n0 - wstawic do drzewa\n1 - wyswietlic\n2 - znalezc\n3 - usunac\n4 - skopiowac drzezwo\n5 - dodac drzewo\n%d - wyjscie", EXIT);
        scanf("%d", &wybor);

        switch(wybor) {
            case 0:
                printf("podaj wartosc: \n");
                scanf("%lf", &wartosc);
                wstaw(&drzewko, wartosc, 0, 0);
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
                skopiuj(drzewko);
                printf("zrodlo ma roota w %u\n a tu jego zawartosc:\n", drzewko);
                wypisz(drzewko, 0);
                printf("nowo skopiowany ma roota w %u\n a tu jego zawartosc:\n", kopiowane);
                wypisz(kopiowane, 0);
                break;

            case 5:
                dodaj_drzewa(drzewko, kopiowane);
                wypisz(drzewko, 0);
                break;

            case EXIT:
                printf("Wyjscie");
                wypisz(drzewko, 2);
                return 0;
        }
    }

    return 0;
}
