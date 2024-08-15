#include "GameOfLife.h"

#include <string>

int main(int argc, char* argv[]) {

    // Базовые значения
    int cell_size = 10;
    int game_speed = 100;


    // Если указаны аргументы при запуске, то меняем настройки игры
    if (argc > 1) {
        // Перебор переданных аргументов командной строки
        for (int i = 1; i < argc; ++i) {
            std::string gameParam = argv[i];
            // Считываем значение параметра "размер"
            if (gameParam == "--size" && i + 1 < argc) {
                int input_size = std::atoi(argv[++i]);

                if (input_size > 10 && input_size < 30) {
                    cell_size = input_size;
                }
            }
            // Считываем значение параметра "скорость"
            else if (gameParam == "--speed" && i + 1 < argc) {
                int input_speed = std::atoi(argv[++i]);

                if (input_speed > 50 && input_speed < 500) {
                    game_speed = input_speed;
                }
            }
            else {
                return 1;
            }
        }
    }

    GameOfLife game(cell_size, game_speed);	// СОздаем объект игры

    game.Launch();                          // Запускам игру

    return EXIT_SUCCESS;
}