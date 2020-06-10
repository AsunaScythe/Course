#include "list.h"
//нахождение длинны списка
int get_length(Node *some){
    int len;
    Node *curr;
    if(some != NULL)
        for(curr = some->next,len = 1;curr != some;curr = curr->next,len++);
    else
        len = 0;
    return len;
}

//поиск элемента по значению
Node* find_value(Node *some,void *value,int size){
    Node *curr;
    if(some != NULL && !same(some->data,value,size)) {
        for (curr = some->next; curr != some && !same(curr->data, value, size); curr = curr->next);
        if(curr == some)
            curr = NULL;
    }
    else if(some == NULL)
        curr = NULL;
    else curr = some;
    return curr;
}

//удаление элемента
//void delete_Node(Node *some,void (*delete_data)(void*)){
//    if(some != NULL) {
//        Node *prev;
//        prev = get_prev(some);
//        prev->next = some->next;
//        delete_data(some->data);
//        free(some);
//    }
//}

Node* delete_Node(Node *some,void (*delete_data)(void*)){
    if(some != NULL) {
        Node *del;
        if (some->next != some){
            delete_data(some->data);
        del = some->next;
        some->data = some->next->data;
        some->next = some->next->next;
        free(del);

        }else{
            delete_data(some->data);
            //free(some);
            some = NULL;
        }
    }
    return some;
}

void delete_list(Node *some,void(*delete)(void*)){
    int i,
        n;
    Node *curr,
        *next;
    if(some != NULL) {
        n = get_length(some);
        for(curr = some,next = some->next,i = 0;i<n;i++,curr = next,next = next->next){
            delete(curr->data);
            free(curr);
        }
    }
}

//сравнение на равно
int same(void *a,void *b,int size){
    for(;size > 0 && *(char*)a == *(char*)b;size--,a++,b++);
    return !size;
}

//получение предыдущего элемента
Node* get_prev(Node *some){
    Node *curr;
    if(some != NULL)
        for(curr = some;curr->next != some;curr = curr->next);
    else curr = NULL;
    return curr;
}

//вывод списка
void print(Node *some,void(*print_data)(void*)){
    Node *curr;
    if(some!=NULL){
        curr = some;
        do{
            print_data(curr->data);
            curr = curr->next;
            puts("");
        }while(curr != some);
    }
}

//вывод списка в обратном порядке
void print_reverse(Node*some,void(*print_data)(void*)){
    int len,
            i;
    void **array;

    len = get_length(some);
    array = calloc(sizeof(void*),len);

    for(i = 0;i<len;i++,some=some->next){
        array[i] = some->data;
    }

    for(;i>0;i--) {
        print_data(array[i - 1]);
        puts("");
    }

    free(array);
}

//вставка до
Node* insert_prev(Node **some,void *data){
    Node *new;
    new = calloc(sizeof(Node), 1);
    new->data = data;
    if(*some != NULL) {
        new->next = *some;
        get_prev(*some)->next = new;
    }
    else {
        *some = new;
        (*some)->next = new;
    }
    return new;
}

//вставка после
Node* insert_after(Node **some,void *data){
    Node *new;
    new = calloc(sizeof(Node),1);
    new->data = data;
    if(*some!=NULL){
        new->next = (*some)->next;
        (*some)->next = new;
    }
    else {
        (*some) = new;
        (*some)->next = new;
    }
    return new;
}

Node* init(FILE* f,void* (*struct_create)(char*)){
    Node *head = NULL;

    void *new;

    char *data;

    int len;
    char curr;

    while(curr != EOF){
        curr = fgetc(f);
        for(len = 0;curr != '\n'  && curr != EOF ;len++,curr = fgetc(f));
        if(curr == EOF)
            fseek(f,-len, SEEK_CUR );
        else
            fseek(f,-len-2, SEEK_CUR );
        data = malloc(len+1);
        fread(data,1,len,f);
        data[len] = '\0';
        new = struct_create(data);
        free(data);
        insert_after(&head,new);
        curr = fgetc(f);
    }
    return head;
}

Node* get(Node *some,int number){
    for(;number > 0 && some!= NULL;number--)
        some = some->next;
    return some;
}

void sort_list(Node *some,int(*comp)(void*,void*),int size){
    if(some != NULL) {
        int n,
                i;
        void ***link;

        n = get_length(some);

        link = calloc(sizeof(void **), n);
        for (i = 0; i < n; i++, some = some->next)
            link[i] = &(some->data);

        sort(link, link + n, size, comp, swap_list);

        free(link);
    }
}

void delete_default(void *some){
    free(some);
}

void delete_empty(void *empty){};

void swap_list(void ***a,void ***b,int size){
    swap(*a,*b,size);
}

void print_char(void*some){
    printf("%c",*(char*)some);
}

char* from_list_to_str(Node *some){
    char *str;
    int n,
        i;
    n = get_length(some);

    str = calloc(sizeof(char),n+1);
    for(i = 0;i<n;i++)
        str[i] = *(char*)get(some,i)->data;

    str[i] = '\0';

    return str;
}

Node* from_char_to_node(char *some){
    Node *new = NULL;
    char *symb;
    int i;

    for(i = 0;some[i]!='\0';i++){
        symb = calloc(sizeof(char),1);
        *symb = some[i];
        insert_prev(&new,symb);

    }
    return new;
}

Node* filtr(Node *some,int(*true)(void*)){
    Node *new,
        *one;
    int n,
        i;

    n = get_length(some);

    for(i = 0;i < n;i++){
        one = get(some,i);
        if(true(one->data))
            insert_prev(&new,one->data);
    }
    return new;

}

