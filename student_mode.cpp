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
        newtListboxAppendEntry(list, "查看待选课程信息", &q);
        newtListboxAppendEntry(list, "选课变更", &r);
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
                student_overlook();
                break;
            case 3:
                student_modify();
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
    if (!index) {
        show_warning_win("找不到您的个人信息");
        return;
    }
    student_t s = student_list[index];
    char text[512] = {0};
    wchar_t sex = s.sex ? L'女' : L'男';
    pNode myclass = s.student_class_link_head->next; //TODO:把添加class的teacher信息
    sprintf(text, "姓名:%s\n学号:%d\n性别:%lc\n已获得学分:%d\n已选课程:\n", s.name, s.ID, sex, s.credits);
    while (myclass) {
        sprintf(text + strlen(text), "课程名:%s \t成绩:未公布\n", get_itemRef_by_ID<class_t>(myclass->targetID).name);
        myclass = myclass->next;
    }
    newtComponent form, t, button;
    t = newtTextboxReflowed(1, 1, text, 64, 5, 5, 0);
    newtCenteredWindow(100, 20, "学生信息");
    button = newtButton(45, 16, "返回");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, t, button, NULL);
    newtRunForm(form);
    newtFormDestroy(form);
}

void student_modify() {
    auto &s = get_itemRef_by_ID<student_t>(myID);
    if (s.ID == 0) {
        show_warning_win("找不到您的个人信息");
        return;
    }
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
    uint32_t end_id = get_max_ID(class_list);//获取上下界，减少次数
    for (uint32_t id = start_id; id <= end_id; id++) {
        class_t c = get_itemRef_by_ID<class_t>(id);
        if (c.ID && !c.type) {
            int flag = 0;
            for (pNode p = s.student_class_link_head->next; p; p = p->next) {
                if (c.ID == p->targetID) {
                    flag = NEWT_FLAG_SELECTED;
                    break;
                }
            }
            char info[64]{};
            sprintf(info, "%s  \t(%s)", c.name, c.type ? "选修" : "必修");
            newtCheckboxTreeAddItem(checkboxTree, info, (void *) (c.ID), flag, NEWT_ARG_APPEND, NEWT_ARG_LAST);
            count++;
        }
    }
    for (uint32_t id = start_id; id <= end_id; id++) {
        class_t c = get_itemRef_by_ID<class_t>(id);
        if (c.ID && c.type) {
            int flag = 0;
            for (pNode p = s.student_class_link_head->next; p; p = p->next) {
                if (c.ID == p->targetID) {
                    flag = NEWT_FLAG_SELECTED;
                    break;
                }
            }
            char info[64]{};
            sprintf(info, "%s  \t(%s)", c.name, c.type ? "选修" : "必修");
            newtCheckboxTreeAddItem(checkboxTree, info, (void *) (c.ID), flag, NEWT_ARG_APPEND, NEWT_ARG_LAST);
            count++;
        }
    }
    button1 = newtButton(10, 15, "提交");
    button2 = newtButton(35, 15, "取消");

    newtFormAddComponents(form, checkboxTree, button1, button2, NULL);
    answer = newtRunForm(form);
    uint32_t selected_id[32] = {0};
    if (answer == button1) {
        result = newtCheckboxTreeGetSelection(checkboxTree, &numselected);
        ptr = result;
        for (int i = 0; i < numselected; i++) {
            selected_id[i] = *((uint32_t *) ptr++);
        }
        if (!policy_check(selected_id)) {
            pNode newhead = list_create(0);
            for (uint32_t *p = selected_id; *p; p++) {
                list_append(newhead, *p);
            }
            list_del_all(get_itemRef_by_ID<student_t>(myID).student_class_link_head);
            get_itemRef_by_ID<student_t>(myID).student_class_link_head = newhead;
            show_info_win("成功");
        }
    } else {
        char text[32]{};
        show_info_win("您已取消");
    }
    newtFormDestroy(form);

}

