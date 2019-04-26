// David Sena Oliveira
// versão: 3.0
// data: 26/06/2019


#include <iostream>
#include <list>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "visual.h"

using namespace std;

//########################################################
//############# VOCE DEVE IMPLEMENTAR processKey #########
//########################################################

//State define uma lista de caracteres e um cursor que define onde o próximo caractere será inserido
//Se nosso text é "amor", e o cursor aponta para 'a', ao inserir o char 'p', o resultado será
//"apmor" com cursor ainda apontando para o 'm'.
//para inserir depois do 'r', o cursor deve apontar para text.end()
struct State{
    list<char> text;
    list<char>::iterator cursor;
    //cria um estado vazio com o cursor apontando pra text.end()
    State();
    //construtor de cópia, faz o cursor da cópia apontar para o canto correto no novo ambiente criado
    State(const State& other);
    //retorna uma string com o texto
    string textLayer();
    //retorna uma string colocando um | no lugar do cursor, mantendo os '\n' e removendo os outros caracteres
    string cursorLayer();
};

//########################################################
//############# VOCE DEVE IMPLEMENTAR processKey #########
//########################################################

//funcao deve processar o evento alterando o estado atual e o buffer de estados.
void processKey(list<State>& states, list<State>::iterator& itc, sf::Event& event){
    //Se o char nao for printável, retorna '\0'
    auto tecla = sf2char(event);

    if(event.key.control && (event.key.code == sf::Keyboard::Z)){ //control z
        //TODO
    }
    else if(event.key.control && (event.key.code == sf::Keyboard::R)){ //control r
        //TODO
    }
    else if(tecla != '\0'){ //alguma tecla printável
        //TODO
        itc->text.insert(itc->cursor, tecla);
    }
    else if(event.key.code == sf::Keyboard::BackSpace){
        //TODO
    }
    else if(event.key.code == sf::Keyboard::Delete){
        //TODO
    }
    else if(event.key.code == sf::Keyboard::Left){
        //TODO
        itc->cursor--;
    }
    else if(event.key.code == sf::Keyboard::Right){
        //TODO
        itc->cursor++;
    }
    else if(event.key.code == sf::Keyboard::Up){
        //TODO
    }
    else if(event.key.code == sf::Keyboard::Down){
        //TODO
    }
}

//########################################################
//############# FUNCAO MAIN ##############################
//########################################################

int main()
{
    list<State> states(1); //inicia a lista com 1 State
    list<State>::iterator itc = states.begin(); //it currrent aponta para o estado atual

    string texto_inicial = "Digite ou clique\nesquerda ou direita.";
    for(char c : texto_inicial)
        itc->text.push_back(c);
/*
    itc->text.push_back('a');
    itc->text.push_back('m');
    itc->text.push_back('o');
    itc->text.push_back('r');
*/
    sf::RenderWindow janela(sf::VideoMode(800, 600), "Janela");

    while(janela.isOpen()){

        sf::Event event;
        while(janela.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                janela.close();
            if(event.type == sf::Event::KeyPressed){
                processKey(states, itc, event);
            }
        }

        draw(janela, itc->textLayer(), itc->cursorLayer());
    }
    return 0;
}

//########################################################
//############# IMPLEMENTACAO DA CLASSE STATE ############
//########################################################


State::State(){
    cursor = text.end();
}

State::State(const State &other):
    text(other.text)
{
    this->cursor = this->text.begin();
    for(auto it = other.text.begin(); it != other.cursor; it++)
        this->cursor++;
}

string State::textLayer(){
    stringstream ss;
    for(auto& elem : text)
        ss << elem;
    return ss.str();
}

string State::cursorLayer(){
    stringstream ss;
    for(auto it = text.begin(); it != text.end(); it++){
        if(it == cursor){
            ss << "|";
            break;
        }
        else if(*it == '\n')
            ss << "\n";
        else
            ss << " ";
    }
    if(cursor == text.end())
        ss << "|";
    return ss.str();
}


