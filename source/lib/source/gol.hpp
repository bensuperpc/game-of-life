#ifndef BENLIB_GOL_HPP_
#define BENLIB_GOL_HPP_

#include <algorithm>  // std::fill, std::generate
#include <fstream>  // std::ifstream, std::ofstream
#include <iostream>  // std::cout, std::endl
#include <random>  // std::mt19937, std::uniform_int_distribution
#include <string>  // std::string
#include <vector>  // std::vector

namespace benlib
{
// A class for representing a game of life.
class Gol
{
public:
  // Constructor.
  Gol(const uint64_t width, const uint64_t height);
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
  void SetCell(const uint64_t x, const uint64_t y, const bool alive);
  // Get the cell at the given coordinates.
  bool GetCell(const uint64_t x, const uint64_t y) const;
  // Get grid.
  std::vector<std::vector<bool>> GetGrid() const;
  // Set grid.
  void SetGrid(const std::vector<std::vector<bool>>& grid);
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
  // Populate the game of life with value in boolean
  void Fill(const bool value);
  // Reset the game of life.
  void Reset();

  // Overload operator== to compare a game of life.
  bool operator==(const Gol& gol) const;
  // Overload operator= to copy a game of life.
  Gol& operator=(const Gol& gol);
  // Overload operator!= to compare a game of life.
  bool operator!=(const Gol& gol) const;
  // Overload operator(x, y) to get the cell at the given coordinates.
  bool operator()(const uint64_t x, const uint64_t y) const;

  // Save the game of life to a file.
  void Serialize(const std::string& filename);
  // Load the game of life from a file.
  void Deserialize(const std::string& filename);

protected:
  // The number of generations.
  uint64_t generations = 0;
  // The game of life grid.
  std::vector<std::vector<bool>> grid;
};
}  // namespace benlib
#endif  // BENLIB_GOL_HPP_
