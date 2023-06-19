//
// Created by 董绍启 on 2023/4/6.
//
#include "FullTime.h"
FullTime::FullTime(const string &name) : name(name),totalWork(0) {}

void FullTime::ptInfo(vector<Date*> holiday, vector<DayOff> Dayoffs) {
    printf("%-14s%-16s\n","姓名：",name.c_str());
    printf("%-14s%-16s\n","学号：",id.c_str());
    printf("%-14s%-16s\n","电话：",phone.c_str());
    printf("%-16s%-16s\n","所在楼栋：",building.c_str());
    printf("%-14s%-16s\n","宿舍：",dorm.c_str());
    printf("%-16s%d(工作日工作量：%.1f; 周末工作量：%.1f)\n","工作次数：",(int)this->OnWorklist.size(), this->countWeekdayWork(), this->countWeekendWork());
    for(int i =0; i < OnWorklist.size(); ++i){
        if(i == OnWorklist.size() - 1) {
            cout << OnWorklist[i]->StringDate(holiday,Dayoffs);
            cout << endl;
        }
        else{
            cout << OnWorklist[i]->StringDate(holiday,Dayoffs);
            cout << " ";
        }
    }
}

string FullTime::ExportBlankInfo(){
    double a = 0.0;
    stringstream s;
    s   << this->name << " "
        << this->id << " "
        << this->phone << " "
        << this->building << " "
        << this->dorm << " "
        << a;
    return s.str();
}

string FullTime::ExportInfo() {
    stringstream s;
    s   << this->name << " "
        << this->id << " "
        << this->phone << " "
        << this->building << " "
        << this->dorm << " "
        << this->totalWork;
    if((int)OnWorklist.size()){
        s << " ";
        for(int i = 0; i < OnWorklist.size(); ++i){
            if(i == OnWorklist.size()-1){
                s   << OnWorklist[i]->year << " "
                    << OnWorklist[i]->month << " "
                    << OnWorklist[i]->day<<" "
                    << OnWorklist[i]->comment<<" "
                    << OnWorklist[i]->isDouble<<" "
                    << OnWorklist[i]->isTriple << " "
                    << OnWorklist[i]->noon << " "
                    << OnWorklist[i]->workload;
                break;
            }
            s   << OnWorklist[i]->year << " "
                << OnWorklist[i]->month << " "
                << OnWorklist[i]->day << " "
                << OnWorklist[i]->comment<<" "
                << OnWorklist[i]->isDouble<<" "
                << OnWorklist[i]->isTriple << " "
                << OnWorklist[i]->noon << " "
                << OnWorklist[i]->workload << " ";
        }
    }
    return s.str();
}

bool FullTime::addWork(Date *d) {
    if(OnWorklist.empty()){
        OnWorklist.push_back(d);
        this->totalWork = OnWorklist.size();
        return true;
    }
    for(int i =0; i < this->OnWorklist.size(); ++i){
        if(OnWorklist[i]->equal(*d)) {
            cout << "error: " << "已插入 "<< this->name <<" 在 "<< d->pureDate() << " 的工作记录！" << endl;
            return false;
        }
        if(OnWorklist[i]->operator>(*d)){
            OnWorklist.insert(OnWorklist.begin()+i,d);
            this->totalWork = OnWorklist.size();
            return true;
        }
    }
    OnWorklist.push_back(d);
    this->totalWork = OnWorklist.size();
    return true;
}

FullTime::~FullTime() {
    if(!OnWorklist.empty()){
        for(int i =0; i < OnWorklist.size(); ++i){
            delete OnWorklist[i];
        }
    }
}

Date *FullTime::isWork(Date &d) {
    Date* work = NULL;
    for(int i =0; i < OnWorklist.size(); ++i){
        if(OnWorklist[i]->operator==(d) && OnWorklist[i]->n() == d.n()){
            work = OnWorklist[i];
            break;
        }
    }
    return work;
}

bool FullTime::deleteDate(Date &d) {
    Date* tmp = NULL;
    bool de = false;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        if((*this->OnWorklist[i]) == d){
            tmp = this->OnWorklist[i];
            this->OnWorklist.erase(OnWorklist.begin()+i);
            delete tmp;
            de = true;
        }
    }
    totalWork = OnWorklist.size();
    return de;
}

void FullTime::deleteOver(Date &d, int index, bool noon) {
    if(this->OnWorklist.empty()) return;
    Date* tmp = NULL;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        if(d.operator<=(*this->OnWorklist[i])){
            if((this->OnWorklist[i]->dayth() == index) && (this->OnWorklist[i]->n() == noon)) {
                tmp = this->OnWorklist[i];
                this->OnWorklist.erase(OnWorklist.begin()+i);
                delete tmp;
                i--;
            }
        }
    }
    totalWork = OnWorklist.size();
}

double FullTime::countWeekdayWork() {
    if(this->OnWorklist.empty()) return 0.0;
    double day_times = 0.0;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        int d = OnWorklist[i]->dayth();
        if((!OnWorklist[i]->Dou()) && (!OnWorklist[i]->Tri()) && d>=1 && d<=5) day_times += OnWorklist[i]->workload;
    }
    return day_times;
}

