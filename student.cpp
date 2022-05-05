#include "student.h"

Student::Student(){//default
    studentId = -1;
    name = "";
    level = "";
    major = "";
    gpa = -1.0;
    advisor = -1;
}

Student::Student(int a, string b, string c, string d, double e, int f){ //overloaded
    studentId = a;
    name = b;
    level = c;
    major = d;
    gpa = e;
    advisor = f;
}

int Student::getId(){ //returns studentId
    return studentId;
}

string Student::getStudentName(){ //returns name
    return name;
}

string Student::getStudentLevel(){ //returns level
    return level;
}

string Student::getStudentMajor(){ //returns major
    return major;
}

double Student::getStudentGPA(){ //returns gpa
    return gpa;
}

int Student::getStudentAdvisor(){ //returns advisor
    return advisor;
}

void Student::setStudentId(int a){ //sets studentID
    studentId = a;
}

void Student::setStudentName(string a){ //sets name
    name = a;
}

void Student::setStudentLevel(string a){ //set level
    level = a;
}

void Student::setStudentMajor(string a){ //sets major
    major = a;
}

void Student::setStudentGPA(double a){ //sets gpa
    gpa = a;
}

void Student::setStudentAdvisor(int a){ //sets advisor
    advisor = a;
}

void Student::setStudentAdvisor(){ //makes advisor -102, which means that the student does not have an advisor set
    advisor = -102;
}

int Student::compareTo(Student* s){ //comparing two students
  int tempId = s->getId();
  if(studentId > tempId){
    return 0;
  }
  return 1;
}

bool Student::operator==(const Student& stud) const { //comparing if students are equal for BST
    return studentId==stud.studentId;
}

bool Student::operator<(const Student& stud) const { //comparing if student is less than another student for BST
    return studentId<stud.studentId;
}

bool Student::operator>(const Student& stud) const { //comparing if student is greater than another student for BST
    return studentId>stud.studentId;
}

bool Student::operator!=(const Student& stud) const { //comparing if studne is different than anotehr student
    return studentId!=stud.studentId;
}

void Student::printInfo(){ //printing data for specific student
    gpa = (gpa*100.00)/100.00;
    string info = "Student ID: ";
    info = info + to_string(studentId) + "\n";
    info = info + "Student Name: " + name + "\n";
    info = info + "Student Level: " + level + "\n";
    info = info + "Student Major: " + major + "\n";
    info = info + "Student GPA: " + to_string(gpa) + "\n";
    if(advisor==-102){
        info = info + "Student Advisor ID: ";
    }
    else{
        info = info + "Student Advisor ID: " + to_string(advisor);
    }
    returning = info;
    cout <<  info << endl;
}

string Student::stringInfo(){ //
    return returning;
}