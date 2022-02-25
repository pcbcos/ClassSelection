////
//// Created by wengz on 2022/2/9.
////
//
//#include <clocale>
//#include <iostream>
//#include "DataBase.h"
//#include "LinkList.h"
//#include "cstring"
//#include "cstdlib"
//#include "unordered_map"
//#include "newt.h"
//
//int max_x, max_y;
//
////void whiptail() {
////    FILE *stream;
////    char buf[20];
////    memset(buf, 0, sizeof(buf));
////    stream=popen("whiptail --menu 中文测试 0 0 2 a 中文 b 英文  --nocancel","r");
////
////    fread(buf, 20, 1,stream);
////    printf("the result is %s",buf);
////    fclose(stream);
////}
//
//auto main(int argc, char *args[]) -> int {
//    //setlocale(LC_ALL,"zh-CN");
////    printf("你好\n");
////    char text[]="你好";
////    printf("%d\n",sizeof(Biweekly));
////    for(auto i: text){
////        printf("%d\n",i);
////    }
////    read_student_data();
////    std::cout << student_num << std::endl;
////    for (int i = 0; i <= 100; i++) {
////        std::cout << student_list[i].name << ((student_list[i].ID ^ 31415927) % MAX_STUDENT_NUM) << std::endl;
////    }
////    std::cout << get_index_by_ID(19211606, student_list) << std::endl;
////    std::cout << student_list[1174].ID << student_list[1174].name << std::endl;
////
////    read_class_data();
////    for (const auto &i: class_list) {
////        if (i.ID != 0)
////            std::cout << i.ID << "  " << i.name << "  " << i.credits << std::endl;
////    }
////    auto temp = class_list[get_index_by_ID(235, class_list)];
////    std::cout << temp.ID << "  " << temp.name << "  " << temp.credits << std::endl;
//    //whiptail();
////    newtInit();
////    newtCls();
////    newtDrawRootText(10,10,"abc");
////    getchar();
////    newtFinished();
////    //getchar();
////    return 0;
//}

#include <newt.h>
#include <stdio.h>
#include <stdlib.h>
#include <csignal>
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

void student_mode() {
    newtComponent form, label, entry, button, cb;
    char *entryValue;
    newtCls();
    newtCenteredWindow(50, 10, "");
    /*left,top 是相对于中心窗口而言 */
    label = newtLabel(10, 1, "请输入 :");
    entry = newtEntry(19, 1, NULL, 20, (const char **) &entryValue, NEWT_FLAG_SCROLL);
    newtEntrySet(entry, "\0", 0);
    button = newtButton(10, 5, "完全按钮");
    cb = newtCompactButton(25, 5, "紧缩按钮");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label, entry, button, cb, NULL);
    newtRunForm(form);
    if (*entryValue != '\0') {
        newtDrawRootText(0, 0, "你输入了 :");
        newtDrawRootText(12, 0, entryValue);
    } else
        newtDrawRootText(0, 0, "无输入 !");
    newtRefresh();
    newtFormDestroy(form);
    sleep(5);
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
        newtListboxAppendEntry(list, "教师模式", &q);
        newtListboxAppendEntry(list, "管理员模式", &r);
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
                rootwin_show();
                break;
            case 2:
                student_mode();
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