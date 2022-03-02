//
// Created by cosine on 2022/2/26.
//

#ifndef CLASSSELECTION_MAIN_H
#define CLASSSELECTION_MAIN_H


#include <newt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DataBase.h"
#include "unistd.h"
#include "admin_mode.h"
#include "student_mode.h"

extern uint32_t myID;

void login();

void callback(void* data);

#endif //CLASSSELECTION_MAIN_H
