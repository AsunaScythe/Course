

#ifndef FILE_CABINET_TELE_H
#define FILE_CABINET_TELE_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "sort.h"

typedef struct{
    char color;
    int price;
    char *company;
}tele;


tele* create_tele(char*);

void print_tele(tele*);

char* create_str_from_tele(tele *);

int comp_color(tele***,tele***);

int comp_color_reverse(tele***,tele***);

#endif //FILE_CABINET_TELE_H
