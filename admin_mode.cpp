//
// Created by cosine on 2022/3/2.
//

#include "admin_mode.h"

void admin_mode() {
    int p = 1, q = 2, r = 3, s = 4, a = 5, b = 6, *u;
    do {
        newtComponent list, form;

        newtCls();
        newtRefresh();
        newtDrawRootText(100, 0, "管理员模式");

        newtCenteredWindow(50, 10, "管理员模式-请选择您的操作");
        list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
        newtListboxAppendEntry(list, "浏览记录", &p); //1
        newtListboxAppendEntry(list, "查询记录", &q); //2
        newtListboxAppendEntry(list, "修改记录", &r);//3
        newtListboxAppendEntry(list, "添加记录", &s);//4
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
    } while (1);
}

void admin_lookover() {
    newtCls();
    newtCenteredWindow(50, 12, "管理员模式-浏览");
    newtRefresh();
    newtComponent form, label1, label2, label3, entry1, entry2, button, rb[3];
    char *estart_ID;
    char *eend_ID;
    uint8_t type = 0;
    rb[0] = newtRadiobutton(12, 2, "学生", 1, NULL);
    rb[1] = newtRadiobutton(22, 2, "课程", 0, rb[0]);
    rb[2] = newtRadiobutton(32, 2, "教师", 0, rb[1]);

    label1 = newtLabel(2, 2, "检索类别:");
    label2 = newtLabel(2, 4, "起始ID:");
    label3 = newtLabel(2, 6, "结束ID:");

    entry1 = newtEntry(10, 4, "", 30, (const char **) &estart_ID, NEWT_FLAG_SCROLL);
    entry2 = newtEntry(10, 6, "", 30, (const char **) &eend_ID, NEWT_FLAG_SCROLL);
    newtEntrySet(entry1, "\0", 0);
    newtEntrySet(entry2, "\0", 0);
    button = newtButton(22, 8, "浏览");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, label1, label2, label3, rb[0], rb[1], rb[2], entry1, entry2, button, NULL);
    newtRunForm(form);
    char *start_id = newtEntryGetValue(entry1);
    char *end_id = newtEntryGetValue(entry2);
    uint8_t ALL = 0;
    uint32_t ustart_id = atoi(start_id);
    uint32_t uend_id = atoi(end_id);
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rb[0]) == rb[i]) {
            type = i;
        }
    }
    if (start_id[0] == '*' || end_id[0] == '*') {
        //输出所有
        ALL = 1;
        goto make_list;
    }



    //id合法性检验
    if (!ustart_id || !uend_id) {
        show_warning_win("ID非法,ID不能为0");
        newtComponentDestroy(form);
        return;
    }

//开始做列表的渲染,默认是升序的
    make_list:
    newtFormDestroy(form);
    newtRefresh();
    newtCls();
    newtRefresh();
    newtComponent form2, list;
    form2 = newtForm(NULL, NULL, 0);
    newtCenteredWindow(80, 30, "浏览模式");
    list = newtListbox(1, 1, 28, NEWT_ENTRY_RETURNEXIT);
    newtListboxSetWidth(list, 48);
    student_t s;
    teacher_t t;
    class_t c;
    char text[64]{};
    uint32_t *index;
    if (ALL) {
        switch (type) {
            case 0:
                ustart_id = get_min_ID(student_list);
                uend_id = get_max_ID(student_list);
                break;
            case 1:
                ustart_id = get_min_ID(class_list);
                uend_id = get_max_ID(class_list);
                break;
            case 2:
                ustart_id = get_min_ID(teacher_list);
                uend_id = get_max_ID(teacher_list);
                break;
        }
    }
    uint32_t zero_return = 0;
    newtListboxAppendEntry(list, "返回", &zero_return);
    switch (type) {
        case 0:
            for (uint32_t id = ustart_id; id <= uend_id; id++) {
                s = student_list[get_index_by_ID(id, student_list)];
                if (s.ID) {
                    sprintf(text, "ID:%d\t姓名:%s", s.ID, s.name);
                    newtListboxAppendEntry(list, text, (int *) &id);
                    memset(text, 0, 64);
                }
            }
            break;
        case 1:
            for (uint32_t id = ustart_id; id <= uend_id; id++) {
                c = class_list[get_index_by_ID(id, class_list)];
                if (c.ID) {
                    sprintf(text, "ID:%d\t课程名称:%s", c.ID, c.name);
                    newtListboxAppendEntry(list, text, index + id);
                    memset(text, 0, 64);
                }
            }
            break;
        case 2:
            for (uint32_t id = ustart_id; id <= uend_id; id++) {
                t = teacher_list[get_index_by_ID(id, teacher_list)];
                if (t.ID) {
                    sprintf(text, "ID:%d\t姓名:%s", t.ID, t.name);
                    newtListboxAppendEntry(list, text, index + id);
                    memset(text, 0, 64);
                }
            }
            break;
    }
