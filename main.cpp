#include <cstdio>
#include <cstring>
#include <clocale>
#include "LinkList.h"
#include "DataBase.h"
#include "curses.h"
#include "menus.h"
#include "cstring"

int max_x, max_y;

void init() {
    initscr();
    clear();
    noecho();
    cbreak();
    refresh();
//    LINES=50;
//    COLS=170;
}

void end() {

    clrtoeol();
    refresh();
    //getch();
    endwin();
}


int main(int argc, char *args[]) {
    if (argc != 3) {
        printf("请输入正确的账号密码!\n");
        getchar();
        return 1;
    } else {
        if (strcmp(args[1], "wengzy1920") == 0 && strcmp(args[2], "kalium1910") == 0) { ;
        } else {
            printf("账号密码无效!\n");
            getchar();
            return 2;
        }
    }
    init();
    max_x = 170;//getmaxx(stdscr);
    max_y = 40;//getmaxy(stdscr);
    while (true) {
        int next = main_menu();//主菜单
        switch (next) {
            case 1:
                if (student_menu() == 4) {
                    continue;
                }
                break;
            case 2:
                if (teacher_menu() == 2) {
                    continue;
                }
                break;
            case 3:
                if (admin_menu() == 4) {
                    continue;
                }
                break;
            case 4:
                //window_floor_test("您 的 输 入 有 误 ");
                show_warning_win("您 的 输 入 有 误 ");
                //show_warning_win("123");
                goto EXIT;
                break;
        }
    }

    EXIT:
    end();
//    class_t c= class_loader("ID:123 name:pcbcos的奇妙课堂 type:0 credits:4 max_stu:20 now_stu:10 time&&location:11|经信F1,12|经信F2");
//    ClassResourceLink in=c.class_resource_link_head;
//    class_resource_t t =*(class_resource_t*)(list_at(in,1));
//    printf("%s",t.location);
//    printclassinfo(c);
    return 0;
}


