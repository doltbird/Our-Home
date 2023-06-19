//
// Created by 董绍启 on 2023/4/12.
//

#ifndef MAIN_BUILDING_H
#define MAIN_BUILDING_H
#include "FullTime.h"
#include "string"
#include "iostream"
#include "sstream"
using namespace std;
struct DutyDay{
    FullTime* forenoon;
    FullTime* afternoon;
};
class Building {
public:
    string name;
    Building(string building_name);
    ~Building();
    void ptOnDuty();

    // 加入常任值班员
    // day: 0->星期天；1->星期一
    // noon: 0->上午; 1->下午
    void addOnDuty(int day, FullTime* staff,bool noon=false);

    // 查找常任值班员
    // day: 0->星期天；1->星期一
    // noon: 0->上午; 1->下午
    FullTime* FindOnDuty(int day, string index,bool noon=false);
    string ExportOnduty();
    void addWork(Date* work, int index, bool noon = false);
    bool FindWeekend(int day, string index);
private:
    DutyDay onDutyList[7];
};


#endif //MAIN_BUILDING_H
