#include <iostream>
#include <string>
using namespace std;

class GradeBook{
    public:
    void setCourseName(string name){
        courseName = name;
    };

    
string getCourseName() const{
    return courseName;
}

void displayMessage() const{
    cout << "Welcome to the GradeBook for " << getCourseName() << "!" << endl;
}

private:

string courseName;
};

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