//free(index);

    newtFormAddComponents(form2, list, NULL);
    newtRunForm(form2);
    newtFormDestroy(form2);



//    sleep(5);
}

void admin_querry() {
    newtComponent form, label1, label2, entry, button, rb[3], rankrule[3], label3;
    char *entryValue;

    newtCls();
    //newtCenteredWindow(50, 10, "管理员模式-修改记录");

    newtOpenWindow(100, 5, 50, 40, "查询结果");
    newtOpenWindow(40, 20, 50, 12, "管理员模式-查询记录");
    /*left,top 是相对于中心窗口而言 */
    label1 = newtLabel(10, 1, "请输入查询信息:");
    entry = newtEntry(25, 1, "小明", 20, (const char **) &entryValue, NEWT_FLAG_SCROLL);
    newtEntrySet(entry, "\0", 0);
    button = newtButton(22, 6, "确认");
    form = newtForm(NULL, NULL, 0);

    label2 = newtLabel(6, 3, "查询类别:");
    rb[0] = newtRadiobutton(15, 3, "学生", 1, NULL);
    rb[1] = newtRadiobutton(25, 3, "课程", 0, rb[0]);
    rb[2] = newtRadiobutton(35, 3, "教师", 0, rb[1]);

    label3 = newtLabel(6, 4, "排序依据:");
    rankrule[0] = newtRadiobutton(15, 4, "无序", 1, NULL);
    rankrule[1] = newtRadiobutton(25, 4, "ID升序", 0, rankrule[0]);
    rankrule[2] = newtRadiobutton(35, 4, "ID降序", 0, rankrule[1]);
    newtFormAddComponents(form, label1, label2, label3, entry, rb[0], rb[1], rb[2], rankrule[0], rankrule[1],
                          rankrule[2], button, NULL);

    newtPushHelpLine("< 空格健 > 选择");
    newtRunForm(form);
    uint8_t type = 0;
    uint8_t rank = 0;//是否排序,升序/降序
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rb[0]) == rb[i]) {
            newtDrawRootText(0, 2, "您查询的类别是:");
            if (i == 0) {
                newtDrawRootText(16, 2, "学生");
                type = 0;
            }
            if (i == 1) {
                newtDrawRootText(16, 2, "课程");
                type = 1;
            }
            if (i == 2) {
                newtDrawRootText(16, 2, "教师");
                type = 2;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rankrule[0]) == rankrule[i]) {
            newtDrawRootText(0, 3, "排序依据:");
            switch (i) {
                case 1:
                    newtDrawRootText(9, 3, "ID升序");
                    break;
                case 2:
                    newtDrawRootText(9, 3, "ID降序");
                    break;
                default:
                    newtDrawRootText(9, 3, "无序");
                    break;
            }
            rank = i;
        }
    }

    if (*entryValue != '\0') {
        newtDrawRootText(0, 0, "你查询的字段是:");
        newtDrawRootText(16, 0, entryValue);
        uint32_t id = atoi(entryValue);
        uint32_t *result = NULL;
        if (id) {
            switch (type) {
                case 0:
                    result = widesearch(id, NULL, student_list, rank);
                    break;
                case 1:
                    result = widesearch(id, NULL, class_list, rank);
                    break;
                case 2:
                    result = widesearch(id, NULL, teacher_list, rank);
                    break;
            }
        } else {
            switch (type) {
                case 0:
                    result = widesearch(0, entryValue, student_list, rank);
                    break;
                case 1:
                    result = widesearch(0, entryValue, class_list, rank);
                    break;
                case 2:
                    result = widesearch(0, entryValue, teacher_list, rank);
                    break;
            }
        }
        newtPopWindowNoRefresh();

        //渲染结果
        int current = 1;
        while (1) {
            newtComponent list, form2;
            size_t N;
            for (N = 0; result[N] != 0; N++);
            if (N == 0) {
                free(result);
                show_warning_win("找不到!");
                newtRefresh();
                newtFormDestroy(form);
                return;
            }
            list = newtListbox(1, 2, 16, NEWT_FLAG_RETURNEXIT);
            form2 = newtForm(NULL, NULL, 0);
            int *num = (int *) malloc(sizeof(int) * N);
            memset(num, 0, sizeof(int) * N);
            for (int i = 0; i < N; i++) {
                num[i] = i + 1;
            }
            int zero_return = 0;
            newtListboxAppendEntry(list, "退出", &zero_return);
            char itemtext[64]{};
            newtListboxSetWidth(list, 40);
            switch (type) {
                case 0: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t姓名:%s", student_list[result[i]].ID, student_list[result[i]].name);
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }
                    break;
                case 1: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t课程名称:%s(%s)", class_list[result[i]].ID, class_list[result[i]].name,
                                class_list[result[i]].type ? "选修" : "必修");
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }

                    break;
                case 2: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t姓名:%s", teacher_list[result[i]].ID, teacher_list[result[i]].name);
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }
                    break;
            }
            int *u = (int *) newtListboxGetCurrent(list);
            current = *u;
            if (!*u) { //按下退出
                if (result) {
                    free(result);
                }
                newtFormDestroy(form2);
                return;
            }
            char text[1024] = {0};
            student_t s;
            class_t C;
            teacher_t t;
            pNode ct;
            pNode cr;
            switch (type) {
                case 0:
                    s = student_list[result[*u - 1]];
                    sprintf(text, "ID:%d\n姓名:%s\n性别:%lc\n年龄:%d\n已获得学分:%d", s.ID, s.name, s.sex ? L'女' : L'男', s.age,
                            s.credits);
                    break;
                case 1:
                    C = class_list[result[*u - 1]];
                    ct = C.class_teacher_link_head->next;
                    cr = C.class_resource_link_head->next;

                    //渲染文本
                    sprintf(text, "课程名称:%s(%s)\n", C.name, C.type ? "选修" : "必修");
                    sprintf(text + strlen(text), "学分:%.1f\n", C.credits);
                    sprintf(text + strlen(text), "教师:");
                    for (pNode p = ct; p; p = p->next) {
                        sprintf(text + strlen(text), "%s ", get_itemRef_by_ID<teacher_t>(p->targetID).name);
                    }
                    sprintf(text + strlen(text), "\n");
                    sprintf(text + strlen(text), "时间地点:\n");
                    for (pNode p = cr; p; p = p->next) {
                        const resource_t &r = get_itemRef_by_ID<resource_t>(p->targetID);
                        sprintf(text + strlen(text), "周%lc第%2d节\t%s\n", WEEK[r.day], r.rank, r.name);
                    }
                    break;
                case 2:
                    t = teacher_list[result[*u - 1]];
                    sprintf(text, "ID:%d,姓名%s", t.ID, t.name);
                    break;
            }
            show_info_win(text);
            newtFormDestroy(form2);
            newtRefresh();
        }
    } else {
        show_warning_win("无输入");
    }

    newtFormDestroy(form);
    newtRefresh();

}

