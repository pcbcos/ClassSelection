#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"

#include "main.h"

uint32_t myID;
const wchar_t WEEK[7] = {L'日', L'一', L'二', L'三', L'四', L'五', L'六'};

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
    myID = atoi(id);
    if(!get_itemRef_by_ID<student_t>(myID).ID){
        newtFinished();
        show_warning_win("Not Found!");
        exit(1);
    }
    if (strcmp(passwd, "kalium1910") == 0) {
        newtRefresh();
        newtFormDestroy(form);
        return;
    } else {
        newtFinished();
        printf("%s", id);
        exit(1);
    }
}

int main() {
    DataBaseInit();
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
                printf("ID=%d\n", myID);
                DataBaseSave();
                printf("Saved!\n");
                exit(0);
        }
    } while (1);
#else
    //    for (auto &r: resource_list) {
    //        if (r.ID) {
    //            printf("ID:%d,周%d第%d节,教室:%s\n",r.ID,r.day,r.rank,r.name);
    //        }
    //    }
//        student_t s = student_list[get_index_by_ID(19201022, student_list)];
//        class_t& c1= get_itemRef_by_ID<class_t>(94);
//        class_t c2=class_list[get_index_by_ID(121,class_list)];
//        c1.credits=100.0;
//        printf("%d\n", list_at(student_list[get_index_by_ID(19201022, student_list)].student_class_link_head, 1));
//        printf("%lf",class_list[get_index_by_ID(94,class_list)].credits);
//    for (auto &r: resource_list) {
//        if (r.ID) {
//            printf("%d\n",r.ID);
//        }
//    }
    pNode l= list_create(1);
    for(int i=2;i<=10;i++) {
        list_append(l, i);
    }
    list_del_entity(l,5);
    for(pNode p=l;p;p=p->next) {
        printf("%d\n",p->targetID);
    }
    DataBaseSave();
#endif
    return 0;
}

void callback(void *data) {
    newtCls();
    newtRefresh();
    newtFinished();
    printf("Hello,world!\n");
    DataBaseSave();
    printf("Saved!\n");
    exit(1);
}


#pragma clang diagnostic pop
