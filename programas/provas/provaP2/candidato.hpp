//Candidato.hpp
#pragma once
#include <string>
//Classe Candidato
class Candidato{
    public:
        //Construtor
        Candidato(std::string nome,std::string partido,int numero, int votos = 0);

        //Getters
        std::string getNome() const;
        std::string getPartido() const;
        int getNumero() const;
        int getVotos() const;
        
        //atribui um voto ao candidato
        void atribuirVoto(){
            votos++;
        }

        private:
        //Membros
        std::string nome;
        std::string partido;
        int numero;
        int votos;
};