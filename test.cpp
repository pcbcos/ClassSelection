//
// Created by wengz on 2022/2/9.
//

#include <clocale>
#include <iostream>
#include "DataBase.h"
#include "LinkList.h"
#include "cstring"
#include "cstdlib"
#include "unordered_map"

int max_x, max_y;

auto main(int argc, char *args[]) -> int {
    //setlocale(LC_ALL,"zh-CN");
//    printf("你好\n");
//    char text[]="你好";
//    printf("%d\n",sizeof(Biweekly));
//    for(auto i: text){
//        printf("%d\n",i);
//    }
    read_student_data();
    std::cout << student_num << std::endl;
    for (int i = 0; i <= 100; i++) {
        std::cout << student_list[i].name << ((student_list[i].ID ^ 31415927) % MAX_STUDENT_NUM) << std::endl;
    }
    std::cout<< get_index_by_ID(19211606, student_list)<<std::endl;
    std::cout<<student_list[1174].ID<<student_list[1174].name<<std::endl;

    read_class_data();
    for(const auto& i:class_list){
        if(i.ID!=0)
        std::cout<<i.ID<<"  "<<i.name<<"  "<<i.credits<<std::endl;
    }
    auto temp=class_list[get_index_by_ID(235,class_list)];
    std::cout<<temp.ID<<"  "<<temp.name<<"  "<<temp.credits<<std::endl;


    //getchar();
    return 0;
}