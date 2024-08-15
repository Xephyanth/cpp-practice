#include "FieldGenerator.h"

#include <stdexcept>
#include <random>

FieldGenerator::FieldGenerator(int difficulty) : difficulty_(difficulty) {
    if (difficulty < 1 || difficulty > 3) {
        throw std::invalid_argument("Difficulty error"); // Не забудь придумать
    }
}

Board FieldGenerator::generateField(int size) const {
    if (size < 3 || size > 9) {
        throw std::invalid_argument("Field size error"); // Не забудь придумать
    }

    Board board(size);      // Результирующее поле

    fillNumbers(board);     // Заполнение сетки цифрмами по правилам игры
    
    createGroups(board);    // Создание объединенных групп

    return board;           // Возвращаем заполненную доску
}

int FieldGenerator::getDifficulty() const {
    return difficulty_;
}

void FieldGenerator::fillNumbers(Board& board) const {
    // Получаем размер поля
    const int brd_size = board.getSize();

    std::vector<std::vector<Cell>> grid(brd_size, std::vector<Cell>(brd_size));

    // Заполняем первый ряд
    std::vector<Cell>& first_row = grid[0];
    for (int i = 0; i < brd_size; ++i) {
        first_row[i].board_value = i + 1;
    }

    // Заполняем остальные ряды со смещением
    for (int row = 1; row < brd_size; ++row) {
        for (int col = 0; col < brd_size; ++col) {
            grid[row][col].board_value = (grid[0][col].board_value + row) % brd_size;

            if (grid[row][col].board_value == 0) {
                grid[row][col].board_value = brd_size;
            }
        }
    }

    // Инициализируем генератор случайных чисел
    std::random_device rd;
    std::mt19937 g_mt(rd());

    // Перемешиваем строки
    std::shuffle(grid.begin(), grid.end(), g_mt);
    // Перемешиваем столбцы
    // Поворачиваем сетку на 90 градусов по часовой стрелке
    std::vector<std::vector<Cell>> rotated_grid(brd_size, std::vector<Cell>(brd_size));
    for (int i = 0; i < brd_size; ++i) {
        for (int j = 0; j < brd_size; ++j) {
            rotated_grid[i][j] = grid[brd_size - 1 - j][i];
        }
    }

    // Перемешиваем строки повернутой сетки (бывшие столбцы)
    std::shuffle(rotated_grid.begin(), rotated_grid.end(), g_mt);

    // Обмениваем содержимое board с grid
    board.swap(rotated_grid);
}

void FieldGenerator::createGroups(Board& board) const {

}