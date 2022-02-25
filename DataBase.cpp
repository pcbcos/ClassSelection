#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"
//
// Created by wengz on 2022/1/13.
//


#include "DataBase.h"

class_t class_list[MAX_CLASS_NUM];
student_t student_list[MAX_STUDENT_NUM];
teacher_t teacher_list[MAX_TEACHER_NUM];
resource_t resource_list[MAX_RESOURCE_NUM];

class_teacher_t relation_class_teacher_list[MAX_REL_CLASS_TEACHER_NUM];
class_student_t relation_class_student_list[MAX_REL_CLASS_STUDENT_NUM];
class_resource_t relation_class_resource_list[MAX_REL_CLASS_RESOURCE_NUM];

/***各种实体、关系的数量,存在文件的开头位置***/
uint32_t class_num = 0;
uint32_t student_num = 0;
uint32_t teacher_num = 0;
uint32_t resource_num = 0;

uint32_t class_teacher_num = 0;
uint32_t class_student_num = 0;
uint32_t class_resource_num = 0;

//快速索引表系
uint32_t index_of_class_hashID[MAX_CLASS_NUM] = {0};
uint32_t index_of_student_hashID[MAX_STUDENT_NUM] = {0};
uint32_t index_of_teacher_hashID[MAX_TEACHER_NUM] = {0};
uint32_t index_of_resource_hashID[MAX_RESOURCE_NUM] = {0};


char *week[] = {
        "日", "一", "二", "三", "四", "五", "六"
};


//零号课程，占位用
class_t class_zero = {
        .ID=0,
        .name={'0'},
        .type=0,
        .credits=0,
        .max_stu=1,
        .now_stu=1,
        .class_resource_link_head=NULL,
        .class_teacher_link_head=NULL,
        .class_student_link_head=NULL
};

//零号教师
teacher_t teacher_zero = {
        .ID=0,
        .name={'0'},
        .teacher_class_link_head=NULL
};

//零号学生
student_t student_zero = {
        .ID=0,
        .name={'0'},
        .sex=true,
        .credits=0,
        .student_class_link_head=NULL
};

//零号课程表资源
resource_t resource_zero = {
        .ID=0,
        .day=0,
        .rank=0,
        .name={'0'},
        .first_week=0,
        .last_week=0,
        .odd_even=ALL
};




/*
 * 读入课程信息
 *
 * */
//TODO:将课程和时间地点分离开来，课程结构体只中只保留时间地点的资源ID
class_t class_loader(char *raw_text) {
    class_t Aclass = {0};
    class_t *p = &Aclass;
    char text_temp[512] = {0};
    sscanf(raw_text, "ID:%d name:%s type:%d credits:%d max_stu:%d now_stu:%d time&&name:%s",
           &(Aclass.ID),
           Aclass.name, &(Aclass.type), &(Aclass.credits), &(Aclass.max_stu), &(Aclass.now_stu), text_temp);
    char *p1 = text_temp;
    char *p2 = text_temp;
    resource_t resource_temp;
    bool isfirst = true;
    while (*p1) {
        while (*p2 != ',' && *p2) {
            p2++;
        }
        resource_temp = class_time_analysis((*p1 == ',' ? ++p1 : p1), p2);
//        auto *t = (resource_t *) malloc(sizeof(resource_t));
//        memcpy(t, &resource_temp, sizeof(resource_t));
//        t->ID=resource_num+1;
//        resource_num++;
        //SOLVED:直接将recourse_temp加入堆区的大数组,考虑ID的自动获取问题
        uint32_t ID = get_min_available_ID(index_of_resource_hashID, MAX_RESOURCE_NUM);
        //如果返回的ID为0,说明存满了,这里返回零号课程 TODO:要有存满了的提示，将来可以自动扩容
        if (!ID) {
            return class_zero;
        }
        resource_temp.ID = ID;
        resource_list[resource_num + 1] = resource_temp; //存入大数组
        index_of_resource_hashID[resource_temp.ID] = resource_num + 1; //更新ID索引表
        resource_num++;

        if (isfirst) {
            Aclass.class_resource_link_head = list_create(resource_temp.ID);
            isfirst = false;
        } else {
            list_append(Aclass.class_resource_link_head, resource_temp.ID);
        }
        p1 = ++p2;
    }
    //TODO:检测并处理ID重复的问题
    uint32_t classid = get_min_available_ID(index_of_class_hashID, MAX_CLASS_NUM);
    if (!classid) {
        //TODO:检测了存满的情况,还没加后续步骤
        return class_zero;
    }

    return Aclass;
}

