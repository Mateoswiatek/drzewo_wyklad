#include <stdio.h>
#include <malloc.h>

struct element_drzewa{ //binary tree
    double wartosc;
    struct element_drzewa *lewy, *prawy;
};

void wstaw(struct element_drzewa **poczatkowy, double dana){
    struct element_drzewa *nowy, *wskaznik, *nastepny;
    wskaznik=*poczatkowy;
    nowy=malloc(sizeof(struct element_drzewa));
    nowy->wartosc=dana;
    nowy->lewy=nowy->prawy=0;
    if(!wskaznik) *poczatkowy=nowy; // jeśli nie ma żadnego elementu, no to nowo utworzony bedzie korzeniem

}
int main() {
    printf("Hello, World!\n");
    printf("siemano");
    return 0;
}
