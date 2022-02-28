//
// Created by wengz on 2022/1/13.
//

#ifndef CLASSSELECTION_DATABASE_H
#define CLASSSELECTION_DATABASE_H

#include <cstdint>
#include "LinkList.h"
#include <cstdlib>
#include <cstdio>
#include "curses.h"
#include "cstring"
#include "newt.h"
#include "algorithm"

#define MAX_CLASS_NUM 500
#define MAX_STUDENT_NUM 10000
#define MAX_TEACHER_NUM 500
#define MAX_RESOURCE_NUM 3000
#define MAX_REL_CLASS_TEACHER_NUM 2000
#define MAX_REL_CLASS_STUDENT_NUM 100000
#define MAX_REL_CLASS_RESOURCE_NUM 1500
#define MAX_HASH_TIME 8
typedef struct teacher_t teacher_t;
typedef struct student_t student_t;
typedef struct class_t class_t;
typedef struct resource_t resource_t;

typedef struct class_resource_t class_resource_t;
typedef struct class_student_t class_student_t;
typedef struct class_teacher_t class_teacher_t;


extern class_t class_list[MAX_CLASS_NUM];
extern student_t student_list[MAX_STUDENT_NUM];
extern teacher_t teacher_list[MAX_TEACHER_NUM];
extern resource_t resource_list[MAX_RESOURCE_NUM];
extern class_teacher_t relation_class_teacher_list[];
extern class_student_t relation_class_student_list[];
extern class_resource_t relation_class_resource_list[];

extern uint32_t class_num;
extern uint32_t student_num;
extern uint32_t teacher_num;
extern uint32_t resource_num;
extern uint32_t class_teacher_num;
extern uint32_t class_student_num;
extern uint32_t class_resource_num;

extern uint32_t index_of_class_hashID[];
extern uint32_t index_of_student_hashID[];
extern uint32_t index_of_teacher_hashID[];
extern uint32_t index_of_resource_hashID[];

/*********单双周***********/
enum Biweekly {
    ALL = 0, odd = 1, even = 2
};


/*********实体*************/
struct teacher_t {
    uint32_t ID{0};
    char name[32]{0};
    TeacherClassLink teacher_class_link_head = NULL;
};

struct student_t {
    uint32_t ID{0};
    char name[32]{0};
    uint8_t age{0};
    bool sex{false};
    uint8_t credits{0};
    StudentClassLink student_class_link_head{0};
};

struct class_t {
    uint32_t ID{0};
    char name[64]{0};
    uint8_t type{0}; //0为必修课，1为选修课
    float credits{0};
    //TeacherInfo teachers;  //只存教师的ID,避免老师重名
    uint16_t max_stu{0};
    uint16_t now_stu{0};

    ClassResourceLink class_resource_link_head{0};
    ClassTeacherLink class_teacher_link_head{0};
    ClassStudentLink class_student_link_head{0};

};

struct resource_t {
    uint32_t ID{};
    uint8_t day{}; //0为周日
    uint8_t rank{}; //一天中第几节,从1开始数
    char name[64]{};//教室位置
    uint8_t first_week{1};//从第几周开始 默认从第一周开始
    uint8_t last_week{20};//默认到第20周结束
    Biweekly odd_even{ALL};//单双周信息，默认单双周都上
};


/***********关系***********/
struct class_resource_t {
    uint32_t class_ID{0};
    uint32_t recourse_ID{0};
};

struct class_teacher_t {
    uint32_t class_ID{0};
    uint32_t teacher_ID{0};
};

struct class_student_t {
    uint32_t class_ID{0};
    uint32_t student_ID{0};
};

//从文本添加课程
class_t class_loader(char *raw_text);

//辅助函数
resource_t class_time_analysis(char *text_p1, char *text_p2);

//打印课程信息
void printclassinfo(class_t c);

void dump_class_data_gui(char mode); //将课程信息存入磁盘
void dump_student_data_gui(char mode);//将学生信息存入磁盘
void dump_teacher_data_gui(char mode); //将教师的信息存入磁盘


void dump_class_data(char mode); //将课程信息存入磁盘
void dump_student_data(char mode);//将学生信息存入磁盘
void dump_teacher_data(char mode); //将教师的信息存入磁盘

void DataBaseInit();//数据库初始化
void show_warning_win(char *text);//显示错误信息
void read_student_data();

void read_teacher_data();

void read_class_data();

void read_resource_data();


uint32_t hashID(uint32_t ID, uint64_t max);


uint32_t get_min_available_ID(const uint32_t *index_list, uint32_t max_num);//自动找一个ID,利用了堆区数组自动零初始化的性质

template<typename T, std::size_t N>
uint32_t get_index_by_ID(uint32_t ID, const T(&entity_list)[N]) {
    uint32_t hID = ID;
    uint8_t hash_count = 0;
    do {
        hID = hashID(hID, N);//取哈希作为索引
        hash_count++;
    } while (hash_count < MAX_HASH_TIME && entity_list[hID].ID != ID);
    if (entity_list[hID].ID == ID) {
        return hID;
    } else {
        return 0;
    }
}

//template<typename T, T* entity_list>
//int ID_UP(const void *e1, const void *e2) {
//    T t1 = entity_list[*(uint32_t *) e1];
//    T t2 = entity_list[*(uint32_t *) e2];
//    return t1.ID - t2.ID;
//};
//
//template<typename T, T* entity_list>
//int ID_DOWN(const void *e1, const void *e2) {
//    T t1 = entity_list[*(uint32_t *) e1];
//    T t2 = entity_list[*(uint32_t *) e2];
//    return t2.ID - t1.ID;
//};

template<typename T, std::size_t N>
uint32_t *widesearch(uint32_t ID, const char *name, const T(&entity_list)[N], const uint8_t &rank = 0) {
    uint32_t i = 0;
    uint32_t m = 32;
    auto *result = (uint32_t *) malloc(32 * 4);
    memset(result, 0, 32 * sizeof(uint32_t));
    if (ID) {
        uint32_t index = get_index_by_ID(ID, entity_list);
        result[i++] = index;
    } else if (name) {
        for (int index = 1; index < N; index++) {
            T e = entity_list[index];
            if (strstr(e.name, name)) {
                result[i++] = index;
                if (i == m) {
                    result = (uint32_t *) realloc(result, (m + 32) * 4);
                    memset(result + m, 0, 32 * sizeof(uint32_t));
                    m += 32;
                }
            }
        }
    }

    switch (rank) {
        case 1:
            std::sort(result, result + i, [&](uint32_t e1, uint32_t e2) {
                return entity_list[e1].ID < entity_list[e2].ID;
            });
            break;
        case 2:
            std::sort(result, result + i, [&](uint32_t e1, uint32_t e2) {
                return entity_list[e1].ID > entity_list[e2].ID;
            });
            break;
        default:
            break;

    }
    return result;
}

#endif //CLASSSELECTION_DATABASE_H
