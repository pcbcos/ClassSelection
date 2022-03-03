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


void DataBaseInit();//数据库初始化
void DataBaseSave();//数据库数据保存
void show_warning_win(char *text);//显示错误信息
void show_info_win(char *text);

void read_student_data();

void read_teacher_data();

void read_class_data();

void read_resource_data();

void read_relation();

void save_student_data();

void save_teacher_data();

void save_class_data();

void save_resource_data();

void save_relation();

uint32_t hashID(uint32_t ID, uint64_t max);

uint32_t get_min_available_ID(const uint32_t *index_list, uint32_t max_num);//自动找一个ID,利用了堆区数组自动零初始化的性质

template<typename T>
concept have_relation_with_class = std::is_same_v<T, student_t> || std::is_same_v<T, resource_t> ||
                                   std::is_same_v<T, teacher_t>;

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

//template<typename T,std::size_t N>
//auto& get_itemRef_by_ID(uint32_t ID,T(&entity_list)[N]){
//    return entity_list[get_index_by_ID(ID,entity_list)];
//}
template<typename T>
requires have_relation_with_class<T> || std::is_same_v<T, class_t>
T &get_itemRef_by_ID(uint32_t ID) {
    if constexpr(std::is_same_v<T, student_t>) {
        return student_list[get_index_by_ID(ID, student_list)];
    } else if constexpr(std::is_same_v<T, class_t>) {
        return class_list[get_index_by_ID(ID, class_list)];
    } else if constexpr(std::is_same_v<T, resource_t>) {
        return resource_list[get_index_by_ID(ID, resource_list)];
    } else {
        return teacher_list[get_index_by_ID(ID, teacher_list)];
    }
}


template<typename T, std::size_t N>
uint32_t *widesearch(uint32_t ID, const char *name, T(&entity_list)[N], const uint8_t &rank = 0) {
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


template<typename T, std::size_t N>
uint32_t get_max_ID(T(&entity_list)[N]) {
    return std::max_element(entity_list, entity_list + N, [](const T &e1, const T &e2) {
                                return e1.ID < e2.ID;
                            }
    )->ID;
}

template<typename T, std::size_t N>
uint32_t get_min_ID(T(&entity_list)[N]) {
    return std::min_element(entity_list, entity_list + N, [](const T &e1, const T &e2) {
        if (e1.ID && e2.ID) {
            return e1.ID < e2.ID;
        } else if (e1.ID == 0) {
            return false;
        } else {
            return true;
        }
    })->ID;
}

template<typename T>
constexpr decltype(auto) get_T_list() noexcept {
    if constexpr(std::is_same_v<T, class_t>) {
        return class_list;
    } else if constexpr(std::is_same_v<T, teacher_t>) {
        return teacher_list;
    } else if constexpr(std::is_same_v<T, student_t>) {
        return student_list;
    } else {
        return resource_list;
    }
}


template<typename T>
requires have_relation_with_class<T>
auto get_T_head(class_t c) {
    if constexpr(std::is_same_v<T, student_t>) {
        return c.class_student_link_head;
    } else if constexpr(std::is_same_v<T, resource_t>) {
        return c.class_resource_link_head;
    } else if constexpr(std::is_same_v<T, teacher_t>) {
        return c.class_teacher_link_head;
    }
}

template<typename T>
requires std::is_same_v<T, student_t> || std::is_same_v<T, teacher_t>
auto get_T_head(T e) {
    if constexpr(std::is_same_v<T, student_t>) {
        return e.student_class_link_head;
    } else if constexpr(std::is_same_v<T, teacher_t>) {
        return e.teacher_class_link_head;
    }
}

template<typename T, std::size_t N>
requires std::is_same_v<T, resource_t>
void addRelation(uint32_t class_id, uint32_t other_id, T(&entity_list)[N]) {
    class_t c = class_list[get_index_by_ID(class_id, class_list)];
    T e = entity_list[get_index_by_ID(other_id, entity_list)];
    auto class_xxx_link_head = get_T_head<T>(c);
    list_append(class_xxx_link_head, other_id);
}

template<typename T, std::size_t N>
requires have_relation_with_class<T> && (!std::is_same_v<T, resource_t>)
void addRelation(uint32_t class_id, uint32_t other_id, T(&entity_list)[N]) {
    class_t c = class_list[get_index_by_ID(class_id, class_list)];
    T e = entity_list[get_index_by_ID(other_id, entity_list)];
    auto class_xxx_link_head = get_T_head<T>(c);
    auto xxx_class_link_head = get_T_head(e);
    list_append(class_xxx_link_head, other_id);
    list_append(xxx_class_link_head, class_id);
}

template<typename T>
requires std::is_same_v<T, class_t>
void del_entity(uint32_t id) {
    uint32_t index = get_index_by_ID(id, class_list);
    if (!index) return;
    const class_t &c = get_itemRef_by_ID<T>(id);
    pNode ct = c.class_teacher_link_head->next;
    pNode cs = c.class_student_link_head->next;
    for (pNode p = ct; p; p = p->next) {
        teacher_t &t = get_itemRef_by_ID<teacher_t>(p->targetID);
        list_del_entity(t.teacher_class_link_head, id);
    }
    for (pNode p = cs; p; p = p->next) {
        student_t &s = get_itemRef_by_ID<student_t>(p->targetID);
        list_del_entity(s.student_class_link_head, id);
    }
    list_del_all(c.class_student_link_head);
    list_del_all(c.class_resource_link_head);
    list_del_all(c.class_teacher_link_head);
    memset(class_list + index, 0, sizeof(class_t));
}

template<typename T>
requires have_relation_with_class<T> && (!std::is_same_v<T, resource_t>)
void del_entity(uint32_t id) {
    uint32_t index = 0;
    T &e = get_itemRef_by_ID<T>(id);
    pNode ec;
    if constexpr(std::is_same_v<T, student_t>) {
        index = get_index_by_ID(id, student_list);
        ec = e.student_class_link_head;
    } else if constexpr(std::is_same_v<T, teacher_t>) {
        index = get_index_by_ID(id, teacher_list);
        ec = e.teacher_class_link_head;
    }
    if (!index) return;
    for (pNode p = ec->next; p; p = p->next) {
        class_t &c = get_itemRef_by_ID<class_t>(p->targetID);
        list_del_entity(get_T_head<T>(c), id);
    }
    list_del_all(get_T_head<T>(e));
    memset(&e,0,sizeof(T));
}


#endif //CLASSSELECTION_DATABASE_H
