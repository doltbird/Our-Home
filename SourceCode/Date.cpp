//
// Created by 董绍启 on 2023/4/15.
//

#include "Date.h"
bool Date::operator<(const Date &d) {
    if(d.year > this->year) return true;
    else if (d.year < this->year) return false;
    else if (d.month > this->month) return true;
    else if (d.month < this->month) return false;
    else if (d.day > this->day) return true;
    else return false;
}

bool Date::operator==(const Date &d) {
    if(d.year != this->year) return false;
    else if(d.month != this->month) return false;
    else return d.day == this->day;
}

bool Date::operator>(const Date &d) {
    if(d.year < this->year) return true;
    else if (d.year > this->year) return false;
    else if (d.month < this->month) return true;
    else if (d.month > this->month) return false;
    else if (d.day < this->day) return true;
    else return false;
}

bool Date::isValid() {
    if(this->year < 2023) return false;
    else if(this->month <= 0 || this->month > 12) return false;
    else {
        switch (this->month) {
            case 2:
                if(is_leapyear(this->year)){
                    return (this->day >= 1 && this->day <= 29);
                } else return (this->day >= 1 && this->day <= 28);
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
                return (this->day >= 1 && this->day <= 31);
            case 4:case 6:case 9:case 11:
                return (this->day >= 1 && this->day <= 30);
            default:
                return false;
        }
    }
}

bool Date::operator<=(const Date &d) {
    return this->operator<(d) || this->operator==(d);
}

bool Date::operator>=(const Date &d) {
    return this->operator>(d) || this->operator==(d);
}

