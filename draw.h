#ifndef FILE_CABINET_DRAW_H
#define FILE_CABINET_DRAW_H
#include "list.h"
#include "sort.h"

typedef struct window window;

struct window{
    int from_h;
    int from_w;
    int height;
    int width;
    char **screen;
    Node *current_window;
    Node *windows;
    Node *buttons;
    Node *functions;
    window *main;
    window *himself;
};


window* create_window(int,int,int,int);

window* create_window_from_string(char*,int,int);

Node* create_windows_from_list(Node*,char*(*)(void*),int,int,window*);

void draw(window *,char **,int,int);

Node* add_window(window*,window*);

void add_button(window*,void*(*)(window*),char);

void* right(window*);

void* left(window*);

void* down(window*);

void* up(window*);

void* enter(window*);

void delete_window(window*);

void move(window*,char);

void insert_text(char*,window*,int,int);

#endif //FILE_CABINET_DRAW_H
