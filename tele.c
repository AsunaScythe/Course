
#include "tele.h"


tele* create_tele(char *str){
    tele *new;
    int i,
            j;

    new  = calloc(sizeof(tele),1);

    for(i = 0;str[i] != ',';i++);
    new->company = calloc(sizeof(char),i+1);
    for(j = 0;j < i;j++)
        new->company[j] = str[j];
    new->company[j] = '\0';
    i++;
    j = i;
    for(;str[i]!=',';i++);
    new->price = to_int(&str[j],&str[i]);

    new->color = str[++i];
    return new;
}

void print_tele(tele *some){
    int i;
    printf("%d ",some->price);
    for(i = 0;some->company[i]!='\0';i++)
        printf("%c",some->company[i]);
    printf(" %c",some->color);
}

char* create_str_from_tele(tele *some){
    int m1 = 20,
        m2 = 48,
        i;
    char *new,
        *plus;
    new = calloc(sizeof(char),51);
    for(i = 0;some->company[i]!='\0';i++)
        new[i] = some->company[i];
    for(;i<m1;i++)
        new[i] = ' ';
    plus = to_string(some->price);

    for(i=0;plus[i]!= '\0';i++) {
        new[i + m1] = plus[i];
    }


    for(;i+m1<m2;i++)
        new[i+m1] = ' ';

    new[m2] = some->color;
    new[m2+1] = '\0';
    free(plus);

    return new;
}

int comp_color_reverse(tele ***a,tele ***b){
    return (**a)->color < (**b)->color;
}

int comp_color(tele ***a,tele ***b){
    return (**a)->color > (**b)->color;
}