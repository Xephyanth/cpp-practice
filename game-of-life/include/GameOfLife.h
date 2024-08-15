#pragma once

#include <SDL.h>
#include <vector>

using Board = std::vector<std::vector<bool>>;

// ����� ���������� ����
class GameOfLife {
public:
    GameOfLife(int size, int speed);    // ����������� � �����������

    ~GameOfLife();                      // ���������� ��� ������������ ��������

    void Launch();                      // ������ ����

private:
    SDL_Window* window;         // ��������� �� ����
    SDL_Renderer* renderer;     // ��������� �� �����������

    Board glider;               // ������� ����

    bool isRunning;             // ������� ����, ��� ���� ��������
    bool isPaused;              // ������� ����, ��� ���� �� �����

    void BasicInitialization(); // ������������� ����, �������� ���� � �����������
    void EventHandling();       // ������ ��� ��������� �������, ��������, ���������������� ����
    void NextCycleOfLife();     // ���������� ��������� ����
    void DisplayStatus();       // ����������� �������� ���������
    void Shutdown();            // ������� ��������

    int cell_size_;             // ������ ������
    int game_speed_;            // �������� ����
};