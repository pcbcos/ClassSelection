//
// Created by cosine on 2022/2/26.
//

#ifndef CLASSSELECTION_MAIN_H
#define CLASSSELECTION_MAIN_H

#ifndef TEST_MENU
#define TEST_MENU 1
#endif

#include <newt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DataBase.h"
#include "unistd.h"

void login();

void student_querry();

void student_addclass();

void student_delclass();


void admin_lookover();

void admin_querry();

void admin_modify();

void admin_addclass();

#endif //CLASSSELECTION_MAIN_H
