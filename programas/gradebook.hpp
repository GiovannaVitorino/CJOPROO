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
