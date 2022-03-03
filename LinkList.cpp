#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"
//
// Created by wengz on 2022/1/13.
//
#include "LinkList.h"

pNode list_create(uint32_t targetID) {
    auto head = (pNode) malloc(sizeof(Node));
    head->targetID = targetID;
    head->next = NULL;
    return head;
}

pNode list_append(pNode head, uint32_t targetID) {
    auto p = (pNode) malloc(sizeof(Node));
    p->targetID = targetID;
    p->next = NULL;
    pNode temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = p;
    return p;
}

uint32_t list_at(pNode head, uint16_t n) {
    pNode p = head;
    if (n == 0) {
        return head->targetID;
    }
    for (int i = 0; i < n; i++) {
        p = p->next;
        if (!p) {
            return UINT32_MAX;
        }
    }
    return p->targetID;
}

pNode list_del_item(pNode head, uint16_t index) {
    if (index == 0) {
        pNode new_head = head->next;
        free(head);
        return new_head;
    }
    pNode p = head;
    pNode p_;
    for (uint16_t i = 0; i < index; i++) {
        if (p->next == NULL) {
            return head;
        }
        p_ = p;
        p = p->next;
    }
    p_->next = p->next;
    free(p);
    return head;
}

void list_del_all(pNode head) {
    if (!head) {
        return;
    }
    pNode h = head;
    pNode p = head->next;
    while (p) {
        free(h);
        h = p;
        p = p->next;
    }
    free(h);
}

void list_del_same(pNode head) {
    if(!head) return;
    for (pNode p = head->next; p; p = p->next) {
        uint32_t ID = p->targetID;
        pNode p2 = p->next;
        pNode p3 = p;
        for (; p2;) {
            if (p2->targetID == ID) {
                p3->next = p2->next;
                free(p2);
                p2 = p3->next;
                continue;
            }
            p3 = p2;
            p2 = p2->next;
        }
    }
}

void list_del_entity(pNode head,uint32_t id){
    if(!head) return;
    pNode p1=head;
    pNode p2=head->next;
    while(p2){
        if(p2->targetID==id){
            p1->next=p2->next;
            free(p2);
            break;
        }else{
            p1=p2;
            p2=p2->next;
        }
    }
}

#pragma clang diagnostic pop
