//
// Created by wengz on 2022/1/13.
//

#ifndef CLASSSELECTION_LINKLIST_H
#define CLASSSELECTION_LINKLIST_H
#include <cstdint>
#include <cstdlib>
#include "cstdio"
typedef struct Node Node;
typedef Node* pNode;
//typedef pNode TeacherInfo;
typedef pNode ClassResourceLink;

typedef pNode ClassTeacherLink;
typedef pNode TeacherClassLink;


typedef pNode ClassStudentLink;
typedef pNode StudentClassLink;

struct Node{
    uint32_t targetID;
    pNode next;
};

pNode list_create(uint32_t targetID);
pNode list_append(pNode head, uint32_t targetID);
uint32_t list_at(pNode head, uint16_t n);
pNode list_del_item(pNode head, uint16_t index);
void list_del_all(pNode head);
#endif //CLASSSELECTION_LINKLIST_H
