#include <iostream>
#include <random>
#include <vector>

#include "gol.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"

auto main() -> int
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;
  const uint32_t targetFPS = 120;
  const uint32_t gridUpdatePerSecond = 10;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  raylib::Window window(screenWidth, screenHeight, "raylib-cpp game of life");

  SetTargetFPS(targetFPS);

  auto gol = benlib::Gol(screenWidth, screenHeight);

  float cellXSize = 10.0f;
  float cellYSize = 10.0f;

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

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 vect = camera.GetScreenToWorld(mousePosition);
      auto x = static_cast<int64_t>(vect.x / cellXSize);
      auto y = static_cast<int64_t>(vect.y / cellYSize);

      if (x >= 0 && x < gol.GetWidth() && y >= 0 && y < gol.GetHeight()) {
        gol.SetCell(x, y, true);
      }
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 vect = camera.GetScreenToWorld(mousePosition);
      auto x = static_cast<int64_t>(vect.x / cellXSize);
      auto y = static_cast<int64_t>(vect.y / cellYSize);
      if (x >= 0 && x < gol.GetWidth() && y >= 0 && y < gol.GetHeight()) {
        gol.SetCell(x, y, false);
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
      const std::string filename = "gol.txt";
      gol.Serialize(filename);
    }

    if (IsKeyPressed(KEY_L)) {
      const std::string filename = "gol.txt";
      gol.Deserialize(filename);
    }

    if (IsKeyPressed(KEY_G)) {
      displayGrid = !displayGrid;
    }

    if (IsKeyPressed(KEY_H)) {
      displayHelp = !displayHelp;
    }

    if (framesCounter % (targetFPS / gridUpdatePerSecond) == 0 && !paused) {
      gol.Update();
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
      gol.Reset();
    }

    if (IsKeyPressed(KEY_R)) {
      gol.RandomFill();
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
    // Draw only on screen
    const Vector2 vectH = camera.GetScreenToWorld((Vector2) {0.0f, 0.0f});
    const Vector2 vectB =
        camera.GetScreenToWorld((Vector2) {static_cast<float>(screenWidth), static_cast<float>(screenHeight)});

    int64_t xStart = static_cast<int64_t>(vectH.x / cellXSize);
    int64_t yStart = static_cast<int64_t>(vectH.y / cellYSize);

    int64_t xEnd = static_cast<int64_t>(vectB.x / cellXSize) + 1;
    int64_t yEnd = static_cast<int64_t>(vectB.y / cellYSize) + 1;

    if (xStart < 0) {
      xStart = 0;
    }
    if (yStart < 0) {
      yStart = 0;
    }

    if (xEnd > gol.GetWidth()) {
      xEnd = gol.GetWidth();
    }
    if (yEnd > gol.GetHeight()) {
      yEnd = gol.GetHeight();
    }

    for (uint64_t x = xStart; x < xEnd; x++) {
      for (uint64_t y = yStart; y < yEnd; y++) {
        if (gol.GetCell(x, y)) {
          DrawRectangle(static_cast<int>(x * cellXSize),
                        static_cast<int>(y * cellYSize),
                        static_cast<int>(cellXSize),
                        static_cast<int>(cellYSize),
                        BLACK);
        } else {
          DrawRectangle(static_cast<int>(x * cellXSize),
                        static_cast<int>(y * cellYSize),
                        static_cast<int>(cellXSize),
                        static_cast<int>(cellYSize),
                        LIGHTGRAY);
        }
        if (displayGrid) {
          DrawRectangleLinesEx((Rectangle) {static_cast<float>(x * cellXSize),
                                            static_cast<float>(y * cellYSize),
                                            static_cast<float>(cellXSize),
                                            static_cast<float>(cellYSize)},
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

  // CloseWindow();  // Close window and OpenGL context

  return 0;
}
