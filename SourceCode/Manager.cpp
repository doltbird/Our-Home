//
// Created by 董绍启 on 2023/4/12.
//
#include "Manager.h"

void Manager::load(string path) {
    ifstream in;
    vector<string>buffer;
    size_t pos1, pos2;
    Building* b = NULL;
    FullTime* o = NULL;
    in.open(path);
    if (!in.is_open()) {
        this->initManager();
        return;
    }
    string line;
    pos1 = 0;
    while (getline(in, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        buffer.clear();
        char symbol = line[0];
        pos1 = 0;

        // 将该行所有token存入buffer
        while (true) {
            pos2 = line.find(' ', pos1 + 1);
            if (pos2 == string::npos) {
                buffer.push_back(line.substr(pos1, string::npos));
                break;
            }
            else {
                if (pos1 == 0) {
                    buffer.push_back(line.substr(pos1 + 1, pos2 - pos1 - 1));
                }
                else {
                    buffer.push_back(line.substr(pos1, pos2 - pos1));
                }
            }
            pos1 = pos2 + 1;
        }

        // 分类创建对象
        FullTime* staff1 = NULL, * staff2 = NULL;
        int counts = 0;
        int de = 0;
        int year = 2013;
        int month = 2;
        int day = 13;
        int change = 0;
        bool D = false, T = false, N = false;
        int size = 0;
        int size1 = 0;
        int beg = 0;
        double l = 1.0;
        Date* d;
        DayOff off;
        Date of;
        switch (symbol) {
            case 'M':
                this->name = buffer[0];
                this->id = buffer[1];
                this->wageBegin.setDate(atoi(buffer[2].c_str()), atoi(buffer[3].c_str()), atoi(buffer[4].c_str()));
                this->wageEnd.setDate(atoi(buffer[5].c_str()), atoi(buffer[6].c_str()), atoi(buffer[7].c_str()));
                size = atoi(buffer[8].c_str());
                if (size) {
                    for (int i = 0; i < size; ++i) {
                        year = atoi(buffer[8 + 5 * i + 1].c_str());
                        month = atoi(buffer[8 + 5 * i + 2].c_str());
                        day = atoi(buffer[8 + 5 * i + 3].c_str());
                        D = atoi(buffer[8 + 5 * i + 4].c_str());
                        T = atoi(buffer[8 + 5 * i + 5].c_str());
                        d = new Date(year, month, day, false, D, T);
                        this->holiday.push_back(d);
                    }
                }
                beg = 8 + 5 * size + 1;
                size1 = atoi(buffer[beg].c_str());
                if(size1){
                    for(int i = 0; i < size1; ++i){
                        year = atoi(buffer[beg + 4 * i + 1].c_str());
                        month = atoi(buffer[beg + 4 * i + 2].c_str());
                        day = atoi(buffer[beg + 4 * i + 3].c_str());
                        change = atoi(buffer[beg + 4 * i + 4].c_str());
                        of.setDate(year,month,day);
                        off.day = of;
                        off.change = change;
                        this->DayOffs.push_back(off);
                    }
                }
                break;
            case 'A':
                this->area.name = buffer[0];
                for (int i = 1; i < buffer.size(); ++i) {
                    area.addBuilding(buffer[i]);
                }
                //                this->area.ptDormList();
                break;
            case 'B':
                if (buffer[0] == "D34" || buffer[0] == "D35") {
                    for (int i = 0; i <= 6; ++i) {
                        staff1 = findStaff(buffer[2 * (i + 1) - 1]);
                        if (staff1 == NULL) {
                            staff1 = new FullTime(buffer[2 * (i + 1) - 1]);
                            this->staff_list.push_back(staff1);
                        }
                        staff2 = findStaff(buffer[2 * (i + 1)]);
                        if (!staff2) {
                            staff2 = new FullTime(buffer[2 * (i + 1)]);
                            this->staff_list.push_back(staff2);
                        }
                        this->area.addStaff(buffer[0], staff1, i, false);
                        this->area.addStaff(buffer[0], staff2, i, true);
                    }
                }
                else {
                    staff1 = findStaff(buffer[1]);
                    if (!staff1) {
                        staff1 = new FullTime(buffer[1]);
                        this->staff_list.push_back(staff1);
                    }
                    staff2 = findStaff(buffer[2]);
                    if (!staff2) {
                        staff2 = new FullTime(buffer[2]);
                        this->staff_list.push_back(staff2);
                    }
                    this->area.addStaff(buffer[0], staff1, 6, false);
                    this->area.addStaff(buffer[0], staff2, 0, false);
                }
                //                this->area.ptDorm(buffer[0]);
                break;
            case 'O':
                staff1 = this->findStaff(buffer[0]);
                staff1->addInfo(buffer[1], buffer[2], buffer[3], buffer[4]);

                counts = atoi(buffer[5].c_str());
                if (counts) {
                    for (int i = 0; i < counts; ++i) {
                        year = atoi(buffer[5 + 8 * i + 1].c_str());
                        month = atoi(buffer[5 + 8 * i + 2].c_str());
                        day = atoi(buffer[5 + 8 * i + 3].c_str());
                        D = atoi(buffer[5 + 8 * i + 5].c_str());
                        T = atoi(buffer[5 + 8 * i + 6].c_str());
                        N = atoi(buffer[5 + 8 * i + 7].c_str());
                        l = atof(buffer[5 + 8 * i + 8].c_str());
                        d = new Date(year, month, day, N, D, T, l);
                        d->addComment(buffer[5 + 8 * i + 4]);
                        staff1->addWork(d);
                    }
                }
                //                staff1->ptInfo();
                break;
            case 'P':
                staff1 = new FullTime(buffer[0]);
                staff1->addInfo(buffer[1], buffer[2], buffer[3], buffer[4]);
                counts = atoi(buffer[5].c_str());
                if (counts) {
                    for (int i = 0; i < counts; ++i) {
                        year = atoi(buffer[5 + 8 * i + 1].c_str());
                        month = atoi(buffer[5 + 8 * i + 2].c_str());
                        day = atoi(buffer[5 + 8 * i + 3].c_str());
                        D = atoi(buffer[5 + 8 * i + 5].c_str());
                        T = atoi(buffer[5 + 8 * i + 6].c_str());
                        N = atoi(buffer[5 + 8 * i + 7].c_str());
                        l = atof(buffer[5 + 8 * i + 8].c_str());
                        d = new Date(year, month, day, N, D, T, l);
                        d->addComment(buffer[5 + 8 * i + 4]);
                        staff1->addWork(d);
                    }
                }
                this->part_time.push_back(staff1);
                //                staff1->ptInfo();
                break;
            default:
                break;
        }
    }
    in.close();
}

void Manager::FulltoPart() {
    string index;
    string id, phone, building, dorm, bname;
    int d = 0;
    bool noon = false;
    char symbol = 'Y';
    FullTime* staff = NULL;
    Building* b = NULL;
    do {
        cout << "请输入原常任值班员姓名/学号: ";
        cin >> index;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'Y' && symbol != 'y');
    cout << "请输入原常任值班员任职的楼栋名（eg:D33/X15）: ";
    cin >> bname;
    b = this->findBuilding(bname);
    if (!b) {
        cout << "error: " << bname << " 不属于" << this->area.name << "区!" << endl;
        return;
    }
    cout << "请输入原常任值班员任职的是（0->星期天；1->星期一；2->星期二 ...）: ";
    cin >> d;
    if (bname == "D34" || bname == "D35") {
        if (d >= 1 && d <= 5) {
            cout << "请输入原常任值班员任职的是上午/下午（0->上午；1->下午）: ";
            cin >> noon;
        }
        else {
            noon = b->FindWeekend(d, index);
        }
    }
    staff = b->FindOnDuty(d, index, noon);
    if (!staff) {
        cout << "error: " << index << " 不是原常任值班员!" << endl;
        return;
    }
    // 这步以后得到：staff：老值班员、b：所需替换楼栋、d：所需替换日期、noon：上午/下午

    // 得到合法替换起始日期
    int year, month, day;
    Date rBegin;
    bool valid = false;
    while (!valid) {
        cout << "请输入从哪一天开始替换: " << endl;
        cout << "年: ";
        cin >> year;
        cout << "月: ";
        cin >> month;
        cout << "日: ";
        cin >> day;
        rBegin.setDate(year, month, day);
        valid = rBegin.isValid();
        if (!valid) {
            cout << "error: 输入日期不合法！请重新输入" << endl;
        }
        else {
            break;
        }
    }
    // 这步以后得到：rBegin：替换日期



    // 输入新常任值班员姓名/学号
    string newp("");
    char psymbol;
    bool ispname = true;
    do {
        cout << "请输入新常任值班员姓名/学号: ";
        cin >> newp;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> psymbol;
    } while (psymbol != 'Y' && psymbol != 'y');
    if (index == newp) {
        cout << "error: " << index << " 不能和自己交换值班日期！" << endl;
        return;
    }

    // 若新常任值班员在stafflist中，意味着这是常任值班员相互交换，需要更改值班表，并重新初始化双方替换日期后的值班记录
    bool in = false;
    if (newp[0] >= '0' && newp[0] <= '9') {
        ispname = false;
    }
    else {
        ispname = true;
    }
    if (ispname) {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->name == newp) {
                in = true;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->id == newp) {
                in = true;
                break;
            }
        }
    }
    if (in) {
        string pbname;
        Building* pb;
        int pd;
        FullTime* pf;
        bool pnoon = false;
        cout << newp << " 和 " << index << " 交换常任值班日期！" << endl;
        cout << "请输入 " << newp << " 之前任职的楼栋名（eg:D33/X15）: ";
        cin >> pbname;
        pb = this->findBuilding(pbname);
        if (!pb) {
            cout << "error: " << pbname << " 不属于" << this->area.name << "区!" << endl;
            return;
        }
        cout << "请输入 " << newp << " 之前任职的是（0->星期天；1->星期一；2->星期二 ...）: ";
        cin >> pd;
        if (pbname == "D34" || pbname == "D35") {
            if (pd >= 1 && pd <= 5) {
                cout << "请输入 " << newp << " 之前任职的是上午/下午（0->上午；1->下午）: ";
                cin >> pnoon;
            }
            else {
                pnoon = pb->FindWeekend(pd, newp);
            }
        }
        pf = pb->FindOnDuty(pd, newp, pnoon);
        if (!pf) {
            cout << "error: " << newp << " 不是原常任值班员!" << endl;
            return;
        }

        // 交换值班表
        b->addOnDuty(d, pf, noon);
        pb->addOnDuty(pd, staff, pnoon);

        // 交换二者在员工表中的位置
        int sb = 0, spb = 0;
        for (int i = 0; i < this->staff_list.size(); ++i) {
            if (this->staff_list[i] == staff) sb = i;
            if (this->staff_list[i] == pf) spb = i;
        }
        swap(this->staff_list[sb], this->staff_list[spb]);

        // 分别删除交换日期之后,之前的值班记录
        pf->deleteOver(rBegin, pd, pnoon);
        staff->deleteOver(rBegin, d, noon);

        // 初始化交换日期之后的值班记录
        this->initStaff(rBegin, this->wageEnd, b, d, noon);
        this->initStaff(rBegin, this->wageEnd, pb, pd, pnoon);
        return;
    }
    // 这步以后得到：newp：新值班员索引

    // 若新常任值班员不在stafflist中，意味着是老常任值班员辞职
    // 需要将老常任值班员从值班表中删除、从stafflist中删除，加入parttime，并将新值班员加入stafflist和值班表

    // 在parttime中查找替班员，若没找到则说明是新值班员，需新建并录入信息；若找到则需要将新值班员从parttime中删除
    FullTime* pf = NULL;
    bool isPart = false;
    if (ispname) {
        for (int i = 0; i < part_time.size(); ++i) {
            if (part_time[i]->name == newp) {
                pf = part_time[i];
                part_time.erase(part_time.begin() + i);
                isPart = true;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < part_time.size(); ++i) {
            if (part_time[i]->id == newp) {
                pf = part_time[i];
                part_time.erase(part_time.begin() + i);
                isPart = true;
                break;
            }
        }
    }
    if (!isPart && ispname) {
        pf = new FullTime(newp);
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的学号: ";
        cin >> id;
        cout << "请输入该同学的电话号码: ";
        cin >> phone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> building;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> dorm;
        cout << endl;
        pf->addInfo(id, phone, building, dorm);
    }
    else if (!isPart && !ispname) {
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的姓名: ";
        cin >> id;
        pf = new FullTime(id);
        cout << "请输入该同学的电话号码: ";
        cin >> phone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> building;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> dorm;
        cout << endl;
        pf->addInfo(newp, phone, building, dorm);
    }
    // 这步以后得到：pf：新值班员

    // 将新值班员加入stafflist,并将老值班员删除、加入partime
    bool isname = true;
    if (index[0] >= '0' && index[0] <= '9') {
        isname = false;
    }
    else {
        isname = true;
    }
    if (isname) {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->name == index) {
                staff_list[i] = pf;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->id == index) {
                staff_list[i] = pf;
                break;
            }
        }
    }
    // 将老值班员插入parttime
    this->part_time.push_back(staff);

    // 删除原常任值班员起始日期之后（包含）的所有值班记录
    staff->deleteOver(rBegin, d, noon);

    // 将新值班员加入到值班表
    b->addOnDuty(d, pf, noon);

    // 初始化新常任值班员从起始日期到wageEnd的值班记录
    this->initStaff(rBegin, wageEnd, b, d, noon);
}

