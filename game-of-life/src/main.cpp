#include "GameOfLife.h"

#include <boost/program_options.hpp>
#include <string>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // ��������� ���� �� ���������
    int cell_size;
    int game_speed;

    // ������ ��������, ������ ������� ������ ��������� ������
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Use --size N or --speed N to adjust the game settings, where N is a number")
    // ������������� �������� �� ���������, ���� �������� �� ��� ������� � ��������, ������� ����� ��������������, ���� �������� ������� ��� ���������
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

    // ������� ����� ������� ������
    if (vm.count("help")) {
        std::cout << desc << '\n';

        return EXIT_SUCCESS;
    }
    // ��������� �������� ��������� "��������"
    if (vm.count("speed")) {
        std::cout << vm.count("speed");
        game_speed = vm["speed"].as<int>();
    }
    // ��������� �������� ��������� "������" 
    if (vm.count("size")) {
        cell_size = vm["size"].as<int>();
    }

    GameOfLife game(cell_size, game_speed);	// ������� ������ ����

    game.Launch();                          // �������� ����

    return EXIT_SUCCESS;
}