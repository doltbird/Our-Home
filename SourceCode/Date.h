//
// Created by 董绍启 on 2023/4/15.
//

#ifndef MAIN_DATE_H
#define MAIN_DATE_H
#include "string"
#include "FullTime.h"
#include "iostream"
#include "sstream"
using namespace std;
#define Year 2023
#define Month  2
#define Day 12
struct DayOff;
class Date {
    friend class FullTime;
private:
    double workload;
    bool isDouble;
    bool isTriple;
    int year;
    int month;
    int day;
    bool noon; // 0:forenoon 1:afternoon
    string comment;
public:
    Date();
    Date(const Date &d);
    Date( int year, int month, int day,bool noon = false, bool isDouble = false, bool isTriple = false, double workload = 1.0){
        this->isDouble = isDouble;
        this->isTriple = isTriple;
        this->year = year;
        this->month = month;
        this->day = day;
        this->noon = noon;
        this->workload = workload;
        this->comment = "0";
    }
    void setDate( int year, int month, int day,bool noon = false){
        this->year = year;
        this->month = month;
        this->day = day;
        this->noon = noon;
    }
    void setWorkload(double a){this->workload = a;};
    bool operator< (const Date &d);
    bool operator== (const Date &d);
    bool operator> (const Date &d);
    bool operator<= (const Date &d);
    bool operator>= (const Date &d);
    Date operator+ (int d);
    Date operator- (int d);
    bool isValid();
    bool is_leapyear(int year){
        return !(year%4);
    };
    string StringDate(vector<Date*> holiday, vector<DayOff> Dayoffs);
    string pureDate(){
        stringstream s;
        s << year << "年"  << month << "月" << day << "日";
        return s.str();
    }
    int dayth(){return this->dateLength() % 7;}; // 0:星期天
    int dateLength(); // 求出当前日期距离2023年2月12日多少天
    int dateLength(const Date &d); // 求出当前日期距离d多少天
    void setDouble(){isDouble = true;workload = 2.0;};
    void setTriple(){isTriple = true;workload = 3.0;};
    int y(){return this->year;};
    int m(){return this->month;};
    int d(){return this->day;};
    bool n(){return this->noon;};
    bool Dou(){return this->isDouble;};
    bool Tri(){return this->isTriple;};
    double w(){return this->workload;};
    void addComment(string s){
        this->comment = s;
    };
    bool equal(const Date &d);
};
struct DayOff{
    Date day;
    int change;
};

#endif //MAIN_DATE_H