double FullTime::countWeekendWork() {
    if(this->OnWorklist.empty()) return 0.0;
    double end_times = 0.0;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        int d = OnWorklist[i]->dayth();
        if((!OnWorklist[i]->Dou()) && (!OnWorklist[i]->Tri()) && d>=1 && d<=5) continue;
        else end_times += OnWorklist[i]->workload;
    }
    return end_times;
}

void FullTime::deleteBetween(Date &begin, Date &end) {
    if(this->OnWorklist.empty()) return;
    Date* tmp = NULL;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        if(end.operator<(*this->OnWorklist[i])) break;
        if(begin.operator<=(*this->OnWorklist[i])){
            tmp = this->OnWorklist[i];
            this->OnWorklist.erase(OnWorklist.begin()+i);
            delete tmp;
            i--;
        }
    }
    totalWork = OnWorklist.size();
}

bool FullTime::deleteExact(Date &d) {
    if(this->OnWorklist.empty()) return false;
    Date* tmp = NULL;
    bool de = false;
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        if(this->OnWorklist[i]->equal(d)){
            tmp = this->OnWorklist[i];
            this->OnWorklist.erase(OnWorklist.begin()+i);
            delete tmp;
            de = true;
        }
    }
    totalWork = OnWorklist.size();
    return de;
}

double FullTime::countWeekdayWork(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> Dayoffs) {
    if(!this->OnWorklist.empty()) {
        double day_times = 0;
        bool empty = holiday.empty();
        bool off_empty = Dayoffs.empty();
        for (int i = 0; i < this->OnWorklist.size(); ++i) {
            if (end.operator<(*this->OnWorklist[i])) break;
            if (begin.operator<=(*this->OnWorklist[i])) {
                int d = OnWorklist[i]->dayth();
                bool in = false;
                bool of = false;
                int chan = 0;
                if(!empty) {
                    int size = holiday.size();
                    for (int j = 0; j < size; ++j) {
                        if (OnWorklist[i]->operator==(*holiday[j])) {
                            in = true;
                            break;
                        }
                    }
                } else in = false;
                if(!off_empty){
                    int size1 = Dayoffs.size();
                    for(int k = 0; k < size1; ++k){
                        if (OnWorklist[i]->operator==(Dayoffs[k].day)) {
                            of = true;
                            chan = Dayoffs[k].change;
                            break;
                        }
                    }
                } else of = false;
                if (((!in) && d >= 1 && d <= 5) || (of && chan >= 1 && chan <= 5)) day_times += OnWorklist[i]->workload;
            }
        }
        return day_times;
    }
    return 0.0;
}

double FullTime::countWeekendWork(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> Dayoffs) {
    if(this->OnWorklist.empty()) return 0.0;
    double end_times = 0;
    bool empty = holiday.empty();
    bool off_empty = Dayoffs.empty();
    for(int i = 0; i < this->OnWorklist.size(); ++i){
        if(end.operator<(*this->OnWorklist[i])) break;
        if(begin.operator<=(*this->OnWorklist[i])) {
            int d = OnWorklist[i]->dayth();
            bool in = false;
            bool of = false;
            int chan = 0;
            if(!empty) {
                int size = holiday.size();
                for (int j = 0; j < size; ++j) {
                    if (OnWorklist[i]->operator==(*holiday[j])) {
                        in = true;
                        break;
                    }
                }
            } else in = false;
            if(!off_empty){
                int size1 = Dayoffs.size();
                for(int k = 0; k < size1; ++k){
                    if (OnWorklist[i]->operator==(Dayoffs[k].day)) {
                        of = true;
                        chan = Dayoffs[k].change;
                        break;
                    }
                }
            } else of = false;
            if (((!in) && d >= 1 && d <= 5) || (of && chan >= 1 && chan <= 5)) continue;
            else end_times+= OnWorklist[i]->workload;
        }
    }
    return end_times;
}

string FullTime::StringDate(Date &begin, Date &end,vector<Date*> holiday, vector<DayOff> Dayoffs) {
    if(this->OnWorklist.empty()) return "";
    stringstream s;
    for(int i =0; i < OnWorklist.size(); ++i){
        if(end.operator<(*this->OnWorklist[i])) break;
        if(begin.operator<=(*this->OnWorklist[i])) {
            if ((i == OnWorklist.size() - 1) || (end.operator<(*this->OnWorklist[i+1]))) {
                s << OnWorklist[i]->StringDate(holiday,Dayoffs);
                break;
            } else {
                s << OnWorklist[i]->StringDate(holiday,Dayoffs);
                s << " ";
            }
        }
    }
    return s.str();
}

void FullTime::setBuilding(string building){
    this->building = building;
}

void FullTime::setPhone(string phone){
    this->phone = phone;
}

void FullTime::setDorm(string dorm){
    this->dorm = dorm;
}

