#ifndef VISUAL_H
#define VISUAL_H

#include <iostream>
#include <list>
#include <sstream>
#include "xfont.h"
#include <SFML/Graphics.hpp>

using namespace std;

//path da font, altere se precisar
//const string font_path = "../projeto/ed_font.ttf";

#define NEW_SFML 0

//uma funcao feia, mas simples.
//pega alguns caracteres, inclusive separando maiúsculos.
//se a tecla nao corresponder a um char printável, retorna '\0'
char sf2char(sf::Event event){
    if(event.type != sf::Event::KeyPressed)
        return '\0';

    auto key = event.key.code;
    auto shift = event.key.shift;
    if((key >= sf::Keyboard::A)  and (key <= sf::Keyboard::Z))
        return (key - sf::Keyboard::A) + (shift? 'A' : 'a');
    else if((key >= sf::Keyboard::Num0) and (key <= sf::Keyboard::Num9))
        return key - sf::Keyboard::Num0 + '0';
    else if((key >= sf::Keyboard::Numpad0) and (key <=sf::Keyboard::Num9))
        return key - sf::Keyboard::Numpad0 + '0';
    else if(key == sf::Keyboard::LBracket)
        return shift ? '{': '[';
    else if(key == sf::Keyboard::RBracket)     ///< The ] key
        return shift ? '}': ']';
    else if(key == sf::Keyboard::Comma)        ///< The , key
        return shift ? '<': ',';
    else if(key == sf::Keyboard::Period)       ///< The . key
        return shift ? '>': '.';
    else if(key == sf::Keyboard::Quote)        ///< The ' key
        return shift ? '"': '\'';
    else if(key == sf::Keyboard::Slash)
        return '/';
    else if(key == sf::Keyboard::Equal)
        return shift ? '=': '=';
    else if(key == sf::Keyboard::Space)
        return ' ';
#if NEW_SFML
    else if(key == sf::Keyboard::Semicolon)    ///< The ; key
        return shift ? ':': ';';
    else if(key == sf::Keyboard::Hyphen)
        return shift ? '_': '-';
    else if(key == sf::Keyboard::Enter)
        return '\n';
#else
    else if(key == sf::Keyboard::SemiColon)    ///< The ; key
        return shift ? ':': ';';
    else if(key == sf::Keyboard::Comma)
        return shift ? '_': '-';
    else if(key == sf::Keyboard::Return)
        return '\n';
#endif
    return '\0';
}

//########################################################
//############# FUNCOES DE DESENHO #######################
//########################################################

class sfText : public sf::Text{
    static sf::Font * get_default_font();
public:
    sfText(sf::Vector2f pos, std::string texto, sf::Color color = sf::Color::White, int size = 16);
};

sfText::sfText(sf::Vector2f pos, string texto, sf::Color color, int size){
    this->setFont(*this->get_default_font());
#if NEW_SFML
    this->setFillColor(color);
    this->setOutlineColor(color);
#else
    this->setColor(color);
#endif
    this->setPosition(pos);
    this->setString(texto);
    this->setCharacterSize(size);
}

sf::Font *sfText::get_default_font(){
    static sf::Font font;
    static bool init = true;
    if(init){
        init = false;
        font.loadFromMemory(font_buffer_profont, sizeof(font_buffer_profont));
//        if(!font.loadFromFile(font_path))
//            std::cerr << "Font " << font_path << " nao encontrada." << std::endl;
    }
    return &font;
}

void draw(sf::RenderWindow& janela, string textLayer, string cursorLayer){
    static sf::Clock clock;
    static auto cursorTime = 300; //milisegundos
    static bool cursorOn = true;

    //para fazer o cursor piscar
    if(clock.getElapsedTime() > sf::milliseconds(cursorTime)){
        clock.restart();
        cursorOn = !cursorOn;
    }

    auto pos = sf::Vector2f(30, 50);
    int size = 50;
    janela.clear();
    janela.draw(sfText(pos, textLayer, sf::Color::White, size));

    if(cursorOn){
        pos.x -= size / 4.f;
        janela.draw(sfText(pos, cursorLayer, sf::Color::White, size));
    }
    janela.display();
}

#endif // VISUAL_H
