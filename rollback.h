#ifndef ROLLBACK_H
#define ROLLBACK_H

#include "simulation.h"
#include <iostream>

using namespace std;

/*
Rollback is created to keep track of changes that are not wanted
Faculty, Students, and string data is held in specific cases. There are many
functions to run different tasks to get the rollback feature workign.
*/

class Rollback{
    private:
        Student StudentDB_Data;
        Faculty FacultyDB_Data;
        string DB_type;
    public:
        void storeDB_type(string a);
        void studentDB(Student a);
        Student getStudent();
        Faculty getFaculty();
        string getType();
        void facultyDB(Faculty a);
        Rollback();
};


#endif