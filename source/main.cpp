#include <iostream>
#include <random>
#include <vector>

#include "raylib.h"
#include "raylib-cpp.hpp"

void printGrid(const std::vector<std::vector<bool>>& grid)
{
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      if (grid[x][y] == true) {
        std::cout << " O ";
      } else {
        std::cout << " . ";
      }
      if (y == grid[0].size() - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << std::endl;
}

void updateGrid(std::vector<std::vector<bool>>& gridA)
{
  std::vector<std::vector<bool>> gridB {};

  // Copy gridA to gridB
  gridB.insert(gridB.end(), gridA.begin(), gridA.end());

  for (uint64_t x = 0; x < gridA.size(); x++) {
    for (uint64_t y = 0; y < gridA[0].size(); y++) {
      std::size_t aliveCell = 0;
      for (int64_t i = -1; i < 2; i++) {
        for (int64_t j = -1; j < 2; j++) {
          // If is not the center cell
          if (!(i == 0 && j == 0)) {
            // Avoid out of bounds error on border
            if (x + i >= 0 && x + i < gridA.size() && y + j >= 0
                && y + j < gridA[0].size()) {
              if (gridB[x + i][y + j]) {
                ++aliveCell;
              }
            }
          }
        }
      }
      // Game of life rules
      if (aliveCell < 2) {
        gridA[x][y] = false;
      } else if (aliveCell == 3) {
        gridA[x][y] = true;
      } else if (aliveCell > 3) {
        gridA[x][y] = false;
      }
    }
  }
}

void clearGrid(std::vector<std::vector<bool>>& grid)
{
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      grid[x][y] = false;
    }
  }
}

void randomGrid(std::vector<std::vector<bool>>& grid)
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_int_distribution<uint64_t> dist(0, 1000);
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      if (dist(rng) < 500) {
        grid[x][y] = true;
      } else {
        grid[x][y] = false;
      }
    }
  }
}

auto main() -> int
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  raylib::Window window(
      screenWidth, screenHeight, "raylib-cpp game of life example");

  SetTargetFPS(60);

  std::vector<std::vector<bool>> grid {192, std::vector<bool>(108)};

  auto cellXSize = screenWidth / grid.size();
  auto cellYSize = screenHeight / grid[0].size();

  raylib::Camera2D camera = {};
  camera.target = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};

  camera.offset = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  uint64_t framesCounter = 0;

  bool paused = false;
  bool displayGrid = true;
  bool displayHelp = true;

  while (!WindowShouldClose()) {
    framesCounter++;

    float frameTime = GetFrameTime();
    auto mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      auto vect = camera.GetScreenToWorld(mousePosition);
      auto x = (int)(vect.x / cellXSize);
      auto y = (int)(vect.y / cellYSize);

      if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
        grid[x][y] = true;
      }
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      auto vect = camera.GetScreenToWorld(mousePosition);
      auto x = (int)(vect.x / cellXSize);
      auto y = (int)(vect.y / cellYSize);
      if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
        grid[x][y] = false;
      }
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P)) {
      if (paused) {
        paused = false;
      } else {
        paused = true;
      }
    }

    if (IsKeyPressed(KEY_G)) {
      displayGrid = !displayGrid;
    }

    if (IsKeyPressed(KEY_H)) {
      displayHelp = !displayHelp;
    }

    if (framesCounter % 10 == 0 && !paused) {
      updateGrid(grid);
    }

    if (IsKeyDown(KEY_LEFT)) {
      camera.target.x -= 50.0f * frameTime;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      camera.target.x += 50.0f * frameTime;
    }
    if (IsKeyDown(KEY_UP)) {
      camera.target.y -= 50.0f * frameTime;
    }
    if (IsKeyDown(KEY_DOWN)) {
      camera.target.y += 50.0f * frameTime;
    }

    if (IsKeyPressed(KEY_C)) {
      clearGrid(grid);
    }

    if (IsKeyPressed(KEY_R)) {
      randomGrid(grid);
    }

    if (IsKeyPressed(KEY_B)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
      camera.target = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};
    }

    if (IsKeyDown(KEY_A)) {
      camera.rotation--;
    }

    if (IsKeyDown(KEY_S)) {
      camera.rotation++;
    }

    if (camera.rotation > 40) {
      camera.rotation = 40;
    }

    if (camera.rotation < -40) {
      camera.rotation = -40;
    }

    camera.zoom += ((float)GetMouseWheelMove() * 0.10f);

    if (camera.zoom > 35.0f)
      camera.zoom = 5.0f;
    else if (camera.zoom < 0.01f)
      camera.zoom = 0.01f;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    // Drawing world

    for (int x = 0; x < grid.size(); x++) {
      for (int y = 0; y < grid[0].size(); y++) {
        if (grid[x][y]) {
          DrawRectangle(
              x * cellXSize, y * cellYSize, cellXSize, cellYSize, BLACK);
        } else {
          DrawRectangle(
              x * cellXSize, y * cellYSize, cellXSize, cellYSize, LIGHTGRAY);
        }

        if (displayGrid) {
          DrawRectangleLinesEx((Rectangle) {static_cast<float>(x * cellXSize),
                                            static_cast<float>(y * cellYSize),
                                            static_cast<float>(cellXSize),
                                            static_cast<float>(cellYSize)},
                               0.7,
                               BLACK);
        }
      }
    }

    EndMode2D();
    // Drawing interface

    if (displayHelp) {
      DrawRectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.95f));
      DrawRectangleLines(10, 10, 250, 113, BLUE);

      DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
      DrawText("- D-Pad to move Offset", 40, 40, 10, DARKGRAY);
      DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
      DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
      DrawText("- B to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

      DrawRectangle(10, 123, 250, 133, Fade(SKYBLUE, 0.95f));
      DrawRectangleLines(10, 123, 250, 133, BLUE);

      DrawText("Game of life controls:", 20, 133, 10, BLACK);
      DrawText("- R to random values", 40, 153, 10, DARKGRAY);
      DrawText("- C to clear game", 40, 173, 10, DARKGRAY);
      DrawText("- Space to pause", 40, 193, 10, DARKGRAY);
      DrawText("- G to display grid", 40, 213, 10, DARKGRAY);
      DrawText("- H to display help", 40, 233, 10, DARKGRAY);
    }

    EndDrawing();
  }

  // CloseWindow();  // Close window and OpenGL context

  return 0;
}
