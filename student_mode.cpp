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
    } while (1);
}

void student_querry() {
    newtCls();
    newtRefresh();
    uint32_t index = get_index_by_ID(myID, student_list);
    student_t s = student_list[index];
    char text[256] = {0};
    wchar_t sex = s.sex ? L'女' : L'男';
    pNode myclass=s.student_class_link_head->next; //TODO:把添加class的teacher信息
    sprintf(text, "姓名:%s\n学号:%d\n性别:%lc\n已获得学分:%d\n已选课程:\n", s.name, s.ID, sex, s.credits);
    while(myclass){
        sprintf(text+ strlen(text),"课程名:%s \t成绩:未公布\n", get_itemRef_by_ID<class_t>(myclass->targetID).name);
        myclass=myclass->next;
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

void student_addclass() {
    auto& s= get_itemRef_by_ID<student_t>(myID);
    newtCls();
    newtRefresh();
    newtCenteredWindow(50,20,"学生选课");
    newtComponent form,checkboxTree;
    form= newtForm(NULL,NULL,0);
    int cbvalue=0;
    int numselected;
    const void **result;
    void** ptr;
    checkboxTree= newtCheckboxTreeMulti(1,1,10," *",NEWT_FLAG_SCROLL);
    newtCheckboxTreeSetWidth(checkboxTree,32);
    newtCheckboxTreeAddItem(checkboxTree,"text1",(void*)2,NEWT_FLAG_SELECTED,NEWT_ARG_APPEND,NEWT_ARG_LAST);
    newtCheckboxTreeAddItem(checkboxTree,"text2",(void*)3,NEWT_FLAG_SELECTED,NEWT_ARG_APPEND,NEWT_ARG_LAST);
    result=newtCheckboxTreeGetSelection(checkboxTree,&numselected);
    newtFormAddComponent(form,checkboxTree);

    newtRunForm(form);

}

void student_delclass() { ; }
#pragma clang diagnostic pop