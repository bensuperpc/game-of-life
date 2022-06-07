#include "gol.h"

bool** CreateGrid(uint64_t rows, uint64_t cols)
{
  bool** grid = malloc(rows * sizeof(bool*));
  for (uint64_t i = 0; i < rows; i++) {
    grid[i] = malloc(cols * sizeof(bool));
  }
  ResetGrid(grid, rows, cols);
  return grid;
}

void ResetGrid(bool** grid, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      grid[i][j] = false;
    }
  }
}

void FreeGrid(bool** grid, uint64_t rows)
{
  for (uint64_t i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);
}

void PrintGrid(bool** grid, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      printf("%d", grid[i][j]);
    }
    printf("\n");
  }
}

void CopyGrid(bool** src, bool** dest, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void RandomFill(bool** grid, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      grid[i][j] = rand() % 2;
    }
  }
}

void UpdateGrid(bool** grid, uint64_t rows, uint64_t cols)
{
  bool** gridB = CreateGrid(rows, cols);
  CopyGrid(grid, gridB, rows, cols);

  for (uint64_t x = 0; x < rows; x++) {
    for (uint64_t y = 0; y < cols; y++) {
      // Count living neighbors
      uint64_t aliveCell = 0;
      for (int8_t i = -1; i < 2; i++) {
        for (int8_t j = -1; j < 2; j++) {
          // If is not the center cell
          if (!(i == 0 && j == 0)) {
            // Avoid out of bounds error on border
            if (x + i >= 0 && x + i < rows && y + j >= 0 && y + j < cols) {
              if (gridB[x + i][y + j]) {
                ++aliveCell;
              }
            }
          }
        }
      }

      // Game of life rules
      if (grid[x][y]) {
        if (aliveCell < 2 || aliveCell > 3) {
          grid[x][y] = false;
        }
      } else {
        if (aliveCell == 3) {
          grid[x][y] = true;
        }
      }
    }
  }
  FreeGrid(gridB, rows);
}

void FillGrid(bool** grid, uint64_t rows, uint64_t cols, bool value)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      grid[i][j] = value;
    }
  }
}

uint64_t GetLivingCells(bool** grid, uint64_t rows, uint64_t cols)
{
  uint64_t aliveCells = 0;
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      if (grid[i][j]) {
        ++aliveCells;
      }
    }
  }
  return aliveCells;
}

uint64_t GetDeadCells(bool** grid, uint64_t rows, uint64_t cols)
{
  uint64_t deadCells = 0;
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      if (!grid[i][j]) {
        ++deadCells;
      }
    }
  }
  return deadCells;
}