void admin_modify() {
    newtComponent form, label1, label2, entry, button, rb[3], rankrule[3], label3;
    char *entryValue;

    newtCls();
    //newtCenteredWindow(50, 10, "管理员模式-修改记录");

    newtOpenWindow(100, 5, 50, 40, "查询结果");
    newtOpenWindow(40, 20, 50, 12, "管理员模式-修改记录");
    /*left,top 是相对于中心窗口而言 */
    label1 = newtLabel(10, 1, "请输入查询信息:");
    entry = newtEntry(25, 1, "小明", 20, (const char **) &entryValue, NEWT_FLAG_SCROLL);
    newtEntrySet(entry, "\0", 0);
    button = newtButton(22, 6, "确认");
    form = newtForm(NULL, NULL, 0);

    label2 = newtLabel(6, 3, "查询类别:");
    rb[0] = newtRadiobutton(15, 3, "学生", 1, NULL);
    rb[1] = newtRadiobutton(25, 3, "课程", 0, rb[0]);
    rb[2] = newtRadiobutton(35, 3, "教师", 0, rb[1]);

    label3 = newtLabel(6, 4, "排序依据:");
    rankrule[0] = newtRadiobutton(15, 4, "无序", 1, NULL);
    rankrule[1] = newtRadiobutton(25, 4, "ID升序", 0, rankrule[0]);
    rankrule[2] = newtRadiobutton(35, 4, "ID降序", 0, rankrule[1]);
    newtFormAddComponents(form, label1, label2, label3, entry, rb[0], rb[1], rb[2], rankrule[0], rankrule[1],
                          rankrule[2], button, NULL);

    newtPushHelpLine("< 空格健 > 选择");
    newtRunForm(form);
    uint8_t type = 0;
    uint8_t rank = 0;//是否排序,升序/降序
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rb[0]) == rb[i]) {
            newtDrawRootText(0, 2, "您查询的类别是:");
            if (i == 0) {
                newtDrawRootText(16, 2, "学生");
                type = 0;
            }
            if (i == 1) {
                newtDrawRootText(16, 2, "课程");
                type = 1;
            }
            if (i == 2) {
                newtDrawRootText(16, 2, "教师");
                type = 2;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (newtRadioGetCurrent(rankrule[0]) == rankrule[i]) {
            newtDrawRootText(0, 3, "排序依据:");
            switch (i) {
                case 1:
                    newtDrawRootText(9, 3, "ID升序");
                    break;
                case 2:
                    newtDrawRootText(9, 3, "ID降序");
                    break;
                default:
                    newtDrawRootText(9, 3, "无序");
                    break;
            }
            rank = i;
        }
    }

    if (*entryValue != '\0') {
        newtDrawRootText(0, 0, "你查询的字段是:");
        newtDrawRootText(16, 0, entryValue);
        uint32_t id = atoi(entryValue);
        uint32_t *result = NULL;
        if (id) {
            switch (type) {
                case 0:
                    result = widesearch(id, NULL, student_list, rank);
                    break;
                case 1:
                    result = widesearch(id, NULL, class_list, rank);
                    break;
                case 2:
                    result = widesearch(id, NULL, teacher_list, rank);
                    break;
            }
        } else {
            switch (type) {
                case 0:
                    result = widesearch(0, entryValue, student_list, rank);
                    break;
                case 1:
                    result = widesearch(0, entryValue, class_list, rank);
                    break;
                case 2:
                    result = widesearch(0, entryValue, teacher_list, rank);
                    break;
            }
        }
        newtPopWindowNoRefresh();

        //渲染结果
        int current = 1;
        newtComponent list, form2;
        while (1) {
            size_t N;
            for (N = 0; result[N] != 0; N++);
            if (N == 0) {
                free(result);
                show_warning_win("找不到!");
                newtRefresh();
                newtFormDestroy(form);
                return;
            }
            list = newtListbox(1, 2, 16, NEWT_FLAG_RETURNEXIT);
            form2 = newtForm(NULL, NULL, 0);
            int *num = (int *) malloc(sizeof(int) * N);
            memset(num, 0, sizeof(int) * N);
            for (int i = 0; i < N; i++) {
                num[i] = i + 1;
            }
            int zero_return = 0;
            newtListboxAppendEntry(list, "退出", &zero_return);
            char itemtext[64]{};
            newtListboxSetWidth(list, 40);
            switch (type) {
                case 0: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t姓名:%s", student_list[result[i]].ID, student_list[result[i]].name);
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }
                    break;
                case 1: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t课程名称:%s(%s)", class_list[result[i]].ID, class_list[result[i]].name,
                                class_list[result[i]].type ? "选修" : "必修");
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }

                    break;
                case 2: {
                    for (int i = 0; i < N; i++) {
                        sprintf(itemtext, "ID:%d\t姓名:%s", teacher_list[result[i]].ID, teacher_list[result[i]].name);
                        newtListboxAppendEntry(list, itemtext, num + i);
                        memset(itemtext, 0, 64);
                    }
                    newtFormAddComponent(form2, list);
                    newtListboxSetCurrent(list, current);
                    newtRunForm(form2);
                }
                    break;
            }
            int *u = (int *) newtListboxGetCurrent(list);
            current = *u;
            if (!*u) { //按下退出
                if (result) {
                    free(result);
                }
                //newtFormDestroy(form2);
                break;
            }
            char text[512] = {0};
            student_t s;
            class_t cc;
            teacher_t t;
            char *entry_text[8];
            int rc;
            if (type == 0) {
                newtPushHelpLine("空输入代表原有值");
                newtWinEntry entries[] = {
                        {"姓名",    entry_text + 0, 0},
                        {"性别",    entry_text + 1, 0},
                        {"年龄",    entry_text + 2, 0},
                        {"已获得学分", entry_text + 3, 0},
                        {NULL, NULL,              0}
                };
                memset(entry_text, 0, sizeof(entry_text));
                s = student_list[result[*u - 1]];
                sprintf(text, "原信息:\n");
                sprintf(text + strlen(text), "ID:%d\n姓名:%s\n性别:%lc\n年龄:%d\n已获得学分:%d", s.ID, s.name, s.sex ? L'女' : L'男',
                        s.age, s.credits);
                rc = newtWinEntries("学生信息修改",
                                    text, 50, 5, 5, 20, entries, "提交修改",
                                    "删除", "取消", NULL);
                if (rc == 1) {
                    student_t &tomod = get_itemRef_by_ID<student_t>(s.ID);
                    if (strlen(entry_text[0])) {
                        memset(tomod.name, 0, sizeof(tomod.name));
                        memcpy(tomod.name, entry_text[0], strlen(entry_text[0]));
                    }
                    if (strlen(entry_text[1])) {
                        if (strstr(entry_text[1], "男")) {
                            tomod.sex = false;
                        } else {
                            tomod.sex = true;
                        }
                    }
                    if (strlen(entry_text[2])) {
                        tomod.age = atoi(entry_text[2]);
                    }
                    if (strlen(entry_text[3])) {
                        sscanf(entry_text[3], "%" SCNu8, &tomod.credits);
                    }
                    show_info_win("修改完成");
                    break;
                } else if (rc == 2) {

                    del_entity<student_t>(s.ID);
                    show_info_win("已删除");
                    break;
                }

            } else if (type == 1) {
                newtWinEntry entries[] = {
                        {"课程名称", entry_text + 0, 0},
                        {"课程类型", entry_text + 1, 0},
                        {"学分",   entry_text + 2, 0},
                        {NULL, NULL,             0}
                };
                memset(entry_text, 0, sizeof(entry_text));
                cc = class_list[result[*u - 1]];
                sprintf(text, "原信息:\n");
                sprintf(text + strlen(text), "ID:%d\n课程名称:%s\n课程类型:%s\n学分:%.1f\n上课时间和地点:%s\n", cc.ID, cc.name,
                        cc.type ? "选修" : "必修", cc.credits, "这里不给你看,別的地方能查到的,我懒得写了");
                rc = newtWinEntries("课程信息修改",
                                    text, 50, 5, 5, 20, entries, "提交修改",
                                    "删除", "取消", NULL);
                if (rc == 1) {
                    class_t &tomod = get_itemRef_by_ID<class_t>(cc.ID);
                    if (strlen(entry_text[0])) {
                        memset(tomod.name, 0, sizeof(tomod.name));
                        memcpy(tomod.name, entry_text[0], strlen(entry_text[0]));
                    }
                    if (strlen(entry_text[1])) {
                        if (strstr(entry_text[1], "必")) {
                            tomod.type = 0;
                        } else {
                            tomod.type = 1;
                        }
                    }
                    if (strlen(entry_text[2])) {
                        sscanf(entry_text[2], "%f", &tomod.credits);
                    }

                } else if (rc == 2) {

                    del_entity<class_t>(cc.ID);
                    show_info_win("已删除");
                    break;
                }

            } else if (type == 2) {
                newtWinEntry entries[] = {
                        {"姓名", entry_text + 0, 0},
                        {NULL, NULL,           0}
                };
                memset(entry_text, 0, sizeof(entry_text));
                t = teacher_list[result[*u - 1]];
                sprintf(text, "原信息:\n");
                sprintf(text + strlen(text), "ID:%d\n姓名:%s", t.ID, t.name);
                rc = newtWinEntries("教师信息修改",
                                    text, 50, 5, 5, 20, entries, "提交修改",
                                    "删除", "取消", NULL);
                if (rc == 1) {
                    teacher_t &tomod = get_itemRef_by_ID<teacher_t>(t.ID);
                    if (strlen(entry_text[0])) {
                        memset(tomod.name, 0, sizeof(tomod.name));
                        memcpy(tomod.name, entry_text[0], strlen(entry_text[0]));
                    }
                    show_info_win("修改完成");
                    break;
                } else if (rc == 2) {
                    del_entity<teacher_t>(t.ID);
                    show_info_win("已删除");
                    break;
                }
                //sprintf(text, "ID:%d\n姓名%s", t.ID, t.name);
            }
            //show_info_win(text);
        }

        newtFormDestroy(form2);
        newtRefresh();

    } else {
        show_warning_win("无输入");
    }
    newtFormDestroy(form);
    newtRefresh();
}

