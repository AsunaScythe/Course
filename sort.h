#ifndef LAB8_SORT_H
#define LAB8_SORT_H
#include <stdlib.h>

void swap(void*,void*,int);

void sort(void*,void*,int,int(*)(void*,void*),void(*)(void*,void*,int));

void copy(void*,void*,int);

int to_int(char*,char*);

char* to_string(int);

int get_str_length(char*);

#endif //LAB8_SORT_H
