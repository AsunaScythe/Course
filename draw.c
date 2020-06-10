#include "draw.h"

window* create_window(int width,int height,int from_w,int from_h){
    window *new;
    int i,
        j;

    new = calloc(sizeof(window),1);

    new->from_h = from_h;
    new->from_w = from_w;

    new->screen = calloc(sizeof(char*),height);

    new->height = height;
    new->width = width;

    for(i = 0;i < height;i++){
        new->screen[i] = calloc(sizeof(char),width);
        for(j = 0;j<width;j++)
            new->screen[i][j] = ' ';
    }
    new->current_window = NULL;
    new->windows = NULL;
    new->buttons = NULL;
    new->main = NULL;
    new->himself = new;

    add_button(new,&left,75);
    add_button(new,&right,77);
    add_button(new,&up,72);
    add_button(new,&down,80);

    return new;
}

window* create_window_from_string(char *string,int from_w,int from_h){
    window *new;
    int i,
        j,
        n;
    new = calloc(sizeof(window),1);
    new->from_h = from_h;
    new->from_w = from_w;

    for(n = 0;string[n] != '\0';n++);

    new->width = n+2;
    new->height = 3;

    new->screen = calloc(sizeof(char*),new->height);
    for(i = 0;i < new->height;i++){
        new->screen[i] = calloc(sizeof(char),new->width);
        for(j = 0;j < new->width;j++)
            new->screen[i][j] = ' ';
    }
    for(j = 0;j < new->width - 1;j++){
        new->screen[1][j+1] = string[j];
    }

    new->current_window = NULL;
    new->windows = NULL;
    new->buttons = NULL;
    new->main = NULL;
    new->himself = new;

    add_button(new,&left,75);
    add_button(new,&right,77);
    add_button(new,&up,72);
    add_button(new,&down,80);

    return new;
}

Node* create_windows_from_list(Node *some,char*(*make)(void*),int from_w,int from_h,window *main){
    char *string;
    int n,
        i;

    window *elem;

    n = get_length(some);

    for(i = 0;i<n;i++,some=some->next){
        string = make(some->data);
        elem = create_window_from_string(string,from_w,from_h+i*3);
        add_button(elem,&left,75);
        add_button(elem,&right,77);
        add_button(elem,&up,72);
        add_button(elem,&down,80);
        elem->main = main;
        insert_prev(&(main->windows),elem);

        free(string);
    }

}


void draw(window *some,char **screen,int h,int w){
    if(some != NULL) {
        int i,
            j;
        if(some->main == NULL) {
            screen = some->screen;
            for (i = 0; i < some->height; i++)
                for (j = 0; j < some->width; j++)
                    some->screen[i][j] = ' ';
        }

        h = some->from_h + h;
        w = some->from_w + w;
        for (i = 0; i < some->height; i++)
            for (j = 0; j < some->width; j++)
//                if(some->screen[i][j]!=' ')
                    screen[i + h][j + w] = some->screen[i][j];
        j = get_length(some->windows);

        for (i = 0; i < j; i++) {
            draw(get(some->windows, i)->data, screen, h, w);
        }
        if((some->main == NULL || some->main->current_window->data == some) && some->current_window==NULL){
            for(j = 0;j<some->width;j++)
                screen[h][j + w] = '-';
            for(j = 0;j<some->width;j++)
                screen[h+some->height-1][j + w] = '-';
            for(i = 0;i<some->height;i++)
                screen[h+i][w] = '|';
            for(i = 0;i<some->height;i++)
                screen[h+i][w+some->width-1] = '|';

            screen[h][w] = '+';
            screen[h+some->height-1][w] = '+';
            screen[h][w+some->width-1] = '+';
            screen[h+some->height-1][w+some->width-1] = '+';
        }
        if(some->main == NULL)
            for(i = 0;i < some->height;i++) {
                for (j = 0; j < some->width; j++)
                    printf("%c", some->screen[i][j]);
                puts("");
            }
    }

}

Node* add_window(window *main,window *new){
    new->main = main;

    if(main->current_window == NULL){
        main->current_window = insert_prev(&main->windows,new);
    }
    else
        insert_prev(&main->windows,new);


}

void add_button(window *some,void*(*func)(window*),char button){
    char *button_new;
    button_new = calloc(sizeof(char),1);
    *button_new = button;
    insert_prev(&some->functions,func);
    insert_prev(&some->buttons,button_new);
}

