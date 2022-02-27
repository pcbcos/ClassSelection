import faker.providers.date_time
from faker import Faker
from faker.providers import BaseProvider
import random
import copy


class MyProvider(BaseProvider):
    ifake = Faker(['zh-CN'])

    def student(self):
        age = random.randint(19, 23)
        ID = 19000000 + 20 * 10000 + random.randint(0, 16) * 100 + random.randint(0, 32)
        sex = random.choice(['男', '女'])
        if sex == '男':
            name = self.ifake.unique.name_male()
        else:
            name = self.ifake.unique.name_female()

        credits = random.randint(10, 20)
        # return [ID, name, sex, age, credits]
        if ID==19201022:
            name="翁湛阳"
            sex="男"
            credits=18
        return {"ID": ID, "name": name, "sex": sex, "age": age, "credits": credits}

    def class_(self):
        ID = random.randint(1, 512)
        name = "测试课程_" + str(ID)
        type_ = random.randint(0, 1)
        credits_ = random.randint(1, 10) * 0.5
        max_stu = random.randint(3, 10) * 10  # 3到100人
        now_stu = random.randint(0, max_stu)

        # return [ID, name, type_, credits_, max_stu, now]
        return {"ID": ID, "name": name, "type": type_, "credits": credits_, "max_stu": max_stu, "now_stu": now_stu}

    def teacher(self):
        ID = random.randint(1, 64)
        name = self.ifake.unique.name()
        return {"ID": ID, "name": name}

    def resource(self):
        ID = random.randint(1, 4096)
        day = random.randint(0, 6)
        rank_ = random.randint(1, 5)
        location = random.choice(["经信", "逸夫楼", "李四光", "三教"]) + "-测试教室-" + str(random.randint(1, 16))
        first_week = random.randint(1, 10)
        last_week = random.randint(first_week + 3, 20)
        odd_even_ = random.randint(0, 5)
        return {"ID": ID, "day": day, "rank_": rank_, "location": location,
                "first_week": first_week, "last_week": last_week, "odd_even_": odd_even_}


fake = Faker(['zh-CN'])
fake.add_provider(MyProvider)


def get_fake_students(num: int = 10) -> list:
    i = 0
    res = []
    res_ID = []
    while i < num:
        temp = fake.student()
        if temp["ID"] in res_ID:
            continue
        else:
            res.append(temp)
            res_ID.append(temp["ID"])
            i += 1
    return res


def get_fake_class(num: int = 10) -> list:
    i = 0
    res = []
    res_ID = []
    while i < num:
        temp = fake.class_()
        if temp["ID"] in res_ID:
            continue
        else:
            res.append(temp)
            res_ID.append(temp["ID"])
            i += 1
    return res


def get_fake_teacher(num: int = 10) -> list:
    i = 0
    res = []
    res_ID = []
    while i < num:
        temp = fake.teacher()
        if temp["ID"] in res_ID:
            continue
        else:
            res.append(temp)
            res_ID.append(temp["ID"])
            i += 1
    return res


def get_fake_resource(num: int = 10) -> list:
    i = 0
    res = []
    res_ID = []
    while i < num:
        temp = fake.resource()
        if temp["ID"] in res_ID:
            continue
        else:
            if temp["rank_"] == 5:
                temp["rank_"] = 9
                res.append(temp)

                temp1 = copy.deepcopy(temp)
                temp1["ID"] += 1
                res.append(temp1)
                temp1["rank_"] = 10

                temp2 = copy.deepcopy(temp)
                temp2["ID"] += 2
                res.append(temp2)
                temp2["rank_"] = 11

                res_ID.append(temp["ID"])
                res_ID.append(temp["ID"] + 1)
                res_ID.append(temp["ID"] + 2)

            else:
                temp1 = copy.deepcopy(temp)
                temp["rank_"] = temp["rank_"] * 2 - 1
                temp1["rank_"] = temp["rank_"] + 1
                temp1["ID"] += 1

                res.append(temp)
                res.append(temp1)

                res_ID.append(temp["ID"])
                res_ID.append(temp1["ID"])

            i += 1
    return res

