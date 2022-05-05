#ifndef SIMULATION_H
#define SIMULATION_H
#include "student.h"
#include "faculty.h"
#include "bst.h"
#include <iostream>
#include <string>
using namespace std;

/*
Simulation is simulates and does multiple tasks when called. Almost all options
require this class to be used to correctly change,add,delete data to anything
*/


class Simulation{
    public:
        Simulation();
        void Choices();
        Student addStudent(BST<Student> tree);
        Faculty addFaculty(BST<Faculty> tree);
        int addStudentPart2(Student a,BST<Faculty> tree);
        Student deleteStudent(BST<Student> tree, BST<Faculty> tree1);
        Faculty deleteFaculty(BST<Student> tree, BST<Faculty> tree1);
        Faculty changeAdvisor(BST<Student> tree, BST<Faculty> tree1);
        void removeAdvisee(BST<Student> tree, BST<Faculty> tree1);
        int displayStudent(BST<Student> tree);
        int displayFaculty(BST<Faculty> tree);
        int studentTOfaculty(BST<Student> tree, BST<Faculty> tree1);
        int facultyTOstudent(BST<Student> tree, BST<Faculty> tree1);
};

#endif