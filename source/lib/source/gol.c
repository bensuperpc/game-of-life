#include "gol.h"

bool** CreateGrid(uint64_t rows, uint64_t cols)
{
  bool** grid = malloc(rows * sizeof(bool*));
  if (grid == NULL) {
    return NULL;
  }
  for (uint64_t i = 0; i < rows; i++) {
    grid[i] = malloc(cols * sizeof(bool));
    if (grid[i] == NULL) {
      return NULL;
    }
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
  for (uint64_t i = 0; i < rows - 1; i++) {
    free(grid[i]);
  }
  free(grid);
}

void PrintGrid(bool** grid, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      if (grid[i][j]) {
        printf("%c", '0');
      } else {
        printf("%c", '.');
      }
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

bool IsEqualGrid(bool** src, bool** dest, uint64_t rows, uint64_t cols)
{
  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      if (src[i][j] != dest[i][j]) {
        return false;
      }
    }
  }
  return true;
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
  if (gridB == NULL) {
    return;
  }

  CopyGrid(grid, gridB, rows, cols);

  for (uint64_t x = 0; x < rows; x++) {
    for (uint64_t y = 0; y < cols; y++) {
      // Count living neighbors
      uint64_t aliveCell = 0;
      for (int8_t i = -1; i < 2; i++) {
        for (int8_t j = -1; j < 2; j++) {
          // If is not the center cell
          if (i == 0 && j == 0) {
            continue;
          }

          // Avoid underflow of the grid
          if ((x == 0 && i == -1) || (y == 0 && j == -1)) {
            continue;
          }

          // Avoid overflow of grid
          if (x + i >= rows || y + j >= cols) {
            continue;
          }

          if (gridB[x + i][y + j]) {
            ++aliveCell;
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

void Serialize(bool** grid, uint64_t rows, uint64_t cols, const char* filename)
{
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    return;
  }

  for (uint64_t i = 0; i < rows; i++) {
    for (uint64_t j = 0; j < cols; j++) {
      if (grid[i][j]) {
        fputc('0', file);
      } else {
        fputc('.', file);
      }
    }
    fputc('\n', file);
  }

  fclose(file);
}

void Deserialize(bool** grid, uint64_t rows, uint64_t cols, const char* filename)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return;
  }
  // printf("%d rows, %d cols\n", rows, cols);

  // Read the file, fgets add a \n before nul char.
  uint64_t bufferLength = rows + 2;

  char buffer[bufferLength];
  for (uint64_t i = 0; i < bufferLength; i++) {
    buffer[i] = '\0';
  }

  for (uint64_t i = 0; i < cols; i++) {
    fgets(buffer, bufferLength, file);
    // buffer[strcspn(buffer, "\n")] = 0;
    // printf("%d line:\n", i);
    // printf("%s\n", buffer);
    for (uint64_t j = 0; j < rows; j++) {
      if (buffer[j] == '0') {
        grid[i][j] = true;
      } else if (buffer[j] == '.') {
        grid[i][j] = false;
      } else if (buffer[j] == '\n') {
      } else {
        // printf("Unknown character: %c\n", buff[j]);
      }
    }
    // grid[i][rows] = '\0';
  }

  fclose(file);
}