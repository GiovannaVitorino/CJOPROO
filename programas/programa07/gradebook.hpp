#ifndef GRADEBOOK_HPP
#define GRADEBOOK_HPP
#include <string>

class GradeBook{
    public:
        explicit GradeBook(std::string name);//construtor
        void setCourseName(std::string name); //configura o nome do curso
        std::string getCourseName() const; //obtém o nome do curso
        void displayMessage() const; // exibe mensagem de boas vindas

    private:
        std::string courseName; //nome do curso
};

#endif
