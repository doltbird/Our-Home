//
// Created by 董绍启 on 2023/4/12.
//

#include "DormArea.h"

void DormArea::addBuilding(string building) {
    Building* b = new Building(building);
    this->upOrderInsert(b);
}
void DormArea::upOrderInsert(Building* b){
    int size = this->dormlist.size();
    int b_num = atoi(b->name.c_str() + 1);
    for(int i = 0 ; i < size; ++i){
        int b1_num = atoi(this->dormlist[i]->name.c_str() + 1);
        if(b1_num > b_num){
            this->dormlist.insert(this->dormlist.begin() + i,b);
            return;
        }
    }
    this->dormlist.push_back(b);
    return;
}

DormArea::~DormArea() {
    for(vector<Building*>::iterator it = dormlist.begin();
    it != dormlist.end();
    ++it){
        if(*it) delete(*it);
    }

}

void DormArea::addStaff(string building, FullTime* staff, int day,bool noon) {
    vector<Building*>::iterator it = dormlist.begin();
    for(;
        it != dormlist.end();
        ++it){
        if(strcasecmp((*it)->name.c_str(),building.c_str()) == 0) break;
    }
    (*it)->addOnDuty(day,staff, noon);
}

void DormArea::ptDormList() {
    vector<Building*>::iterator it = dormlist.begin();
    cout << this->name <<"区:"<< endl;
    for(;it != dormlist.end();++it){
        cout << (*it)->name << " ";
    }
    cout << endl;
}

void DormArea::ptDorm(string building) {
    bool in = false;
    vector<Building*>::iterator it = dormlist.begin();
    for(;
            it != dormlist.end();
            ++it){
        if(strcasecmp((*it)->name.c_str(),building.c_str()) == 0) {
            in = true;
            break;
        }
    }
    if(!in){
        cout << "error: " << building << " 不属于 " << this->name << "区!" << endl;
        return;
    }
    (*it)->ptOnDuty();
}

string DormArea::ExportBuildings() {
    stringstream s;
    for(int i =0; i < dormlist.size();++i){
        if(i == dormlist.size()-1){
            s << dormlist[i]->name;
            break;
        } else{
            s << dormlist[i]->name<<" ";
        }
    }
    return s.str();
}


