#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "gol.h"
#include "raylib.h"

int main()
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  InitWindow(screenWidth, screenHeight, "raylib-cpp game of life example");

  SetTargetFPS(60);

  uint64_t cols = screenWidth / 10;
  uint64_t rows = screenHeight / 10;

  bool** grid = CreateGrid(screenWidth / 10, screenHeight / 10);

  uint64_t cellXSize = screenWidth / cols;
  uint64_t cellYSize = screenHeight / rows;

  Camera2D camera = {};
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

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 vect = GetScreenToWorld2D(mousePosition, camera);
      int x = (int)(vect.x / cellXSize);
      int y = (int)(vect.y / cellYSize);

      if (x >= 0 && x < cols && y >= 0 && y < rows) {
        grid[x][y] = true;
      }
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 vect = GetScreenToWorld2D(mousePosition, camera);
      int x = (int)(vect.x / cellXSize);
      int y = (int)(vect.y / cellYSize);

      if (x >= 0 && x < cols && y >= 0 && y < rows) {
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
      UpdateGrid(grid, cols, rows);
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
      ResetGrid(grid, cols, rows);
    }

    if (IsKeyPressed(KEY_R)) {
      RandomPopulate(grid, cols, rows);
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
    for (int x = 0; x < cols; x++) {
      for (int y = 0; y < rows; y++) {
        if (grid[x][y]) {
          DrawRectangle(
              x * cellXSize, y * cellYSize, cellXSize, cellYSize, BLACK);
        } else {
          DrawRectangle(
              x * cellXSize, y * cellYSize, cellXSize, cellYSize, LIGHTGRAY);
        }

        if (displayGrid) {
          DrawRectangleLinesEx((Rectangle) {(float)(x * cellXSize),
                                            (float)(y * cellYSize),
                                            (float)(cellXSize),
                                            (float)(cellYSize)},
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

  FreeGrid(grid, rows);
  CloseWindow();

  return 0;
}