string FullTime::ExportTxt(Date &begin, Date &end, vector<Date*> holiday, vector<DayOff> DayOffs, bool isD4){
    stringstream out;
    int d = begin.dayth();
    bool di = false;
    double total = 0.0;
    if(isD4) {
        for (Date o=begin; o <= end; o = o + 1) {
            bool isEnd = o == end;
            int a = d % 7;
            bool Holiday = this->isHoliday(holiday,o);
            DayOff *dayOff = this->isDayOff(DayOffs,o);
            Date* work = this->isWork(o);
            if (a == 6 || a == 0) {
                // 如果是星期六/星期天，如果工作，则输出工作量，如果未工作，则输出0
                if(work) out << work->workload << ",";
                else {
                    out << 0.00 << ",";
                }
            }
            else if (a == 1) {
                // 如果是星期一，
                // 如果结束，则输出该天工作量；
                // 如果是假期，则输出该天工作量；
                // 如果后一天是假期，则输出该天工作量；
                // 否则为正常情况，则不输出；
                if (isEnd) {
                    if(work) {
                        total = work->workload;
                        out << total << ",";
                    }
                    else{
                        out << 0.00 << ",";
                    }
                    break;
                }
                else if (Holiday) {
                    di = false;
                    total = 0.00;
                    if(work) out << work->workload << ",";
                    else out << 0.00 << ",";
                }
                else {
                    Date h = o + 1;
                    if (this->isHoliday(holiday,h)) {
                        di = false;
                        total = 0.00;
                        if(work) out << work->workload << ",";
                        else out << 0.00 << ",";
                    }
                    else {
                        di = true;
                        total = 0.00;
                        if(work) total += work->workload;
                    }
                }
            }
            else if (a == 5) {
                // 如果是星期五
                // 如果结束，则输出总工作量
                // 如果是假期，则输出总工作量
                // 否则为正常情况，输出总工作量
                if (isEnd) {
                    if(work) {
                        total += work->workload;
                        out << total << ",";
                    }
                    else{
                        out << total << ",";
                    }
                    break;
                }
                else {
                    di = false;
                    if(work) {
                        total += work->workload;
                        out << total << ",";
                    }
                    else{
                        out << total << ",";
                    }
                    total = 0.00;
                }
            }
            else {
                // a >= 2 && a <= 4
                // 输出格式：workload/不输出
                // 如果到截止，则输出总工作量
                // 如果是节假日，则输出总工作量
                // 如果是开始且后一天非节假日，则不输出
                // 如果是开始且后一天是节假日，则输出该天工作量
                // 如果不是开始且后一天非节假日，则不输出
                // 如果不是开始且后一天是节假日，则输出总工作量
                if (isEnd) {
                    if(work) {
                        total += work->workload;
                        out << total << ",";
                    }
                    else{
                        out << total << ",";
                    }
                    break;
                }
                else if (Holiday) {
                    di = false;
                    if(work) {
                        total += work->workload;
                        out << total << ",";
                    }
                    else{
                        out << total << ",";
                    }
                    total = 0.00;
                }
                else {
                    Date h = o + 1;
                    bool holi = this->isHoliday(holiday,h);
                    if (!di) { // 开始
                        if (holi) {
                            di = false;
                            if(work) {
                                total += work->workload;
                                out << total << ",";
                            }
                            else{
                                out << total << ",";
                            }
                            total = 0.00;
                        }
                        else {
                            di = true;
                            if(work) total += work->workload;
                        }
                    }
                    else {
                        if (holi) {
                            di = false;
                            if(work){
                                total += work->workload;
                                out << total << ",";
                            }
                            else out << total << ",";
                            total = 0.00;
                        } else {
                            di = true;
                            if(work) total += work->workload;
                        }
                    }
                }
            }
            d++;
        }
    }
    else{
        for (Date o=begin; o <= end; o = o + 1) {
            int a = d % 7;
            bool Holiday = this->isHoliday(holiday,o);
            DayOff *dayOff = this->isDayOff(DayOffs,o);
            Date* work = this->isWork(o);
            if (a == 6 || a == 0) {
                // 如果是星期六/星期天，如果是调休，则不输出，如果工作，则输出工作量
                if(dayOff){}
                else if(work) out << work->workload << ",";
                else out << 0.00 << ",";
            }
            else {
                // a >= 1 && a <= 5
                // 输出格式：workload/不输出
                // 如果是节假日，则输出总工作量
                // 否则不输出
                if (Holiday) {
                    if(work) {
                        out << work->workload << ",";
                    }
                    else out << 0.00 << ",";
                }
            }
            d++;
        }
    }
    return out.str();
}

bool FullTime::isHoliday(vector<Date*> holiday, Date &d){
    bool in = false;
    if(holiday.empty()) return false;
    for(int i = 0; i < holiday.size(); ++i){
        if(holiday[i]->operator==(d)){
            in = true;
            break;
        }
    }
    return in;
}

DayOff* FullTime::isDayOff(vector<DayOff> DayOffs, Date &d){
    if(DayOffs.empty()) return NULL;
    for(int i = 0; i < DayOffs.size(); ++i){
        if(DayOffs[i].day == d){
            return &DayOffs[i];
        }
    }
    return NULL;
}