int Date::dateLength() {
    int leap_year[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int common_year[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int* year_arr = NULL;
    int days = 0;
    for(int y = Year,m = Month; y <= this->year;){
        if(Year== this->year) {
            if(is_leapyear(Year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= this->month;) {
                if(Month == this->month){
                    days += this->day - Day;
                    break;
                }
                else if (m == this->month) {
                    days += this->day;
                    break;
                }
                else if (m == Month) {
                    days += year_arr[m] - Day;
                }
                else {
                    days += year_arr[m];
                }
                m++;
            }
            break;
        }
        else if(y == this->year) {
            if(is_leapyear(this->year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= this->month;) {
                if(m == this->month) {
                    days += this->day;
                    break;
                }
                else{
                    days += year_arr[m];
                }
                m++;
            }
            break;
        }
        else if(y == Year) {
            if(is_leapyear(Year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= 12;) {
                if(m == Month) {
                    days += year_arr[m] - Day;
                }
                else{
                    days += year_arr[m];
                }
                m++;
            }
            y++;
            m = 1;
        }
        else{
            if(is_leapyear(y)){
                days += 366;
            }
            else{
                days += 365;
            }
            y++;
            m = 1;
        }
    }

    return days;
}

Date::Date(){
    this->isDouble= false;
    this->isTriple = false;
    this->year = 2023;
    this->month = 2;
    this->day = 13;
    this->noon= false;
    this->workload = 1.0;
    this->comment = "0";
}

Date::Date(const Date &d) {
    this->year = d.year;
    this->month = d.month;
    this->day = d.day;
    this->noon = d.noon;
    this->isDouble = d.isDouble;
    this->isTriple = d.isTriple;
    this->comment = d.comment;
    this->workload = d.workload;
}

int Date::dateLength(const Date &d) {
    int leap_year[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int common_year[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int* year_arr = NULL;
    int days = 0;
    for(int y = d.year,m = d.month; y <= this->year;){
        if(d.year== this->year) {
            if(is_leapyear(d.year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= this->month;) {
                if(d.month == this->month){
                    days += this->day - d.day;
                    break;
                }
                else if (m == this->month) {
                    days += this->day;
                    break;
                }
                else if (m == d.month) {
                    days += year_arr[m] - d.day;
                }
                else {
                    days += year_arr[m];
                }
                m++;
            }
            break;
        }
        else if(y == this->year) {
            if(is_leapyear(this->year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= this->month;) {
                if(m == this->month) {
                    days += this->day;
                    break;
                }
                else{
                    days += year_arr[m];
                }
                m++;
            }
            break;
        }
        else if(y == d.year) {
            if(is_leapyear(d.year)) year_arr = leap_year;
            else year_arr = common_year;
            for (; m <= 12;) {
                if(m == d.month) {
                    days += year_arr[m] - d.day;
                }
                else{
                    days += year_arr[m];
                }
                m++;
            }
            y++;
            m = 1;
        }
        else{
            if(is_leapyear(y)){
                days += 366;
            }
            else{
                days += 365;
            }
            y++;
            m = 1;
        }
    }

    return days;
}

Date Date::operator+(int d) {
    int leap_year[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int common_year[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int* year_arr = NULL;
    if(is_leapyear(this->year)) year_arr = leap_year;
    else year_arr = common_year;
    Date tmp;
    bool isNewYear = false;
    bool isNewMonth = false;
    if((this->day + 1) > year_arr[this->month]) isNewMonth = true;
    if(isNewMonth && ((this->month + 1) > 12)) isNewYear = true;
    int year = this->year, month = this->month, day = this->day;
    if(isNewYear) {
        year++;
        month = 1;
        day = 1;
    }
    else if(isNewMonth) {
        month++;
        day = 1;
    } else day+=d;
    tmp.setDate(year,month,day);
    return tmp;
}

bool Date::equal(const Date &d) {
    return (this->year == d.year) && (this->month == d.month) && (this->day == d.day) && (this->isDouble == d.isDouble)
    && (this->isTriple == d.isTriple) && (this->noon == d.noon);
}

string Date::StringDate(vector<Date*> holiday, vector<DayOff> Dayoffs){
    stringstream s;
    s << year << "年"  << month << "月" << day << "日";
    // 如果是假期，则没有上下午，有加倍
    // 如果是调休，没有加倍，有上下午
    // 如果是平时，周内有上下午，周末没有
    bool hol = false;
    bool off = false;
    int chan = -1;
    if(!holiday.empty()) {
        for (int i = 0; i < holiday.size(); ++i){
            if(this->operator==(*holiday[i])){
                hol = true;
                break;
            }
        }
    }
    if(!Dayoffs.empty()){
        for(int i = 0; i < Dayoffs.size(); ++i){
            if(this->operator==(Dayoffs[i].day)){
                off = true;
                chan = Dayoffs[i].change;
                break;
            }
        }
    }
    if(off){
        if(chan >= 1 && chan <= 5){
            string h;
            if(!this->noon) h = "[调休](上午)";
            else{
                h = "[调休](下午)";
            }
            s << h;
        }
    }
    else if(hol) {
        if (this->isDouble) {
            string h;
            h = "(双倍)";
            s << h;
        } else if (this->isTriple) {
            string h;
            h = "(三倍)";
            s << h;
        }
    }
    else{
        int dat = this->dayth();
        if(dat >= 1 && dat <= 5){
            string h;
            if(!this->noon) h = "(上午)";
            else{
                h = "(下午)";
            }
            s << h;
        }
    }
    if (this->comment[0] != '0') s <<"->"<< this->comment;
    return s.str();
}

Date Date::operator-(int d) {
    int leap_year[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int common_year[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int* year_arr = NULL;
    if(is_leapyear(this->year)) year_arr = leap_year;
    else year_arr = common_year;
    Date tmp;
    bool isNewYear = false;
    bool isNewMonth = false;
    if((this->day - 1) == 0) isNewMonth = true;
    if(isNewMonth && ((this->month - 1) == 0)) isNewYear = true;
    int year = this->year, month = this->month, day = this->day;
    if(isNewYear) {
        year--;
        month = 12;
        day = 31;
    }
    else if(isNewMonth) {
        month--;
        day = year_arr[month];
    } else day-=d;
    tmp.setDate(year,month,day);
    return tmp;
};



