//
// Created by 董绍启 on 2023/4/12.
//

#ifndef MAIN_DORMAREA_H
#define MAIN_DORMAREA_H
#include "vector"
#include "string"
#include "Building.h"
#include "FullTime.h"
#include "iostream"
#include "sstream"
using namespace std;
class DormArea {
public:
    vector<Building*> dormlist;
    string name;
    void addBuilding(string building);

    // day: 0->星期天；1->星期一
    // noon: 0->上午; 1->下午
    void addStaff(string building, FullTime* staff,int day,bool noon = false);
    void ptDormList();
    void ptDorm(string building);
    string ExportBuildings();
    void upOrderInsert(Building* b);
    ~DormArea();
};


#endif //MAIN_DORMAREA_H
