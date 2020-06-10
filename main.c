#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "sort.h"
#include "list.h"
#include "SAVE.h"
#include "draw.h"
#include "tele.h"
#define ABC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ."
#define NUM "0123456789"

char get_move(char*);

int check_symbol(char,char*);

int get_len(char*);

char* str_str(char*,char*);

int main() {
    int
        i,
            j,
            n,
            text_sep,
            num_alpha,
            text_sep_filtr,
            num_alpha_filtr,
            curr_sort_name_flag_save = 1,
            curr_sort_data_flag_save = 1,
            curr_sort_company = 1,
            curr_sort_price = 1,
            curr_sort_color = 1,
            buttons[] = {-1,-1,-1};
    char symbol_menu_1[] = {75,77,72,80,13,27,'\0'},
        symbol_messeg_move[] = {32,75,77,13,8,'\0'},
        *symbol_messege = str_str(ABC,symbol_messeg_move),
        added[] = {75,77,72,80,13,27,8,'\0'},
        *change_box = str_str(added,ABC),
        *number_box = str_str(added,NUM),
        *color_box = str_str(added,"rgb"),
        *messege_text,
        curr,
        curr_1,
        curr_messege,
        curr_data_file,
        **table,
        *something,
        curr_param,
        *filename,
        *dele;
    symbol_messege[0] = 27;
    Node *date = NULL,
        *filtred_date = NULL,
        *text = NULL,
        *curr_alpha = NULL,
        *filtr_str_date = NULL,
        *filtr_str_file = NULL,
        *check,
        *tele_list,
        *filtred_tele_list,
        *filename_list,
        *node_1 = NULL,
        *node_2 = NULL,
        *node_3 = NULL,
        *curr_node;
    FILE *f;


    window *main,
        *open,
        *new,
       *help,
       *exit,
       *data_sort,
       *name_sort,
       *add_new,
       *messege,
       *saves,
       *text_filtr,
       *data_base,
       *data_base_name,
       *company_sort,
       *color_sort,
       *price_sort,
       *blue_button,
       *red_button,
       *green_button,
       *add_new_file,
       *add_elem,
       *company,
       *price,
       *color;


    SAVE *new_save;
    time_t new_data;
    struct tm *data_data;

    main = create_window(150,40,0,0);
    open = create_window_from_string("Open",1,1);

    tele *new_tele;

    add_window(main,open);

    new = create_window_from_string("New",10,1);


    add_window(main,new);

    help = create_window_from_string("Help",20,1);


    add_window(main,help);

    exit = create_window_from_string("Exit",30,1);


    add_window(main,exit);




    do{
        system("cls");
        draw(main,table,0,0);
        do {
            curr = get_move(symbol_menu_1);
            system("cls");
            move(main,curr);
            draw(main,table,0,0);
        }while(curr != 13);

        if(main->current_window->data == open){
            f = fopen("dates.txt","r");
            date = init(f,create_SAVE);
            fclose(f);
            saves = create_window(130,34,0,5);
            add_window(main,saves);
            saves->main = main;
            main->current_window = find_value(main->windows,saves,sizeof(window));
            filtr_str_date = NULL;
            data_sort = create_window_from_string("///////////////",19,7);
            add_window(saves,data_sort);
            name_sort = create_window_from_string("///////////////",2,7);
            add_window(saves,name_sort);
            text_filtr = create_window(42,3,0,2);
            insert_text("Find /:",text_filtr,1,1);
            add_window(saves,text_filtr);
            text_sep_filtr = 0;
            num_alpha_filtr = 0;

            add_new = create_window_from_string("   +   ",13,10+get_length(filtred_date)*3);
            add_window(saves,add_new);
            do {
                filtred_date = NULL;
                for(i = 0;i < get_length(date);i++){
                    if(filtr_name(get(date,i)->data,filtr_str_date))
                        insert_prev(&filtred_date,get(date,i)->data);
                }
                if(saves->current_window->data == data_sort || saves->current_window->data == name_sort || saves->current_window->data==text_filtr || saves->current_window->data == add_new){
                    check = get(saves->windows,3);
                    if(check->next != saves->windows) {
                        get_prev(saves->windows)->next = check->next;
                        delete_list(check->next, delete_window);
                        check->next = saves->windows;

                    }
                    create_windows_from_list(filtred_date,create_string_from_SAVE,2,10,saves);
                    for(i = 0;i<get_length(filtred_date);i++){
                        add_window(saves,create_window_from_string("-",37,10+i*3));
                    }
                }else if(((window*)(saves->current_window->data))->height == 3){
                    n = (((window*)(saves->current_window->data))->from_h-10)/3;
                    get_prev(saves->windows)->next = check->next;
                    delete_list(check->next, delete_window);
                    check->next = saves->windows;

                    create_windows_from_list(filtred_date,create_string_from_SAVE,2,10,saves);
                    for(i = 0;i<get_length(filtred_date);i++)
                        add_window(saves,create_window_from_string("-",37,10+i*3));
                    saves->current_window = get(saves->windows,4);

                }
                add_new->from_h = 10+get_length(filtred_date)*3;

                system("cls");
                draw(main,table,0,0);
                if(saves->current_window->data != text_filtr) {
                    do {
                        curr_1 = get_move(symbol_menu_1);
                        system("cls");
                        move(main, curr_1);
                        draw(main, table, 0, 0);
                    } while (curr_1 != 13 && curr_1 != 27 && saves->current_window->data != text_filtr);
                }
                if(curr_1 == 13) {
                    if (saves->current_window->data == name_sort) {
                        if (curr_sort_name_flag_save) {
                            sort_list(date, comp_name, sizeof(void *));
                            curr_sort_name_flag_save = 0;
                        } else {
                            sort_list(date, comp_name_reverse, sizeof(void *));
                            curr_sort_name_flag_save = 1;
                        }

                    }else if(((window*)saves->current_window->data)->width>25){
                        data_base = create_window(120,30,0,0);
                        add_window(saves,data_base);

                        saves->current_window = find_value(saves->windows,data_base,sizeof(window));
                        data_base_name = create_window(30,3,1,1);
                        insert_text("Filename",data_base_name,1,1);
                        filename = ((SAVE*)(get(filtred_date,(((window*)saves->current_window->data)->from_h-10)/3)->data))->name;
                        insert_text(filename,data_base_name,12,1);
                        add_window(data_base,data_base_name);
                        f = fopen("qwe.txt","r");
                        tele_list = init(f,create_tele);

                        company_sort = create_window_from_string("////////////////",35,1);
                        add_window(data_base,company_sort);
                        price_sort = create_window_from_string("////////////////",53,1);
                        add_window(data_base,price_sort);
                        color_sort = create_window_from_string("//////////////",71,1);
                        add_window(data_base,color_sort);
                        green_button = create_window(3,3,8,4);
                        insert_text("green",data_base,2,5);
                        add_window(data_base,green_button);

                        red_button = create_window(3,3,8,8);
                        insert_text("red",data_base,2,9);
                        add_window(data_base,red_button);

                        blue_button = create_window(3,3,8,12);
                        insert_text("blue",data_base,2,13);
                        add_window(data_base,blue_button);

                        add_new_file = create_window(50,3,35,3);
                        insert_text("+",add_new_file,25,1);
                        add_window(data_base,add_new_file);
                        do {
                                filtred_tele_list = NULL;
                                for(i = 0;i < get_length(tele_list);i++){
                                    if(2>1)
                                        insert_prev(&filtred_tele_list,get(tele_list,i)->data);
                                }
                            create_windows_from_list(filtred_tele_list,create_str_from_tele,35,4,data_base);
                            add_new_file->from_h = 8 + 3*get_length(filtred_tele_list);
                            system("cls");
                            draw(main, table, 0, 0);

                            do{
                                curr_data_file = get_move(symbol_menu_1);
                                move(main,curr_data_file);
                                system("cls");
                                draw(main, table, 0, 0);
                            }while(curr_data_file!=13 && curr_data_file!= 27);
                            if(curr_data_file == 13) {
                                if (data_base->current_window->data == color_sort) {
                                    if (curr_sort_color == 1) {
                                        sort_list(tele_list, comp_color, sizeof(void *));
                                        curr_sort_color = 0;
                                    } else {
                                        sort_list(tele_list, comp_color_reverse, sizeof(void *));
                                        curr_sort_color = 1;
                                    }

                                } else if(data_base->current_window->data == green_button) {
                                    buttons[0] *= -1;
                                    if(buttons[0]==1)
                                        green_button->screen[1][1] = '+';
                                    else
                                        green_button->screen[1][1] = ' ';
                                }
                                else if(data_base->current_window->data == red_button) {
                                    buttons[1] *= -1;
                                    if(buttons[1]==1)
                                        red_button->screen[1][1] = '+';
                                    else
                                        red_button->screen[1][1] = ' ';
                                }
                                else if(data_base->current_window->data == blue_button) {
                                    buttons[2] *= -1;
                                    if(buttons[2]==1)
                                        blue_button->screen[1][1]= '+';
                                    else
                                        blue_button->screen[1][1]= ' ';
                                }else if(data_base->current_window->data == add_new_file){
                                    new_tele = calloc(sizeof(tele),1);
                                    add_elem = create_window(50,10,40,10);
                                    add_window(data_base,add_elem);
                                    data_base->current_window = find_value(data_base->windows,add_elem,sizeof(window));
                                    company = create_window(40,3,1,2);
                                    insert_text("Company:",company,1,1);
                                    add_window(add_elem,company);
                                    price = create_window(40,3,1,5);
                                    insert_text("Price:",price,1,1);
                                    add_window(add_elem,price);

                                    color = create_window(40,3,1,8);
                                    insert_text("Color:",color,1,1);
                                    add_window(add_elem,color);

                                    curr_param = 1;

                                    do{
                                        if(curr_param == 1) {
                                            text_sep = get_length(node_1);
                                            num_alpha = get_length(node_1);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            company->screen[1][i + 9] = *(char *) get(node_1, i)->data;
                                                        } else if (i == text_sep)
                                                            company->screen[1][i + 9] = '|';
                                                        else {
                                                            company->screen[1][i + 9] = *(char *) get(node_1,
                                                                                                      i - 1)->data;
                                                        }
                                                    else
                                                        company->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(change_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_1, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_1 = NULL;
                                                        }
                                                    } else if (curr_messege == 80) {
                                                        curr_param = 2;
                                                        add_elem->current_window = find_value(add_elem->windows,price,sizeof(window));
                                                    } else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, ABC) && num_alpha < 14) {
                                                        curr_alpha = get(node_1, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_1 == NULL)
                                                            node_1 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_1, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_1 == NULL)
                                                            node_1 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    something = NULL;
                                                    curr_alpha = NULL;
                                                }
                                            } while (curr_messege != 80 && curr_messege != 13);
                                        }else if(curr_param == 2){
                                            text_sep = get_length(node_2);
                                            num_alpha = get_length(node_2);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            price->screen[1][i + 9] = *(char *) get(node_2, i)->data;
                                                        } else if (i == text_sep)
                                                            price->screen[1][i + 9] = '|';
                                                        else {
                                                            price->screen[1][i + 9] = *(char *) get(node_2,
                                                                                                      i - 1)->data;
                                                        }
                                                    else
                                                        price->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(number_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_2, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_2 = NULL;
                                                        }
                                                    } else if (curr_messege == 80) {
                                                        curr_param = 3;
                                                        add_elem->current_window = find_value(add_elem->windows,color,sizeof(window));
                                                    }else if(curr_messege == 72){
                                                        curr_param = 1;
                                                        add_elem->current_window = find_value(add_elem->windows,company,sizeof(window));
                                                    } else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, NUM) && num_alpha < 14) {
                                                        curr_alpha = get(node_2, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_2 == NULL)
                                                            node_2 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_2, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_2 == NULL)
                                                            node_2 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    something = NULL;
                                                    curr_alpha = NULL;
                                                }
                                            } while (curr_messege != 80 && curr_messege != 13 && curr_messege != 72);
                                        }else if(curr_param == 3) {
                                            text_sep = get_length(node_3);
                                            num_alpha = get_length(node_3);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            color->screen[1][i + 9] = *(char *) get(node_3, i)->data;
                                                        } else if (i == text_sep)
                                                            color->screen[1][i + 9] = '|';
                                                        else {
                                                            color->screen[1][i + 9] = *(char *) get(node_3,
                                                                                                    i - 1)->data;
                                                        }
                                                    else
                                                        color->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(color_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_3, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_3 = NULL;
                                                        }
                                                    } else if (curr_messege == 72) {
                                                        curr_param = 2;
                                                        add_elem->current_window = find_value(add_elem->windows,price,sizeof(window));
                                                    }  else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, ABC) && num_alpha < 1) {
                                                        curr_alpha = get(node_3, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_3 == NULL)
                                                            node_3 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_3, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_3 == NULL)
                                                            node_3 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    curr_alpha = NULL;
                                                    something = NULL;
                                                }
                                            }while(curr_messege!= 13 && curr_messege != 72);
                                        }
                                    }while(curr_messege != 13);
                                    new_tele->company = from_list_to_str(node_1);
                                    dele = from_list_to_str(node_2);
                                    for(i = 0;dele[i]!='\0';i++);
                                    new_tele->price = to_int(dele,dele+i);
                                    free(dele);
                                    new_tele->color = *(char*)(node_3->data);
                                    delete_Node(node_1,delete_default);
                                    delete_Node(node_2,delete_default);
                                    delete_Node(node_3,delete_default);
                                    data_base->windows = delete_Node(find_value(data_base->windows,add_elem,sizeof(window)),delete_window);
                                    insert_prev(&tele_list,new_tele);
                                    node_1 = NULL;
                                    node_2 = NULL;
                                    node_3 = NULL;
                                }else if(((window*)(data_base->current_window->data))->height >30){
                                    puts("sdfsdfsdf");
                                    getch();
                                    new_tele = calloc(sizeof(tele),1);
                                    add_elem = create_window(50,10,40,10);
                                    add_window(data_base,add_elem);
                                    data_base->current_window = find_value(data_base->windows,add_elem,sizeof(window));
                                    company = create_window(40,3,1,2);
                                    insert_text("Company:",company,1,1);
                                    add_window(add_elem,company);
                                    price = create_window(40,3,1,5);
                                    insert_text("Price:",price,1,1);
                                    add_window(add_elem,price);

                                    color = create_window(40,3,1,8);
                                    insert_text("Color:",color,1,1);
                                    add_window(add_elem,color);
                                    new_save = (get(data_base->windows,(((window*)(data_base->current_window->data))->height-4)/3))->data;
                                    print_SAVE(new_save);
                                    getch();

                                    curr_param = 1;

                                    do{
                                        if(curr_param == 1) {
                                            text_sep = get_length(node_1);
                                            num_alpha = get_length(node_1);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            company->screen[1][i + 9] = *(char *) get(node_1, i)->data;
                                                        } else if (i == text_sep)
                                                            company->screen[1][i + 9] = '|';
                                                        else {
                                                            company->screen[1][i + 9] = *(char *) get(node_1,
                                                                                                      i - 1)->data;
                                                        }
                                                    else
                                                        company->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(change_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_1, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_1 = NULL;
                                                        }
                                                    } else if (curr_messege == 80) {
                                                        curr_param = 2;
                                                        add_elem->current_window = find_value(add_elem->windows,price,sizeof(window));
                                                    } else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, ABC) && num_alpha < 14) {
                                                        curr_alpha = get(node_1, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_1 == NULL)
                                                            node_1 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_1, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_1 == NULL)
                                                            node_1 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    something = NULL;
                                                    curr_alpha = NULL;
                                                }
                                            } while (curr_messege != 80 && curr_messege != 13);
                                        }else if(curr_param == 2){
                                            text_sep = get_length(node_2);
                                            num_alpha = get_length(node_2);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            price->screen[1][i + 9] = *(char *) get(node_2, i)->data;
                                                        } else if (i == text_sep)
                                                            price->screen[1][i + 9] = '|';
                                                        else {
                                                            price->screen[1][i + 9] = *(char *) get(node_2,
                                                                                                    i - 1)->data;
                                                        }
                                                    else
                                                        price->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(number_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_2, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_2 = NULL;
                                                        }
                                                    } else if (curr_messege == 80) {
                                                        curr_param = 3;
                                                        add_elem->current_window = find_value(add_elem->windows,color,sizeof(window));
                                                    }else if(curr_messege == 72){
                                                        curr_param = 1;
                                                        add_elem->current_window = find_value(add_elem->windows,company,sizeof(window));
                                                    } else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, NUM) && num_alpha < 14) {
                                                        curr_alpha = get(node_2, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_2 == NULL)
                                                            node_2 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_2, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_2 == NULL)
                                                            node_2 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    something = NULL;
                                                    curr_alpha = NULL;
                                                }
                                            } while (curr_messege != 80 && curr_messege != 13 && curr_messege != 72);
                                        }else if(curr_param == 3) {
                                            text_sep = get_length(node_3);
                                            num_alpha = get_length(node_3);
                                            do {
                                                for (i = 0; i < 16; i++) {
                                                    if (i < num_alpha + 1)
                                                        if (i < text_sep) {
                                                            color->screen[1][i + 9] = *(char *) get(node_3, i)->data;
                                                        } else if (i == text_sep)
                                                            color->screen[1][i + 9] = '|';
                                                        else {
                                                            color->screen[1][i + 9] = *(char *) get(node_3,
                                                                                                    i - 1)->data;
                                                        }
                                                    else
                                                        color->screen[1][i + 9] = ' ';
                                                }
                                                system("cls");
                                                draw(main, table, 0, 0);
                                                curr_messege = get_move(color_box);
                                                if (curr_messege != 13) {
                                                    if (curr_messege == 8) {
                                                        if (text_sep > 0) {
                                                            curr_alpha = get(node_3, text_sep - 1);
                                                            delete_Node(curr_alpha, delete_default);
                                                            text_sep--;
                                                            num_alpha--;
                                                            if (num_alpha == 0)
                                                                node_3 = NULL;
                                                        }
                                                    } else if (curr_messege == 72) {
                                                        curr_param = 2;
                                                        add_elem->current_window = find_value(add_elem->windows,price,sizeof(window));
                                                    }  else if (curr_messege == 75) {
                                                        if (text_sep > 0)
                                                            text_sep--;
                                                    } else if (curr_messege == 77) {
                                                        if (text_sep <= num_alpha - 1)
                                                            text_sep++;
                                                    } else if (check_symbol(curr_messege, ABC) && num_alpha < 1) {
                                                        curr_alpha = get(node_3, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = curr_messege;
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_3 == NULL)
                                                            node_3 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    } else if (curr_messege == 32) {
                                                        curr_alpha = get(node_3, text_sep);
                                                        something = calloc(sizeof(char), 1);
                                                        *something = ' ';
                                                        insert_prev(&curr_alpha, something);
                                                        if (node_3 == NULL)
                                                            node_3 = curr_alpha;
                                                        num_alpha++;
                                                        text_sep++;
                                                    }
                                                }else{
                                                    curr_alpha = NULL;
                                                    something = NULL;
                                                }
                                            }while(curr_messege!= 13 && curr_messege != 72);
                                        }
                                    }while(curr_messege != 13);
                                    new_tele->company = from_list_to_str(node_1);
                                    dele = from_list_to_str(node_2);
                                    for(i = 0;dele[i]!='\0';i++);
                                    new_tele->price = to_int(dele,dele+i);
                                    free(dele);
                                    new_tele->color = *(char*)(node_3->data);
                                    delete_Node(node_1,delete_default);
                                    delete_Node(node_2,delete_default);
                                    delete_Node(node_3,delete_default);
                                    data_base->windows = delete_Node(find_value(data_base->windows,add_elem,sizeof(window)),delete_window);
                                    insert_prev(&tele_list,new_tele);
                                }
                            }
                        }while(curr_data_file != 27);




                    }else if (saves->current_window->data == data_sort) {
                            if (curr_sort_data_flag_save) {
                                sort_list(date, comp_data, sizeof(void *));
                                curr_sort_data_flag_save = 0;
                            } else {
                                sort_list(date, comp_data_reverse, sizeof(void *));
                                curr_sort_data_flag_save = 1;
                            }

                    }else if (((window *) saves->current_window->data)->width == 3) {
                        remove(((SAVE*)(get(date, (((window *) saves->current_window->data)->from_h - 10) / 3)->data))->name);
                        if(find_value(date,get(filtred_date, (((window *) saves->current_window->data)->from_h - 10) / 3)->data,sizeof(SAVE))->next == date)
                            date = delete_Node(find_value(date,get(filtred_date, (((window *) saves->current_window->data)->from_h - 10) / 3)->data,sizeof(SAVE)),delete_SAVE);
                        else
                            delete_Node(find_value(date,get(filtred_date, (((window *) saves->current_window->data)->from_h - 10) / 3)->data,sizeof(SAVE)),delete_SAVE);
                    } else if(((window *) saves->current_window->data)->width == 9){
                        messege = create_window(20,8,7,10);
                        insert_text("Enter filename:",messege,2,2);
                        add_window(saves,messege);
                        saves->current_window = find_value(saves->current_window,messege,sizeof(window));
                        text_sep = 0;
                        num_alpha = 0;
                        do{
                            for(i = 0;i < 16;i++){
                                if(i < num_alpha+1)
                                    if(i<text_sep) {
                                        messege->screen[5][i + 2] = *(char *) get(text, i)->data;
                                    }else if(i == text_sep)
                                        messege->screen[5][i + 2] = '|';
                                    else {
                                        messege->screen[5][i + 2] = *(char *) get(text, i-1)->data;
                                    }
                                else
                                    messege->screen[5][i+2] = ' ';
                            }
                            system("cls");
                            draw(main,table,0,0);
                            curr_messege = get_move(symbol_messege);
                            if(curr_messege != 13) {
                                if (curr_messege == 8) {
                                    if (text_sep > 0) {
                                        curr_alpha = get(text,text_sep-1);
                                        delete_Node(curr_alpha,delete_default);
                                        text_sep--;
                                        num_alpha--;
                                        if(num_alpha == 0)
                                            text = NULL;
                                    }
                                }else if(curr_messege ==80|| curr_messege ==72){



                                }else if(curr_messege ==75){
                                    if(text_sep>0)
                                        text_sep--;
                                }else if(curr_messege == 77) {
                                    if (text_sep <= num_alpha-1)
                                        text_sep++;
                                }else if(check_symbol(curr_messege,ABC) && num_alpha < 14){
                                    curr_alpha = get(text,text_sep);
                                    something = calloc(sizeof(char),1);
                                    *something = curr_messege;
                                    insert_prev(&curr_alpha,something);
                                    if(text == NULL)
                                        text = curr_alpha;
                                    num_alpha++;
                                    text_sep++;
                                }else if(curr_messege == 32){
                                    curr_alpha = get(text,text_sep);
                                    something = calloc(sizeof(char),1);
                                    *something = ' ';
                                    insert_prev(&curr_alpha,something);
                                    if(text == NULL)
                                        text = curr_alpha;
                                    num_alpha++;
                                    text_sep++;
                                }
                            }else{
                                messege_text = from_list_to_str(text);
                                if((f = fopen(messege_text,"r")) == NULL){
                                    for(i = 0;i < messege->height;i++){
                                        for(j = 0;j < messege->width;j++)
                                            messege->screen[i][j] = ' ';
                                    }
                                    insert_text("File doesn't",messege,4,2);
                                    insert_text("  exist!!!",messege,4,3);
                                    insert_text("    ok",messege,4,5);
                                    system("cls");
                                    draw(main,table,0,0);
                                    do {
                                        curr_messege = getch();
                                    }while(curr_messege != 13);
                                }else{
                                    new_save = calloc(sizeof(SAVE),1);
                                    new_save->name = messege_text;
                                    new_data = time(NULL);
                                    data_data = localtime(&new_data);
                                    new_save->date.tm_mday = data_data->tm_mday;
                                    new_save->date.tm_mon = data_data->tm_mon+1;
                                    new_save->date.tm_year = data_data->tm_year+1900;
                                    insert_prev(&date,new_save);
                                    for(i = 0;i < messege->height;i++){
                                        for(j = 0;j < messege->width;j++)
                                            messege->screen[i][j] = ' ';
                                    }
                                    insert_text(" file added ",messege,4,2);
                                    insert_text(" succesfully",messege,4,3);
                                    insert_text("    ok",messege,4,5);
                                    system("cls");
                                    draw(main,table,0,0);
                                    do {
                                        curr_messege = getch();
                                    }while(curr_messege != 13);
                                }
                                fclose(f);
                            }
                        }while(curr_messege != 13  && curr_messege != 27);
                        delete_Node(text,delete_default);
                        saves->windows = delete_Node(saves->current_window,delete_window);
                        saves->current_window = find_value(saves->windows,add_new,sizeof(window));
                        text = NULL;
                    }
                }else if (saves->current_window->data == text_filtr){

                    do {
                        for (i = 0; i < 16; i++) {
                            if (i < num_alpha_filtr + 1)
                                if (i < text_sep_filtr) {
                                    text_filtr->screen[1][i + 8] = *(char *) get(filtr_str_date, i)->data;
                                } else if (i == text_sep_filtr)
                                    text_filtr->screen[1][i + 8] = '|';
                                else {
                                    text_filtr->screen[1][i + 8] = *(char *) get(filtr_str_date, i - 1)->data;
                                }
                            else
                                text_filtr->screen[1][i + 8] = ' ';
                        }
                        system("cls");
                        draw(main, table, 0, 0);
                        curr_messege = get_move(symbol_messege);
                        if (curr_messege != 13) {
                            if (curr_messege == 8) {
                                if (text_sep_filtr > 0) {
                                    curr_alpha = get(filtr_str_date, text_sep_filtr - 1);
                                    delete_Node(curr_alpha, delete_default);
                                    text_sep_filtr--;
                                    num_alpha_filtr--;
                                    if (num_alpha_filtr == 0)
                                        filtr_str_date = NULL;
                                }
                            } else if (curr_messege == 75) {
                                if (text_sep_filtr > 0)
                                    text_sep--;
                            }else if(curr_messege == 72){

                            }else if(curr_messege == 80) {

                                for (i = 0; i < 16; i++) {
                                    if (i < num_alpha_filtr)
                                        text_filtr->screen[1][i + 8] = *(char *) get(filtr_str_date, i)->data;
                                    else
                                        text_filtr->screen[1][i + 8] = ' ';
                                }
                                move(saves->current_window->data, 80);
                            } else if (curr_messege == 77) {
                                if (text_sep_filtr <= num_alpha_filtr - 1)
                                    text_sep_filtr++;
                            }else if(curr_messege == 27){
                                curr_1 = 27;
                            }

                            else if (check_symbol(curr_messege, ABC) && num_alpha_filtr < 14) {
                                curr_alpha = get(filtr_str_date, text_sep_filtr);
                                something = calloc(sizeof(char), 1);
                                *something = curr_messege;
                                insert_prev(&curr_alpha, something);
                                if (filtr_str_date == NULL)
                                    filtr_str_date = curr_alpha;
                                num_alpha_filtr++;
                                text_sep_filtr++;
                            } else if (curr_messege == 32) {
                                curr_alpha = get(filtr_str_date, text_sep_filtr);
                                something = calloc(sizeof(char), 1);
                                *something = ' ';
                                insert_prev(&curr_alpha, something);
                                if (filtr_str_date == NULL)
                                    filtr_str_date = curr_alpha;
                                num_alpha_filtr++;
                                text_sep_filtr++;
                            }
                        }
                    }while(curr_messege != 27 && curr_messege != 80 && curr_messege != 13);

                }
            }while(curr_1 != 27);

            delete_list(date,delete_SAVE);
            main->windows = delete_Node(main->current_window,delete_window);
            main->current_window->data = open;
        }if(main->current_window->data == new);
    }while(main->current_window->data != exit);

    return 0;
}
//
char get_move(char *symbols){
    char symbol;

    do{
        symbol = getch();
    }while(!check_symbol(symbol,symbols));

    return symbol;
}

int check_symbol(char symbol,char *string){
    int flag;
    for(flag = 0;flag == 0 && *string != '\0';string++) {
        if (symbol == *string)
            flag = 1;
    }
    return flag;
}


char* str_str(char *a,char *b){
    int a_len,
        b_len,
        i;

    char *new;

    a_len = get_len(a);
    b_len = get_len(b);

    new = calloc(sizeof(char),a_len+b_len);

    for(i = 0;i <a_len;i++){
        new[i] = a[i];
    }
    for(;i<a_len+b_len;i++)
        new[i] = b[i-a_len];

    new[i] = '\0';

    return new;
}

int get_len(char *a){
    int n;
    for(n = 0;a[n] != '\0';n++);
    return n;
}