void student_overlook() {
    uint32_t ustart_id = get_min_ID(class_list);
    uint32_t uend_id = get_max_ID(class_list);
    uint32_t count = 0;
    for (uint32_t id = ustart_id; id <= uend_id; id++) {
        if (get_itemRef_by_ID<class_t>(id).ID) {
            count++;
        }
    }
    uint32_t zero_return = 0;
    uint32_t *index = (uint32_t *) malloc(count * sizeof(uint32_t));
    memset(index, 0, count * sizeof(uint32_t));


    //开始做列表的渲染,默认是升序的
    newtRefresh();
    newtCls();
    newtRefresh();
    newtCenteredWindow(80, 30, "浏览待选课程");
    uint32_t current = 1;
    while (1) {
        newtComponent form2, list;
        form2 = newtForm(NULL, NULL, 0);
        list = newtListbox(1, 1, 28, NEWT_ENTRY_RETURNEXIT);
        newtListboxSetWidth(list, 48);
        class_t c;
        char text[64]{};
        newtListboxAppendEntry(list, "返回", &zero_return);

        uint32_t t = 0;
        for (uint32_t id = ustart_id; id <= uend_id; id++) {
            c = class_list[get_index_by_ID(id, class_list)];
            if (c.ID) {
                sprintf(text, "ID:%d \t课程名称:%s", c.ID, c.name);
                newtListboxAppendEntry(list, text, index + t);
                index[t++] = c.ID;
                memset(text, 0, 64);
            }
        }
        newtListboxSetCurrent(list, (int) current);
        newtFormAddComponents(form2, list, NULL);
        newtRunForm(form2);
        current = (uint32_t *) newtListboxGetCurrent(list) - index + 1;
        uint32_t result_id = *(uint32_t *) newtListboxGetCurrent(list);
        if (!result_id) {
            newtFormDestroy(form2);
            free(index);
            return;
        } else {
            const class_t &C = get_itemRef_by_ID<class_t>(result_id);
            pNode ct = C.class_teacher_link_head->next;
            pNode cr = C.class_resource_link_head->next;
            char text2[256] = {0};
            //渲染文本
            sprintf(text2, "课程名称:%s(%s)\n", C.name, C.type ? "选修" : "必修");
            sprintf(text2 + strlen(text2), "学分:%.1f\n", C.credits);
            sprintf(text2 + strlen(text2), "教师:");
            for (pNode p = ct; p; p = p->next) {
                sprintf(text2 + strlen(text2), "%s ", get_itemRef_by_ID<teacher_t>(p->targetID).name);
            }
            sprintf(text2 + strlen(text2), "\n");
            sprintf(text2 + strlen(text2), "时间地点:\n");
            for (pNode p = cr; p; p = p->next) {
                const resource_t &r = get_itemRef_by_ID<resource_t>(p->targetID);
                sprintf(text2 + strlen(text2), "周%lc第%2d节\t%s\n", WEEK[r.day], r.rank, r.name);
            }
            show_info_win(text2);
        }
        newtFormDestroy(form2);
    }
}

int policy_check(uint32_t *select_id) {
    //先检查必修课是不是都选上了
    uint32_t start_id = get_min_ID(class_list);
    uint32_t end_id = get_max_ID(class_list);//获取上下界，减少次数
    float credits = 0.0f;
    for (uint32_t id = start_id; id <= end_id; id++) {
        if (get_itemRef_by_ID<class_t>(id).ID == 0) continue;
        if (get_itemRef_by_ID<class_t>(id).type == 0) {
            uint32_t *p;
            for (p = select_id; *p; p++) {
                if (*p != id) {
                    continue;
                } else {
                    break;
                }
            }
            if (!*p) {
                show_warning_win("您有必修课未选!");
                return 1;
            } else {
                credits += get_itemRef_by_ID<class_t>(id).credits;
            }
        } else {
            uint32_t *p;
            for (p = select_id; *p; p++) {
                if (*p != id) {
                    continue;
                } else {
                    credits += get_itemRef_by_ID<class_t>(id).credits;
                    break;
                }
            }
        }
    }
    if (credits < 28) {
        show_warning_win("学分没选够!");
        return 1;
    }
    //时间冲突检查
    for (uint32_t *p1 = select_id; *p1; p1++) {
        pNode head1 = get_itemRef_by_ID<class_t>(*p1).class_resource_link_head->next;
        for (uint32_t *p2 = p1 + 1; *p2; p2++) {
            pNode head2 = get_itemRef_by_ID<class_t>(*p2).class_resource_link_head->next;
            for (pNode r1 = head1; r1; r1 = r1->next) {
                for (pNode r2 = head2; r2; r2 = r2->next) {
                    if (resource_cmp(get_itemRef_by_ID<resource_t>(r1->targetID),
                                     get_itemRef_by_ID<resource_t>(r2->targetID)) == 0) {
                        show_warning_win("有时间冲突，自己查一下");
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

#pragma clang diagnostic pop
