#include "simulation.h"

/*
Main program in the Project. This does many of the heavy lifting for specifc tasks.
This will print our choices, and do many things like adding students to the BST, deleting, etc.
*/



Simulation::Simulation(){ //default

}


void Simulation::Choices(){
    string choice = "Type in the number of the choice you want to make: \n";
    choice = choice + "1. Print all students and their information (sorted by ascending id #) \n";
    choice = choice + "2. Print all faculty and their information (sorted by ascending id #) \n";
    choice = choice + "3. Find and display student information given the students id \n";
    choice = choice + "4. Find and display faculty information given the faculty id \n";
    choice = choice + "5. Given a student's id, print the name and info of their faculty advisor \n";
    choice = choice + "6. Given a faculty id, print ALL the names and info of his/her advisees. \n";
    choice = choice + "7. Add a new student \n";
    choice = choice + "8. Delete a student given the id \n";
    choice = choice + "9. Add a new faculty member \n";
    choice = choice + "10. Delete a faculty member given \n";
    choice = choice + "11. Change a student's advisor given the student id and the new faculty id. \n";
    choice = choice + "12. Remove an advisee from a faculty member given the ids \n";
    choice = choice + "13. Rollback \n";
    choice = choice + "14. Exit \n";
    cout << choice << endl;
}

//returns student that will be added to masterStudent
Student Simulation::addStudent(BST<Student> tree){
    Student a = Student();
    string curr, rand, name, level, major, gpa;
    bool same = false;
    cout << "Enter Student ID: ";
    cin >> curr;
    try{ //making sure user does not add letters or unknowns
        a.setStudentId(stoi(curr));
        cout << "";
        while(tree.search(stoi(curr))!=NULL){ //student id already exists, and every student has a unique id
            cout << "Student ID already exists!" << endl;
            cout << "Enter Student ID: ";
            cin >> curr;
            a.setStudentId(stoi(curr));
        }
        getline(cin,rand); //asking user for vital information for the student
        cout << "Enter Student Name: ";
        getline(cin,name);
        a.setStudentName(name);
        cout << "Enter Student Level: ";
        getline(cin, level);
        a.setStudentLevel(level);
        cout << "Enter Student Major: ";
        getline(cin, major);
        a.setStudentMajor(major);
        cout << "Enter Student GPA: ";
        getline(cin, gpa);
        try{ //making sure student gpa can be converted into double
            a.setStudentGPA(stod(gpa));
            cout << endl;
            return a;
        }
        catch(exception &err){ //user messed up with gpa
            cout << "Enter GPA as int or double only!" << endl;
            cout << "Student NOT ADDED. Click 7 again to redo." << endl;
            cout << endl;
            Student b = Student();
            b.setStudentId(-100); //this tells main that student should not be added, somethign went wrong
            return b;
        }
    }
    catch(exception &err){
        cout << "Enter ID as int number only!" << endl;
        cout << "Student NOT ADDED. Click 7 again to redo." << endl;
        cout << endl;
        Student b = Student();
        b.setStudentId(-100); //this also tells main that the student shoult NOT be added due to user error.
        return b;
    }
    return a;
}  

//close to addStudent but with a faculty member
//faculty can only add students by option 11 and manually changing student advisor to them
Faculty Simulation::addFaculty(BST<Faculty> tree){
    Faculty f = Faculty();
    f.setFacultyId(-100); //assuming user to do something wrong until it is done correct
    int facId = 0;
    string currId, rand, name, level, depart;
    cout << "Enter Faculty ID Num: ";
    cin >> currId;
    try{//making sure user does it correct
        facId = stoi(currId);
        f.setFacultyId(facId);
        while(tree.search(facId)!=NULL){ //each fauclty has their own id number so they cannot share the id number, user must try again
            cout << "Faculty ID already exists!" << endl;
            cout << "Enter Faculty ID: ";
            cin >> currId;
            facId = stoi(currId);
            f.setFacultyId(stoi(currId));
        }
        cout << "";
        getline(cin,rand);
        cout << "Enter Faculty Name: ";
        getline(cin,name);
        f.setFacultyName(name);
        cout << endl;
        cout << "Enter Faculty Level: ";
        getline(cin,level);
        f.setFacultyLevel(level);
        cout << endl;
        cout << "Enter Faculty Department: ";
        getline(cin,depart);
        f.setFacultyDepart(depart);
        return f;
    }
    catch(exception &err){
        cout << "Enter Faculty ID as int number!" << endl;
        cout << "Faculty Member NOT added. Click 9 to retry!" << endl;
        cout << endl;
        return f;
    }
}

