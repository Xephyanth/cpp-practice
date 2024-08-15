#include "GameOfLife.h"

// ��������� ������� ����
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

/*
* ����������� � ����������
*/

GameOfLife::GameOfLife(int cell_size, int game_speed)
    : window(nullptr), renderer(nullptr), isRunning(false), isPaused(true), cell_size_(cell_size), game_speed_(game_speed)
{
    glider.resize(WINDOW_HEIGHT / cell_size, std::vector<bool>(WINDOW_WIDTH / cell_size, false));
}

GameOfLife::~GameOfLife() {
    Shutdown(); // ������� ������� ��� ����������� �������
}

/*
* ������ ������
*/

void GameOfLife::Launch() {
    BasicInitialization(); // ������ ���� (��������� �������������)

    while (isRunning) {
        SDL_Delay(game_speed_); // �������� ����������� (�������� ����)

        if (isPaused) {
            EventHandling();
            DisplayStatus();
        }

        EventHandling();        // ������������ �������
        NextCycleOfLife();      // ��������� ��������� ����
        DisplayStatus();        // ���������� ������� ��������
    }

    Shutdown(); // ������� �������
}

/*
* ��������� ������ ������
*/

void GameOfLife::BasicInitialization() {
    // �������������� SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

        return;
    }

    // ������� ���� �� ������ ������ � ������ ��� ������
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());

        SDL_Quit();

        return;
    }
    
    // ������� �������� ������������
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        return;
    }

    isRunning = true; // ������������� ���� ������� ����
    //SDL_Log("Initialization successful");
}

void GameOfLife::EventHandling() {
    // ������������ �������
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // ��������� ���� ��� �������� ����
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        // ������������ ������� ������ ����
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            // ������������ ���� ����
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            int cellX = mouseX / cell_size_;
            int cellY = mouseY / cell_size_;

            // ����������� ��������� ������ (�����/�������)
            if (cellX >= 0 && cellX < glider[0].size() && cellY >= 0 && cellY < glider.size()) {
                glider[cellY][cellX] = !glider[cellY][cellX];
            }
        }
        // ������������ ������� ������ ����������
        else if (event.type == SDL_KEYDOWN) {
            // ������� "Space" (������)
            if (event.key.keysym.sym == SDLK_SPACE) {
                isPaused = !isPaused; // ����������� �����

                // �������� ��������� ���� � ����������� �� ��������� �����
                SDL_SetWindowTitle(window, isPaused ? "Game of Life (paused)" : "Game of Life");
            }

            // ������� "Esc"
            isRunning = event.key.keysym.sym == SDLK_ESCAPE ? !isRunning : isRunning; // ��������� ����
        }
    }
}

void GameOfLife::NextCycleOfLife() {
    // ���� ���� �� �����, �� ��������� ��������� �������
    if (isPaused) {
        //system("cls");
        //SDL_Log("Game paused");
        return;
    }

    Board updGlider = glider;

    // ��������� ��������� ������ �� ������ ������ ����
    for (int y = 0; y < glider.size(); ++y) {
        for (int x = 0; x < glider[0].size(); ++x) {
            int aliveNeighbors = 0;
            // ������������ ���������� ����� �������
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }

                    // ��������� ����������� ������
                    int ny = y + dy;
                    int nx = x + dx;

                    if (ny >= 0 && ny < glider.size() && nx >= 0 && nx < glider[0].size()) {
                        // ���� ��� ����� ������, �� ����������� ���-�� ����� �������
                        if (glider[ny][nx]) {
                            aliveNeighbors++;
                        }
                    }
                }
            }

            // ��������� ������� ���� � ������� ������
            if (glider[y][x]) {
                // ���� � ����� ������ ���� ��� ��� ��� ����� �������, �� ��� ������ ���������� ����;
                // � ��������� ������ (���� ����� ������� ������ ���� ��� ������ ���) ������ �������
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    updGlider[y][x] = false;
                }
            }
            // � ������(������) ������, � ������� ����������� ��� ����� ������, ����������� �����
            else {
                if (aliveNeighbors == 3) {
                    updGlider[y][x] = true;
                }
            }
        }
    }

    glider = std::move(updGlider); // ��������� ������� ����
}

void GameOfLife::DisplayStatus() {

    //SDL_Log("Rendering");

    // ��������� ����� ������ ������
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // ������ ����� ������ ����� ������
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < glider.size(); ++y) {
        for (int x = 0; x < glider[0].size(); ++x) {
            if (glider[y][x]) {
                // "������" �������
                SDL_Rect cell = { x * cell_size_, y * cell_size_, cell_size_, cell_size_ };

                // ������� �������� ������
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer); // ��������� �����
}

void GameOfLife::Shutdown() {
    // ������� �������
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}