FullTime* Manager::findStaff(string index) {
    FullTime* re = NULL;
    if (staff_list.empty() && part_time.empty()) return re;
    bool isname = true;
    if (index[0] >= '0' && index[0] <= '9') {
        isname = false;
    }
    if (isname) {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->name == index) {
                re = staff_list[i];
                break;
            }
        }
        for (int i = 0; i < part_time.size(); ++i) {
            if (part_time[i]->name == index) {
                re = part_time[i];
                break;
            }
        }
    }
    else {
        for (int i = 0; i < staff_list.size(); ++i) {
            if (staff_list[i]->id == index) {
                re = staff_list[i];
                break;
            }
        }
        for (int i = 0; i < part_time.size(); ++i) {
            if (part_time[i]->id == index) {
                re = part_time[i];
                break;
            }
        }
    }
    return re;
}

bool Manager::Find(string index) {
    FullTime* find = findStaff(index);
    if (!find) {
        cout << index << ": 查无此人！" << endl;
        return false;
    }
    find->ptInfo(this->holiday,this->DayOffs);
    cout << endl;
    return true;
}

void Manager::Export(string path) {
    ofstream out, backup;
    string arr[9] = {"D1","D2","D3","D4","X1","X2","X3","X4","X5"};
    string arr_C[9] = {"东一","东二","东三","东四","西一","西二","西三","西四","西五"};
    string p = "../InfoBackup/";
    int h = 0;
    for(; h < 9; ++h){
        if(this->area.name == arr_C[h]){
            break;
        }
    }
    p += arr[h];
    p += "_blank_backup.txt";
    out.open(path);
    backup.open(p);
    assert(out.is_open());
    assert(backup.is_open());
    backup << "# 这是一个副本文件，用于储存值班员空白信息" << endl;
    // 写入经理信息
    out << "# 经理信息（M姓名 学号）" << endl;
    out << "M" << this->name << " " << this->id << " "
        << this->wageBegin.y() << " " << this->wageBegin.m() << " " << this->wageBegin.d() << " "
        << this->wageEnd.y() << " " << this->wageEnd.m() << " " << this->wageEnd.d() << " ";
    out << this->holiday.size() << " ";
    for (int i = 0; i < this->holiday.size(); ++i) {
        out << this->holiday[i]->y() << " "
            << this->holiday[i]->m() << " "
            << this->holiday[i]->d() << " "
            << this->holiday[i]->Dou() << " "
            << this->holiday[i]->Tri() << " ";
    }
    out << this->DayOffs.size() << " ";
    for (int i = 0; i < this->DayOffs.size(); ++i) {
        if (i == this->DayOffs.size() - 1) {
            out << this->DayOffs[i].day.y() << " "
                << this->DayOffs[i].day.m() << " "
                << this->DayOffs[i].day.d() << " "
                << this->DayOffs[i].change << endl;
        }
        else {
            out << this->DayOffs[i].day.y() << " "
                << this->DayOffs[i].day.m() << " "
                << this->DayOffs[i].day.d() << " "
                << this->DayOffs[i].change << " ";
        }
    }
    out << endl;
    backup << "# 经理信息（M姓名 学号）" << endl;
    backup << "M" << this->name << " " << this->id << " "
           << this->wageBegin.y() << " " << this->wageBegin.m() << " " << this->wageBegin.d() << " "
           << this->wageEnd.y() << " " << this->wageEnd.m() << " " << this->wageEnd.d()
           << 0 << " " << 0 << endl;
    backup << endl;

    // 写入片区信息
    out << "# 片区信息（A片区名 楼栋名）" << endl;
    out << "A"
        << this->area.name << " "
        << this->area.ExportBuildings() << endl;
    out << endl;
    backup << "# 片区信息（A片区名 楼栋名）" << endl;
    backup << "A"
           << this->area.name << " "
           << this->area.ExportBuildings() << endl;
    backup << endl;

    // 写入楼栋信息
    out << "# 楼栋信息（B楼栋名 周六 周日 ｜｜ 楼栋名 周一上午 周一下午 周二上午 ）" << endl;
    for (int i = 0; i < this->area.dormlist.size(); ++i) {
        out << "B"
            << this->area.dormlist[i]->name << " "
            << this->area.dormlist[i]->ExportOnduty() << endl;
    }
    out << endl;
    backup << "# 楼栋信息（B楼栋名 周六 周日 ｜｜ 楼栋名 周一上午 周一下午 周二上午 ）" << endl;
    for (int i = 0; i < this->area.dormlist.size(); ++i) {
        backup << "B"
               << this->area.dormlist[i]->name << " "
               << this->area.dormlist[i]->ExportOnduty() << endl;
    }
    backup << endl;

    // 写入值班员信息
    out << "# 值班员信息(O姓名 学号 电话 楼栋 寝室 工作次数 工作日期 ）" << endl;
    for (int i = 0; i < this->staff_list.size(); ++i) {
        out << "O"
            << this->staff_list[i]->ExportInfo() << endl;
    }
    out << endl;
    backup << "# 值班员信息(O姓名 学号 电话 楼栋 寝室 工作次数 工作日期 ）" << endl;
    for (int i = 0; i < this->staff_list.size(); ++i) {
        backup << "O"
               << this->staff_list[i]->ExportBlankInfo() << endl;
    }
    backup << endl;

    // 写入替班员信息
    out << "# 替班员信息(P姓名 学号 电话 楼栋 寝室 工作次数 工作日期 ）" << endl;
    for (int i = 0; i < this->part_time.size(); ++i) {
        out << "P"
            << this->part_time[i]->ExportInfo() << endl;
    }
    backup << "# 替班员信息(P姓名 学号 电话 楼栋 寝室 工作次数 工作日期 ）" << endl;
    for (int i = 0; i < this->part_time.size(); ++i) {
        backup << "P"
               << this->part_time[i]->ExportBlankInfo() << endl;
    }

    out.close();
    backup.close();
}

Manager::~Manager() {

    if (!staff_list.empty()) {
        for (int i = 0; i < this->staff_list.size(); ++i) {
            delete this->staff_list[i];
        }
    }
    if (!part_time.empty()) {
        for (int i = 0; i < this->part_time.size(); ++i) {
            delete this->part_time[i];
        }
    }
    if (!holiday.empty()) {
        for (int i = 0; i < this->holiday.size(); ++i) {
            delete this->holiday[i];
        }
    }
}

