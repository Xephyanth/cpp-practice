#include "GameOfLife.h"

#include <boost/program_options.hpp>
#include <string>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // Параметры игры
    int cell_size;
    int game_speed;

    //
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Use --size N or --speed N to adjust the game settings, where N is a number")
        ("size,sz", po::value<int>(&cell_size)->default_value(10), "Set cell SIZE")
        ("speed,sp", po::value<int>(&game_speed)->default_value(100), "Set game SPEED");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    //
    if (vm.count("help")) {
        std::cout << desc << '\n';

        return EXIT_SUCCESS;
    }
    //
    if (vm.count("speed")) {
        game_speed = vm["speed"].as<int>();
    }
    // 
    if (vm.count("size")) {
        cell_size = vm["size"].as<int>();
    }


    //// Если указаны аргументы при запуске, то меняем настройки игры
    //if (argc > 1) {
    //    // Перебор переданных аргументов командной строки
    //    for (int i = 1; i < argc; ++i) {
    //        std::string gameParam = argv[i];
    //        // Считываем значение параметра "размер"
    //        if (gameParam == "--size" && i + 1 < argc) {
    //            int input_size = std::atoi(argv[++i]);

    //            if (input_size > 10 && input_size < 30) {
    //                cell_size = input_size;
    //            }
    //        }
    //        // Считываем значение параметра "скорость"
    //        else if (gameParam == "--speed" && i + 1 < argc) {
    //            int input_speed = std::atoi(argv[++i]);

    //            if (input_speed > 50 && input_speed < 500) {
    //                game_speed = input_speed;
    //            }
    //        }
    //        else {
    //            return 1;
    //        }
    //    }
    //}

    GameOfLife game(cell_size, game_speed);	// СОздаем объект игры

    game.Launch();                          // Запускам игру

    return EXIT_SUCCESS;
}