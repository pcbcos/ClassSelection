#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"
//
// Created by cosine on 2022/3/2.
//

#include "student_mode.h"

void student_mode() {
    do {
        int p = 1, q = 2, r = 3, s = 4, *u;
        newtCls();
        newtComponent list, form;
        newtCenteredWindow(50, 10, "学生模式-请选择您的操作");
        list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
        newtListboxAppendEntry(list, "查询课程信息、成绩", &p);
        newtListboxAppendEntry(list, "选课变更", &q);
//newtListboxAppendEntry(list, "退课", &r);
        newtListboxAppendEntry(list, "退出", &r);
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
//            case 3:
//                student_delclass();
//                break;
            case 3:
                return;
        }
    } while (1);
}

void student_querry() {
    newtCls();
    newtRefresh();
    uint32_t index = get_index_by_ID(myID, student_list);
    student_t s = student_list[index];
    char text[256] = {0};
    wchar_t sex = s.sex ? L'女' : L'男';
    pNode myclass = s.student_class_link_head->next; //TODO:把添加class的teacher信息
    sprintf(text, "姓名:%s\n学号:%d\n性别:%lc\n已获得学分:%d\n已选课程:\n", s.name, s.ID, sex, s.credits);
    while (myclass) {
        sprintf(text + strlen(text), "课程名:%s \t成绩:未公布\n", get_itemRef_by_ID<class_t>(myclass->targetID).name);
        myclass = myclass->next;
    }
    newtComponent form, t, button;
    t = newtTextboxReflowed(1, 1, text, 30, 5, 5, 0);
    newtCenteredWindow(100, 20, "学生信息");
    button = newtButton(45, 16, "返回");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, t, button, NULL);
    newtRunForm(form);
    newtFormDestroy(form);
}

void student_modify() {
    auto &s = get_itemRef_by_ID<student_t>(myID);
    newtCls();
    newtRefresh();
    newtCenteredWindow(50, 20, "学生选课");
    newtComponent form, checkboxTree, button1, button2, answer;
    form = newtForm(NULL, NULL, 0);
    int cbvalue = 0;
    int numselected;
    const void **result;
    const void **ptr;
    checkboxTree = newtCheckboxTreeMulti(10, 3, 10, " *", NEWT_FLAG_SCROLL);
    newtCheckboxTreeSetWidth(checkboxTree, 32);

    int count = 0;
    uint32_t start_id = get_min_ID(class_list);
    uint32_t end_id = get_max_ID(class_list);
    for (uint32_t id = start_id; id <= end_id; id++) {
        class_t c = get_itemRef_by_ID<class_t>(id);
        if (c.ID) {
            newtCheckboxTreeAddItem(checkboxTree, c.name, (void *) &count, 0, NEWT_ARG_APPEND, NEWT_ARG_LAST);
            count++;
        }
    }
    button1 = newtButton(10, 15, "提交");
    button2 = newtButton(35, 15, "取消");

    newtFormAddComponents(form, checkboxTree, button1, button2, NULL);

    answer = newtRunForm(form);
    if (answer == button1) {
        result = newtCheckboxTreeGetSelection(checkboxTree, &numselected);
        ptr = result;
        char text[32]{};
        sprintf(text, "%d", numselected);
        show_info_win(text);
    } else {
        char text[32]{};
        show_info_win("您已取消");
    }


}

void student_delclass() { ; }

#pragma clang diagnostic pop
