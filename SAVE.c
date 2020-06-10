
#include "SAVE.h"
SAVE* create_SAVE(char *string){
    char *curr;
    int size;
    SAVE *new;
    new = calloc(sizeof(SAVE),1);
    for(curr = string;*curr != ',';curr++);
    size = curr - string;
    new->name = calloc(sizeof(char),size+1);
    copy(string,new->name,size);
    new->name[size] = '\0';

    string = ++curr;
    for(curr = string;*curr != ',';curr++);

    new->date.tm_mday = to_int(string,curr);

    string = ++curr;
    for(curr = string;*curr != ',';curr++);

    new->date.tm_mon = to_int(string,curr);

    string = ++curr;
    for(curr = string;*curr != '\0';curr++);

    new->date.tm_year = to_int(string,curr);

    return new;
}

void delete_SAVE(SAVE *some){
    if(some!=NULL)
        free(some->name);
}

void print_SAVE(SAVE *some){
    char *curr;
    for(curr = some->name;*curr != '\0';curr++)
        printf("%c",*curr);
    printf(" %d",some->date.tm_mday);
    printf(" %d",some->date.tm_mon);
    printf(" %d",some->date.tm_year);
}

char *create_string_from_SAVE(SAVE *some){
    int i,
        n,
        m;

    m=20;
    char *string,
        *number;

    for(n = 0;some->name[n]!= '\0';n++);

    string = calloc(sizeof(char),m+12);

    for(i=0;i<m;i++)
        string[i] = ' ';

    for(i = 0;i < n;i++){
        string[i] = some->name[i];
    }
    string[m] = ' ';
    number = to_string(some->date.tm_mday);
    if(number[1]!='\0')
        copy(number,&string[m+1],2);
    else{
        string[m+1]='0';
        string[m+2]= number[0];
    }
    free(number);
    string[m+3] = '.';

    number = to_string(some->date.tm_mon);
    if(number[1]!='\0')
        copy(number,&string[m+4],2);
    else{
        string[m+4]  = '0';
        string[m+5]  = number[0];
    }
    free(number);
    string[m+6] = '.';

    number = to_string(some->date.tm_year);
    copy(number,&string[m+7],4);
    free(number);
    string[m+11] ='\0';

    return string;
}

int comp_name(SAVE ***a,SAVE ***b){
    char *name_a,
        *name_b;
    int flag;


    for(name_a = (**a)->name,name_b = (**b)->name;*name_a == *name_b && *name_b!='\0';name_a++,name_b++);

    if(*name_a < *name_b)
        flag = 1;
    else
        flag = 0;
    return flag;
}

int comp_name_reverse(SAVE ***a,SAVE ***b){
    char *name_a,
            *name_b;
    int flag;


    for(name_a = (**a)->name,name_b = (**b)->name;*name_a == *name_b && *name_b!='\0';name_a++,name_b++);

    if(*name_a > *name_b)
        flag = 1;
    else
        flag = 0;
    return flag;
}

int comp_data(SAVE ***a,SAVE ***b){
    return ((**a)->date.tm_year-1900)*500 + ((**a)->date.tm_mon)*40 + ((**a)->date.tm_mday) < ((**b)->date.tm_year-1900)*500 + ((**b)->date.tm_mon)*40 + ((**b)->date.tm_mday);
}

int comp_data_reverse(SAVE ***a,SAVE ***b){
    return ((**a)->date.tm_year-1900)*500 + ((**a)->date.tm_mon)*40 + ((**a)->date.tm_mday) > ((**b)->date.tm_year-1900)*500 + ((**b)->date.tm_mon)*40 + ((**b)->date.tm_mday);
}

int filtr_name(SAVE *some,Node *str){
    int i,
        j,
        n,
        m,
        flag;
    n = get_length(str);
    m = get_str_length(some->name);
    for(i = 0,flag = 0;i < m-n && flag == 0;i++)
        for(j = 0,flag = 1;j<n&&flag == 1;j++){
            if(some->name[j+i] != *(char*)get(str,j)->data)
                flag = 0;
        }

    return flag;
}