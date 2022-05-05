#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
The Faculty class holds important and vital data of specific faculty members. They are created
similarly to students, but have different properties in some parts.
Many settors/gettors are used throughout the program to get data from a faculty member.
*/


class Faculty{
    private:
        int facultyId;
        string name;
        string level;
        string depart;
        vector<int> members;
    
    public:
        Faculty();
        Faculty(int a, string b, string c, string d);

        void setFacultyId(int a);
        int getId();
        void setFacultyName(string a);
        void setFacultyLevel(string a);
        void setFacultyDepart(string a);

        vector<int> getFacultyMembers();
        void addFacultyMember(int a);
        void removeFacultyMember(int a);
        string getFacultyName();
        string getFacultyLevel();
        string getFacultyDepart();

        void printInfo();

        bool operator==(const Faculty& fac) const;
        bool operator<(const Faculty& fac) const;
        bool operator>(const Faculty& fac) const;
        bool operator!=(const Faculty& fac) const;


};


#endif