#ifndef FILE_CABINET_SAVE_H
#define FILE_CABINET_SAVE_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "list.h"
#include "sort.h"


typedef struct {
    char *name;
    struct tm date;
}SAVE;

SAVE* create_SAVE(char*);

char *create_string_from_SAVE(SAVE*);

void delete_SAVE(SAVE*);

void print_SAVE(SAVE*);

int comp_name(SAVE***,SAVE***);

int comp_name_reverse(SAVE***,SAVE***b);

int comp_data(SAVE***,SAVE ***);

int comp_data_reverse(SAVE***,SAVE***);

int filtr_name(SAVE*,Node*);

#endif //FILE_CABINET_SAVE_H
