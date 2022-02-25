import ctypes

from GEN import *
from ctypes import *

student_num = 2000
class_num = 200
teacher_num = 5
resource_num = 5


class student_t(Structure):
    _fields_ = [("ID", c_uint32),
                ("name", c_char * 32),
                ("age",c_uint8),
                ("sex", c_bool),
                ("credits", c_uint8),
                ("student_class_link_head", c_void_p)]


class teacher_t(Structure):
    _fields_ = [("ID", c_uint32),
                ("name", c_char * 32),
                ("teacher_class_link_head", c_void_p)]


class class_t(Structure):
    _fields_ = [("ID", c_uint32),
                ("name", c_char*64),
                ("type_", c_uint8),
                ("credits_", c_float),
                ("max_stu", c_uint16),
                ("now_stu", c_uint16),
                ("class_resource_link_head", c_void_p),
                ("class_teacher_link_head", c_void_p),
                ("class_student_link_head", c_void_p)]


class resource_t(Structure):
    _fields_ = [("ID", c_uint32),
                ("day", c_uint8),
                ("rank", c_uint8),
                ("location", c_char * 64),
                ("first_week", c_uint8),
                ("last_week", c_uint8),
                ("odd_even", c_uint32)
                ]


def main():
    students = sorted(get_fake_students(student_num), key=lambda i: i["ID"])
    classes = sorted(get_fake_class(class_num), key=lambda i: i["ID"])
    teachers = sorted(get_fake_teacher(teacher_num), key=lambda i: i["ID"])
    resources = sorted(get_fake_resource(resource_num), key=lambda i: i["ID"])
    # print(sorted(get_fake_students(5), key=lambda i: i["ID"]))
    # print(sorted(get_fake_class(5), key=lambda i: i["ID"]))
    # print(sorted(get_fake_teacher(5), key=lambda i: i["ID"]))
    # print(sorted(get_fake_resource(2), key=lambda i: i["ID"]))
    f_s = open("student_data", "wb")
    f_c = open("class_data", "wb")
    f_t = open("teacher_data", "wb")
    f_r = open("resource_data", "wb")

    f_s.write(c_uint32(student_num))
    f_c.write(c_uint32(class_num))
    f_t.write(c_uint32(teacher_num))
    f_r.write(c_uint32(resource_num))

    for i in range(student_num):
        temp=student_t()
        temp.ID = students[i]["ID"]
        temp.name = bytes(students[i]["name"], encoding="UTF-8")
        temp.age=students[i]["age"]
        temp.sex = 0 if students[i]["sex"] == '男' else 1
        temp.credits=students[i]["credits"]
        temp.student_class_link_head=c_void_p(0)
        f_s.write(temp)

    for i in range(class_num):
        temp=class_t()
        temp.ID=classes[i]["ID"]
        temp.name=bytes(classes[i]["name"],encoding="UTF-8")
        temp.type_=classes[i]["type"]
        temp.credits_=classes[i]["credits"]
        temp.max_stu=classes[i]["max_stu"]
        temp.now_stu=classes[i]["now_stu"]
        temp.class_resource_link_head=c_void_p(0)
        temp.class_teacher_link_head=c_void_p(0)
        temp.class_student_link_head=c_void_p(0)
        f_c.write(temp)

    for i in range(resource_num):
        temp.ID=resources[i]["ID"]
        temp.day=resources[i]["day"]
        temp.rank = resources[i]["rank_"]
        temp.location = resources[i]["location"]
        temp.first_week = resources[i]["first_week"]
        temp.last_week = resources[i]["last_week"]
        temp.odd_even = resources[i]["odd_even_"]
        f_r.write(temp)

    f_s.close()
    f_c.close()
    f_t.close()
    f_r.close()


if __name__ == '__main__':
    random.seed(0)
    main()
