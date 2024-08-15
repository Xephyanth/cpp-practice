#include "GameOfLife.h"

#include <string>

int main(int argc, char* argv[]) {

    // ������� ��������
    int cell_size = 10;
    int game_speed = 100;


    // ���� ������� ��������� ��� �������, �� ������ ��������� ����
    if (argc > 1) {
        // ������� ���������� ���������� ��������� ������
        for (int i = 1; i < argc; ++i) {
            std::string gameParam = argv[i];
            // ��������� �������� ��������� "������"
            if (gameParam == "--size" && i + 1 < argc) {
                int input_size = std::atoi(argv[++i]);

                if (input_size > 10 && input_size < 30) {
                    cell_size = input_size;
                }
            }
            // ��������� �������� ��������� "��������"
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

    GameOfLife game(cell_size, game_speed);	// ������� ������ ����

    game.Launch();                          // �������� ����

    return EXIT_SUCCESS;
}