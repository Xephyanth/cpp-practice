#include "GameOfLife.h"

#include <boost/program_options.hpp>
#include <string>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // Параметры игры по умолчанию
    int cell_size;
    int game_speed;

    // Задаем описание, которе выводит список доступных команд
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Use --size N or --speed N to adjust the game settings, where N is a number")
    // Устанавливаем значение по умолчанию, если аргумент не был передан и значение, которое будет использоваться, если аргумент передан без параметра
        ("size,sz", po::value<int>(&cell_size)->default_value(10)->implicit_value(10), "Set cell SIZE")
        ("speed,sp", po::value<int>(&game_speed)->default_value(100)->implicit_value(100), "Set game SPEED");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (const po::error& e) {
        std::cerr << "Error: " << e.what() << "\n\n";

        return EXIT_FAILURE;
    }

    // Выводим текст раздела помощи
    if (vm.count("help")) {
        std::cout << desc << '\n';

        return EXIT_SUCCESS;
    }
    // Считываем значение параметра "скорость"
    if (vm.count("speed")) {
        std::cout << vm.count("speed");
        game_speed = vm["speed"].as<int>();
    }
    // Считываем значение параметра "размер" 
    if (vm.count("size")) {
        cell_size = vm["size"].as<int>();
    }

    GameOfLife game(cell_size, game_speed);	// СОздаем объект игры

    game.Launch();                          // Запускам игру

    return EXIT_SUCCESS;
}