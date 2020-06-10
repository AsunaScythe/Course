#ifndef FILE_CABINET_LIST_H
#define FILE_CABINET_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

typedef struct Node Node;

struct Node{
    void *data;
    Node *next;
};

int get_length(Node*);

Node* find_value(Node*,void*,int);

Node* delete_Node(Node*,void (*)(void*));

int same(void*,void*,int);

Node* get_prev(Node*);

void print(Node*,void(*)(void*));

void print_reverse(Node*,void(*)(void*));

Node* insert_prev(Node**,void*);

Node* insert_after(Node**,void*);

Node* init(FILE*,void* (*)(char*));

Node* get(Node*,int);

void sort_list(Node *,int(*)(void*,void*),int);

void delete_default(void*);

void delete_empty(void*);

void swap_list(void***,void***,int);

void delete_list(Node*,void(*)(void*));

void print_char(void*);

char* from_list_to_str(Node*);

Node* from_char_to_node(char*);

#endif //FILE_CABINET_LIST_H