resource_t class_time_analysis(char *text_p1, char *text_p2) {
    char *p1 = text_p1;
    char *p2 = text_p2;
    //class_resource_t *info = (class_resource_t *) malloc(sizeof(class_resource_t));
    resource_t info = {0};
    info.day = *p1 - '0';
    p1++;
    ///解析时间开始
    if (*(p1 + 1) != '|') {
        info.rank = (*p1 - '0') * 10 + *(p1 + 1) - '0';
        p1 += 3;
    } else {
        info.rank = *p1 - '0';
        p1 += 2;
    }
    char *p_next = strchr(p1, '|');
    if (p_next && p_next < p2) {
        strncpy(info.name, p1, p_next - p1);
    } else {
        strncpy(info.name, p1, p2 - p1);
    }
    //TODO:特殊时间
    return info;
}

//TODO:要修正，这个是原版的方案,改用新版ID索引方案
void printclassinfo(class_t c) {
    printf("ID:%d\n", c.ID);
    printf("课程名称:%s\n", c.name);
    printf("类型:%s\n", c.type ? "选修" : "必修");
    printf("最大学生容量:%d\n", c.max_stu);
    printf("当前学生人数:%d\n", c.now_stu);
    printf("--------上课时间和地点------\n");

    //printf("时间:")
    ClassResourceLink info = c.class_resource_link_head;
    resource_t *t;
    int i = 0;
    while (t = (resource_t *) (list_at(info, i))) {
        i++;
        printf("周%s第%d节 %s\n", week[t->day], t->rank, t->name);
    }
}


//将课程信息存入磁盘 TODO:模式应该是写错了,要修正
void dump_class_data(char mode) {
    FILE *fp = NULL;
    if (mode == 'a') {
        fp = fopen("class_data", "ab");
        if (fp == NULL) {
            fp = fopen("class_data", "wb");
        }
    } else if (mode == 'w') {
        fp = fopen("class_data", "wb");
    }
    if (fp == NULL) {
        show_warning_win("ERROR!");
        return;
    }
    //fwrite()

}

//将学生信息存入磁盘
void dump_student_data(char mode) {


}

//将教师的信息存入磁盘
void dump_teacher_data(char mode) {


}


void dump_class_data_gui(char mode) {
    FILE *fp = NULL;
    if (mode == 'a') {
        fp = fopen("class_data", "ab");
        if (fp == NULL) {
            show_warning_win("文 件 不 存 在 , 按 任 意 键 创 建 ");
            fp = fopen("class_data", "wb");
        }
    } else if (mode == 'w') {
        fp = fopen("class_data", "wb");
    }
    if (fp == NULL) {
        show_warning_win("文 件 加 载 失 败 ");
    }

}

void dump_student_data_gui(char mode) {

}

void dump_teacher_data_gui(char mode) {

}


