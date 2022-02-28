#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"

#include "main.h"

uint32_t ID;

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
    } while (1);
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
    student_t s = student_list[index];
    char text[128] = {0};
    wchar_t sex = s.sex ? L'女' : L'男';
    sprintf(text, "姓名:%s\n学号:%d\n性别:%lc\n已获得学分:%d\n", s.name, s.ID, sex, s.credits);
    newtComponent form, t, button;
    t = newtTextboxReflowed(1, 1, text, 30, 5, 5, 0);
    newtCenteredWindow(100, 20, "学生信息");
    button = newtButton(45, 16, "返回");
    form = newtForm(NULL, NULL, 0);
    newtFormAddComponents(form, t, button, NULL);
    newtRunForm(form);
    newtFormDestroy(form);
}

void student_addclass() { ; }

void student_delclass() { ; }


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
                    newtListboxAppendEntry(list, text, index + id);
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
    free(index);

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
            char text[128] = {0};
            student_t s;
            class_t cc;
            teacher_t t;
            switch (type) {
                case 0:
                    s = student_list[result[*u - 1]];
                    sprintf(text, "ID:%d,姓名:%s,性别:%lc,年龄:%d,学分%d", s.ID, s.name, s.sex ? L'女' : L'男', s.age, s.credits);
                    break;
                case 1:
                    cc = class_list[result[*u - 1]];
                    sprintf(text, "ID:%d,课程名称:%s,课程类型:%s,学分:%.1f,上课时间和地点:%s", cc.ID, cc.name, cc.type ? "选修" : "必修",
                            cc.credits, "待完善");
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
    newtRefresh();
    newtFormDestroy(form);
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
            char text[128] = {0};
            student_t s;
            class_t cc;
            teacher_t t;
            switch (type) {
                case 0:
                    s = student_list[result[*u - 1]];
                    sprintf(text, "ID:%d,姓名:%s,性别:%lc,年龄:%d,学分%d", s.ID, s.name, s.sex ? L'女' : L'男', s.age, s.credits);
                    break;
                case 1:
                    cc = class_list[result[*u - 1]];
                    sprintf(text, "ID:%d,课程名称:%s,课程类型:%s,学分:%.1f,上课时间和地点:%s", cc.ID, cc.name, cc.type ? "选修" : "必修",
                            cc.credits, "待完善");
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
    newtRefresh();
    newtFormDestroy(form);
}

void admin_addclass() { ; }

int main() {
    read_student_data();
    read_class_data();
    read_resource_data();
    read_teacher_data();

#if TEST_MENU
    newtInit();
    newtSetSuspendCallback(callback, NULL);
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
                printf("ID=%d\n", ID);
                exit(0);
        }
    } while (1);
#else

    //    for (auto &s: student_list) {
    //        if (s.ID) {
    //            printf("NAME=%s,ID=%d\n", s.name, s.ID);
    //        }
    //    }
    //    for (uint32_t index = 1; index < MAX_STUDENT_NUM; index++) {
    //        if (strcmp("翁湛阳", student_list[index].name) == 0) {
    //            printf("index=%d",index);
    //            break;
    //        }
    //    }
    //    uint32_t* r=widesearch(0, "测试", resource_list);
    //
    //    for (int i = 0; i < 32; i++) {
    //        resource_t s = resource_list[r[i]];
    //        printf("name=%s\tID=%d\n", s.name, s.ID);
    //    }
//    for (auto &c: class_list) {
//        if (c.ID)
//            printf("name=%s\tID=%d\n", c.name, c.ID);
//    }
//printf("Hello,world\n");
    //printf("maxID=%d\tminID=%d", get_max_ID(class_list), get_min_ID(class_list));

#endif
    return 0;
}

void callback(void *data) {
    newtCls();
    newtRefresh();
    newtFinished();
    printf("Hello,world!\n");
    exit(1);
}


#pragma clang diagnostic pop