#include "candidato.hpp"

        //Construtor
        Candidato(std::string nome,std::string partido,int numero, int votos = 0);
        nome(nome), partido(partido), numero(numero), votos(votos) {}

        //Getters
        //getter para obter o nome do candidato
        std::string getNome() const{
            return nome;
        }
        //getter para obter o partido do candidato
        std::string getPartido() const{
            return partido;
        }
        //getter para obter o numero do candidato
        int getNumero() const{
            return numero;
        }
        //getter para obter os votos do candidato
        int getVotos() const{
            return votos;
        }

        //atribui um voto ao candidato
        void Candidato::atribuirVoto(){
            votos++;
        }