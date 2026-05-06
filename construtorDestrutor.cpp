#include <iostream>
#include <string>
using namespace std;

class GradeBook{
    public:
    //construtor
    //inicializa a courseName com a string fornecida
    //explicit
    explicit GradeBook(string name) : courseName(name) {}

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

    //gae
    GradeBook gradebook1("CS101 Introduction to C++ Programming");
    GradeBook gradebook2("CS102 Data structures in C++");

    //exibe valor de cpursename para cada gradebook
    cout << "gradebook1 created for course " << gradebook1.getCourseName() << endl;
    cout << "gradebook2 created for course " << gradebook2.getCourseName() << endl;
    cout << endl;
    cout << endl;

    return 0;

}