//removes advisee from the faculty 
void Simulation::removeAdvisee(BST<Student> studentTree, BST<Faculty> facultyTree){
    string curr;
    int r = 0, fac =0, stud = 0;
    cout << "Enter Faculty ID: " << endl;
    cin >> curr;
    try{
        while(facultyTree.search(stoi(curr))==NULL){ //faculty member must exist to continue
            cout << "Faculty Member does not exist!" << endl;
            cout << "Enter 1 for list of Faculty, 2 to retry, and 3 for nothing to change: "; //giving options if they really want to remove or if they want to leave
            cin >> r;
            if(r==3){
                continue;
            }
            else if(r==1){
                facultyTree.inorder(facultyTree.getRoot()); //printing all facutly members 
            }
            else if(r==2){
                cout << "Enter Faculty ID: " << endl;
                cin >> curr;
            }
        }
        if(r!=3){
            fac = stoi(curr);
            Faculty *f = facultyTree.search(stoi(curr));
            vector<int> mems = f->getFacultyMembers();
            f->printInfo();
            bool inVec = false; //student id must be in the member vector. if not then it continue
            while(inVec==false){
                cout << "Enter Student ID from this Specific Faculty Member to remove: ";
                cin >> curr;
                for(auto i: mems){
                    if(stoi(curr)==i){
                        inVec = true; //student id is in the vector
                        continue;
                    }
                }
                cout << "Invalid Student ID" << endl;
            }
            Student *s = studentTree.search(stoi(curr));
            f->removeFacultyMember(stoi(curr)); //updates faculty
            s->setStudentAdvisor(); //updates student

        }
    }
    catch(exception &err){ //user did something wrong
        cout << "Enter ID as int Number!" << endl;
        cout << "Advisee is NOT removed!" << endl;
        cout << endl;
    }
} 



//display student given their id number
int Simulation::displayStudent(BST<Student> masterStudent){
    string currId;
    int currentId;
    cout << "Enter Student ID Number: " << endl;          
    cin >> currId;
    cout << endl;
    try{
        currentId = stoi(currId);
        if(masterStudent.search(currentId)!=NULL){ //student must exists
            masterStudent.search(currentId)->printInfo();
            cout << endl;
        }
        else{
            cout << "Student Not Found" << endl; //student not found, then nothing printed for student
            cout << endl;
            return -1;
        }
    }
    catch(exception &err){ //user error
        cout << "Enter ID as Int Number only!" << endl;
        cout << endl;
        return -1;
    }
    return currentId;
}

//same as displayStudent but for faculty member
int Simulation::displayFaculty(BST<Faculty> masterFaculty){
    string currId;
    int currentId;
    cout << "Enter Faculty ID Number: " << endl;
    cin >> currId;
    cout << endl;
    try{
        currentId = stoi(currId);
        if(masterFaculty.search(currentId)!=NULL){
            masterFaculty.search(currentId)->printInfo();
            cout << endl;
        }
        else{
            cout << "Faculty Not Found" << endl;
            cout << endl;
            return -1;
            }
    }
    catch(exception &err){
        cout << "Enter ID as Int Number only!" << endl;
        cout << endl;
        return -1;
    }
    return currentId;
}

//displaying faculty info from student id number
int Simulation::studentTOfaculty(BST<Student> masterStudent, BST<Faculty> masterFaculty){
    string currId;
    int currentId, otherId;
    cout << endl;
    cout << "Enter a Student's ID. Their Faculty Advisor will be printed." << endl;
    cin >> currId;
    try{
        currentId = stoi(currId);
        if(masterStudent.search(currentId)!=NULL){ //student must exist
            otherId = masterStudent.search(currentId)->getStudentAdvisor(); //tells us what to search for
            if(masterFaculty.search(otherId)!=NULL){ //faculty must exist
                masterFaculty.search(otherId)->printInfo();
                return 1;
            }
            else{ //user error
                cout << "Faculty ID not Found!" << endl;
                return -1;
            }
        }
        else{ //user error
            cout << "Student ID not found!" << endl;
            cout << endl;
            return -1;
        }
    }
    catch(exception &err){ //user error
        cout << "Enter ID as int number only!" << endl;
        cout << endl;
        return -1;
    }
    return 1;
}