void Manager::setWages() {


    // 得到合法的登记时间段
    this->ptstate();
    cout << "请输入需要记录的时间段" << endl;
    int year = 2022, month = 2, day = 11;
    Date IwageB(year, month, day + 1), IwageE(year, month, day);
    bool BoverE = true;
    bool Update = false;
    bool isD4 = (this->area.name == "东四");
    Date OwageB(this->wageBegin), OwageE(this->wageEnd);
    while (BoverE || !Update) {
        bool valid = false;
        while (!valid) {
            cout << "请输入起始日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            IwageB.setDate(year, month, day);
            valid = IwageB.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        year = 2022;
        month = 2;
        day = 11;
        IwageE.setDate(year, month, day);
        valid = false;
        while (!valid) {
            cout << "请输入截止日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            IwageE.setDate(year, month, day);
            valid = IwageE.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        BoverE = IwageB > IwageE;
        if (BoverE) {
            cout << "error: 起始日期大于截止日期！请重新输入" << endl;
            continue;
        }

        char is;
        do {
            cout << "请核对输入是否正确?[Y/N]: ";
            cin >> is;
            if (is == 'Y' || is == 'y') {
            }
            else if (is == 'N' || is == 'n') {
                cout << "本次输入无效，不会录入!" << endl;
                return;
            }
            else {
                cout << "error: 请输入Y/N !" << endl;
            }
        } while (is != 'Y' && is != 'y' && is != 'N' && is != 'n');

        // 检测输入日期判断是否需要新增工资
        Update = false;
        if (this->wageBegin == this->wageEnd) {
            Update = true;
            OwageB = IwageB;
            OwageE = IwageE;
            this->wageBegin = IwageB;
            this->wageEnd = IwageE;
        }
        else {
            if ((this->wageBegin <= IwageB) && (this->wageEnd >= IwageE)) {
                Update = false;
                this->fillInBlank(IwageB,IwageE);
            }
            else if (this->wageEnd <= IwageB) {
                if (isD4 && (IwageB.dateLength(this->wageEnd) >= 2)) {
                    cout << "已录入的时间段: ";
                    cout << wageBegin.pureDate() << "->" << wageEnd.pureDate() << endl;
                    cout << "error: 新输入的起始日期与上次记录的截止日期之间有空白日期未登记" << endl;
                    continue;
                }
                else if (!isD4 && (IwageB.dateLength(this->wageEnd) > 7)) {
                    cout << "已录入的时间段: ";
                    cout << wageBegin.pureDate() << "->" << wageEnd.pureDate() << endl;
                    cout << "error: 新输入的起始日期与上次记录的截止日期之间有空白日期未登记" << endl;
                    continue;
                }
                else {
                    OwageB = IwageB;
                    OwageE = IwageE;
                    this->wageEnd = IwageE;
                    Update = true;
                }
            }
            else if (IwageB < this->wageBegin) {
                OwageB = IwageB;
                OwageE = this->wageBegin - 1;
                this->wageBegin = IwageB;
                Update = true;
            }
            else {
                OwageB = this->wageEnd + 1;
                OwageE = IwageE;
                this->wageEnd = IwageE;
                Update = true;
            }
            break;
        }
    }

    if (Update) {
        // 初始化工资表
        this->addBetween(OwageB,OwageE);
        // 更新blankDays
        this->updateBlank(OwageB,OwageE);
    }

    char is;
    // 是否需要更换常任值班员
    cout << "是否需要更换常任值班员?[Y/N]: ";
    cin >> is;
    if (is == 'Y' || is == 'y') {
        is = 'N';
        do {
            this->FulltoPart();
            cout << "是否还需要更换常任值班员?[Y/N]: ";
            cin >> is;
        } while (is != 'N' && is != 'n');
    }

    // 是否有节假日
    cout << "该时间段内是否有节假日?[Y/N]: ";
    cin >> is;
    if (is == 'Y' || is == 'y') {
        is = 'N';
        do {
            this->InputHoliday();
            cout << "是否还需要添加节假日?[Y/N]: ";
            cin >> is;
        } while (is != 'N' && is != 'n');
    }

    // 是否有替换班
    cout << "是否有替换班?[Y/N]: ";
    cin >> is;
    if (is == 'Y' || is == 'y') {
        is = 'N';
        do {
            this->setRelief();
            cout << "是否还需要添加替换班?[Y/N]: ";
            cin >> is;
        } while (is != 'N' && is != 'n');
    }

    cout << endl;
}

void Manager::InputHoliday() {
    int year = 2022, month = 2, day = 11;
    Date holidayBegin(year, month, day);
    Date holidayEnd(year,month,day);
    bool BoverE = true;
    bool isD4 = (this->area.name == "东四");
    while (BoverE) {
        bool valid = false;
        while (!valid) {
            cout << "请输入假期值班的起始日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            holidayBegin.setDate(year, month, day);
            valid = holidayBegin.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        year = 2022;
        month = 2;
        day = 11;
        holidayEnd.setDate(year, month, day);
        valid = false;
        while (!valid) {
            cout << "请输入假期值班的截止日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            cout << endl;
            holidayEnd.setDate(year, month, day);
            valid = holidayEnd.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        BoverE = holidayBegin > holidayEnd;
        if (BoverE) {
            cout << "error: 起始日期大于截止日期！请重新输入" << endl;
            continue;
        }
    }
    if (holidayBegin < this->wageBegin || holidayEnd > this->wageEnd) {
        cout << "error: 已录入值班时间段中没有该假期！" << endl;
        return;
    }
    Date ee1 = holidayEnd + 1;
    int size1 = this->holiday.size();
    bool f1 = false;
    for(Date a = holidayBegin; !(a == ee1); a = a + 1) {
        for (int i = 0; i < size1; ++i) {
            if (this->holiday[i]->operator==(a)) {
                f1 = true;
                break;
            }
        }
        if (f1) {
            cout << "error: 已添加过 " << a.pureDate() << " 节假日! 录入节假日失败。" << endl;
            f1 = false;
            return;
        }
    }

    char is;
    do {
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> is;
        if (is == 'Y' || is == 'y') {
            Date ee = holidayEnd + 1;
            int size = this->holiday.size();
            for(Date a = holidayBegin; !(a == ee); a = a + 1) {
                this->addHoliday(a);
            }
            // 是否有调休
            cout << "是否需要调休?[Y/N]: ";
            cin >> is;
            if(is == 'Y' || is == 'y'){
                is = 'N';
                do {
                    this->setDayOff();
                    cout << "是否还有调休日期?[Y/N]: ";
                    cin >> is;
                } while (is != 'N' && is != 'n');
            }
            return;
        }
        else if (is == 'N' || is == 'n') {
            cout << "本次输入无效，不会录入!" << endl;
            return;
        }
        else {
            cout << "error: 请输入Y/N !" << endl;
        }
    } while (is != 'Y' && is != 'y' && is != 'N' && is != 'n');
}

void Manager::setDayOff(){
    int year, month, day;
    Date rBegin;
    bool valid = false;
    char is = 'N';
    while (!valid) {
        cout << "请输入调休日期: " << endl;
        cout << "年: ";
        cin >> year;
        cout << "月: ";
        cin >> month;
        cout << "日: ";
        cin >> day;
        rBegin.setDate(year, month, day);
        valid = rBegin.isValid();
        if (!valid) {
            cout << "error: 输入日期不合法！请重新输入" << endl;
        } else {
            break;
        }
    }
    do {
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> is;
        if (is == 'Y' || is == 'y') {
        }
        else if (is == 'N' || is == 'n') {
            cout << "本次输入无效，不会录入!" << endl;
            return;
        }
        else {
            cout << "error: 请输入Y/N !" << endl;
        }
    } while (is != 'Y' && is != 'y' && is != 'N' && is != 'n');
    if (rBegin < this->wageBegin || rBegin > this->wageEnd) {
        cout << "error: 已录入值班时间段中没有该调休日期！" << endl;
        return;
    }
    // 输入该天按星期几的值班表
    int d = -1;
    cout << rBegin.pureDate() << " 按星期几的值班表执行?(0->星期天 6->星期六): ";
    cin >> d;
    if(d < 0 || d > 6){
        cout << "error: 输入错误!" << endl;
        return;
    }
    // 删除该天所有值班记录
    for (int i = 0; i < this->staff_list.size(); ++i) {
        this->staff_list[i]->deleteDate(rBegin);
    }
    for (int i = 0; i < this->part_time.size(); ++i) {
        this->part_time[i]->deleteDate(rBegin);
    }
    // 根据调休天和值班表初始化新的值班记录
    Date *work = NULL;
    for (auto & i : this->area.dormlist) {
        if (i->name == "D34" || i->name == "D35") {
            work = new Date(rBegin.y(), rBegin.m(), rBegin.d(), false);
            i->addWork(work, d, false);
            work = new Date(rBegin.y(), rBegin.m(), rBegin.d(), true);
            i->addWork(work, d, true);
        }
        else if ((d == 0) || (d == 6)) {
            work = new Date(rBegin.y(), rBegin.m(), rBegin.d(), false);
            i->addWork(work, d, false);
        }
    }
    DayOff off;
    off.day = rBegin;
    off.change = d;
    this->DayOffs.push_back(off);
}

void Manager::addHoliday(Date& holiday) {

    // 获取合法输入：双倍/三倍工资
    Date* iswork = NULL;
    char is = 'N';
    bool N = false,D = false, T = false;
    cout << holiday.pureDate() << "是正常工资吗?[Y/N]: ";
    cin >> is;
    if(is == 'Y' || is == 'y'){
        N = true;
        D = false;
        T = false;
    }
    else if(is == 'n' || is == 'N') {
        cout << holiday.pureDate() << "是双倍工资吗?[Y/N]: ";
        cin >> is;
        if (is == 'Y' || is == 'y') {
            D = true;
            holiday.setDouble();
        } else if (is == 'N' || is == 'n') {
            D = false;
            cout << holiday.pureDate() << "是三倍工资吗?[Y/N]: ";
            cin >> is;
            if (is == 'Y' || is == 'y') {
                T = true;
                holiday.setTriple();
            }
            else if(is != 'N' && is != 'n'){
                cout << "输入无效，不会录入!" << endl;
                return;
            }
        } else {
            cout << "输入无效，不会录入!" << endl;
            return;
        }
    }
    else{
        cout << "输入无效，不会录入!" << endl;
        return;
    }

    Date* h = new Date(holiday);
    if(this->holiday.empty()){
        this->holiday.push_back(h);
    }
    else {
        bool in = false;
        for (int i = 0; i < this->holiday.size(); ++i) {
            if (this->holiday[i]->operator>(holiday)) {
                this->holiday.insert(this->holiday.begin() + i, h);
                in = true;
                break;
            }
        }
        if(!in) this->holiday.push_back(h);
    }
    // 判断holiday为：周末：（不论哪个片区）删除该天所有记录
    // 工作日：D4区：删除该天所有记录
    bool isD4 = (this->area.name == "东四");
    int index = holiday.dayth();
    bool isWeekend = (index == 0 || index == 6);
    if (isWeekend) {
        for (int i = 0; i < this->staff_list.size(); ++i) {
            this->staff_list[i]->deleteDate(holiday);
        }
        for (int i = 0; i < this->part_time.size(); ++i) {
            this->part_time[i]->deleteDate(holiday);
        }
    }
    else if (isD4) {
        for (int i = 0; i < this->staff_list.size(); ++i) {
            this->staff_list[i]->deleteDate(holiday);
        }
        for (int i = 0; i < this->part_time.size(); ++i) {
            this->part_time[i]->deleteDate(holiday);
        }
    }

    // 输入正确的值班员索引, 并插入该天值班记录
    FullTime* staff = NULL;
    for (int i = 0; i < this->area.dormlist.size(); ++i) {
        this->area.ptDorm(this->area.dormlist[i]->name);
        staff = NULL;
        do {
            staff = this->inputStaff(this->area.dormlist[i]->name, holiday);
            if (!staff) {
                cout << "error: 添加" << this->area.dormlist[i]->name << "楼 " << holiday.pureDate() << " 的值班员失败!"
                     << endl;
            }
        } while (!staff);
        iswork = new Date(holiday);
        if (D) {
            iswork->setDouble();
        }
        else if (T) {
            iswork->setTriple();
        }
        if(!staff->addWork(iswork)){
            i--;
            continue;
        }

        // 如果该楼为 D34 或 D35， 需要两名值班员
        if (this->area.dormlist[i]->name == "D34" || this->area.dormlist[i]->name == "D35") {
            FullTime* staff2 = NULL;
            cout << this->area.dormlist[i]->name<< "楼 "<< holiday.pureDate() << " 是否只有一位值班员?[Y/N]";
            char sym = 'N';
            cin >> sym;
            if(sym == 'y' || sym == 'Y'){
                // 如果该天只有一位值班员，则将另一位值班员工资量+0.5
                // 查找staff在de天的工作记录
                Date* old = staff->isWork(holiday);
                if (!old) {
                    cout << "error: " << staff->name << " 未在 " << holiday.pureDate() << "值班！" << endl;
                    return;
                }

                // 添加备注及设置新工作量
                string comment = "";
                comment = "单人值班";
                old->addComment(this->area.dormlist[i]->name + ":" + comment);
                double w = 1.0;
                w = 1.5;
                old->setWorkload(w);
                staff->ptInfo(this->holiday,this->DayOffs);
            }
            else {
                do {
                    staff2 = this->inputStaff(this->area.dormlist[i]->name, holiday);
                    if (!staff2) {
                        cout << "error: 添加" << this->area.dormlist[i]->name << "楼 " << holiday.pureDate()
                             << " 的值班员失败!"
                             << endl;
                    }
                } while (!staff2);
                iswork = new Date(holiday);
                if (D) iswork->setDouble();
                else if (T) iswork->setTriple();
                if (!staff2->addWork(iswork)) {
                    i--;
                    continue;
                }
            }
        };
    }
}

void Manager::addRelief(Date* d) {
    FullTime* staff = NULL;
    string info = "请输入替班同学的姓名/学号: ";
    do {
        staff = this->inputStaff(info);
        if (!staff) {
            cout << "error: 输入替班员信息错误!" << endl;
        }
    } while (!staff);
    staff->deleteExact(*d);
    staff->addWork(d);
    staff->ptInfo(this->holiday,this->DayOffs);
    cout << endl;
}

Building* Manager::findBuilding(string name) {
    Building* b = NULL;
    for (int i = 0; i < this->area.dormlist.size(); ++i) {
        if (strcasecmp(this->area.dormlist[i]->name.c_str(),name.c_str()) == 0) {
            b = this->area.dormlist[i];
            break;
        }
    }
    return b;
}


void Manager::initStaff(Date begin, Date end, Building* building, int index, bool noon) {
    int year_begin = 2023, month_begin = 2, day_begin = 12;
    int year_end = 2023, month_end = 2, day_end = 11;
    year_begin = begin.y();
    month_begin = begin.m();
    day_begin = begin.d();
    year_end = end.y();
    month_end = end.m();
    day_end = end.d();
    // 初始化工资表
    Date* work = NULL;
    int leap_year[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int common_year[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int* year_arr = NULL;
    int days1 = begin.dateLength();
    for (int y = year_begin, m = month_begin, d = day_begin; y <= year_end;) {
        if (begin.is_leapyear(y)) year_arr = leap_year;
        else year_arr = common_year;
        if (y == year_end) {
            for (; m <= month_end;) {
                if ((y == year_end) && (m == month_end)) {
                    for (; d <= day_end; d++) {
                        if (days1 % 7 == index) {
                            work = new Date(y, m, d, noon);
                            building->addWork(work, index, noon);
                        }
                        days1++;
                    }
                    break;
                }
                else {
                    for (; d <= year_arr[m]; ++d) {
                        if (days1 % 7 == index) {
                            work = new Date(y, m, d, noon);
                            building->addWork(work, index, noon);
                        }
                        days1++;
                    }
                }
                m++;
                d = 1;
            }
        }
        else {
            for (; m <= 12;) {
                for (; d <= year_arr[m]; ++d) {
                    if (days1 % 7 == index) {
                        work = new Date(y, m, d, noon);
                        building->addWork(work, index, noon);
                    }
                    days1++;
                }
                m++;
                d = 1;
            }
        }
        y++;
        m = 1;
        d = 1;
    }

}

void Manager::helpInfo() {
    cout << "欢迎回来，亲爱的 " << this->name << "!" << endl;
    if (this->wageBegin == this->wageEnd) {
        cout << "尚未录入过值班情况!" << endl;
    }
    else {
        cout << "已录入过值班的时间段: ";
        cout << wageBegin.pureDate() << "->" << wageEnd.pureDate() << endl;
    }
    bool blank = this->blankDays.empty();
    if (!blank) {
        cout << "尚未录入的空白时间段: ";
        for (int i = 0; i < this->blankDays.size(); ++i) {
            if (i == this->blankDays.size() - 1)
                cout << this->blankDays[i].begin.pureDate() << "->" << this->blankDays[i].end.pureDate() << endl;
            else cout << this->blankDays[i].begin.pureDate() << "->" << this->blankDays[i].end.pureDate() << " ";
        }
    }
    cout << "你可以输入以下指令: " << endl;
    cout << "\ti: 显示你的个人信息;" << endl;
    cout << "\tw: 录入平时值班情况;" << endl;
    cout << "\tk: 更换常任值班员;" << endl;
    cout << "\tj: 录入假期值班情况;" << endl;
    cout << "\to: 录入调休情况;" << endl;
    cout << "\ta: 显示宿舍片区(添加新楼栋);" << endl;
    cout << "\tb: 显示楼栋值班表;" << endl;
    cout << "\tp: 打印工资表;" << endl;
    cout << "\tn: 录入替换班情况;" << endl;
    cout << "\tf: 查找值班员;" << endl;
    cout << "\td: 扣除/添加工作量;" << endl;
    cout << "\tc: 清除该片区值班情况;" << endl;
    cout << "\th: 查看帮助信息;" << endl;
    cout << "\te: 退出;" << endl;
}

void Manager::Execute() {
    // 核对值班表

    string arr[9] = {"D1","D2","D3","D4","X1","X2","X3","X4","X5"};
    string arr_C[9] = {"东一","东二","东三","东四","西一","西二","西三","西四","西五"};

    string are;
    int h = 3;
    do {
        cout << "请问你管理的片区是?";
        for(int i = 0; i < 9; ++i){
            if(i == 0){
                cout << "( "<< i << "->" << arr_C[i]<<"; ";
            }
            else if(i == 8){
                cout << i << "->" << arr_C[i]<<" ): ";
            }
            else{
                cout << i << "->" << arr_C[i]<<"; ";
            }
        }
        cin >> h;
        are = arr_C[h];
        if(h < 0 || h > 8){
            cout << "没有该宿舍片区! 请重新输入。" << endl;
            continue;
        }
    } while (h < 0 || h > 8);
    this->area_num = h;
    string p = "../DormAreaInfo/";
    p += arr[h];
    p += ".txt";
    this->path = p;
    this->load(this->path);
    char command;
    bool exit = false;
    do {
        this->helpInfo();
        cout << "Command: ";
        cin >> command;
        switch (command) {
            case 'o': case 'O': // 录入调休情况
                this->commandO();
                cout << endl;
                break;
            case 'i': case 'I':// 显示你的个人信息
                this->commandI();
                cout << endl;
                break;
            case 'c': case 'C': // 清除该片区值班情况
                this->commandC();
                cout << endl;
                break;
            case 'a': case 'A': // 显示你管辖的宿舍片区
                this->commandA();
                cout << endl;
                break;
            case 'k' : case 'K': // 更换常任值班员
                this->FulltoPart();
                cout << endl;
                break;
            case 'b': case 'B': // 显示楼栋值班表
                this->commandB();
                cout << endl;
                break;
            case 'p': case 'P': // 打印工资表
                this->ptWage();
                cout << endl;
                break;
            case 'w': case 'W': // 录入该片区值班情况（更换常任值班员）
                this->setWages();
                break;
            case 'n': case 'N': // 录入替换班情况
                this->commandN();
                cout << endl;
                break;
            case 'f': case 'F': // 查找值班员
                this->commandF();
                cout << endl;
                break;
            case 'j': case 'J': // 录入节假日
                this->commandJ();
                cout << endl;
                break;
            case 'd': case 'D': // 减少工资
                this->commandDeduct();
                cout << endl;
                break;
            case 'h': case 'H': // 查看帮助信息
                this->helpInfo();
                cout << endl;
                break;
            case 'e': case 'E': // 退出
                if (this->blankDays.empty()) {
                    exit = true;
                }
                else if (!(this->wageBegin == this->wageEnd)) {
                    cout << "warning: 您有尚未录入的空白时间段,请录入该时间段值班情况!" << endl;
                    cout << endl;
                }
                else exit = true;
                break;
            default:
                cout << "error: Unknown command!" << endl;
                cout << endl;
                break;
        }
    } while (!exit);
    this->Export(this->path);
}

void Manager::commandO(){
    if(!this->DayOffs.empty()){
        cout << "已添加过的调休日期: ";
        for(int i = 0; i < this->DayOffs.size(); ++i){
            cout << this->DayOffs[i].day.pureDate() << " ";
        }
        cout << endl;
    }
    else{
        cout << "尚未录入调休日期!" << endl;
    }
    char is = 'N';
    do {
        this->setDayOff();
        cout << "是否还有调休日期?[Y/N]: ";
        cin >> is;
    } while (is != 'N' && is != 'n');
}

void Manager::commandI() {
    printf("%-11s%-16s\n", "姓名: ", this->name.c_str());
    printf("%-11s%-16s\n", "学号: ", this->id.c_str());
    printf("%-11s%-16s\n", "管理片区: ", this->area.name.c_str());
    this->ptstate();

    char sym = 'N';
    cout << "是否修改个人信息?[Y/N]: ";
    cin >> sym;
    if (sym == 'Y' || sym == 'y') {
        string name, id;
        char h = 'Y';
        cout << "是否修改姓名?[Y/N]: ";
        cin >> h;
        if (h == 'Y' || h == 'y') {
            cout << "请输入新的姓名: ";
            cin >> name;
            this->name = name;
        }
        else if(h == 'N' || h == 'n'){
        }
        else{
            cout << "error: Unknown command!" << endl;
            return;
        }
        cout << "是否修改学号?[Y/N]: ";
        cin >> h;
        if (h == 'Y' || h == 'y') {
            cout << "请输入新的学号: ";
            cin >> id;
            this->id = id;
        }
        else if(h == 'N' || h == 'n'){
        }
        else{
            cout << "error: Unknown command!" << endl;
            return;
        }
    }
    else if(sym == 'N' || sym == 'n'){
        return;
    }
    else{
        cout << "error: Unknown command!" << endl;
        return;
    }
}

void Manager::commandA() {
    this->area.ptDormList();
    char symbol = 'N';
    cout << "是否需要查询楼栋值班表?[Y/N]: ";
    cin >> symbol;
    if (symbol == 'Y' || symbol == 'y') {
        this->commandB();
    }
    else if(symbol == 'N' || symbol == 'n'){
    }
    else{
        cout << "error: Unknown command!" << endl;
        return;
    }
    cout << "是否需要添加楼栋?[Y/N]: ";
    cin >> symbol;
    string build;
    if (symbol == 'Y' || symbol == 'y') {
        cout << "请输入要添加的楼栋名(e退出): ";
        cin >> build;
        if (build[0] == 'e' || build[0] == 'E') return;
        this->addBuilding(build);
    }
    else if(symbol == 'N' || symbol == 'n'){
        return;
    }
    else{
        cout << "error: Unknown command!" << endl;
        return;
    }
}

void Manager::commandB() {
    string building;
    char symbol = 'Y';
    do {
        cout << "请输入要查询的楼栋名(e退出): ";
        cin >> building;
        if (building[0] == 'e' || building[0] == 'E') return;
        this->area.ptDorm(building);
        cout << "是否继续查询?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'N' && symbol != 'n');
}

// 打印工资简表
void Manager::commandP(Date begin, Date end) {
    this->exportBrief(begin,end);
    string n = "姓名";
    string nid = "学号";
    string be = "起始日期";
    string be1 = begin.pureDate();
    string end1 = end.pureDate();
    string enddate = "结束日期";
    string wage = "总酬金";
    double a = 0.0;
    printf("%-13s%-15s%-16s%-13s%s(元)\n", n.c_str(), nid.c_str(), be.c_str(), enddate.c_str(), wage.c_str());
    double wday = 0, wend = 0;
    for (int i = 0; i < this->staff_list.size(); ++i) {
        wday = staff_list[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = staff_list[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        a = wday * WEEKDAY + wend * WEEKEND;
        if (!a) continue;
        printf("%-9s%-16s%-16s%-16s%.2f(元)\n", staff_list[i]->name.c_str(), staff_list[i]->id.c_str(), be1.c_str(),
               end1.c_str(), a);
    }
    for (int i = 0; i < this->part_time.size(); ++i) {
        wday = part_time[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = part_time[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        a = wday * WEEKDAY + wend * WEEKEND;
        if (!a) continue;
        printf("%-9s%-16s%-16s%-16s%.2f(元)\n", part_time[i]->name.c_str(), part_time[i]->id.c_str(), be1.c_str(),
               end1.c_str(), a);
    }
}

// 打印工资详表
void Manager::commandD(Date begin, Date end) {
    this->exportDetail(begin,end);
    string n = "姓名";
    string nid = "学号";
    string kday = "工作日工作量";
    string kend = "周末工作量";
    string wage = "总酬金";
    string date = "工作日期";
    string unit = "(元)";
    double weekday = 0.0, weekend = 0.0;
    double a = 0.0;
    printf("%-10s%-15s%-15s%-15s%-11s%s\n", n.c_str(), nid.c_str(), kday.c_str(), kend.c_str(), wage.c_str(), date.c_str());
    for (int i = 0; i < this->staff_list.size(); ++i) {
        weekday = staff_list[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        weekend = staff_list[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        a = weekday * WEEKDAY + weekend * WEEKEND;
        if (!a) continue;
        printf("%-10s%-15s%-15.1f%-13.1f%.2f%-7s%s\n\n", staff_list[i]->name.c_str(), staff_list[i]->id.c_str(), weekday, weekend, a, unit.c_str(), staff_list[i]->StringDate(begin,end,this->holiday,this->DayOffs).c_str());
    }
    for (int i = 0; i < this->part_time.size(); ++i) {
        weekday = part_time[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        weekend = part_time[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        a = weekday * WEEKDAY + weekend * WEEKEND;
        if (!a) continue;
        printf("%-10s%-15s%-15.1f%-13.1f%.2f%-7s%s\n\n", part_time[i]->name.c_str(), part_time[i]->id.c_str(), weekday, weekend, a, unit.c_str(), part_time[i]->StringDate(begin,end,this->holiday,this->DayOffs).c_str());
    }
}

string Manager::divideDate(Date &begin, Date &end){
    bool isD4 = (this->area.name == "东四");
    stringstream out;
    int d = begin.dayth();
    bool di = false;
    if(isD4) {
        for (Date o=begin; o <= end; o = o + 1) {
            bool isEnd = o == end;
            int a = d % 7;
            bool Holiday = this->isHoliday(o);
            DayOff *dayOff = this->isDayOff(o);
            if (a == 6 || a == 0) {
                // 如果是星期六/星期天，调休则按调休输出，假期/日常正常输出，如果为末尾输出换行
                if (isEnd) {
                    if (!dayOff) {
                        out << o.pureDate() << ",";
                    } else {
                        out << o.pureDate() << "(" << dayOff->change << ")" << ",";
                    }
                    break;
                }
                else {
                    if (!dayOff) {
                        out << o.pureDate() << ",";
                    } else {
                        out << o.pureDate() << "(" << dayOff->change << ")" << ",";
                    }
                }
            } else if (a == 1) {
                // 如果是星期一，
                // 如果结束，则输出末尾；
                // 如果是假期，则单独输出；
                // 如果后一天是假期，则单独输出；
                // 否则为正常情况，输出起始；
                if (isEnd) {
                    out << o.pureDate() << ",";
                    break;
                }
                else if (Holiday) {
                    di = false;
                    out << o.pureDate() << ",";
                }
                else {
                    Date h = o + 1;
                    if (this->isHoliday(h)) {
                        di = false;
                        out << o.pureDate() << ",";
                    } else {
                        di = true;
                        out << o.pureDate() << "-";
                    }
                }
            } else if (a == 5) {
                // 如果是星期五
                // 如果结束，则输出末尾
                // 如果是假期，则输出末尾
                // 否则为正常情况，输出末尾
                if (isEnd) {
                    out << o.pureDate() << ",";
                    break;
                } else {
                    di = false;
                    out << o.pureDate() << ",";
                }
            } else {
                // a >= 2 && a <= 4
                // 输出格式：date-（起始）/date,（末尾）/不输出
                // 如果到截止，则输出截止
                // 如果是节假日，则输出末尾
                // 如果是开始且后一天非节假日，则输出起始
                // 如果是开始且后一天是节假日，则单独输出
                // 如果不是开始且后一天非节假日，则不输出
                // 如果不是开始且后一天是节假日，则输出末尾
                if (isEnd) {
                    out << o.pureDate() << ",";
                    break;
                } else if (Holiday) {
                    di = false;
                    out << o.pureDate() << ",";
                } else {
                    Date h = o + 1;
                    bool holi = this->isHoliday(h);
                    if (!di) { // 开始
                        if (holi) {
                            di = false;
                            out << o.pureDate() << ",";
                        } else {
                            di = true;
                            out << o.pureDate() << "-";
                        }
                    } else {
                        if (holi) {
                            di = false;
                            out << o.pureDate() << ",";
                        } else {
                            di = true;
                        }
                    }
                }
            }
            d++;
        }
    }
    else{
        for (Date o=begin; o <= end; o = o + 1) {
            bool isEnd = (o == end);
            int a = d % 7;
            bool Holiday = this->isHoliday(o);
            DayOff *dayOff = this->isDayOff(o);
            if (a == 6 || a == 0) {
                // 如果是星期六/星期天，调休则不输出，假期/日常正常输出，如果为末尾输出换行
                if (isEnd) {
                    if (!dayOff) {
                        out << o.pureDate() << ",";
                    }
                    break;
                } else {
                    if (!dayOff) {
                        out << o.pureDate() << ",";
                    }
                }
            }
            else {
                // a >= 1 && a <= 5
                // 输出格式：date \n /date, /不输出
                // 如果是节假日
                // 如果是结束，则输出末尾
                // 否则正常输出
                if (Holiday) {
                    if(isEnd){
                        out << o.pureDate() << ",";
                        break;
                    }
                    else{
                        out << o.pureDate() << ",";
                    }
                }
            }
            d++;
        }
    }
    return out.str();
}

bool Manager::isHoliday(Date &d){
    bool in = false;
    if(this->holiday.empty()) return false;
    for(int i = 0; i < this->holiday.size(); ++i){
        if(this->holiday[i]->operator==(d)){
            in = true;
            break;
        }
    }
    return in;
}

DayOff* Manager::isDayOff(Date &d){
    if(this->DayOffs.empty()) return NULL;
    for(int i = 0; i < this->DayOffs.size(); ++i){
        if(this->DayOffs[i].day == d){
            return &this->DayOffs[i];
        }
    }
    return NULL;
}

void Manager::exportDetail(Date &begin, Date &end){
    string arr[9] = {"D1","D2","D3","D4","X1","X2","X3","X4","X5"};
    string arr_C[9] = {"东一","东二","东三","东四","西一","西二","西三","西四","西五"};
    bool isD4 = (this->area.name == "东四");
    double wday = 0.0, wend = 0.0, a = 0.0;
    string path = "../Wage/";
    path += arr[this->area_num];
    path += "_detailTable.txt";
    ofstream out;
    out.open(path);
    assert(out.is_open());
    out << this->area.name << "区" << begin.pureDate() << "-" << end.pureDate() << "室内值班员工资详表"<<endl;
    if(this->area.name == "东四"){
        out << "值班员,学号," << this->divideDate(begin,end) << "周末工作量,工作日工作量,周末工资,工作日工资,工资总计" << endl;
    }
    else{
        out << "值班员,学号," << this->divideDate(begin,end) << "周末工资,周末工作量,工资总计" << endl;
    }
    for(int i = 0; i < this->staff_list.size(); ++i){
        if(isD4) wday = staff_list[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = staff_list[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        if(isD4) a = wday * WEEKDAY + wend * WEEKEND;
        else a = wend * WEEKEND;
        if (!a) continue;
        if(isD4){
            out << this->staff_list[i]->name << "," << this->staff_list[i]->id << "," << this->staff_list[i]->ExportTxt(begin,end,this->holiday,this->DayOffs,isD4)
                << wend << "," << wday << "," << 120 << "," << 50 << "," << a << endl;
        }
        else {
            out << this->staff_list[i]->name << "," << this->staff_list[i]->id << "," << this->staff_list[i]->ExportTxt(begin,end,this->holiday,this->DayOffs,isD4)
                << 120 << "," << wend << "," << a << endl;
        }

    }
    for(int i = 0; i < this->part_time.size(); ++i){
        if(isD4) wday = part_time[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = part_time[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        if(isD4) a = wday * WEEKDAY + wend * WEEKEND;
        else a = wend * WEEKEND;
        if (!a) continue;
        if(isD4){
            out << this->part_time[i]->name << "," << this->part_time[i]->id << "," << this->part_time[i]->ExportTxt(begin,end,this->holiday,this->DayOffs,isD4)
                << wend << "," << wday << "," << 120 << "," << 50 << "," << a << endl;
        }
        else {
            out << this->part_time[i]->name << "," << this->part_time[i]->id << "," << this->part_time[i]->ExportTxt(begin,end,this->holiday,this->DayOffs,isD4)
                << 120 << "," << wend << "," << a << endl;
        }
    }
}

void Manager::exportBrief(Date &begin, Date &end){
    string arr[9] = {"D1","D2","D3","D4","X1","X2","X3","X4","X5"};
    string arr_C[9] = {"东一","东二","东三","东四","西一","西二","西三","西四","西五"};
    string path = "../Wage/";
    path += arr[this->area_num];
    path += "_briefTable.txt";
    double wday = 0.0,wend = 0.0, a = 0.0;
    bool isD4 = (this->area.name == "东四");
    ofstream out;
    out.open(path);
    assert(out.is_open());
    out << this->area.name << "区" << begin.pureDate() << "-" << end.pureDate() << "室内值班员工资简表"<<endl;
    out << "值班员,学号,岗位名称,起始日期,结束日期,总酬金,学校支付金额,聘用单位自付金额,负责助管,备注" << endl;
    for(int i = 0; i < this->staff_list.size(); ++i){
        if(isD4) wday = staff_list[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = staff_list[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        if(isD4) a = wday * WEEKDAY + wend * WEEKEND;
        else a = wend * WEEKEND;
        if (!a) continue;
        out << this->staff_list[i]->name << "," << this->staff_list[i]->id << ",值班员," << begin.pureDate() << ","
            << end.pureDate() << "," << a << "," << a << "," << 0.00 << "," << this->name << ",正常" << endl;
    }
    for(int i = 0; i < this->part_time.size(); ++i){
        if(isD4) wday = part_time[i]->countWeekdayWork(begin, end, this->holiday, this->DayOffs);
        wend = part_time[i]->countWeekendWork(begin, end, this->holiday, this->DayOffs);
        if(isD4) a = wday * WEEKDAY + wend * WEEKEND;
        else a = wend * WEEKEND;
        if (!a) continue;
        out << this->part_time[i]->name << "," << this->part_time[i]->id << ",值班员," << begin.pureDate() << ","
            << end.pureDate() << "," << a << "," << a << "," << 0.00 << "," << this->name << ",正常" << endl;
    }
}

void Manager::commandN() {
    char is = 'N';
    do {
        this->setRelief();
        cout << "是否还需要添加替换班?[Y/N]: ";
        cin >> is;
    } while (is != 'N' && is != 'n');
}

void Manager::commandF() {
    string index;
    char symbol = 'Y';
    do {
        cout << "请输入要查询值班员的姓名/学号(e退出): ";
        cin >> index;
        if (index[0] == 'e' || index[0] == 'E') return;
        if(this->Find(index)) {
            char sym = 'Y';
            cout << "是否修改该值班员信息?[Y/N]: ";
            cin >> sym;
            if (sym == 'Y' || sym == 'y') this->modifyStaff(index);
        }
        cout << "是否继续查询?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'N' && symbol != 'n');
}

void Manager::commandJ() {
    if(this->holiday.empty()) {
        cout << "尚未添加节假日!" << endl;
    } else{
        cout << "已添加的节假日: ";
        for (int i = 0; i < this->holiday.size(); ++i) {
            if (i == this->holiday.size() - 1) cout << this->holiday[i]->pureDate() << endl;
            cout << this->holiday[i]->pureDate() << " ";
        }
    }
    char symbol = 'Y';
    do {
        this->InputHoliday();
        cout << "是否要继续添加节假日?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'N' && symbol != 'n');
}

void Manager::commandC() {
    this->ptstate();
    cout << "请输入需要删除的时间段(闭集）" << endl;
    int year = 2022, month = 2, day = 11;
    int year_begin = 2023, year_end = 2023;
    int month_begin = 2, month_end = 2;
    int day_begin = 14, day_end = 14;
    Date IwageB(year, month, day + 1), IwageE(year, month, day);
    bool BoverE = true;
    bool isD4 = (this->area.name == "东四");
    Date OwageB(this->wageBegin), OwageE(this->wageEnd);
    while (BoverE) {
        bool valid = false;
        while (!valid) {
            cout << "请输入起始日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            IwageB.setDate(year, month, day);
            valid = IwageB.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        year = 2022;
        month = 2;
        day = 11;
        IwageE.setDate(year, month, day);
        valid = false;
        while (!valid) {
            cout << "请输入截止日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            IwageE.setDate(year, month, day);
            valid = IwageE.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        BoverE = IwageB > IwageE;
        if (BoverE) {
            cout << "error: 起始日期大于截止日期！请重新输入" << endl;
            continue;
        }
    }

    if (IwageB < this->wageBegin) {
        cout << "error: 所要删除的起始日期小于已录入的起始日期！删除无效" << endl;
        cout << endl;
        return;
    }
    else if (IwageE > this->wageEnd) {
        OwageB = IwageB;
        OwageE = this->wageEnd;
        this->wageEnd = IwageE;
    }
    else {
        if ((IwageB == this->wageBegin) && (IwageE == this->wageEnd)) {
            OwageB = IwageB;
            OwageE = IwageE;
            this->wageBegin.setDate(2023, 2, 13);
            this->wageEnd.setDate(2023, 2, 13);
        }
        else {
            Blank bb;
            bb.begin = IwageB;
            bb.end = IwageE;
            // 检查是否重复删除，如果是，报错；
            int size = this->blankDays.size();
            for(int j = 0; j < size; ++j){
                if(!(this->blankDays[j].begin > bb.end || this->blankDays[j].end < bb.begin)){
                    if((this->blankDays[j].begin > bb.begin) && (this->blankDays[j].end < bb.end)){
                        bb.begin = this->blankDays[j].begin;
                        bb.end = this->blankDays[j].end;
                    }
                    else if((this->blankDays[j].begin <= bb.begin) && (bb.end <= this->blankDays[j].end)){
                        bb.begin = IwageB;
                        bb.end = IwageE;
                    }
                    else if(this->blankDays[j].begin <= bb.begin) {
                        bb.end = this->blankDays[j].end;
                    }
                    else bb.begin = this->blankDays[j].begin;
                    cout << "error: " << bb.begin.pureDate() << "->" << bb.end.pureDate()
                         << "的值班记录已经被删除过, 删除失败!" << endl;
                    return;
                }
            }
            cout << "warning: 此次删除将会导致" << IwageB.pureDate() << "->" << IwageE.pureDate()
                 << "为未录入的空白日期！" << endl;
            char symbol = 'N';
            cout << "是否要继续删除?[Y/N]: ";
            cin >> symbol;
            if (symbol == 'N' || symbol == 'n') {
                return;
            }
            // 如果没有重复删除，插入新blank
            blankDays.push_back(bb);
            this->jointBlank();
            OwageB = IwageB;
            OwageE = IwageE;
        }
    }
    for (int i = 0; i < this->staff_list.size(); ++i) {
        this->staff_list[i]->deleteBetween(OwageB, OwageE);
    }
    for (int i = 0; i < this->part_time.size(); ++i) {
        this->part_time[i]->deleteBetween(OwageB, OwageE);
    }
    Date* tmp = NULL;
    for (int i = 0; i < this->holiday.size(); ++i) {
        if (OwageE.operator<(*this->holiday[i])) break;
        if (OwageB.operator<=(*this->holiday[i])) {
            tmp = this->holiday[i];
            this->holiday.erase(holiday.begin() + i);
            delete tmp;
            i--;
        }
    }
    cout << endl;
}

void Manager::ptstate() {
    if (this->wageBegin == this->wageEnd) {
        cout << "尚未录入过值班情况!" << endl;
        return;
    }
    cout << "已录入过值班的时间段: ";
    cout << wageBegin.pureDate() << "->" << wageEnd.pureDate() << endl;
    bool blank = this->blankDays.empty();
    if (!blank) {
        cout << "尚未录入的空白时间段: ";
        for (int i = 0; i < this->blankDays.size(); ++i) {
            if (i == this->blankDays.size() - 1)
                cout << this->blankDays[i].begin.pureDate() << "->" << this->blankDays[i].end.pureDate() << endl;
            else cout << this->blankDays[i].begin.pureDate() << "->" << this->blankDays[i].end.pureDate() << " ";
        }
    }
    if(!this->holiday.empty()) {
        cout << "已添加的节假日: ";
        for (int i = 0; i < this->holiday.size(); ++i) {
            if (i == this->holiday.size() - 1) cout << this->holiday[i]->pureDate() << endl;
            else cout << this->holiday[i]->pureDate() << " ";
        }
    }
    if(!this->DayOffs.empty()){
        cout << "已添加过的调休日期: ";
        for(int i = 0; i < this->DayOffs.size(); ++i){
            cout << this->DayOffs[i].day.pureDate() << " ";
        }
        cout << endl;
    }

}

void Manager::setRelief() {
    string index;
    string bname;
    int d = 0;
    bool noon = false;
    char symbol = 'Y';
    FullTime* staff = NULL;
    Building* b = NULL;
    do {
        cout << "请输入原值班员姓名/学号(e退出): ";
        cin >> index;
        if (index[0] == 'e' || index[0] == 'E') return;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'Y' && symbol != 'y');
    FullTime* p = this->findStaff(index);
    if (p == NULL) {
        cout << "error: " << index <<" 查无此人!" << endl;
        return;
    }
    p->ptInfo(this->holiday,this->DayOffs);
    cout << endl;
    cout << "请输入需要替班的楼栋名（eg:D33/X15）: ";
    cin >> bname;
    b = this->findBuilding(bname);
    if (!b) {
        cout << "error: " << bname << " 不属于" << this->area.name << "区!" << endl;
        return;
    }

    // 得到合法替班日期
    int year, month, day;
    Date* rBegin = new Date();
    Date x;
    bool valid = false;
    bool N = false,D = false, T = false;
    bool ho = false;
    while (!valid) {
        cout << "请输入需要替班的日期: " << endl;
        cout << "年: ";
        cin >> year;
        cout << "月: ";
        cin >> month;
        cout << "日: ";
        cin >> day;
        x.setDate(year, month, day);
        char is = 'N';
        for(int i = 0; i < this->holiday.size(); ++i){
            if(this->holiday[i]->operator==(x)){
                is = 'Y';
            }
        }
        if(is == 'y' || is == 'Y'){
            ho = true;
            cout << x.pureDate() << "是正常工资吗?[Y/N]: ";
            cin >> is;
            if(is == 'Y' || is == 'y'){
                N = true;
                D = false;
                T = false;
            }
            else if(is == 'n' || is == 'N') {
                cout << x.pureDate() << "是双倍工资吗?[Y/N]: ";
                cin >> is;
                if (is == 'Y' || is == 'y') {
                    D = true;
                } else if (is == 'N' || is == 'n') {
                    D = false;
                    cout << x.pureDate() << "是三倍工资吗?[Y/N]: ";
                    cin >> is;
                    if (is == 'Y' || is == 'y') {
                        T = true;
                    }
                    else if(is != 'N' && is != 'n'){
                        cout << "输入无效，不会录入!" << endl;
                        return;
                    }
                } else {
                    cout << "输入无效，不会录入!" << endl;
                    return;
                }
            }
            else{
                cout << "输入无效，不会录入!" << endl;
                return;
            }
        }


        d = x.dayth();
        // 如果rBegin是调休日期，则将d换成调休至星期几
        if(!this->DayOffs.empty()) {
            for (int i = 0; i < this->DayOffs.size(); ++i) {
                if (x.operator==(this->DayOffs[i].day)){
                    d = this->DayOffs[i].change;
                    break;
                }
            }
        }
        if (bname == "D34" || bname == "D35") {
            if(!ho) {
                if (d >= 1 && d <= 5) {
                    cout << "请输入需要替班的是上午/下午（0->上午；1->下午）: ";
                    cin >> noon;
                } else {
                    noon = b->FindWeekend(d, index);
                }
            }
            else{
                noon = false;
            }
        }
        rBegin->setDate(year, month, day, noon);
        if(ho){
            if (D) {
                rBegin->setDouble();
            }
            else if (T) {
                rBegin->setTriple();
            }
        }
        valid = rBegin->isValid();
        if (!valid) {
            cout << "error: 输入日期不合法！请重新输入" << endl;
        }
        else {
            break;
        }
    }
    // 这步以后得到：rBegin：替班日期

    staff = b->FindOnDuty(d,index,noon);
    if (!staff) {
        cout << "error: " << index << " 不是原值班员!" << endl;
        return;
    }
    // 这步以后得到：staff：老值班员、b：所需替换楼栋、d：所需替换日期、noon：上午/下午

    // 删除老值班员该天的值班记录
    staff->deleteExact(*rBegin);
    // 写入新值班员
    string comment = bname;
    comment += "替班";
    rBegin->addComment(comment);
    this->addRelief(rBegin);
}

void Manager::ptWage() {
    if (this->wageBegin == this->wageEnd) {
        cout << "尚未录入过值班情况!" << endl;
        return;
    }
    cout << "请输入需要打印工资的时间段(闭集）" << endl;
    this->ptstate();
    int year = 2022, month = 2, day = 11;
    int year_begin = 2023, year_end = 2023;
    int month_begin = 2, month_end = 2;
    int day_begin = 14, day_end = 14;
    Date IwageB(year, month, day + 1), IwageE(year, month, day);
    bool BoverE = true;
    Date OwageB(this->wageBegin), OwageE(this->wageEnd);
    while (BoverE) {
        bool valid = false;
        while (!valid) {
            cout << "请输入起始日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            IwageB.setDate(year, month, day);
            valid = IwageB.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        year = 2022;
        month = 2;
        day = 11;
        IwageE.setDate(year, month, day);
        valid = false;
        while (!valid) {
            cout << "请输入截止日期: " << endl;
            cout << "年: ";
            cin >> year;
            cout << "月: ";
            cin >> month;
            cout << "日: ";
            cin >> day;
            cout << endl;
            IwageE.setDate(year, month, day);
            valid = IwageE.isValid();
            if (!valid) {
                cout << "error: 输入日期不合法！请重新输入" << endl;
            }
            else {
                break;
            }
        }
        BoverE = IwageB > IwageE;
        if (BoverE) {
            cout << "error: 起始日期大于截止日期！请重新输入" << endl;
            continue;
        }
    }
    if (IwageB > this->wageEnd){
        cout << "error: 尚未录入 " << IwageB.pureDate() << " 之后的工资!" << endl;
        return;
    }
    if ((IwageB < this->wageBegin) && (IwageE <= this->wageEnd)) {
        OwageB = this->wageBegin;
        OwageE = IwageE;
    }
    else if ((IwageB >= this->wageBegin) && (IwageE > this->wageEnd)) {
        OwageB = IwageB;
        OwageE = this->wageEnd;
    }
    else if ((IwageB < this->wageBegin) && (IwageE > this->wageEnd)) {
        OwageB = this->wageBegin;
        OwageE = this->wageEnd;
    }
    else {
        OwageB = IwageB;
        OwageE = IwageE;
    }
    // 这一步得到输出工资日期OwageB OwageE

//    cout << OwageB.pureDate() << "->" << OwageE.pureDate() << "的周末: ";
//    for(Date a = OwageB; a <= OwageE; a = a + 1){
//        int dayth = a.dayth();
//        if(dayth == 6 || dayth == 0){
//            cout << a.pureDate() << " ";
//        }
//    }
//    cout << endl;

    bool decide = false;
    char symbol = 'Y';
    do {
        cout << "请输入需要打印的是工资简表/详表（0->简表；1->详表）: ";
        cin >> decide;
        if (!decide) {
            this->commandP(OwageB, OwageE);
        }
        else {
            this->commandD(OwageB, OwageE);
        }
        cout << "是否要继续打印工资表?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'N' && symbol != 'n');
}

void Manager::initManager() {
    cout << "你好鸭！初次见面，我该怎么称呼你呢? ";
    cin >> this->name;
    cout << "你好！亲爱的 " << this->name << " ，请问你的学号是? ";
    string idd;
    cin >> idd;
    this->id = idd;
    string arr_C[9] = {"东一","东二","东三","东四","西一","西二","西三","西四","西五"};
    int h = 0;
    string are;
    do {
        cout << "请问你管理的片区是?";
        for(int i = 0; i < 9; ++i){
            if(i == 0){
                cout << "( "<< i << "->" << arr_C[i]<<"; ";
            }
            else if(i == 8){
                cout << i << "->" << arr_C[i]<<" ): ";
            }
            else{
                cout << i << "->" << arr_C[i]<<"; ";
            }
        }
        cin >> h;
        are = arr_C[h];
        if(h < 0 || h > 8){
            cout << "没有该宿舍片区! 请重新输入。" << endl;
            continue;
        }
    } while (h < 0 || h > 8);
    this->area.name = are;
    char symbol = 'Y';
    do {
        cout << "请输入属于 " << this->area.name << " 区的楼栋名(eg:D34/X10): ";
        string build;
        cin >> build;
        this->area.addBuilding(build);
        cout << "楼栋是否添加完全?[Y/N]: ";
        cin >> symbol;
    } while (symbol != 'Y' && symbol != 'y');

    this->initBuiding();

}

void Manager::initBuiding() {
    if (this->area.name == "东四") {
        FullTime* staff = NULL;
        for (int i = 0; i < this->area.dormlist.size(); ++i) {
            string building = this->area.dormlist[i]->name;
            if (building == "D34" || building == "D35") {
                for (int j = 0; j < 7; ++j) {
                    string d = "";
                    switch (j) {
                        case 0:
                            d = "星期天";
                            break;
                        case 1:
                            d = "星期一";
                            break;
                        case 2:
                            d = "星期二";
                            break;
                        case 3:
                            d = "星期三";
                            break;
                        case 4:
                            d = "星期四";
                            break;
                        case 5:
                            d = "星期五";
                            break;
                        case 6:
                            d = "星期六";
                            break;
                        default:
                            break;
                    }
                    do {
                        staff = NULL;
                        staff = this->inputStaff(building, j, false);
                        if (!staff) {
                            cout << "error: 添加" << building << d << "上午的值班员失败!" << endl;
                            continue;
                        }
                    }while(!staff);
                    this->area.addStaff(building, staff, j, false);

                    do {
                        staff = NULL;
                        staff = this->inputStaff(building, j, true);
                        if (!staff) {
                            cout << "error: 添加" << building << d << "下午的值班员失败!" << endl;
                            continue;
                        }
                    }while(!staff);
                    this->area.addStaff(building, staff, j, true);
                }
            }
            else {
                do {
                    staff = NULL;
                    staff = this->inputStaff(building, 6, false);
                    if (!staff) {
                        cout << "error: 添加" << building << "星期六的值班员失败!" << endl;
                        continue;
                    }
                }while(!staff);
                this->area.addStaff(building, staff, 6, false);

                do {
                    staff = NULL;
                    staff = this->inputStaff(building, 0, false);
                    if (!staff) {
                        cout << "error: 添加" << building << "星期天的值班员失败!" << endl;
                        continue;
                    }
                }while(!staff);
                this->area.addStaff(building, staff, 0, false);
                building = "";
            }
        }

    }
    else {
        FullTime* staff = NULL;
        for (int i = 0; i < this->area.dormlist.size(); ++i) {
            string building = this->area.dormlist[i]->name;
            do {
                staff = NULL;
                staff = this->inputStaff(building, 6, false);
                if (!staff) {
                    cout << "error: 添加" << building << "星期六的值班员失败!" << endl;
                    continue;
                }
            }while(!staff);
            this->area.addStaff(building, staff, 6, false);
            do {
                staff = NULL;
                staff = this->inputStaff(building, 0, false);
                if (!staff) {
                    cout << "error: 添加" << building << "星期天的值班员失败!" << endl;
                    continue;
                }
            }while(!staff);
            this->area.addStaff(building, staff, 0, false);
            building = "";
        }
    }
}

void Manager::addBuilding(string building) {
    this->area.addBuilding(building);
    if (this->area.name == "东四") {
        FullTime* staff = NULL;
        if (building == "D34" || building == "D35") {
            for (int j = 0; j < 7; ++j) {
                string d = "";
                switch (j) {
                    case 0:
                        d = "星期天";
                        break;
                    case 1:
                        d = "星期一";
                        break;
                    case 2:
                        d = "星期二";
                        break;
                    case 3:
                        d = "星期三";
                        break;
                    case 4:
                        d = "星期四";
                        break;
                    case 5:
                        d = "星期五";
                        break;
                    case 6:
                        d = "星期六";
                        break;
                    default:
                        break;
                }
                do {
                    staff = NULL;
                    staff = this->inputStaff(building, j, false);
                    if (!staff) {
                        cout << "error: 添加" << building << d << "上午的值班员失败!" << endl;
                        continue;
                    }
                }while(!staff);
                this->area.addStaff(building, staff, j, false);

                do {
                    staff = NULL;
                    staff = this->inputStaff(building, j, true);
                    if (!staff) {
                        cout << "error: 添加" << building << d << "下午的值班员失败!" << endl;
                        continue;
                    }
                }while(!staff);
                this->area.addStaff(building, staff, j, true);
            }
        }
        else {
            do {
                staff = NULL;
                staff = this->inputStaff(building, 6, false);
                if (!staff) {
                    cout << "error: 添加" << building << "星期六的值班员失败!" << endl;
                    continue;
                }
            }while(!staff);
            this->area.addStaff(building, staff, 6, false);

            do {
                staff = NULL;
                staff = this->inputStaff(building, 0, false);
                if (!staff) {
                    cout << "error: 添加" << building << "星期天的值班员失败!" << endl;
                    continue;
                }
            }while(!staff);
            this->area.addStaff(building, staff, 0, false);
            building = "";
        }

    }
    else {
        FullTime* staff = NULL;
        do {
            staff = NULL;
            staff = this->inputStaff(building, 6, false);
            if (!staff) {
                cout << "error: 添加" << building << "星期六的值班员失败!" << endl;
                continue;
            }
        }while(!staff);
        this->area.addStaff(building, staff, 6, false);

        do {
            staff = NULL;
            staff = this->inputStaff(building, 0, false);
            if (!staff) {
                cout << "error: 添加" << building << "星期天的值班员失败!" << endl;
                continue;
            }
        }while(!staff);
        this->area.addStaff(building, staff, 0, false);
        building = "";
    }
}

FullTime* Manager::inputStaff(string building, int day, bool noon) {
    FullTime* staff = NULL;
    string n;
    bool is = false;
    if (this->area.name == "东四") {
        if (building == "D34" || building == "D35") {
            if(day >= 1 && day <= 5) {
                is = true;
                if (!noon) n = "上午";
                else n = "下午";
            }
        }
    }
    string d;
    if (day == 0) d = "星期天";
    else if (day == 1) d = "星期一";
    else if (day == 2) d = "星期二";
    else if (day == 3) d = "星期三";
    else if (day == 4) d = "星期四";
    else if (day == 5) d = "星期五";
    else if (day == 6) d = "星期六";
    else return NULL;
    string index;
    char psymbol;
    bool ispname = true;
    do {
        if (is) cout << "请输入" << building << d << n << "值班员的姓名/学号: ";
        else cout << "请输入" << building << d << " 值班员的姓名/学号: ";
        index = "";
        cin >> index;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> psymbol;
    } while (psymbol != 'Y' && psymbol != 'y');
    bool in = false;
    in = this->Find(index);
    if (index[0] >= '0' && index[0] <= '9') {
        ispname = false;
    }
    else {
        ispname = true;
    }

    string nid, nphone, nbuilding, ndorm;
    if (ispname && !in) {
        staff = new FullTime(index);
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的学号: ";
        cin >> nid;
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        staff->addInfo(nid, nphone, nbuilding, ndorm);
        this->staff_list.push_back(staff);
    }
    else if (!ispname && !in) {
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的姓名: ";
        cin >> nid;
        staff = new FullTime(id);
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        this->staff_list.push_back(staff);
        staff->addInfo(index, nphone, nbuilding, ndorm);
    }
    else {
        staff = this->findStaff(index);
    }
    if (!in) {
            staff->ptInfo(this->holiday,this->DayOffs);
            cout << endl;
        }
    return staff;
}

void Manager::commandDeduct() {
    string index = "";
    char psymbol;
    do {
        cout << "请输入要扣除/添加工作量的值班员姓名/学号(e退出): ";
        cin >> index;
        if (index[0] == 'e' || index[0] == 'E') return;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> psymbol;
    } while (psymbol != 'Y' && psymbol != 'y');
    FullTime* staff = NULL;
    staff = this->findStaff(index);
    if (!staff) {
        cout << "error: " << index << " 没有值过班！" << endl;
        return;
    }
    staff->ptInfo(this->holiday,this->DayOffs);
    // 这步以后得到staff：待扣除工作量的值班员

    int year = 2022, month = 2, day = 11;
    bool n = false;
    Date de(year, month, day);
    bool valid = false;
    bool ho = false;
    while (!valid) {
        cout << "请输入要扣除/添加工作量的日期: " << endl;
        cout << "年: ";
        cin >> year;
        cout << "月: ";
        cin >> month;
        cout << "日: ";
        cin >> day;
        de.setDate(year, month, day);
        char is = 'N';
        ho = this->isHoliday(de);

        valid = de.isValid();
        if (!valid) {
            cout << "error: 输入日期不合法！请重新输入" << endl;
            continue;
        }
        break;
    }
    if (de < this->wageBegin || de > this->wageEnd) {
        cout << "error: 已录入工资的时间段中没有该日期！" << endl;
        return;
    }
    Date iswork1,iswork2;
    iswork1.setDate(year,month,day, false);
    iswork2.setDate(year,month,day, true);

    if((!staff->isWork(iswork1)) && (!staff->isWork(iswork2))){
        cout << "error: " << staff->name << "未在 " << de.pureDate() << "值过班!" << endl;
        return;
    }

    string b = "";
    Building* buiding = NULL;
    cout << "该天值班楼栋(eg:D34/X23): ";
    cin >> b;
    buiding = this->findBuilding(b);
    if (!buiding) {
        cout << "error: " << b << " 不属于" << this->area.name << "区!" << endl;
        return;
    }
    if (this->area.name == "东四") {
        if (b == "D34" || b == "D35") {
            if(!ho) {
                int dayth = de.dayth();
                if (dayth >= 1 && dayth <= 5) {
                    cout << "上午/下午(0->上午;1->下午): ";
                    cin >> n;
                } else {
                    n = buiding->FindWeekend(dayth, index);
                }
            }
            else{
                n = false;
            }
        }
    }
    de.setDate(year, month, day, n);
    // 这步以后得到de：待扣除工作量的日期

    // 查找staff在de天的工作记录
    Date* old = staff->isWork(de);
    if (!old) {
        cout << "error: " << index << " 未在 " << de.pureDate() << "值班！" << endl;
        return;
    }

    // 添加备注及设置新工作量
    string comment = "";
    cout << "请添加备注: ";
    cin >> comment;
    old->addComment(b + ":" + comment);
    double w = 1.0;
    cout << "请输入新的工作量(x>=0): " << endl;
    char load[100];
    getchar();
    cin.getline(load,99);
    w = this->getnumDivide(load);
    if (w < 0.0) {
        cout << "error: 错误的剩余工作量 " << w << "!" << endl;
        return;
    }
    old->setWorkload(w);
    staff->ptInfo(this->holiday,this->DayOffs);
    cout << endl;
}

double Manager::getnumDivide(char *arr ){
    int length = strlen(arr);
    double re = 1.0,tmp =0;
    int pos = 0;
    bool dep = false;
    for(int i =0;i<length;i++){

        if(arr[i]>='0'&&arr[i]<='9'){
            if(dep) pos++;
            tmp = tmp*10+(arr[i]-'0');
            continue;
        }
        if(arr[i]=='.'){
            if(dep){
                tmp /= pow(10, pos);
                printf("tmp=%f\n",tmp);

                re += tmp;
                pos = 0;
                tmp =0;
                continue;
            }
            else {
                dep = true;
                continue;
            }
        }
        if(arr[i] == ' ' || arr[i] == '/'){
            if(i==0||arr[i-1]<'0'||arr[i-1]>'9') continue;
            tmp /= pow(10, pos);
            if(re == 1) re = tmp;
            else re = re / tmp;
            pos = 0;
            dep = false;
            tmp =0;
            continue;
        }

    }
    tmp /= pow(10, pos);
    re = re / tmp;
    return re;
}

void Manager::modifyStaff(string index) {
    FullTime* staff = NULL;
    staff = this->findStaff(index);
    string sname, id, phone, building, dorm;
    cout << "请输入该同学的姓名(e退出): ";
    cin >> sname;
    if (sname[0] != 'e' && sname[0] != 'E') {
        staff->name = sname;
    }
    cout << "请输入该同学的学号(e退出): ";
    cin >> id;
    if (id[0] != 'e' && id[0] != 'E') {
        staff->id = id;
    }
    cout << "请输入该同学的电话号码(e退出): ";
    cin >> phone;
    if (phone[0] != 'e' && phone[0] != 'E') {
        staff->setPhone(phone);
    }
    cout << "请输入该同学所在楼栋(eg:D4/X4)(e退出): ";
    cin >> building;
    if (building[0] != 'e' && building[0] != 'E') {
        staff->setBuilding(building);
    }
    cout << "请输入该同学的宿舍号(eg:314)(e退出): ";
    cin >> dorm;
    if (dorm[0] != 'e' && dorm[0] != 'E') {
        staff->setDorm(dorm);
    }
    staff->ptInfo(this->holiday,this->DayOffs);
}

FullTime *Manager::inputStaff(string building, Date& holiday) {
    FullTime* staff = NULL;
    string index;
    char psymbol;
    bool ispname = true;
    do {
        cout << "请输入 " << building << " 楼" << holiday.pureDate() << " 值班员的姓名/学号: ";
        index = "";
        cin >> index;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> psymbol;
    } while (psymbol != 'Y' && psymbol != 'y');
    bool in = false;
    staff = this->findStaff(index);
    in = (staff == NULL)? false:true;
    staff = NULL;
    if (index[0] >= '0' && index[0] <= '9') {
        ispname = false;
    }
    else {
        ispname = true;
    }

    string nid, nphone, nbuilding, ndorm;
    if (ispname && !in) {
        staff = new FullTime(index);
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的学号: ";
        cin >> nid;
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        staff->addInfo(nid, nphone, nbuilding, ndorm);
        this->part_time.push_back(staff);
    }
    else if (!ispname && !in) {
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的姓名: ";
        cin >> nid;
        staff = new FullTime(id);
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        staff->addInfo(index, nphone, nbuilding, ndorm);
        this->part_time.push_back(staff);
    }
    else {
        staff = this->findStaff(index);
    }
    if (!in) {
            staff->ptInfo(this->holiday,this->DayOffs);
            cout << endl;
        }
    return staff;
}
FullTime* Manager::inputStaff(string info){
    FullTime* staff = NULL;
    string index;
    char psymbol;
    bool ispname = true;
    do {
        cout << info;
        index = "";
        cin >> index;
        cout << "请核对输入是否正确?[Y/N]: ";
        cin >> psymbol;
    } while (psymbol != 'Y' && psymbol != 'y');
    bool in = false;
    staff = this->findStaff(index);
    in = (staff == NULL)? false:true;
    staff = NULL;
    if (index[0] >= '0' && index[0] <= '9') {
        ispname = false;
    }
    else {
        ispname = true;
    }

    string nid, nphone, nbuilding, ndorm;
    if (ispname && !in) {
        staff = new FullTime(index);
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的学号: ";
        cin >> nid;
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        staff->addInfo(nid, nphone, nbuilding, ndorm);
        this->part_time.push_back(staff);
    }
    else if (!ispname && !in) {
        cout << "该同学为新值班员，需对其进行培训！" << endl;
        cout << "请输入该同学的姓名: ";
        cin >> nid;
        staff = new FullTime(id);
        cout << "请输入该同学的电话号码: ";
        cin >> nphone;
        cout << "请输入该同学所在楼栋:(eg:D4/X4) ";
        cin >> nbuilding;
        cout << "请输入该同学的宿舍号:(eg:314) ";
        cin >> ndorm;
        cout << endl;
        staff->addInfo(index, nphone, nbuilding, ndorm);
        this->part_time.push_back(staff);
    }
    else {
        staff = this->findStaff(index);
    }
    if (!in) staff->ptInfo(this->holiday,this->DayOffs);
    cout << endl;
    return staff;
}
void Manager::updateBlank(Date &begin, Date &end) {
    // 遍历blankDays
    for(int i = 0; i < this->blankDays.size(); ++i){
        // 如果blank含于（begin，end），则删除该blank
        if((this->blankDays[i].begin >= begin) && (this->blankDays[i].end <= end)){
            this->blankDays.erase(this->blankDays.begin() + i);
            i--;
            continue;
        }
        // 如果（begin，end）含于 blank, 拆分blank并重新插入
        if((this->blankDays[i].begin < begin) && (this->blankDays[i].end > end)){
            Blank b1,b2;
            b1.begin = this->blankDays[i].begin;
            b1.end = begin - 1;
            b2.begin = end + 1;
            b2.end = this->blankDays[i].end;
            this->blankDays.erase(this->blankDays.begin() + i);
            this->blankDays.insert(this->blankDays.begin() + i, b1);
            this->blankDays.insert(this->blankDays.begin() + i + 1, b2);
            i++;
            continue;
        }
        // 如果blank有部分位于（begin，end），则更新该blank
        if(this->blankDays[i].begin <= begin){
            this->blankDays[i].end = begin - 1;
        }
        else{
            this->blankDays[i].begin = end + 1;
        }
    }
}

void Manager::addBetween(Date &begin, Date &end) {
    // 初始化工资表
    Date* work = NULL;
    int days1 = begin.dateLength();
    for(Date a = begin; a <= end; a = a + 1){
        for (auto & i : this->area.dormlist) {
            if (i->name == "D34" || i->name == "D35") {
                work = new Date(a.y(), a.m(), a.d(), false);
                i->addWork(work, days1 % 7, false);
                work = new Date(a.y(), a.m(), a.d(), true);
                i->addWork(work, days1 % 7, true);
            }
            else if ((days1 % 7 == 0) || (days1 % 7 == 6)) {
                work = new Date(a.y(), a.m(), a.d(), false);
                i->addWork(work, days1 % 7, false);
            }
        }
        days1++;
    }
}

void Manager::fillInBlank(Date &begin, Date &end) {
    // 遍历blankDays
    for(int i = 0; i < this->blankDays.size(); ++i){
        // 如果blank含于（begin，end），则加入blank内的值班记录、删除该blank
        if((this->blankDays[i].begin >= begin) && (this->blankDays[i].end <= end)){
            this->addBetween(this->blankDays[i].begin,this->blankDays[i].end);
            this->blankDays.erase(this->blankDays.begin() + i);
            i--;
            continue;
        }
        // 如果（begin，end）含于 blank, 则拆分blank、加入（begin，end）内的值班记录、并重新插入
        if((this->blankDays[i].begin < begin) && (this->blankDays[i].end > end)){
            Blank b1,b2;
            b1.begin = this->blankDays[i].begin;
            b1.end = begin - 1;
            b2.begin = end + 1;
            b2.end = this->blankDays[i].end;
            this->addBetween(begin,end);
            this->blankDays.erase(this->blankDays.begin() + i);
            this->blankDays.insert(this->blankDays.begin() + i, b1);
            this->blankDays.insert(this->blankDays.begin() + i + 1, b2);
            i++;
            continue;
        }
        // 如果blank有部分位于（begin，end），则加入blank内的值班记录、更新该blank
        if(this->blankDays[i].begin <= begin){
            this->addBetween(begin,this->blankDays[i].end);
            this->blankDays[i].end = begin - 1;
        }
        else{
            this->addBetween(this->blankDays[i].begin,end);
            this->blankDays[i].begin = end + 1;
        }
    }
}
void Manager::jointBlank(){
    for(int i = 0; i < this->blankDays.size() -1 ; ++i){
        if((this->blankDays[i].end+1) == (this->blankDays[i+1].begin)){
            Blank b;
            b.begin = this->blankDays[i].begin;
            b.end = this->blankDays[i+1].end;
            this->blankDays[i].begin = b.begin;
            this->blankDays[i].end = b.end;
            this->blankDays.erase(this->blankDays.begin() + i + 1);
        }
    }
}
