#include "fileio.h"
#include "GenStack.h"

/*
Main calls numerous amounts of classes and objects to simulate a basic Student adn Faculty Database.
*/
int main(int charc, char** argv){
    int rollback_count = 0;
    BST<Student> masterStudent; //main Student BST
    BST<Faculty> masterFaculty; //main Faculty BST
    GenStack<Rollback> rollback = GenStack<Rollback>(); //rollback options are on a stack
    FileIo looking = FileIo();
    if(looking.startWith()){ //studentTable and facultyTable exist
        masterFaculty = looking.processFacultyData(); 
        masterStudent = looking.processStudentData();
    }


    int num = -1;
    string currNum;
    while(num!=14){ //options for the user
        Simulation sim = Simulation();
        sim.Choices(); //displaying options
        cin >> currNum;
        try{
            num = stoi(currNum); 
        }
        catch(exception &err){ //incase user does not enter actual number/int
            cout << "Enter a number" << endl;
            cout << endl;
            continue;
        }
        if(num==1){
            masterStudent.inorder(masterStudent.getRoot()); //displays all student info in BST
        }
        else if(num==2){
            masterFaculty.inorder(masterFaculty.getRoot()); //displays all faculty info in BST
        }
        else if(num==3){
            int a = sim.displayStudent(masterStudent); //displays specific student in BST
        }
        else if(num==4){
            int a = sim.displayFaculty(masterFaculty); //displays specific faculty member in BST
        }
        else if(num==5){
            int a = sim.studentTOfaculty(masterStudent,masterFaculty); //displays specific Faculty member from student id num in BST
        }
        else if(num==6){
            int a = sim.facultyTOstudent(masterStudent,masterFaculty); //dislpays specifc student(s) from faculty id in BST
        }
        else if(num==7){
            Student a = sim.addStudent(masterStudent); //adding a student to our BST
            if(a.getId()<0){ //we do not add student here. User did something wrong
                continue;
            }
            else{
                if(masterFaculty.isEmpty()){ 
                    a.setStudentAdvisor(); //there are no faculty members, so student is left with no faculty advisor
                    cout << "Warning! No Advisors in Table, so student is left with NO ADVISOR" << endl;
                }
                else{
                    int y = sim.addStudentPart2(a, masterFaculty);
                    if(y<0){
                        continue; //User did somethign wrong, so student will not be added
                    }
                    a.setStudentAdvisor(y);
                    Rollback r = Rollback();
                    r.storeDB_type("student insert"); //rollback feature
                    r.studentDB(a); //rollback holding data before it changes
                    rollback.push(r); //rollback stack collecting data
                    masterStudent.insert(a); //student is added to masterStudent BST
                    rollback_count++; //we have something in stack, we are going to count each action
                }
            }
        }

        else if(num==8){ //deleting a student from masterStudent
            Student b = sim.deleteStudent(masterStudent,masterFaculty); //uses Simulation for bulk of deletions
            if(b.getId()>0){ //user entered everything correct
                Rollback r = Rollback(); //rollback info
                r.storeDB_type("student delete");
                masterStudent.deleteNode(b); //student successfully deletec
                r.studentDB(b);
                rollback.push(r);
                rollback_count++;
            }
        }
        else if(num==9){ //adding faculty member
            Faculty f = sim.addFaculty(masterFaculty);
            if(f.getId()==-100){ //user did something wrong
                continue;
            }
            else{
                Rollback r = Rollback();
                r.facultyDB(f);
                r.storeDB_type("faculty insert");
                rollback.push(r);
                masterFaculty.insert(f); //faculty member added
                rollback_count++;
            }
        }
        else if(num==10){ //deleting faculty member
            Faculty f = sim.deleteFaculty(masterStudent,masterFaculty); //class Simulation does bulk of deletion
            if(f.getId()>0){ //checking if user did somethign wrong in Simulation Class
                Rollback r = Rollback();
                r.facultyDB(f);
                r.storeDB_type("faculty delete");
                rollback.push(r);
                rollback_count++;
                masterFaculty.deleteNode(f); //faculty member successfully deleted
            }
        }
        else if(num==11){ //changing advisor
            Rollback r = Rollback();
            Faculty f = sim.changeAdvisor(masterStudent,masterFaculty);
            if(f.getId()>0){ //Faculty member must exist
                if(rollback_count>0){ //checking if something is on our stack 
                    if(rollback.peek().getType()=="faculty insert"){ //if our last action was faculty insert than continue
                        if(rollback.peek().getFaculty().getId()==f.getId()){ //allows for more realistic rollback feature
                            rollback.pop();
                            r.storeDB_type("faculty insert");
                            r.facultyDB(masterFaculty.getThis(f.getId()));
                            rollback.push(r);
                        }
                    }
                }
            }
        }

        else if(num==12){
            sim.removeAdvisee(masterStudent,masterFaculty);
        }
        else if(num==13){
            int c = 0;
            if(rollback_count>0){
                if(rollback.peek().getType()=="student insert"){ //we delete the student, and update faculty members
                    Student a = rollback.pop().getStudent();
                    int studId = a.getId();
                    int advisId = a.getStudentAdvisor();
                    if(advisId!=-102){
                        Faculty *f = masterFaculty.search(advisId);
                        f->removeFacultyMember(studId);
                    }
                    masterStudent.deleteNode(a);
                }
                else if(rollback.peek().getType()=="student delete"){ //we add the student back, and update faculty
                    Student a = rollback.pop().getStudent();
                    int studId = a.getId();
                    int advisId = a.getStudentAdvisor();
                    if(advisId!=-102){
                        Faculty *f = masterFaculty.search(advisId);
                        f->addFacultyMember(studId);
                    }
                    masterStudent.insert(a);
                }
                else if(rollback.peek().getType()=="faculty insert"){ //we delete the faculty member, and update students
                    Faculty f = rollback.pop().getFaculty();
                    int facId = f.getId();
                    vector<int> studIds = f.getFacultyMembers();
                    for(auto i: studIds){
                        Student *s = masterStudent.search(i);
                        s->setStudentAdvisor();
                    }
                    masterFaculty.deleteNode(f);
                }
                else{ //we insert faculy member and update students who had them
                    Faculty f = rollback.pop().getFaculty();
                    int facId = f.getId();
                    vector<int> studIds = f.getFacultyMembers();
                    for(auto i: studIds){
                        Student *s = masterStudent.search(i);
                        s->setStudentAdvisor(facId);
                    }
                    masterFaculty.insert(f);
                }
                rollback_count--;
            }
            else{
                cout << "Nothing to roll back!" << endl;
            }
        }
    }

    looking.end(masterStudent,masterFaculty); //sends our BST back to FileIO and that then rewrites files
    return 0;

}
