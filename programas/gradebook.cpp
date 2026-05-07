#include <iostream>
#include <string>
#include "gradebook.hpp"

using namespace std;

int main(void){
    cout << "\nGradeBook\n\n";
    string nameOfCourse;

    GradeBook myGradebook;

    cout << "* Initial coursename is " << myGradebook.getCourseName() << endl;

    cout << "* Please enter the courseName: ";
    getline(cin, nameOfCourse);

    myGradebook.setCourseName(nameOfCourse);

    myGradebook.displayMessage();
    cout << endl;

    return 0;

}

/*int main(void){
    cout << "\nGradeBook\n\n";

    //gae
    GradeBook gradebook1("CS101 Introduction to C++ Programming");
    GradeBook gradebook2("CS102 Data structures in C++");

    //exibe valor de cpursename para cada gradebook
    cout << "gradebook1 created for course " << gradebook1.getCourseName() << endl;
    cout << "gradebook2 created for course " << gradebook2.getCourseName() << endl;
    cout << endl;
    cout << endl;

    return 0;

}*/