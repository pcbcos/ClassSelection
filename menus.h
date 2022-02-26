//
// Created by wengz on 2022/1/17.
//

#ifndef CLASSSELECTION_MENUS_H
#define CLASSSELECTION_MENUS_H

#include "curses.h"
#include "panel.h"

#define main_menu_size_x 30
#define main_menu_size_y 10
extern int max_x,max_y;
void printmenu(WINDOW *menu_win, int highlight, char *choices[], int n_choices);
void printmenu2(WINDOW *menu_win, int highlight, char *choices[], int n_choices);
int main_menu();
int student_menu();
int teacher_menu();
int admin_menu();
void window_floor_test(const char *text);
void show_warning_win(const char *waring_text);

#endif //CLASSSELECTION_MENUS_H
