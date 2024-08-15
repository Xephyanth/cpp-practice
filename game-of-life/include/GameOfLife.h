#pragma once

#include <SDL.h>
#include <vector>

using Board = std::vector<std::vector<bool>>;

// Класс реализация игры
class GameOfLife {
public:
    GameOfLife(int size, int speed);    // Конструктор с параметрами

    ~GameOfLife();                      // Деструктор для освобождения ресурсов

    void Launch();                      // ЗАпуск игры

private:
    SDL_Window* window;         // Указатель на окно
    SDL_Renderer* renderer;     // Указатель на отображение

    Board glider;               // Игровое поле

    bool isRunning;             // Признак того, что игра запущена
    bool isPaused;              // Признак того, что игра на паузе

    void BasicInitialization(); // Инициализация игры, создание окна и отображение
    void EventHandling();       // Служит для обработки событий, например, пользовательский ввод
    void NextCycleOfLife();     // Обновление состояния игры
    void DisplayStatus();       // Отображение текущего состояния
    void Shutdown();            // Очистка ресурсов

    int cell_size_;             // Размер клеток
    int game_speed_;            // Скорость игры
};