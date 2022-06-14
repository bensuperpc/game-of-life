#include "gol.h"

bool** CreateGrid(uint64_t x, uint64_t y)
{
  bool** grid = (bool**)malloc(x * sizeof(bool*));

  // Check if malloc failed
  if (grid == NULL) {
    return NULL;
  }

  for (uint64_t i = 0; i < x; i++) {
    grid[i] = (bool*)malloc(y * sizeof(bool));

    // Check if malloc failed
    if (grid[i] == NULL) {
      for (uint64_t j = 0; j < i; j++) {
        free(grid[j]);
      }
      free(grid);

      return NULL;
    }
  }
  return grid;
}

void ResetGrid(bool** grid, uint64_t x, uint64_t y)
{
  for (uint64_t i = 0; i < x; i++) {
    memset(grid[i], false, y * sizeof(bool));
  }
}

bool** ResizeGrid(bool** A, uint64_t rows, uint64_t cols, uint64_t newRow, uint64_t newCol)
{
  // If old size is same as new size, return the same grid
  // if (newRow == rows && newCol == cols) {
  //   return A;
  // }

  // If new size is smaller than old size, free the extra memory
  if (rows > newRow) {
    for (uint64_t i = newRow; i < rows; i++) {
      free(A[i]);
    }
  }

  A = (bool**)realloc(A, sizeof(bool*) * newRow);
  // Check if realloc fails
  if (A == NULL) {
    return NULL;
  }

  for (uint64_t i = 0; i < newRow; i++) {
    // Reallocate memory only on already allocated rows
    if (rows > i) {
      A[i] = (bool*)realloc(A[i], sizeof(bool) * newCol);
    } else {
      A[i] = (bool*)malloc(sizeof(bool) * newCol);
    }
    // Check if realloc/malloc fails
    if (A[i] == NULL) {
      // Free all the rows that have been allocated
      for (uint64_t j = 0; j < i; j++) {
        free(A[j]);
      }
      free(A);

      return NULL;
    }
  }
  return A;
}

void FreeGrid(bool** grid, uint64_t x)
{
  for (uint64_t i = 0; i < x; i++) {
    free(grid[i]);
  }
  free(grid);
}

void PrintGrid(bool** grid, uint64_t x, uint64_t y)
{
  for (uint64_t i = 0; i < x; i++) {
    for (uint64_t j = 0; j < y; j++) {
      if (grid[i][j]) {
        printf("%c", '0');
      } else {
        printf("%c", '.');
      }
    }
    printf("\n");
  }
}

void CopyGrid(bool** src, bool** dest, uint64_t x, uint64_t y)
{
  for (uint64_t i = 0; i < x; i++) {
    memcpy(dest[i], src[i], y * sizeof(bool));
  }
}

bool IsEqualGrid(bool** src, bool** dest, uint64_t x, uint64_t y)
{
  for (uint64_t i = 0; i < x; i++) {
    for (uint64_t j = 0; j < y; j++) {
      if (src[i][j] != dest[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void RandomFill(bool** grid, uint64_t x, uint64_t y)
{
  for (uint64_t i = 0; i < x; i++) {
    for (uint64_t j = 0; j < y; j++) {
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

void FillGrid(bool** grid, const uint64_t x, const uint64_t y, const bool value)
{
  for (uint64_t i = 0; i < x; i++) {
    memset(grid[i], value, y * sizeof(bool));
  }
}

uint64_t GetLivingCells(bool** grid, uint64_t x, uint64_t y)
{
  uint64_t aliveCells = 0;
  for (uint64_t i = 0; i < x; i++) {
    for (uint64_t j = 0; j < y; j++) {
      if (grid[i][j]) {
        ++aliveCells;
      }
    }
  }
  return aliveCells;
}

uint64_t GetDeadCells(bool** grid, uint64_t x, uint64_t y)
{
  uint64_t deadCells = 0;
  for (uint64_t i = 0; i < x; i++) {
    for (uint64_t j = 0; j < y; j++) {
      if (!grid[i][j]) {
        ++deadCells;
      }
    }
  }
  return deadCells;
}

void Serialize(bool** grid, uint64_t x, uint64_t y, const char* filename)
{
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    return;
  }

  for (uint64_t i = 0; i < y; i++) {
    for (uint64_t j = 0; j < x; j++) {
      if (grid[j][i]) {
        fputc('0', file);
      } else {
        fputc('.', file);
      }
    }
    fputc('\n', file);
  }

  fclose(file);
}

void Deserialize(bool** grid, uint64_t x, uint64_t y, const char* filename)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return;
  }
  // Read the file, fgets add a \n before nul char.
  uint64_t bufferLength = x + 2;

  char buffer[bufferLength];
  for (uint64_t i = 0; i < bufferLength; i++) {
    buffer[i] = '\0';
  }

  for (uint64_t i = 0; i < y; i++) {
    fgets(buffer, (int)bufferLength, file);
    for (uint64_t j = 0; j < x; j++) {
      if (buffer[j] == '0') {
        grid[j][i] = true;
      } else if (buffer[j] == '.') {
        grid[j][i] = false;
      } else if (buffer[j] == '\n') {
      } else {
        // printf("Unknown character: %c\n", buff[j]);
      }
    }
  }

  fclose(file);
}
