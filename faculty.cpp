#include "faculty.h"

Faculty::Faculty(){ //deafult
    facultyId = -1;
    name = "";
    depart = "";
    level = "";
}

Faculty::Faculty(int a, string b, string c, string d){ //overloaded
    facultyId = a;
    name = b;
    depart = c; 
    level = d;
}

void Faculty::setFacultyId(int a){ //sets facultyid
    facultyId = a;
}

int Faculty::getId(){
    return facultyId;
}

void Faculty::addFacultyMember(int a){
    members.push_back(a);
}

vector<int> Faculty::getFacultyMembers(){
    return members;
}


bool Faculty::operator==(const Faculty& fac) const { //checks if faculty members are the same through their id
    return facultyId==fac.facultyId;
}

bool Faculty::operator<(const Faculty& fac) const { //checks if faculty member is smaller than another faculty
    return facultyId<fac.facultyId;
}

bool Faculty::operator>(const Faculty& fac) const { //checks if faculty member is bigger than anotehr faculty member
    return facultyId>fac.facultyId;
}

bool Faculty::operator!=(const Faculty& fac) const { //checks if they are differetn
    return facultyId!=fac.facultyId;
}

void Faculty::printInfo(){ //prints faculty info
    string ret = "Faculty ID: " + to_string(facultyId) + "\n";
    ret = ret + "Faculty Name: " + name + "\n";
    ret = ret + "Faculty Level: " + level + "\n";
    ret = ret + "Faculty Department: " + depart + "\n";
    ret = ret + "Member IDS: ";
    sort(members.begin(), members.end());
    for(auto i: members){
        ret = ret + to_string(i) + " ";
    }
    ret = ret + "\n";
    cout << ret << endl;
}

void Faculty::removeFacultyMember(int a){ //removes the student from their vector of students
    int count = 0;
    for(auto i: members){
        if(i==a){
            break;
        }
        count++;
    }
    members.erase(members.begin()+count);
}

void Faculty::setFacultyDepart(string a){
    depart = a;
}

void Faculty::setFacultyLevel(string a){
    level = a;
}

void Faculty::setFacultyName(string a){
    name = a;
}

string Faculty::getFacultyDepart(){
    return depart;
}

string Faculty::getFacultyLevel(){
    return level;
}

string Faculty::getFacultyName(){
    return name;
}