void admin_addentity() {
    start:
    newtCls();
    newtRefresh();
    newtComponent form, list;
    newtCenteredWindow(50, 10, "管理员模式-添加记录");
    list = newtListbox(18, 3, 4, NEWT_FLAG_RETURNEXIT);
    int p = 1, q = 2, r = 3, s = 4;
    newtListboxAppendEntry(list, "添加学生", &p);
    newtListboxAppendEntry(list, "添加课程", &q);
    newtListboxAppendEntry(list, "添加教师", &r);
    newtListboxAppendEntry(list, "返回", &s);
    newtPushHelpLine(" Move using the arrow keys and press ENTER to select");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponent(form, list);
    newtRunForm(form);
    int *u = (int *) newtListboxGetCurrent(list);
    if (*u == 1) {
        char *entry_text[8];
        int rc;
        newtWinEntry entries[] = {
                {"ID*",          entry_text + 0, 0},
                {"姓名*",          entry_text + 1, 0},
                {"性别*",          entry_text + 2, 0},
                {"年龄*",          entry_text + 3, 0},
                {"本学期前已获学分*",    entry_text + 4, 0},
                {"已选课程ID(空格隔开)", entry_text + 5, 0},
                {NULL, NULL,                     0}
        };
        memset(entry_text, 0, sizeof(entry_text));
        rc = newtWinEntries("添加学生",
                            "请输入学生信息", 64, 5, 5, 32, entries, "提交",
                            "取消", NULL);
        if (rc == 1) {
            if (strlen(entry_text[0]) && strlen(entry_text[1]) && strlen(entry_text[2]) && strlen(entry_text[3]) &&
                strlen(entry_text[4])) {
                student_t ss{};
                ss.ID = atoi(entry_text[0]);
                memcpy(ss.name, entry_text[1], strlen(entry_text[1]));
                ss.sex = strcmp("男", entry_text[2]) ? true : false;
                ss.age = atoi(entry_text[3]);
                sscanf(entry_text[4], "%" SCNu8, &ss.credits);
                ss.student_class_link_head = list_create(0);
                uint32_t hID = ss.ID;
                if (get_itemRef_by_ID<student_t>(ss.ID).ID) {
                    show_warning_win("ID重复");
                } else {
                    uint8_t hash_count = 0;
                    do {
                        hID = hashID(hID, MAX_STUDENT_NUM);
                        hash_count++;
                    } while (student_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
                    if (student_list[hID].ID == 0) {
                        student_list[hID] = ss;
                        student_num++;
                        show_info_win("完成");
                    } else {
                        char waring_text[64] = {0};
                        sprintf(waring_text, "ID=%d hash冲突%d次,加入失败", ss.ID, MAX_HASH_TIME);
                        show_warning_win(waring_text);
                    }
                    if (strlen(entry_text[5])) {
                        char temp[128]{};
                        strcpy(temp, entry_text[5]);
                        char *token = strtok(temp, " ");
                        while (token) {
                            addRelation<student_t>(atoi(token), ss.ID, student_list);
                            token = strtok(NULL, " ");
                        }
                    }
                }
            } else {
                show_warning_win("前5项为必填项");
            }
        } else {
            show_info_win("用户取消操作");
            newtFormDestroy(form);
            newtCls();
            goto start;
        }
    } else if (*u == 2) {
        char *entry_text[8];
        int rc;
        newtWinEntry entries[] = {
                {"ID*",   entry_text + 0, 0},
                {"课程名称*", entry_text + 1, 0},
                {"学分*",   entry_text + 2, 0},
                {"类型*",   entry_text + 3, 0},
                {NULL, NULL,              0}
        };
        memset(entry_text, 0, sizeof(entry_text));
        rc = newtWinEntries("添加课程",
                            "请输入课程基本信息(暂不支持设置时间地点)", 64, 5, 5, 32, entries, "提交",
                            "取消", NULL);
        if (rc == 1) {
            if (strlen(entry_text[0]) && strlen(entry_text[1]) && strlen(entry_text[2]) && strlen(entry_text[3])) {
                class_t newC{};
                newC.ID = atoi(entry_text[0]);
                memcpy(newC.name, entry_text[1], strlen(entry_text[1]));
                sscanf(entry_text[2], "%f", &newC.credits);
                newC.type = strstr(entry_text[3], "必") ? 0 : 1;
                newC.class_student_link_head = list_create(0);
                newC.class_resource_link_head = list_create(0);
                newC.class_teacher_link_head = list_create(0);
                uint32_t hID = newC.ID;
                if (get_itemRef_by_ID<class_t>(newC.ID).ID) {
                    show_warning_win("ID重复");
                } else {
                    uint8_t hash_count = 0;
                    do {
                        hID = hashID(hID, MAX_CLASS_NUM);
                        hash_count++;
                    } while (class_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
                    if (class_list[hID].ID == 0) {
                        class_list[hID] = newC;
                        class_num++;
                        show_info_win("完成");
                    } else {
                        char waring_text[64] = {0};
                        sprintf(waring_text, "ID=%d hash冲突%d次,加入失败", newC.ID, MAX_HASH_TIME);
                        show_warning_win(waring_text);
                    }
                }

            } else {
                show_warning_win("四项均为必填项");
            }
        } else {
            show_info_win("用户取消操作");
            newtFormDestroy(form);
            newtCls();
            goto start;
        }
    } else if (*u == 3) {
        show_info_win("此功能暂未开放");
        goto start;
    }
    newtFormDestroy(form);
    newtRefresh();
    newtCls();
}
