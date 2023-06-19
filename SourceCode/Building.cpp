//
// Created by 董绍启 on 2023/4/12.
//

#include "Building.h"

Building::~Building() {}

Building::Building(string building_name) {
    name = building_name;
    for(int i = 0; i<7;++i){
        onDutyList[i].forenoon = NULL;
        onDutyList[i].afternoon = NULL;
    }
}

void Building::addOnDuty(int day,FullTime* staff,bool noon) {
    if(!noon) onDutyList[day].forenoon = staff;
    else onDutyList[day].afternoon = staff;
}

void Building::ptOnDuty() {
    cout << this->name << "值班表:" << endl;
    if(this->name == "D34" || this->name == "D35") {
        cout << "\t星期一上午: " << onDutyList[1].forenoon->name;
        cout << "\t星期一下午: " << onDutyList[1].afternoon->name << endl;
        cout << "\t星期二上午: " << onDutyList[2].forenoon->name ;
        cout << "\t星期二下午: " << onDutyList[2].afternoon->name << endl;
        cout << "\t星期三上午: " << onDutyList[3].forenoon->name ;
        cout << "\t星期三下午: " << onDutyList[3].afternoon->name << endl;
        cout << "\t星期四上午: " << onDutyList[4].forenoon->name ;
        cout << "\t星期四下午: " << onDutyList[4].afternoon->name << endl;
        cout << "\t星期五上午: " << onDutyList[5].forenoon->name ;
        cout << "\t星期五下午: " << onDutyList[5].afternoon->name << endl;
        cout << "\t星期六: " << onDutyList[6].forenoon->name;
        cout << " " << onDutyList[6].afternoon->name << endl;
        cout << "\t星期天: " << onDutyList[0].forenoon->name;
        cout << " " << onDutyList[0].afternoon->name << endl;
    }
    else{
        cout << "\t星期六: " << onDutyList[6].forenoon->name<<endl;
        cout << "\t星期天: " << onDutyList[0].forenoon->name<<endl;
    }
}

string Building::ExportOnduty() {
    stringstream s;
    if(this->name == "D34" || this->name == "D35") {
        for(int i =0; i < 7;++i){
            if(i == 6){
                s   << onDutyList[i].forenoon->name << " "
                    << onDutyList[i].afternoon->name;
                break;
            } else{
                s   << onDutyList[i].forenoon->name << " "
                    << onDutyList[i].afternoon->name<<" ";
            }
        }
    }else{
        s   << onDutyList[6].forenoon->name << " "
            << onDutyList[0].forenoon->name ;
    }
    return s.str();
}

void Building::addWork(Date *work, int index, bool noon) {
    if(!noon) {
        this->onDutyList[index].forenoon->addWork(work);
        return;
    }
    this->onDutyList[index].afternoon->addWork(work);
}

FullTime *Building::FindOnDuty(int day, string index, bool noon) {
    FullTime* re = NULL;
    bool isname = true;
    if(index[0]>='0' && index[0] <= '9'){
        isname = false;
    }
    if(isname){
        if(!noon) {
            if (this->onDutyList[day].forenoon->name == index) re = this->onDutyList[day].forenoon;
        }
        else{
            if (this->onDutyList[day].afternoon->name == index) re = this->onDutyList[day].afternoon;
        }
    }else{
        if(!noon) {
            if (this->onDutyList[day].forenoon->id == index) re = this->onDutyList[day].forenoon;
        }
        else{
            if (this->onDutyList[day].afternoon->id == index) re = this->onDutyList[day].afternoon;
        }
    }
    return re;
}

bool Building::FindWeekend(int day, string index) {
    if(this->FindOnDuty(day, index, false)) return false;
    if(this->FindOnDuty(day, index, true)) return true;
    return false;
}


