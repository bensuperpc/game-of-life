#ifndef BENLIB_GOL_H_
#define BENLIB_GOL_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool** CreateGrid(uint64_t rows, uint64_t cols);
void ResetGrid(bool** grid, uint64_t rows, uint64_t cols);
void FreeGrid(bool** grid, uint64_t rows);
bool** ResizeGrid(bool** A, uint64_t rows, uint64_t cols, uint64_t new_rows, uint64_t new_cols);
void PrintGrid(bool** grid, uint64_t rows, uint64_t cols);
void CopyGrid(bool** src, bool** dest, uint64_t rows, uint64_t cols);
bool IsEqualGrid(bool** src, bool** dest, uint64_t rows, uint64_t cols);
void RandomFill(bool** grid, uint64_t rows, uint64_t cols);
void UpdateGrid(bool** grid, uint64_t rows, uint64_t cols);
void FillGrid(bool** grid, uint64_t rows, uint64_t cols, bool value);
uint64_t GetLivingCells(bool** grid, uint64_t rows, uint64_t cols);
uint64_t GetDeadCells(bool** grid, uint64_t rows, uint64_t cols);

void Serialize(bool** grid, uint64_t rows, uint64_t cols, const char* filename);
void Deserialize(bool** grid, uint64_t rows, uint64_t cols, const char* filename);

#if defined(__cplusplus)
}
#endif

#endif