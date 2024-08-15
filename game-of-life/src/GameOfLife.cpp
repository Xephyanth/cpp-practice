#include "GameOfLife.h"

// Константы размера окна
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

/*
* Конструктор и деструктор
*/

GameOfLife::GameOfLife(int cell_size, int game_speed)
    : window(nullptr), renderer(nullptr), isRunning(false), isPaused(true), cell_size_(cell_size), game_speed_(game_speed)
{
    glider.resize(WINDOW_HEIGHT / cell_size, std::vector<bool>(WINDOW_WIDTH / cell_size, false));
}

GameOfLife::~GameOfLife() {
    Shutdown(); // Очищаем ресурсы при уничтожении объекта
}

/*
* Методы класса
*/

void GameOfLife::Launch() {
    BasicInitialization(); // Запуск игры (первичная инициализация)

    while (isRunning) {
        SDL_Delay(game_speed_); // Задержка отображения (скорость игры)

        if (isPaused) {
            EventHandling();
            DisplayStatus();
        }

        EventHandling();        // Обрабатываем события
        NextCycleOfLife();      // Обновляем состояние игры
        DisplayStatus();        // Отображаем текущую ситуацию
    }

    Shutdown(); // Очищаем ресурсы
}

/*
* Приватные методы класса
*/

void GameOfLife::BasicInitialization() {
    // Инициализируем SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

        return;
    }

    // Создаем окно по центру экрана и задаем его размер
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());

        SDL_Quit();

        return;
    }
    
    // Создаем контекст визуализации
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        return;
    }

    isRunning = true; // Устанавливаем флаг запуска игры
    //SDL_Log("Initialization successful");
}

void GameOfLife::EventHandling() {
    // Обрабатываем события
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Завершаем игру при закрытии окна
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // Обарбатываем нажатия кнопок мыши
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Обрабатываем клик мыши
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            int cellX = mouseX / cell_size_;
            int cellY = mouseY / cell_size_;

            // Переключаем состояние клетки (живая/мертвая)
            if (cellX >= 0 && cellX < glider[0].size() && cellY >= 0 && cellY < glider.size()) {
                glider[cellY][cellX] = !glider[cellY][cellX];
            }
        }
        // Обрабатываем нажатия кнопок клавиатуры
        else if (event.type == SDL_KEYDOWN) {
            // Клавиша "Space" (пробел)
            if (event.key.keysym.sym == SDLK_SPACE) {
                isPaused = !isPaused; // Переключаем паузу

                // Изменяем заголовок окна в зависимости от состояния паузы
                SDL_SetWindowTitle(window, isPaused ? "Game of Life (paused)" : "Game of Life");
            }

            // Клавиша "Esc"
            isRunning = event.key.keysym.sym == SDLK_ESCAPE ? !isRunning : isRunning; // Завершаем игру
        }
    }
}

void GameOfLife::NextCycleOfLife() {
    // Если игра на паузе, не обновляем состояние колонии
    if (isPaused) {
        //system("cls");
        //SDL_Log("Game paused");
        return;
    }

    Board updGlider = glider;

    // Обновляем состояние клеток на основе правил игры
    for (int y = 0; y < glider.size(); ++y) {
        for (int x = 0; x < glider[0].size(); ++x) {
            int aliveNeighbors = 0;
            // Подсчитываем количество живых соседей
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }

                    // Вычисляем кооррдинаты соседа
                    int ny = y + dy;
                    int nx = x + dx;

                    if (ny >= 0 && ny < glider.size() && nx >= 0 && nx < glider[0].size()) {
                        // Если это живая клетка, то увеличиваем кол-во живых соседей
                        if (glider[ny][nx]) {
                            aliveNeighbors++;
                        }
                    }
                }
            }

            // Применяем правила игры к текущей клетке
            if (glider[y][x]) {
                // Если у живой клетки есть две или три живые соседки, то эта клетка продолжает жить;
                // в противном случае (если живых соседей меньше двух или больше трёх) клетка умирает
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    updGlider[y][x] = false;
                }
            }
            // в пустой(мёртвой) клетке, с которой соседствуют три живые клетки, зарождается жизнь
            else {
                if (aliveNeighbors == 3) {
                    updGlider[y][x] = true;
                }
            }
        }
    }

    glider = std::move(updGlider); // Обновляем игровое поле
}

void GameOfLife::DisplayStatus() {

    //SDL_Log("Rendering");

    // Заполняем экран черным цветом
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Рисуем живые клетки белым цветом
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < glider.size(); ++y) {
        for (int x = 0; x < glider[0].size(); ++x) {
            if (glider[y][x]) {
                // "Рисуем" квадрат
                SDL_Rect cell = { x * cell_size_, y * cell_size_, cell_size_, cell_size_ };

                // Заливка квадрата цветом
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer); // Обновляем экран
}

void GameOfLife::Shutdown() {
    // Очищаем ресурсы
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}