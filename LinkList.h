//
// Created by wengz on 2022/1/13.
//

#ifndef CLASSSELECTION_LINKLIST_H
#define CLASSSELECTION_LINKLIST_H
#include <cstdint>
#include <cstdlib>
#include "cstdio"
typedef struct Node Node;
typedef Node* Node_ptr;
//typedef Node_ptr TeacherInfo;
typedef Node_ptr ClassResourceLink;

typedef Node_ptr ClassTeacherLink;
typedef Node_ptr TeacherClassLink;


typedef Node_ptr ClassStudentLink;
typedef Node_ptr StudentClassLink;


/*历史版本，保留备用
struct Node {
    void *entity;
    Node_ptr next;
};

Node_ptr list_create(void *first_entity);
Node_ptr list_append(Node_ptr head, void *entity_to_append);
void *list_at(Node_ptr head, uint16_t n);
Node_ptr list_del_item(Node_ptr head, uint16_t index);
*/
struct Node{
    uint32_t targetID;
    Node_ptr next;
};

Node_ptr list_create(uint32_t targetID);
Node_ptr list_append(Node_ptr head,uint32_t targetID);
uint32_t list_at(Node_ptr head, uint16_t n);
Node_ptr list_del_item(Node_ptr head, uint16_t index);
void list_del_all(Node_ptr head);
#endif //CLASSSELECTION_LINKLIST_H
