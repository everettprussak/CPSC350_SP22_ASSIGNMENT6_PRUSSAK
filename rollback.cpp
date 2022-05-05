#include "rollback.h"

Rollback::Rollback(){ //default
    StudentDB_Data = Student();
    FacultyDB_Data = Faculty();
    DB_type = "";
}

void Rollback::facultyDB(Faculty a){ //We are rolling back a Faculty Insert/deletion
    FacultyDB_Data = a;
}

void Rollback::studentDB(Student a){ //we are rolling back a Student Insert/Deletion
    StudentDB_Data = a;
}

void Rollback::storeDB_type(string a){ //what type of insert/delete and member
    DB_type = a;
}


Student Rollback::getStudent(){ //returns student
    return StudentDB_Data;
}

Faculty Rollback::getFaculty(){ //retrusn faculty
    return FacultyDB_Data;
}

string Rollback::getType(){ //returns data type
    return DB_type;
}