#include "Board.h"

#include <iostream>

/*
* Конструкторы
*/

// Конструктор с параметром по умолчанию
// Устанавливает минимальные параметры, которые необходимы для корректной генерации головоломки
Board::Board(int size = 3) : b_size_(size), board_(size, std::vector<Cell>(size)) {}

/*
* Методы
*/

void Board::swap(std::vector<std::vector<Cell>>& other) {
    board_.swap(other);
}

/*
* Методы
*/

int Board::getSize() const { return b_size_; }

void Board::setValue(int row, int col, int value) {
    board_[row][col].user_value = value;

    //displayBoard();
}

int Board::getValue(int row, int col) const {
    return board_[row][col].user_value;
}

void Board::displayBoard() const {
    for (const auto& cols : board_) {
        for (const auto& cell : cols) {
            std::cout << cell.board_value << ' ';
        }
        std::cout << '\n';
    }
}