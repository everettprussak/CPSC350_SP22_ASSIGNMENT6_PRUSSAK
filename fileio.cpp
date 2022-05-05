#include "fileio.h"
#include <fstream>

FileIo::FileIo(){ //deafult (checks if facultyTable and studentTable exist in Current Directory)
    string facus = "facultyTable";
    string studs = "studentTable";
    facTable = true;
    studTable = true;
    facultyCount = 0;
    studentCount = 0;

    ifstream file1(facus);
    ifstream file2(studs);

    if(file1.fail()){
        cout << "facultyTable file does not exist" << endl;
        facTable = false;
    }
    if(file2.fail()){
        cout << "studentTable file does not exist" << endl;
        studTable = false;
    }

    if(studTable==true && facTable==true){
        string line;
        while(getline(file1,line)){ //writing data from existing facultyTable file
            facultyData = facultyData + line + "\n";
            facultyCount++;
        }
        while(getline(file2,line)){ //writing data from existing studentTable file
            studentData = studentData + line + "\n";
            studentCount++;
        }
    }
}


string FileIo::getFacultyData(){
    return facultyData;
}

string FileIo::getStudentData(){
    return studentData;
}

bool FileIo::startWith(){
    if(facTable==true and studTable==true){
        return true;
    }
    return false;
}

int FileIo::getFacultyCount(){
    return facultyCount;
}

int FileIo::getStudentCount(){
    return studentCount;
}


BST<Faculty> FileIo::processFacultyData(){  //making the BST<Faculty> with the masterFaculty BST and specific nodes
    vector<int> currMembers; //collects student Id numbers for this faculty member
    BST<Faculty> tree1;
    string facId, facName, facLevel, facDepart, facList; //variables being stored to locally
    int counter=0, counter2 = 0;
    char last;
    bool facList_set = false;

    for(char t: facultyData){ //checks every character to correctly assign the character to a specific variable
        if(t=='|'){
            counter++;
            last = t;
            continue;
        }
        else if(counter==0){ //id because | has yet to be found
            if(t==' '){
                last = t;
                continue;
            }
            last = t;
            facId = facId + t;
        }
        else if(counter==1){ //name because | is present once
            last = t;
            if(last=='|' && t==' '){
                continue;
            }
            facName = facName + t;
        }
        else if(counter==2){ //level beacause | is presnet twice thus far
            last = t;
            if(last=='|' && t==' '){
                continue; 
            }
            facLevel = facLevel + t;
        }
        else if(counter==3){ //department variable being added to
            last = t;
            if(last=='|' && t==' '){
                continue;
            }
            facDepart = facDepart + t;
        }
        else if(counter==4){
            if(last=='|' && t==' '){
                continue;
            }
            else if(t==','){ //this means that there are multiple students in database.
                int curr = stoi(facList);
                facList = "";
                currMembers.push_back(curr); //adding the student to the faculty vector
                counter2++;
                continue;
            }
            else if(t!=' ' && t!='\n'){
                facList = facList + t;
                facList_set = true;
                continue;
            }
            if(facList_set==true){ //if the faculty has 1 or more student ids, then we go here
                int curr = stoi(facList);
                facList = "";
                facList_set = false;
                currMembers.push_back(curr);
            }

            int curr1 = stoi(facId);

            Faculty f = Faculty(curr1,facName,facLevel,facDepart); //faculty member created with our variable
            for(auto i: currMembers){
                f.addFacultyMember(i); //adding each student id one at a time
            }
            tree1.insert(f); //inserting into our tree
            curr1 = 0;
            facId = "";
            facName = "";
            facLevel = "";
            facDepart = "";
            currMembers.clear();
            counter = 0;
        }
    }
    return tree1; //returns the tree of faculty members we created
}



BST<Student> FileIo::processStudentData(){ //very similar to faculty. making specific students then adding them to the tree until file is complete
    BST<Student> tree2;
    string studId, studName, studLevel, studMajor, studGPA, advisorId;
    int counter=0, counter2 = 0;
    char last;
    for(char t: studentData){
        if(t=='|'){
            counter++;
            continue;
        }
        else if(counter==0){
             if(t==' '){
                last = t;
                continue;
            }
            last = t;
            studId = studId + t;
        }
        else if(counter==1){
            if(last=='|' && t==' '){
                last = t;
                continue;
            }
            last = t;
            studName = studName + t;
        }
        else if(counter==2){
                if(last=='|' && t==' '){
                    last = t;
                    continue;
                }
                last = t;
                studLevel = studLevel + t;
        }
        else if(counter==3){
                if(last=='|' && t==' '){
                    last = t;
                    continue;
                }
                last = t;
                studMajor = studMajor + t;
        }
        else if(counter==4){
            if(last=='|' && t==' '){
                last = t;
                continue;
            }
            else if(last!='|' && t==' '){
                last = t;
                continue;
            }
            studGPA = studGPA + t;
        }
        else if(counter==5){
            if(last==' ' && t==' '){
                last = t;
                continue;
            }
            else if(t!=' ' && t!='\n'){
                advisorId = advisorId + t;
                continue;
            }
            int curr = stoi(studId);
            double curr1 = stod(studGPA);
            int curr2 = stoi(advisorId);
            Student s = Student(curr,studName,studLevel,studMajor,curr1,curr2);
            curr = 0;
            curr1 = 0.0;
            curr2 = 0;
            advisorId = "";
            studId = "";
            studMajor = "";
            studGPA = "";
            studName = "";
            studLevel = "";
            tree2.insert(s);
            counter = 0;
        }
    }
    return tree2;
}

void FileIo::end(BST<Student> masterStudent, BST<Faculty> masterFaculty){ //at the end of the program when user clicks 14. this will add our database into the facultyTable and studentTable database
    string fac = "facultyTable";
    string stud = "studentTable";

    ofstream outfile;
    ofstream outfile1;

    outfile.open("facultyTable");
    while(masterFaculty.isEmpty()!=true){
        Faculty f = *masterFaculty.getMin(); //adding faculty members from smallest id to largest
        string a = to_string(f.getId()) + "|" + f.getFacultyName() + "|" + f.getFacultyLevel() + "|" + f.getFacultyDepart() + "|";
        vector<int> ab = f.getFacultyMembers();
        int count = 1;
        for(auto i: ab){
            if(count==ab.size()){
                a = a+to_string(i);
            }
            else{
                a = a + to_string(i) + ","; //adding each studentid 
            }
            count++;
        }

        masterFaculty.deleteNode(f); //deleteing node, to continue for loop
        if(masterFaculty.isEmpty()==true){ //we do not want a new line on last faculty member
            outfile << a; //facultyTable now has the faculty members
        }
        else{
            a = a + "\n"; //new faculty member
            outfile << a;
        }
    }


    outfile1.open("studentTable");

    while(masterStudent.isEmpty()==false){ //same as faculty but with a student and studentTable
        Student s = *masterStudent.getMin();
        string a = to_string(s.getId()) + "|" + s.getStudentName() + "|" + s.getStudentLevel() + "|" + s.getStudentMajor() + "|";
        a = a + to_string(s.getStudentGPA()) + "|";

        if(s.getStudentAdvisor()>0){
            a = a+to_string(s.getStudentAdvisor());
        }
        masterStudent.deleteNode(s);
        if(masterStudent.isEmpty()){
            outfile1 << a;
        }
        else{
            a = a + "\n";
            outfile1 << a;
        }
    } 
}