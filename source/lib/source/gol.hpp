#ifndef BENLIB_GOL_HPP_
#define BENLIB_GOL_HPP_

#include <algorithm>  // std::fill, std::generate
#include <fstream>  // std::ifstream, std::ofstream
#include <iostream>  // std::cout, std::endl
#include <random>  // std::mt19937, std::uniform_int_distribution
#include <string>  // std::string
#include <vector>  // std::vector

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#  if __has_include("omp.h")
#    include <omp.h>
#  else
#    if _MSC_VER && !__INTEL_COMPILER
#      pragma message("Can t find omp.h, please install OpenMP")
#    else
#      warning Can t find omp.h, please install OpenMP.
#    endif
#  endif
#endif

namespace benlib
{
// A class for representing a game of life.
class Gol
{
public:
  // Constructor.
  Gol(const uint64_t width, const uint64_t height);
  // Constructor.
  Gol(uint8_t** _grid, const uint64_t width, const uint64_t height);
  // Constructor.
  Gol(bool** _grid, const uint64_t width, const uint64_t height);
  // Constructor.
  Gol(const std::vector<std::vector<uint8_t>>& _grid);
  // Destructor.
  ~Gol();
  // Get the width of the game of life.
  uint64_t GetWidth() const;
  // Get the height of the game of life.
  uint64_t GetHeight() const;
  // Get the number of living cells.
  uint64_t GetLivingCells() const;
  // Get the number of dead cells.
  uint64_t GetDeadCells() const;
  // Get the number of cells.
  uint64_t GetCells() const;
  // Get the number of generations.
  uint64_t GetGenerations() const;
  // Set the number of generations.
  void SetGenerations(const uint64_t generations);
  // Set the cell at the given coordinates to be alive.
  void SetCell(const uint64_t x, const uint64_t y, const uint8_t alive);
  // Get the cell at the given coordinates.
  uint8_t GetCell(const uint64_t x, const uint64_t y) const;
  // Get grid.
  std::vector<std::vector<uint8_t>> GetGrid() const;
  // Set grid.
  void SetGrid(const std::vector<std::vector<uint8_t>>& grid);
  // Set grid.
  void SetGrid(const uint8_t** grid, const uint64_t width, const uint64_t height);
  // Update the game of life.
  void Update();
  // Print the game of life.
  void Print();
  // Clear the game of life.
  void Clear();
  // Resize the game of life.
  void Resize(const uint64_t width, const uint64_t height);

  // Randomly populate the game of life.
  void RandomFill();
  // Randomly populate the game of life with rng.
  void RandomFill(std::mt19937_64& rng);
  // Randomly populate the game of life with a given percentage of life.
  void RandomFill(const float percentage);
  // Populate the game of life with value in uint8_tean
  void Fill(const uint8_t value);
  // Reset the game of life.
  void Reset();

  // Overload operator== to compare a game of life.
  uint8_t operator==(const Gol& gol) const;
  // Overload operator= to copy a game of life.
  Gol& operator=(const Gol& gol);
  // Overload operator!= to compare a game of life.
  uint8_t operator!=(const Gol& gol) const;
  // Overload operator(x, y) to get the cell at the given coordinates.
  uint8_t operator()(const uint64_t x, const uint64_t y) const;

  // Save the game of life to a file.
  void Serialize(const std::string& filename);
  // Load the game of life from a file.
  void Deserialize(const std::string& filename);

protected:
  // The number of generations.
  uint64_t generations = 0;
  // The game of life grid.
  std::vector<std::vector<uint8_t>> grid;
};
}  // namespace benlib
#endif  // BENLIB_GOL_HPP_
