#pragma once

#include "Board.h"

class FieldGenerator {
public:
    /*
    * Конструкторы
    */
    
    FieldGenerator(int difficulty);

    /*
    * Методы
    */

    Board generateField(int size) const;

    int getDifficulty() const;

private:
    int difficulty_ = 0;    // Сложность пазла

    /*
    * Методы
    */

    void fillNumbers(Board& board) const;   // Заполняет поле цифрами по правилам игры
    
    void createGroups(Board& board) const;  // Разбивает поле на отдельные блоки

};