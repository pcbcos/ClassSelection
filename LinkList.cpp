#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"
//
// Created by wengz on 2022/1/13.
//
#include "LinkList.h"


/*
Node_ptr list_create(void *first_entity) {
    auto head = (Node_ptr) malloc(sizeof(Node));
    head->entity = first_entity;
    head->next = NULL;
    return head;
}

Node_ptr list_append(Node_ptr head, void *entity_to_append) {
    auto p = (Node_ptr) malloc(sizeof(Node));
    p->entity = entity_to_append;
    p->next = NULL;
    Node_ptr temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = p;
    return p;
}

void *list_at(Node_ptr head, uint16_t n) {
//    if (!n) {
//        return head->entity;
//    } else {
//        return list_at(head->next, n - 1);
//    }
    Node_ptr p = head;
    if (n == 0) {
        return head->entity;
    }
    for (int i = 0; i < n; i++) {
        p = p->next;
        if (!p) {
            return NULL;
        }
    }
    return p->entity;
}

Node_ptr list_del_item(Node_ptr head, uint16_t index) {
    if (index == 0) {
        Node_ptr new_head = head->next;
        free(head);
        return new_head;
    }
    Node_ptr p = head;
    Node_ptr p_;
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
*/
Node_ptr list_create(uint32_t targetID) {
    auto head = (Node_ptr) malloc(sizeof(Node));
    head->targetID = targetID;
    head->next = NULL;
    return head;
}

Node_ptr list_append(Node_ptr head, uint32_t targetID) {
    auto p = (Node_ptr) malloc(sizeof(Node));
    p->targetID = targetID;
    p->next = NULL;
    Node_ptr temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = p;
    return p;
}

uint32_t list_at(Node_ptr head, uint16_t n) {
//    if (!n) {
//        return head->entity;
//    } else {
//        return list_at(head->next, n - 1);
//    }
    Node_ptr p = head;
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

Node_ptr list_del_item(Node_ptr head, uint16_t index) {
    if (index == 0) {
        Node_ptr new_head = head->next;
        free(head);
        return new_head;
    }
    Node_ptr p = head;
    Node_ptr p_;
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

void list_del_all(Node_ptr head) {
    if (!head) {
        return;
    }
    Node_ptr h = head;
    Node_ptr p = head->next;
    while (p) {
        free(h);
        h = p;
        p = p->next;
    }
    free(h);
}
#pragma clang diagnostic pop