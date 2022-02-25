#include "main.h"

uint32_t ID;

void student_mode() {
    int p = 1, q = 2, r = 3, s = 4, *u;
    newtComponent list, form;
    newtCenteredWindow(50, 10, "学生模式-请选择您的操作");
    list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
    newtListboxAppendEntry(list, "查询课程信息、成绩", &p);
    newtListboxAppendEntry(list, "选课", &q);
    newtListboxAppendEntry(list, "退课", &r);
    newtListboxAppendEntry(list, "退出", &s);
    newtPushHelpLine(" Move using the arrow keys and press ENTER to select");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponent(form, list);
    newtRunForm(form);
    u = (int *) newtListboxGetCurrent(list);
    newtPopWindow();
    newtFormDestroy(form);
    switch (*u) {
        case 1:
            student_querry();
            break;
        case 2:
            student_addclass();
            break;
        case 3:
            student_delclass();
            break;
        case 4:
            return;
    }
}


void admin_querry() {
    newtComponent form, label1, label2, entry, button, rb[3];
    char *entryValue;
    newtCls();
    newtCenteredWindow(50, 10, "管理员模式-查询记录");
    /*left,top 是相对于中心窗口而言 */
    label1 = newtLabel(10, 1, "请输入查询信息:");
    entry = newtEntry(25, 1, "小明", 20, (const char **) &entryValue, NEWT_FLAG_SCROLL);
    newtEntrySet(entry, "\0", 0);
    button = newtButton(22, 5, "确认");
    form = newtForm(NULL, NULL, 0);

    label2 = newtLabel(5, 3, "查询类别:");
    rb[0] = newtRadiobutton(10, 3, "学生", 1, NULL);
    rb[1] = newtRadiobutton(20, 3, "课程", 0, rb[0]);
    rb[2] = newtRadiobutton(30, 3, "教师", 0, rb[1]);
    newtFormAddComponents(form, label1, label2, entry, rb[0], rb[1], rb[2], button, NULL);
    newtPushHelpLine("< 空格健 > 选择");
    newtRunForm(form);
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rb[0]) == rb[i]) {
            newtDrawRootText(0, 2, "您查询的类别是:");
            if (i == 0)newtDrawRootText(16, 2, "学生");
            if (i == 1)newtDrawRootText(16, 2, "课程");
            if (i == 2)newtDrawRootText(16, 2, "教师");
        }
    }


    if (*entryValue != '\0') {
        newtDrawRootText(0, 0, "你查询的字段是:");
        newtDrawRootText(16, 0, entryValue);
    } else
        newtDrawRootText(0, 0, "无输入 !");
    newtRefresh();
    newtFormDestroy(form);
    sleep(10);
}


void admin_mode() {
    int p = 1, q = 2, r = 3, s = 4, a = 5, b = 6, *u;
    newtComponent list, form;
    newtCls();
    newtRefresh();
    newtDrawRootText(100, 0, "管理员模式");

    newtCenteredWindow(50, 10, "管理员模式-请选择您的操作");
    list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
    newtListboxAppendEntry(list, "浏览记录", &p); //1
    newtListboxAppendEntry(list, "查询记录", &q); //2
    newtListboxAppendEntry(list, "修改记录", &r);//3
    newtListboxAppendEntry(list, "添加课程", &s);//4
    newtListboxAppendEntry(list, "退出", &a);
    newtPushHelpLine(" Move using the arrow keys and press ENTER to select");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponent(form, list);
    newtRunForm(form);
    u = (int *) newtListboxGetCurrent(list);
    newtPopWindow();
    newtFormDestroy(form);
    switch (*u) {
        case 1:
            admin_lookover();
            break;
        case 2:
            admin_querry();
            break;
        case 3:
            admin_modify();
            break;
        case 4:
            admin_addclass();
            break;
        case 5:
            return;
    }
}


int main() {
#define TEST_MENU 0
#if TEST_MENU
    newtInit();
    login();
    newtComponent list, fm;
    int p = 1, q = 2, r = 3, s = 4, t = 5, *u;
    do {
        newtCls();
        newtRefresh();
        newtDrawRootText(100, 0, "这是我的学生选课系统");
        newtCenteredWindow(50, 10, "请选择");
        list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
        newtListboxAppendEntry(list, "学生模式", &p);
        newtListboxAppendEntry(list, "管理员模式", &q);
        newtListboxAppendEntry(list, "退出系统", &s);
        newtPushHelpLine(" Move using the arrow keys and press ENTER to select");
        fm = newtForm(NULL, NULL, 0);
        newtFormAddComponents(fm, list, NULL);
        newtRunForm(fm);
        u = (int *) newtListboxGetCurrent(list);
        newtPopWindow();
        newtFormDestroy(fm);
        switch (*u) {
            case 1:
                student_mode();
                break;
            case 2:
                admin_mode();
                break;
            case 4:
                newtFinished();
                printf("ID=%d\n",ID);
                exit(0);
        }
    } while (1);
#else
    read_student_data();
//    for (auto &s: student_list) {
//        if (s.ID) {
//            printf("NAME=%s,ID=%d\n", s.name, s.ID);
//        }
//    }
    uint32_t index = get_index_by_ID(19201022, student_list);
    if(index){
        student_t s=student_list[index];
        printf("name=%s,ID=%d",s.name,s.ID);
    }

#endif
    return 0;
}

void login() {
    //newtInit();
    newtCls();
    newtRefresh();
    newtCenteredWindow(100, 10, "请输入帐号密码");
    newtComponent form, label1, label2, entry1, entry2, button;
    char *id = (char *) malloc(16);
    char *passwd = (char *) malloc(16);
    memset(id, 0, 16);
    memset(passwd, 0, 16);
    button = newtButton(45, 6, "登录");
    label1 = newtLabel(35, 3, "ID");
    label2 = newtLabel(35, 4, "密码");
    entry1 = newtEntry(40, 3, "19201022", 20, (const char **) &id, NEWT_FLAG_SCROLL);
    entry2 = newtEntry(40, 4, "kalium1910", 20, (const char **) &passwd, NEWT_FLAG_SCROLL | NEWT_FLAG_PASSWORD);
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label1, label2, entry1, entry2, button, NULL);
    newtRunForm(form);
    ID = atoi(id);
    if (strcmp(id, "19201022") == 0 and strcmp(passwd, "kalium1910") == 0) {
        newtRefresh();
        newtFormDestroy(form);
        return;
    } else {
        newtFinished();
        printf("%s", id);
        exit(1);
    }
}

void student_querry() {
    newtCls();
    newtRefresh();
    uint32_t index = get_index_by_ID(ID, student_list);
}

void student_addclass() { ; }

void student_delclass() { ; }


void admin_lookover() { ; }

void admin_modify() { ; }

void admin_addclass() { ; }

