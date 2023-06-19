//
// Created by 董绍启 on 2023/4/12.
//

#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H
#include "vector"
#include "string"
#include "DormArea.h"
#include "FullTime.h"
#include "Building.h"
#include "Date.h"
#include "fstream"
#include "iostream"
#include "stdlib.h"
#include "assert.h"
#include "algorithm"
#define WEEKDAY 50
#define WEEKEND 120
using namespace std;
struct Blank{
    Date begin;
    Date end;
};
class Manager {
private:
    DormArea area;
    int area_num;
    vector<FullTime*> staff_list;
    vector<FullTime*> part_time;
    vector<Blank> blankDays;
    vector<DayOff> DayOffs;
    vector<Date*> holiday;
    Date wageBegin;
    Date wageEnd;
    string path;
public:
    string name;
    string id;
    void ptstate(); // 打印当前状态
    void load(string path);
    void Export(string path);
    void FulltoPart(); // 替换常任值班员

    // index: 学号id或姓名name
    FullTime* findStaff(string index);
    bool Find(string index);
    virtual ~Manager();
    void setWages(); // 写入工资
    void InputHoliday(); // 设置节假日
    void addHoliday(Date &holiday);
    void setRelief(); // 设置替班
    void addRelief(Date* d);
    Building* findBuilding(string name);
    void initStaff(Date begin, Date end, Building* building, int index, bool noon);
    void helpInfo();
    void Execute();
    void commandI();
    void commandA();
    void commandB();
    void commandP(Date begin, Date end);
    void commandD(Date begin, Date end);
    void addBetween(Date &begin, Date &end);
    void commandN();
    void commandF();
    void commandJ();
    void commandC();
    void commandO();
    void commandDeduct();
    void ptWage();
    void initManager(); // 第一次初始化
    void initBuiding(); // 加入各楼栋的值班员
    void addBuilding(string building); // 添加楼栋并初始化
    FullTime* inputStaff(string building, int day, bool noon);
    FullTime* inputStaff(string building, Date& holiday);
    FullTime* inputStaff(string info);
    void modifyStaff(string index);
    void updateBlank(Date &begin, Date &end);
    void fillInBlank(Date &begin, Date &end);
    void jointBlank();
    void setDayOff();
    void exportDetail(Date &begin, Date &end);
    void exportBrief(Date &begin, Date &end);
    string divideDate(Date &begin, Date &end);
    bool isHoliday(Date &d);
    DayOff* isDayOff(Date &d);
    double getnumDivide(char *arr );
};


#endif //MAIN_MANAGER_H