//displays student info from faculty id
int Simulation::facultyTOstudent(BST<Student> masterStudent, BST<Faculty> masterFaculty){
    string currId;
    int currentId, otherId;
    cout << endl;
    cout << "Enter a Faculty ID. All of Their Advisees will be printed." << endl;
    cin >> currId;
    try{
        currentId = stoi(currId);
        if(masterFaculty.search(currentId)!=NULL){ //facutly must exist
            vector<int> currMems = masterFaculty.search(currentId)->getFacultyMembers();
            sort(currMems.begin(),currMems.end());
            for(auto i: currMems){ //searching for student in faculty vector
                cout << endl;
                masterStudent.search(i)->printInfo();
                cout << endl;
            }
            return 1;
        }
        else{ //user error
            cout << "Faculty ID not found!" << endl;
            cout << endl;
            return -1;
        }
    }
    catch(exception &err){ //user error
        cout << "Enter ID as int number only!" << endl;
        cout << endl;
        return -1;
    }
    return 1;
}

//part 2 of adding a student for asking what their faculty id should be. Part2 takes place if faculty members exist
int Simulation::addStudentPart2(Student a, BST<Faculty> masterFaculty){
    cout << "Enter Faculty Idea ID Number from this list: " << endl;
    masterFaculty.inorder(masterFaculty.getRoot());
    string currFacId;
    cout << "Enter ID now: ";
    cin >> currFacId;
    try{
        while(masterFaculty.search(stoi(currFacId))==NULL){ //faculty must exist to continue
            cout << "Faculty ID does not exist. Please try again." << endl;
            cout << "Enter ID now: ";
            cin >> currFacId;
        }
        a.setStudentAdvisor(stoi(currFacId));
        Faculty *f = masterFaculty.search(stoi(currFacId));
        f->addFacultyMember(a.getId()); //adds student id to facaulty members vector
        return stoi(currFacId); //returns facultyId to add to student in main
    }
    catch(exception &err){
        cout << "Enter ID as int Number!" << endl;
        cout << "Student NOT added. Click 7 to restart process." << endl;
        cout << endl;
        Student b = Student();
        return -5; //something went wrong on users end
    }
}

//returns what student to delete 
Student Simulation::deleteStudent(BST<Student> masterStudent, BST<Faculty> masterFaculty){
    string currentId;
    int r = 0;
    cout << "Enter Student ID of Student to delete: " << endl;
    cin >> currentId;
    cout << endl;
    try{
        while(r!=3 && masterStudent.search(stoi(currentId))==NULL){ //student must exust
            cout << "Invalid Student ID." << endl;
            cout << "Click 1 to list Students, 2 to retry, and 3 to delete nobody: "; //offers help
            cin >> r;
            cout << endl;
            if(r==1){
                masterStudent.inorder(masterStudent.getRoot()); //printing all students to terminal for help
            }
            else if(r==2){
                cout << "Enter Student ID of Student to delete: " << endl;
                cin >> currentId;
            }
            else if(r==3){
                Student a = Student();
                a.setStudentAdvisor(); //tells main that we want to disregard what had happened
               return a;
            }
        }
        if(r==3){
            Student a = Student();
            a.setStudentAdvisor();
            return a;
        }
        else{
            if(masterStudent.search(stoi(currentId))->getStudentAdvisor()==-102){ //tells us that deleting student does not have a faculty member anyways, so we do not update the faculty
                cout << "Student does not have an Advisor, so Existing Advisors stay the same." << endl;
                Student a = masterStudent.getThis(stoi(currentId));
                return a;
            }
            else{
                masterFaculty.inorder(masterFaculty.getRoot());
                Student a = masterStudent.getThis(stoi(currentId));
                int currFacId = a.getStudentAdvisor();
                int currStudId = a.getId();
                masterStudent.deleteNode(a);
                Faculty *f = masterFaculty.search(currFacId); //updating faculty by removing student id from their vector
                f->removeFacultyMember(currStudId);
                return a;
            }
        }
    }
    catch(exception &err){ //user error
        cout << "Enter ID as int Number only!" << endl;
        cout << "Student NOT Deleted" << endl;
        cout << endl;
        Student a = Student();
        a.setStudentAdvisor();
        return a;
    }
}

