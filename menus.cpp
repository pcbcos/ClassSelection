//
// Created by wengz on 2022/1/17.
//

#include <unistd.h>
#include "menus.h"


/**
 * HIGHT:y\n
 * WIDTH:x
 */

char *main_menu_choices[] = {
        "学生模式",
        "教师模式",
        "管理员模式",
        "退出系统",
};
int n_main_menu_choices = sizeof(main_menu_choices) / sizeof(char *);

char *student_menu_choices[] = {
        "查看成绩",
        "查看课单",
        "选课",
        "返回主菜单",
};
int n_student_menu_choices = sizeof(student_menu_choices) / sizeof(char *);

char *teacher_menu_choices[] = {
        "查看班级\n学生信息",
        "返回主菜单",
};
int n_teacher_menu_choices = sizeof(teacher_menu_choices) / sizeof(char *);

char *admin_menu_choices[] = {
        "录入、更改\n学生信息",
        "录入、更改\n教师信息",
        "录入、更改\n课程信息",
        "返回主菜单",
};
int n_admin_menu_choices = sizeof(admin_menu_choices) / sizeof(char *);


void printmenu(WINDOW *menu_win, int highlight, char *choices[], int n_choices) {
    int x = 2;
    int y = 2;
    //wrefresh(menu_win);

    for (auto i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            //mvwaddwstr(menu_win, y, x, choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            //mvwaddwstr(menu_win, y, x, choices[i]);
        }
        y += 2;
    }
    box(menu_win, '|', 0);
    usleep(8000);
    wrefresh(menu_win);
}

void printmenu2(WINDOW *menu_win, int highlight, char *choices[], int n_choices) {
    int x = 2;
    int y = 2;
    //box(menu_win, 1, 0);
    for (auto i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        y += 5;
    }
    usleep(8000);
    wrefresh(menu_win);
}

int main_menu() {
    clear();
    int highlight = 1;
    int choice = 0;
    //创建主选项菜单
    WINDOW *main_menu_win = newwin(main_menu_size_y, main_menu_size_x, (max_y - main_menu_size_y) / 2,
                                   (max_x - main_menu_size_x) / 2);
    keypad(main_menu_win, TRUE);
    mvprintw((max_y - main_menu_size_y) / 2 - 2, (max_x - main_menu_size_x) / 2 + 1, "请使用方向键来选择,回车确认");
    refresh();
    //printmenu(main_menu_win, 2, main_menu_choices, n_main_menu_choices);
    //printmenu(main_menu_win, highlight, main_menu_choices, n_main_menu_choices);
    wrefresh(main_menu_win);
    printmenu(main_menu_win, highlight, main_menu_choices, n_main_menu_choices);
    refresh();
    while (true) {
        int c = wgetch(main_menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_main_menu_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_main_menu_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        printmenu(main_menu_win, highlight, main_menu_choices, n_main_menu_choices);
        if (choice != 0)    /* User did a choice come out of the infinite loop */
        {
            break;
        }
    }
    //mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, main_menu_choices[choice - 1]);
    return choice;
}

int student_menu() {
    clear();
    int highlight = 1;
    int choice = 0;
    mvvline(0, 30, '|', max_y);
    //创建主选项菜单
    WINDOW *student_menu_win = newwin(20, 18, 5, 0);
    //(max_x - main_menu_size_x) / 2);
    keypad(student_menu_win, TRUE);
    //mvprintw((max_y - main_menu_size_y) / 2 - 2, (max_x - main_menu_size_x) / 2 + 1, "请 使 用 方 向 键 来 选 择 ，回 车 确 认 ");
    refresh();
    printmenu2(student_menu_win, 1, student_menu_choices, n_student_menu_choices);
    while (true) {
        int c = wgetch(student_menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_student_menu_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_student_menu_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        printmenu2(student_menu_win, highlight, student_menu_choices, n_student_menu_choices);
        if (choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }
    //mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, main_menu_choices[choice - 1]);
    return choice;
}

int teacher_menu() {
    clear();
    int highlight = 1;
    int choice = 0;
    mvvline(0, 18, '|', max_y);
    //创建主选项菜单
    WINDOW *teacher_menu_win = newwin(20, 18, 5, 0);
//    WINDOW *teacher_menu_win = newwin(main_menu_size_y, main_menu_size_x, (max_y - main_menu_size_y) / 2,
//                                      (max_x - main_menu_size_x) / 2);
    keypad(teacher_menu_win, TRUE);
    //mvprintw((max_y - main_menu_size_y) / 2 - 2, (max_x - main_menu_size_x) / 2 + 1, "请 使 用 方 向 键 来 选 择 ，回 车 确 认 ");
    refresh();
    printmenu2(teacher_menu_win, 1, teacher_menu_choices, n_teacher_menu_choices);
    while (true) {
        int c = wgetch(teacher_menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_teacher_menu_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_teacher_menu_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        printmenu2(teacher_menu_win, highlight, teacher_menu_choices, n_teacher_menu_choices);
        if (choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }
    //mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, main_menu_choices[choice - 1]);
    return choice;
}

int admin_menu() {
    clear();
    int highlight = 1;
    int choice = 0;
    mvvline(0, 18, '|', max_y);
    //创建主选项菜单
    WINDOW *admin_menu_win = newwin(20, 18, 5, 0);
    keypad(admin_menu_win, TRUE);
    //mvprintw((max_y - main_menu_size_y) / 2 - 2, (max_x - main_menu_size_x) / 2 + 1, "请 使 用 方 向 键 来 选 择 ，回 车 确 认 ");
    refresh();
    printmenu2(admin_menu_win, 1, admin_menu_choices, n_admin_menu_choices);
    while (true) {
        int c = wgetch(admin_menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_admin_menu_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_admin_menu_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        printmenu2(admin_menu_win, highlight, admin_menu_choices, n_admin_menu_choices);
        if (choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }
    //mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, main_menu_choices[choice - 1]);
    return choice;
}

void window_floor_test(const char *text) {
    WINDOW *test_win = newwin(10, 80, 10, 20);
    keypad(test_win, true);
    mvwprintw(test_win, 5, 5, text);
    box(test_win, 0, 0);
    wrefresh(test_win);
    while (true) {
        int c = wgetch(test_win);
        switch (c) {
            case 10:
                return;
            default:
                continue;
        }
    }
}

void show_warning_win(const char *waring_text) {
//    WINDOW *warning_win = newwin(10, 80, 10, 50);
//    wclear(warning_win);
//    keypad(warning_win, true);
//    mvwprintw(warning_win, 5, 25, waring_text);
//    //mvwaddnwstr(warning_win, 5, 5, L"警 告 ", 4);
//    //mvwaddwstr(warning_win,5,5,L"啊啊啊");
//    box(warning_win, 0, 0);
//    wrefresh(warning_win);
//    refresh();
//    while (!wgetch(warning_win));
    MessageBox(NULL, waring_text, "警告", MB_OK);
    return;
}