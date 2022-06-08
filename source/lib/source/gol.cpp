#include "gol.hpp"

benlib::Gol::Gol(const uint64_t width, const uint64_t height)
{
  grid.reserve(width);
  for (uint64_t x = 0; x < width; x++) {
    std::vector<bool> row;
    row.reserve(height);
    for (uint64_t y = 0; y < height; y++) {
      row.push_back(false);
    }
    grid.push_back(row);
  }
}

benlib::Gol::~Gol() {}

uint64_t benlib::Gol::GetWidth() const
{
  return grid.size();
}

uint64_t benlib::Gol::GetHeight() const
{
  return grid[0].size();
}

uint64_t benlib::Gol::GetLivingCells() const
{
  uint64_t livingCell = 0;
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      if (grid[x][y]) {
        ++livingCell;
      }
    }
  }
  return livingCell;
}

uint64_t benlib::Gol::GetDeadCells() const
{
  uint64_t deadCell = 0;
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      if (!grid[x][y]) {
        ++deadCell;
      }
    }
  }
  return deadCell;
}

uint64_t benlib::Gol::GetCells() const
{
  return grid.size() * grid[0].size();
}

uint64_t benlib::Gol::GetGenerations() const
{
  return generations;
}

std::vector<std::vector<bool>> benlib::Gol::GetGrid() const
{
  return grid;
}

void benlib::Gol::SetGrid(const std::vector<std::vector<bool>>& _grid)
{
  this->grid = _grid;
  // this->grid.clear();
  // this->grid.shrink_to_fit();
  // this->grid.insert(this->grid.end(), grid.begin(), grid.end());
}

void benlib::Gol::SetCell(const uint64_t x, const uint64_t y, const bool alive)
{
  grid[x][y] = alive;
}

bool benlib::Gol::GetCell(const uint64_t x, const uint64_t y) const
{
  return grid[x][y];
}

void benlib::Gol::Print()
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

void benlib::Gol::Update()
{
  generations++;

  std::vector<std::vector<bool>> gridB {};

  gridB = grid;

  // Copy grid to gridB
  // gridB.insert(gridB.end(), grid.begin(), grid.end());

  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      
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
          if(x + i >= grid.size() || y + j >= grid[0].size()) {
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
}

void benlib::Gol::Clear()
{
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      grid[x][y] = false;
    }
  }
}

void benlib::Gol::RandomFill()
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_int_distribution<uint32_t> dist(0, 1000);
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

void benlib::Gol::RandomFill(const float percentage)
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      if (dist(rng) < percentage) {
        grid[x][y] = true;
      } else {
        grid[x][y] = false;
      }
    }
  }
}

void benlib::Gol::Fill(const bool value)
{
  for (uint64_t x = 0; x < grid.size(); x++) {
    for (uint64_t y = 0; y < grid[0].size(); y++) {
      grid[x][y] = value;
    }
  }
}

bool benlib::Gol::operator==(const benlib::Gol& other) const
{
  return grid == other.grid;
}

bool benlib::Gol::operator!=(const benlib::Gol& other) const
{
  return grid != other.grid;
}

benlib::Gol& benlib::Gol::operator=(const benlib::Gol& other)
{
  // if (this == &other)
  //     return *this;
  grid = other.grid;
  return *this;
}

bool benlib::Gol::operator()(const uint64_t x, const uint64_t y) const
{
  return grid[x][y];
}