//从磁盘中读取学生信息,更新index-ID索引
//void read_student_data() {
//    FILE *fp = fopen("student_data", "rb");
//    student_t temp = {0};
//    fread(&student_num, sizeof(student_num), 1, fp);//读取数量
//    for (int i = 0; i < student_num; i++) {
//        fread(&temp, sizeof(temp), 1, fp);
//        temp.student_class_link_head = NULL; //设为空指针
//        uint32_t hID = temp.ID;
//        uint8_t hash_count = 0;
//        do {
//            hID = hashID(hID, MAX_STUDENT_NUM);
//            hash_count++;
//        } while (index_of_student_hashID[hID] != 0 && hash_count < MAX_HASH_TIME);
//        if(index_of_student_hashID[hID] ==0){
//            index_of_student_hashID[hID]=i+1;
//            student_list[i + 1] = temp;
//        } else{
//            char waring_text[64]={0};
//            sprintf(waring_text,"i=%d,ID=%d hash冲突%d次,加入失败",i,MAX_HASH_TIME,temp.ID);
//            show_warning_win(waring_text);
//        }
//    }
//    fclose(fp);
//}
void read_student_data() {
    FILE *fp = fopen("../test_data_gen/student_data", "rb");
    student_t temp{0};
    fread(&student_num, sizeof(student_num), 1, fp);//读取数量
    for (int i = 0; i < student_num; i++) {
        fread(&temp, sizeof(temp), 1, fp);
        temp.student_class_link_head = NULL; //设为空指针
        uint32_t hID = temp.ID;
        uint8_t hash_count = 0;
        do {
            hID = hashID(hID, MAX_STUDENT_NUM);
            hash_count++;
        } while (student_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
        if (student_list[hID].ID == 0) {
            student_list[hID] = temp;
        } else {
            char waring_text[64] = {0};
            sprintf(waring_text, "i=%d,ID=%d hash冲突%d次,加入失败", i, MAX_HASH_TIME, temp.ID);
            show_warning_win(waring_text);
        }
    }
    fclose(fp);
}

//从磁盘中读取教师信息,更新index-ID索引
void read_teacher_data() {
    FILE *fp = fopen("../test_data_gen/teacher_data", "rb");
    teacher_t temp{0};
    fread(&teacher_num, sizeof(teacher_num), 1, fp);//读取数量
    for (int i = 0; i < teacher_num; i++) {
        fread(&temp, sizeof(temp), 1, fp);
        temp.teacher_class_link_head = NULL; //设为空指针
        uint32_t hID = temp.ID;
        uint8_t hash_count = 0;
        do {
            hID = hashID(hID, MAX_TEACHER_NUM);
            hash_count++;
        } while (teacher_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
        if (teacher_list[hID].ID == 0) {
            teacher_list[hID] = temp;
        } else {
            char waring_text[64] = {0};
            sprintf(waring_text, "i=%d,ID=%d hash冲突%d次,加入失败", i, MAX_HASH_TIME, temp.ID);
            show_warning_win(waring_text);
        }
    }

    fclose(fp);
}

//从磁盘中读取课程信息,更新index-ID索引
void read_class_data() {

    FILE *fp = fopen("../test_data_gen/class_data", "rb");
    class_t temp{0};
    fread(&class_num, sizeof(class_num), 1, fp);//读取数量
    for (int i = 0; i < class_num; i++) {
        fread(&temp, sizeof(temp), 1, fp);
        temp.class_resource_link_head = NULL; //设为空指针
        temp.class_teacher_link_head = NULL;
        temp.class_student_link_head = NULL;
        uint32_t hID = temp.ID;
        uint8_t hash_count = 0;
        do {
            hID = hashID(hID, MAX_CLASS_NUM);
            hash_count++;
        } while (class_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
        if (class_list[hID].ID == 0) {
            class_list[hID] = temp;
        } else {
            char waring_text[64] = {0};
            sprintf(waring_text, "i=%d,ID=%d hash冲突%d次,加入失败", i, MAX_HASH_TIME, temp.ID);
            show_warning_win(waring_text);
        }
    }


    fclose(fp);
}

//从磁盘中读取课程表资源信息,更新index-ID索引
void read_resource_data() {
    FILE *fp = fopen("../test_data_gen/resource_data", "rb");
    resource_t temp{0};
    fread(&resource_num, sizeof(resource_num), 1, fp);//读取数量
    for (int i = 0; i < resource_num; i++) {
        fread(&temp, sizeof(temp), 1, fp);
        uint32_t hID = temp.ID;
        uint8_t hash_count = 0;
        do {
            hID = hashID(hID, MAX_RESOURCE_NUM);
            hash_count++;
        } while (resource_list[hID].ID != 0 && hash_count < MAX_HASH_TIME);
        if (resource_list[hID].ID == 0) {
            resource_list[hID] = temp;
        } else {
            char waring_text[64] = {0};
            sprintf(waring_text, "i=%d,ID=%d hash冲突%d次,加入失败", i, MAX_HASH_TIME, temp.ID);
            show_warning_win(waring_text);
        }
    }


    fclose(fp);
}


void DataBaseInit() {
    //初始化0号实体
    class_list[0] = class_zero;
    student_list[0] = student_zero;
    teacher_list[0] = teacher_zero;
    resource_list[0] = resource_zero;
    int zero = 0;

    //初始化0号关系
    class_zero.class_resource_link_head = list_create(0);
    class_zero.class_student_link_head = list_create(0);
    class_zero.class_teacher_link_head = list_create(0);
    teacher_zero.teacher_class_link_head = list_create(0);
    student_zero.student_class_link_head = list_create(0);

    //从磁盘中读取实体 TODO:基本实现了
    read_student_data();
    read_teacher_data();
    read_class_data();
    read_resource_data();

    //从磁盘中读入关系 TODO:实现以下函数


}

uint32_t get_min_available_ID(const uint32_t *index_list, uint32_t max_num) {
    for (int i = 1; i < max_num; i++) {
        if (index_list[i] == 0) {
            return i;
        }
    }
    return 0;
}

uint32_t hashID(uint32_t ID, uint64_t max) {
    uint32_t hID = (ID ^ 31415927) % max;
    if (hID == 0) {
        return 5;
    } else {
        return hID;
    }
}

void show_warning_win(char *text) {
    newtWinMessage("警告", "确定", text);
}



#pragma clang diagnostic pop