void move(window *main,char button){
    Node *curr;
    int n,
        i;
    if(main->current_window != NULL)
        move(main->current_window->data,button);
    else{
        curr = main->buttons;
        n = get_length(curr);
        for(i = 0;i<n && *(char*)curr->data != button;i++,curr=curr->next);
        if(i<n)
            (*(void*(*)(struct window*))get(main->functions,i)->data)(main);
    }
}

void* right(window *some){
    window *main,
           *new;

    float  h,
        w,
        h_some,
        w_some;

    double s;

    Node *curr,
         *next,
         *this;
    main = some->main;

    s = (main->height)*(main->height)*4 +  (main->width)*(main->width);

    curr = find_value(main->windows,some,sizeof(window));

    this = curr;

    w_some = some->width + some->from_w;
    h_some = some->height/2*2 + some->from_h*2;

    for(next = curr->next;next!= curr;next = next->next){
        new = ((window*)(next->data));
        w = new->from_w;
        h = new->height/2*2 + new->from_h*2;
        if(w >= w_some){
            if((w-w_some)*(w-w_some) + (h-h_some)*(h-h_some)*4 < s) {
                s = (w - w_some) * (w - w_some) + (h - h_some) * (h - h_some)*4;
                this = next;
            }
        }
    }

    main->current_window = this;
}

void* left(window *some){
    window *main,
            *new;

    float  h,
            w,
            h_some,
            w_some;

    double s;

    Node *curr,
            *next,
            *this;
    main = some->main;

    s = (main->height)*(main->height)*4 +  (main->width)*(main->width);

    curr = find_value(main->windows,some,sizeof(window));

    this = curr;

    w_some = some->from_w;
    h_some = some->height/2*2 + some->from_h*2;

    for(next = curr->next;next!= curr;next = next->next){
        new = ((window*)(next->data));
        w = new->from_w + new->width;
        h = new->height/2*2 + new->from_h*2;
        if(w <= w_some){
            if((w-w_some)*(w-w_some) + (h-h_some)*(h-h_some)*4 < s) {
                s = (w - w_some) * (w - w_some) + (h - h_some) * (h - h_some)*4;
                this = next;
            }
        }
    }

    main->current_window = this;
}

void* down(window *some){
    window *main,
            *new;

    float  h,
            w,
            h_some,
            w_some;

    double s;

    Node *curr,
            *next,
            *this;
    main = some->main;

    s = (main->height)*(main->height)*4 +  (main->width)*(main->width);

    curr = find_value(main->windows,some,sizeof(window));

    this = curr;

    w_some = some->from_w + some->width/2;
    h_some = some->height*2 + some->from_h*2;

    for(next = curr->next;next!= curr;next = next->next){
        new = ((window*)(next->data));
        w = new->from_w + new->width/2;
        h = new->from_h*2;
        if(h >= h_some){
            if((w-w_some)*(w-w_some) + (h-h_some)*(h-h_some)*4 < s) {
                s = (w - w_some) * (w - w_some) + (h - h_some) * (h - h_some)*4;
                this = next;
            }
        }
    }

    main->current_window = this;
}

void* up(window *some){
    window *main,
            *new;

    float  h,
            w,
            h_some,
            w_some;

    double s;

    Node *curr,
            *next,
            *this;
    main = some->main;

    s = (main->height)*(main->height)*4 +  (main->width)*(main->width);

    curr = find_value(main->windows,some,sizeof(window));

    this = curr;

    w_some = some->from_w + some->width/2;
    h_some = some->from_h*2;

    for(next = curr->next;next!= curr;next = next->next){
        new = ((window*)(next->data));
        w = new->from_w + new->width/2;
        h = new->from_h*2 + new->height*2;
        if(h <= h_some){
            if((w-w_some)*(w-w_some) + (h-h_some)*(h-h_some)*4 < s) {
                s = (w - w_some) * (w - w_some) + (h - h_some) * (h - h_some)*4;
                this = next;
            }
        }
    }

    main->current_window = this;
}

void delete_window(window *some){
    if(some != NULL) {
        int i;
        for (i = 0; i < some->height; i++)
            free(some->screen[i]);
        delete_Node(some->windows, delete_window);
        delete_Node(some->buttons, delete_default);
        delete_Node(some->functions, delete_empty);
    }
}

void insert_text(char *str,window *some,int from_w,int from_h){
    int i;
    for(i = 0;str[i]!='\0';i++){
        some->screen[from_h][from_w+i]= str[i];
    }
}