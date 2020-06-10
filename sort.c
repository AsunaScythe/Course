#include "sort.h"

void sort(void *begin,void *end,int size,int (*comp)(void*,void*),void(*swap)(void*,void*,int)){
    void *left,
         *right;

    left = begin;
    right = end - size;

    while(left < right){
        while(left < right && comp(begin,right))
            right-= size;
        while(left < right && !comp(begin,left))
            left+= size;
        swap(left,right,size);
    }
    swap(left,begin,size);

    if((end-left-size)/size>1)
        sort(left+size,end,size,comp,swap);
    if((left-begin)/size>1)
        sort(begin,left,size,comp,swap);
}

void swap(void*a,void*b,int size){
    char buff;

    for(;size>0;a++,b++,size--){
        buff = *(char*)a;
        *(char*)a = *(char*)b;
        *(char*)b = buff;
    }
}

void copy(void *from,void *to,int size){

    for(;size>0;size--,from++,to++){
        *(char*)to = *(char*)from;
    }

}

int to_int(char *begin,char *end){
    int s;
    for(s = 0;begin < end;begin++)
        s = s*10 + (*begin-48);
    return s;
}

char* to_string(int a){
    int b,
        n;
    char *string;
    for(b = a,n = 0;b!=0 ;b /=10,n++);

    string = calloc(sizeof(char),n+1);
    string[n] = '\0';

    for(n--;n>=0;n--,a /= 10){
        string[n] = a%10+48;
    }
    return string;
}

int get_str_length(char *str){
    int i;
    for(i = 0;str[i] != '\0';i++);
    return i;
}