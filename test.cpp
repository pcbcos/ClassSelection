#include <newt.h>
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <cstring>

void rootwin_show() {
    newtCls();
    /* 请观察 left,top 为正数 , 为负数地情形 */
    newtDrawRootText(0, 0, "左上角");
    newtDrawRootText(-6, 0, "右上角");
    newtDrawRootText(0, -3, "左下角");
    newtDrawRootText(-6, -3, "右下角");
    /* 注意 helpline 缺省时的内容 */
    newtPushHelpLine(NULL);
    newtRefresh();
    sleep(10);
    newtPushHelpLine("我的帮助行");
    newtRefresh();
    sleep(3);
    newtPopHelpLine();
    newtRefresh();
    sleep(1);
}

//void student_mode1() {
//    newtComponent form, label, entry, button, cb;
//    char *entryValue;
//    newtCls();
//    newtCenteredWindow(50, 10, "");
//    /*left,top 是相对于中心窗口而言 */
//    label = newtLabel(10, 1, "请输入 :");
//    entry = newtEntry(19, 1, NULL, 20, (const char **) &entryValue, NEWT_FLAG_SCROLL);
//    newtEntrySet(entry, "\0", 0);
//    button = newtButton(10, 5, "完全按钮");
//    cb = newtCompactButton(25, 5, "紧缩按钮");
//    form = newtForm(NULL, NULL, 0);
//    newtFormAddComponents(form, label, entry, button, cb, NULL);
//    newtRunForm(form);
//    if (*entryValue != '\0') {
//        newtDrawRootText(0, 0, "你输入了 :");
//        newtDrawRootText(12, 0, entryValue);
//    } else
//        newtDrawRootText(0, 0, "无输入 !");
//    newtRefresh();
//    newtFormDestroy(form);
//    sleep(5);
//}
void student_querry() { ; }

void student_modify() { ; }

void student_overlook() { ; }

void student_mode() {
    int p = 1, q = 2, r = 3, s = 4, *u;
    newtComponent list, form;
    newtCenteredWindow(50, 10, "管理员模式-请选择您的操作");
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
            student_modify();
            break;
        case 3:
            student_overlook();
            break;
        case 4:
            return;
    }
}

void admin_lookover() { ; }

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
    newtFormAddComponents(form, label1, label2, entry, rb[0], rb[1], rb[2], button,NULL);
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

void admin_modify() { ; }

void admin_addentity() { ; }

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
            admin_addentity();
            break;
        case 5:
            return;
    }


}

void check_radio() {
    newtComponent form, checkbox, rb[3], button, lable1, lable2;
    char cbValue, cv[2];
    int i;
    newtCls();
    newtOpenWindow(10, 8, 40, 11, "检查盒与单选盒演示");
    lable1 = newtLabel(2, 1, "检查盒 :");
    checkbox = newtCheckbox(10, 1, "A checkbox", ' ', " *X", &cbValue);
    lable2 = newtLabel(2, 4, "单选盒 :");
    rb[0] = newtRadiobutton(10, 3, "Choice 1", 1, NULL);
    rb[1] = newtRadiobutton(10, 4, "Choice 2", 0, rb[0]);
    rb[2] = newtRadiobutton(10, 5, "Choice 3", 0, rb[1]);
    button = newtButton(15, 7, "退出");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponent(form, checkbox);
    newtFormAddComponent(form, lable1);
    newtFormAddComponent(form, lable2);
    for (i = 0; i < 3; i++)
        newtFormAddComponent(form, rb[i]);
    newtFormAddComponent(form, button);
    newtPushHelpLine("< 空格健 > 选择");
    newtRefresh();
    newtRunForm(form);
    for (i = 0; i < 3; i++)
        if (newtRadioGetCurrent(rb[0]) == rb[i]) {
            newtDrawRootText(0, 0, "单选盒 :");
            newtDrawRootText(9, 0, "第");
            if (i == 0)newtDrawRootText(11, 0, "1");
            if (i == 1)newtDrawRootText(11, 0, "2");
            if (i == 2)newtDrawRootText(11, 0, "3");
            newtDrawRootText(12, 0, "个");
        }
    newtDrawRootText(0, 3, "检查盒状态 :");
    cv[0] = cbValue;
    cv[1] = '\0';
    newtDrawRootText(13, 3, cv);
    newtRefresh();
    newtFormDestroy(form);
    sleep(5);
}

void test() {
    char message[] = "This is a pretty long message. It will be displayed "
                     "in a newt textbox, and illustrates how to construct "
                     "a textbox from arbitrary text which may not have "
                     "very good line breaks.\n\n"
                     "Notice how literal \\n characters are respected, and "
                     "may be used to force line breaks and blank lines.";
    newtComponent form, text, button;
    newtCls();
    text = newtTextboxReflowed(1, 1, message, 30, 5, 5, 0);
    button = newtButton(12, newtTextboxGetNumLines(text) + 2, "退出");
    newtOpenWindow(10, 5, 37,
                   newtTextboxGetNumLines(text) + 7, "文本盒");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, text, button, NULL);
    newtRunForm(form);
    newtFormDestroy(form);
}

int main(int argc, char *args[]) {

    newtComponent list, fm;
    int p = 1, q = 2, r = 3, s = 4, t = 5, *u;
    newtInit();
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
                //student_mode();
                check_radio();
//                newtCheckboxTree()
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                check_radio();
                break;
            case 4:
                newtFinished();
                exit(0);
        }
    } while (1);
}