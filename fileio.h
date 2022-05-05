#ifndef FILEIO_H
#define FILEIO_H
#include <string>
#include "bst.h"
#include "faculty.h"
#include "student.h"
#include <iostream>

using namespace std;

//header file for FileIo class that starts and ends the program

class FileIo{
    public:
        FileIo();
        string getStudentData();
        string getFacultyData();
        bool startWith();
        int getStudentCount();
        int getFacultyCount();
        string facultyBase(string a, int b);
        BST<Faculty> processFacultyData();
        BST<Student> processStudentData();
        void end(BST<Student> masterStudent, BST<Faculty> masterFaculty);
    private:
        string studentData;
        string facultyData;
        bool facTable;
        bool studTable;
        int studentCount;
        int facultyCount;
};


#endif