//funcao principal
//@ProvaP2 $ g++ *.cpp -o votacao
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "candidato.hpp"

//prototipos de funcoes
void exibirMenu(const std::vector<std::unique_ptr<Candidato>>& candidatos);

//funcao principal
int main(){
    std::cout << "Prova P2\n";
    //cria vetor para armazenar candidatos
    std::vector<std::unique_ptr<Candidato>>& candidatos;

    //aramazenando candidatos
    std::candidatos.push_back(std::make_unique<Candidato>("Pokelino", "Gordinho Feliz", 171));
    std::candidatos.push_back(std::make_unique<Candidato>("Fernando Buda", "Budista Flutuante", 100));
    std::candidatos.push_back(std::make_unique<Candidato>("Alison Mineiro", "Comedores de Queijo", 201));
    std::candidatos.push_back(std::make_unique<Candidato>("Guto Manzano", "1% Programadores", 101));
    std::candidatos.push_back(std::make_unique<Candidato>("Helton Peruca", "Peruqueiro $$$", 666));

    //Criando um candidato
    Candidato c1("Pokelino", "Gordinho Feliz", 171);
    std::cout << "Nome: " << c1.getNome() << std::endl;
    std::cout << "Partido: " << c1.getPartido() << std::endl;
    std::cout << "Numero: " << c1.getNumero() << std::endl;
    std::cout << "Votos: " << c1.getVotos() << std::endl;

    std::cout << candidatos[0]->getNome() << std::endl;

    int escolha;

    while(true){
        std::cout << ">> Cabin de Votacao - IFSP\n";

        //exibir menu de candidatos
        exibirMenu(candidatos);

        //obter escolha do usuario
        std::cout << "\n=>Informe o numero do candidato: ";
        std::cin >> escolha;

        //ENCERRA A VOTACAO
        if(escolha == -1){
            std::cout << "\n* Votacao encerrada!\n\n";
            break;
        }

        //armazena os votos de cada candidato
        switch (escolha)
        {
        case 171:
            candidatos[0]->atribuirVoto();
            simularPausa();
            break;
        case 100:
            candidatos[1]->atribuirVoto();
            simularPausa();
            break;
        case 201:
            candidatos[2]->atribuirVoto();
            simularPausa();
            break;
        case 101:
            candidatos[3]->atribuirVoto();
            simularPausa();
            break;
        case 666:
            candidatos[4]->atribuirVoto();
            simularPausa();
            break;
        
        default:
            break;
        }
    }

    std::cout << "Resultado Final - Eleicoes IFSP\n\n";

    return 0;
}

//funcoe auxiliares
//simula uma pausa
void simularPausa(){
    std::cout << "\n* Seu voto foi computado, obrigado! Pressione <ENTER> para continuar...";
    std::cin.ignore();
    std::cin.get();
}

//exibe menu de candidatos
void exibirMenu(const std::vector<std::unique_ptr<Candidato>>& candidatos){
    //loop para exibir candidatos
    for(auto& candidato : candidatos){
        std::cout << "[" << candidato->getNumero() << "] " << std::setw(15) << candidato->getNome() << " (" << candidato->getPartido() << ")\n";
    }
    //opcao para encerrar votacao
    std::cout << "\n[ -1] Encerrar Votacao\n";
}

//eixibir resultado final
void exibirResultado(const std::vector<std::unique_ptr<Candidato>>& candidatos){
    //loop para exibir resultado
    for(auto& candidato : candidatos){
        std::cout << " - " << candidato->getNome() << ", do Partido " << candidato->getPartido() << ": " << candidato->getVotos() << "\n";
    }
}