//returns what faculty member to delete
Faculty Simulation::deleteFaculty(BST<Student> masterStudent, BST<Faculty> masterFaculty){
    string facId;
    int fac, r;
    cout << "Enter Faculty ID to Delete: ";
    cin >> facId;
    try{
        fac = stoi(facId);
        while(r!=3 && masterFaculty.search(fac)==NULL){ //facutly must ecist
            cout << "Faculty Member does not exist!" << endl;
            cout << "Enter 1 to see a list of Faculty Members, 2 to retry, and 3 to not delete anyone: ";
            cin >> r;
            if(r==1){
                masterFaculty.inorder(masterFaculty.getRoot());
            }
            else if(r==2){
                cout << "Enter Faculty ID to Delete: ";
                cin >> facId;
                fac = stoi(facId);
            }
            else{
                Faculty f1 = Faculty();
                f1.setFacultyId(-1);
               return f1;
            }
        }
        if(r==3){ //we do not want to have anything changed
            Faculty f1 = Faculty();
            f1.setFacultyId(-1);
            return f1;
        }
        Faculty f = masterFaculty.getThis(fac);
        int facId = f.getId();
        vector<int> facMems = f.getFacultyMembers();
        for(auto i: facMems){
            Student *a = masterStudent.search(i);
            a->setStudentAdvisor(); //updating all students in the facultys advisee list that they now have no advisor
        }
        return f;
    }
    catch(exception &err){//user error
        cout << "Enter Faculty ID as int Number!" << endl;
        cout << "Faculty member NOT deleted." << endl;
        cout << endl;
        Faculty f1 = Faculty();
        f1.setFacultyId(-1);
        return f1;
    }
}

//changing advisor from one faculty(or null) to another
Faculty Simulation::changeAdvisor(BST<Student> masterStudent, BST<Faculty> masterFaculty){
    string curr;
    int r = 0;
    cout << "Enter Student ID: " << endl;
    cin >> curr;
    try{
        while(r!=3 && masterStudent.search(stoi(curr))==NULL){ //searching for student id
            cout << "Invalid Student ID!" << endl;
            cout << "Enter 1 for list of Students, 2 to retry, and 3 to go back to home: ";
            cin >> r;
            if(r==1){
                masterStudent.inorder(masterStudent.getRoot()); //showing all students if requested
            }
            else if(r==2){
                cout << "Enter Student ID: " << endl;
                cin >> curr;
            }
            else if(r==3){
                Faculty f1 = Faculty();
                f1.setFacultyId(-1);
                return f1; //do not have anythign swithc
            }
        }
        if(r==3){
            Faculty f1 = Faculty();
            f1.setFacultyId(-1);
            return f1;
        }
        Student *s = masterStudent.search(stoi(curr));
        int oldFac = s->getStudentAdvisor();
        cout << "Enter Faculty ID for this student: ";
        cin >> curr;
        while(r!=3 && masterFaculty.search(stoi(curr))==NULL){ //faculty id for student does not exist. choices are given
            cout << "Faculty ID does not exist!" << endl;
            cout << "Enter 1 for list of Faculty, 2 to retry, and 3 to go back to home: ";
            cin >> r;
            if(r==1){
                 masterFaculty.inorder(masterFaculty.getRoot());
            }
            else if(r==2){
                cout << "Enter Faculty ID for this student: ";
                cin >> curr;
            }
            else if(r==3){
                Faculty f1 = Faculty();
                f1.setFacultyId(-1);
                return f1;
            }
        }
        if(r==3){
            Faculty f1 = Faculty();
            f1.setFacultyId(-1);
            return f1;
        }
        Faculty *f = masterFaculty.search(stoi(curr));
        if(oldFac!=-102){ //student had an old advisor, so old advisor must delete this student from their list
            Faculty *f1 = masterFaculty.search(oldFac);
            f1->removeFacultyMember(s->getId());
        }
        f->addFacultyMember(s->getId()); //adding student id to faculty member that was choosen
        s->setStudentAdvisor(stoi(curr)); //switching the student advisor id
        return *f;
    }
    catch(exception &err){ //user error
        cout << "Enter ID as int Number!" << endl;
        cout << "Student Advisor not Changed!" << endl;
        cout << endl;
        Faculty f1 = Faculty();
        f1.setFacultyId(-1);
        return f1;
    }
}