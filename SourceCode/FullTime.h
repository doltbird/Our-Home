//
// Created by 董绍启 on 2023/4/6.
//

#ifndef ONDUTY_H
#define ONDUTY_H
#include "string"
using namespace std;
#include "stdlib.h"
#include "iostream"
#include "Date.h"
#include "vector"
#include "sstream"
#include <algorithm>
class Date;
struct DayOff;
class FullTime {
private:
    string phone;
    string dorm;
    string building;
    vector<Date*> OnWorklist;
    int totalWork;
public:
    string id;
    string name;

    explicit FullTime(const string &name);

    void addInfo(string id, string phone, string building, string dorm){
        this->id = id;
        this->dorm = dorm;
        this->phone = phone;
        this->building = building;
    }
    bool addWork(Date* d);
    void ptInfo(vector<Date*> holiday, vector<DayOff> Dayoffs);
    string ExportInfo();
    string ExportBlankInfo();
    Date* isWork(Date &d);
    virtual ~FullTime();
    bool deleteDate(Date &d); // 删除日期为d的所有值班记录
    void deleteOver(Date &d, int index, bool noon); // 删除从d开始、星期index、noon午的所有值班
    void deleteBetween(Date &begin, Date &end);
    bool deleteExact(Date &d);
    double countWeekdayWork();
    double countWeekdayWork(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> Dayoffs);
    double countWeekendWork();
    double countWeekendWork(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> Dayoffs);
    string StringDate(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> Dayoffs);
    void setBuilding(string building);
    void setPhone(string phone);
    void setDorm(string dorm);
    string ExportTxt(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> DayOffs, bool isD4);
    bool isHoliday(vector<Date*> holiday, Date &d);
    DayOff* isDayOff(vector<DayOff> DayOffs, Date &d);
};



#endif //ONDUTY_H
