#include <iostream>
#include "gradebook.hpp"

using namespace std;

int main(void){
    cout << "\nGradeBook\n\n";

    GradeBook gradebook1("CS101 Introduction to C++ Programming");
    GradeBook gradebook2("CS102 Data structures in C++");

    //exibe valor inicial de course name para cada gradebook
    cout << "gradebook1's initial course name: " << gradebook1.getCourseName() << endl;
    cout << "gradebook2's initial course name: " << gradebook2.getCourseName() << endl;

    //
    cout << "gradebook1 created for course " << gradebook1.getCourseName() << endl;
    cout << "gradebook2 created for course " << gradebook2.getCourseName() << endl;
    cout << endl;
    cout << endl;

    return 0;

}