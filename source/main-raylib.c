#include <stdbool.h>  // bool
#include <stdint.h>  // uint64_t
#include <stdio.h>  // printf
#include <stdlib.h>  // malloc, realloc, free

#include "gol.h"
#include "raylib.h"

int main()
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;
  const uint32_t targetFPS = 120;
  const uint32_t gridUpdatePerSecond = 10;

  const float gridOffsetX = 0.0f;
  const float gridOffsetY = 0.0f;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "raylib game of life");

  SetTargetFPS(targetFPS);

  uint64_t cols = screenWidth;
  uint64_t rows = screenHeight;

  bool** grid = CreateGrid(cols, rows);

  ResetGrid(grid, cols, rows);

  float cellXSize = 10.0f;
  float cellYSize = 10.0f;

  Camera2D camera = {};
  camera.target = (Vector2) {screenWidth / 2.0f + gridOffsetX, screenHeight / 2.0f + gridOffsetY};
  camera.offset = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  uint64_t framesCounter = 0;

  bool paused = false;
  bool displayGrid = true;
  bool displayHelp = true;

  while (!WindowShouldClose()) {
    framesCounter++;

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 vect = GetScreenToWorld2D(mousePosition, camera);

      // Apply grid offset
      vect.x -= gridOffsetX;
      vect.y -= gridOffsetY;

      uint64_t x = (uint64_t)(vect.x / cellXSize);
      uint64_t y = (uint64_t)(vect.y / cellYSize);

      if (x >= 0 && x < cols && y >= 0 && y < rows) {
        grid[x][y] = true;
      }
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 vect = GetScreenToWorld2D(mousePosition, camera);

      // Apply grid offset
      vect.x -= gridOffsetX;
      vect.y -= gridOffsetY;

      uint64_t x = (uint64_t)(vect.x / cellXSize);
      uint64_t y = (uint64_t)(vect.y / cellYSize);

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

    if (IsKeyPressed(KEY_U)) {
      char* fileName = "gol.txt";
      Serialize(grid, cols, rows, fileName);
    }

    if (IsKeyPressed(KEY_L)) {
      char* fileName = "gol.txt";
      Deserialize(grid, cols, rows, fileName);
    }

    if (IsKeyPressed(KEY_G)) {
      displayGrid = !displayGrid;
    }

    if (IsKeyPressed(KEY_H)) {
      displayHelp = !displayHelp;
    }

    if (framesCounter % (targetFPS / gridUpdatePerSecond) == 0 && !paused) {
      UpdateGrid(grid, cols, rows);
    }

    if (IsKeyDown(KEY_LEFT)) {
      camera.target.x -= 5.0f;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      camera.target.x += 5.0f;
    }
    if (IsKeyDown(KEY_UP)) {
      camera.target.y -= 5.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
      camera.target.y += 5.0f;
    }

    if (IsKeyPressed(KEY_C)) {
      ResetGrid(grid, cols, rows);
    }

    if (IsKeyPressed(KEY_R)) {
      RandomFill(grid, cols, rows);
    }

    if (IsKeyPressed(KEY_B)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
      camera.target = (Vector2) {screenWidth / 2.0f + gridOffsetX, screenHeight / 2.0f + gridOffsetY};
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

    // Draw only on screen
    Vector2 vectH = GetScreenToWorld2D((Vector2) {0.0f, 0.0f}, camera);
    Vector2 vectB = GetScreenToWorld2D((Vector2) {(float)screenWidth, (float)screenHeight}, camera);

    // Apply grid offset
    vectH.x -= gridOffsetX;
    vectH.y -= gridOffsetY;
    vectB.x -= gridOffsetX;
    vectB.y -= gridOffsetY;

    int64_t xStart = (int64_t)(vectH.x / cellXSize);
    int64_t yStart = (int64_t)(vectH.y / cellYSize);

    int64_t xEnd = (int64_t)(vectB.x / cellXSize) + 1;
    int64_t yEnd = (int64_t)(vectB.y / cellYSize) + 1;

    // Avoid out of bounds of the grid
    if (xStart < 0) {
      xStart = 0;
    }
    if (yStart < 0) {
      yStart = 0;
    }

    if (xEnd > cols) {
      xEnd = cols;
    }
    if (yEnd > rows) {
      yEnd = rows;
    }

    // Draw grid
    for (uint64_t x = xStart; x < xEnd; x++) {
      for (uint64_t y = yStart; y < yEnd; y++) {
        // If cell is alive
        if (grid[x][y]) {
          DrawRectangle((int)(x * cellXSize + gridOffsetX),
                        (int)(y * cellYSize + gridOffsetY),
                        (int)(cellXSize),
                        (int)(cellYSize),
                        BLACK);
        } else {
          DrawRectangle((int)(x * cellXSize + gridOffsetX),
                        (int)(y * cellYSize + gridOffsetY),
                        (int)(cellXSize),
                        (int)(cellYSize),
                        LIGHTGRAY);
        }

        if (displayGrid) {
          DrawRectangleLinesEx((Rectangle) {(float)(x * cellXSize + gridOffsetX),
                                            (float)(y * cellYSize + gridOffsetY),
                                            (float)(cellXSize),
                                            (float)(cellYSize)},
                               0.7f,
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

      DrawRectangle(10, 123, 250, 153, Fade(SKYBLUE, 0.95f));
      DrawRectangleLines(10, 123, 250, 153, BLUE);

      DrawText("Game of life controls:", 20, 133, 10, BLACK);
      DrawText("- R to random values", 40, 153, 10, DARKGRAY);
      DrawText("- C to clear game", 40, 173, 10, DARKGRAY);
      DrawText("- Space to pause", 40, 193, 10, DARKGRAY);
      DrawText("- G to display grid", 40, 213, 10, DARKGRAY);
      DrawText("- H to display help", 40, 233, 10, DARKGRAY);
      DrawText("- U to Serialize, L to Deserialize", 40, 253, 10, DARKGRAY);
    }

    // display FPS
    DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
    DrawText(TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

    EndDrawing();
  }

  FreeGrid(grid, rows);
  CloseWindow();

  return 0;
}