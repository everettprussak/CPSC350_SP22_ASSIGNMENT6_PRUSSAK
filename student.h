#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>

using namespace std;

/*
header class for student.cpp
The main goal of this is to have an object type Student that has certain data aspects that is true to just them.
Students will be stored in the BST.
*/

class Student{
    private:
        int studentId;
        string name;
        string level;
        string major;
        double gpa;
        int advisor; //contains student faculty id number for their personal advisor
        string returning;

    public:
        Student();
        Student(int a, string b, string c, string d, double e, int f);
        void setStudentId(int a);
        void setStudentName(string a);
        void setStudentLevel(string a);
        void setStudentMajor(string a);
        void setStudentGPA(double a);
        void setStudentAdvisor(int a);
        void setStudentAdvisor();

        int getId();
        string getStudentName();
        string getStudentLevel();
        string getStudentMajor();
        double getStudentGPA();
        int getStudentAdvisor();

        int compareTo(Student* s);
        bool operator==(const Student& stud) const;
        bool operator<(const Student& stud) const;
        bool operator>(const Student &stud) const;
        bool operator!=(const Student &stud) const;

        void printInfo();
        string stringInfo();

};

#endif