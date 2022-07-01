#include "gol.hpp"

benlib::Gol::Gol(const uint64_t width, const uint64_t height)
{
  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));
  grid2D = std::move(new_grid);
}

benlib::Gol::Gol(uint8_t** _grid, const uint64_t width, const uint64_t height)
{
  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));
  for (uint64_t i = 0; i < width; i++) {
    std::copy(_grid[i], _grid[i] + height, new_grid[i].begin());
  }
  grid2D = std::move(new_grid);
}

benlib::Gol::Gol(bool** _grid, const uint64_t width, const uint64_t height)
{
  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));
  for (uint64_t i = 0; i < width; i++) {
    for (uint64_t j = 0; j < height; j++) {
      new_grid[i][j] = _grid[i][j] ? 1 : 0;
    }
  }
  grid2D = std::move(new_grid);
}

benlib::Gol::Gol(const std::vector<std::vector<uint8_t>>& _grid)
{
  grid2D = _grid;
}

benlib::Gol::Gol(const std::vector<uint8_t>& _grid1D, const uint64_t width, const uint64_t height)
{
  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));
  for (uint64_t i = 0; i < width; i++) {
    std::copy(_grid1D.begin() + i * height, _grid1D.begin() + (i + 1) * height, new_grid[i].begin());
  }
  grid2D = std::move(new_grid);
}

benlib::Gol::~Gol() {}

uint64_t benlib::Gol::GetWidth() const
{
  return grid2D.GetWidth();
}

uint64_t benlib::Gol::GetHeight() const
{
  return grid2D.GetHeight();
}

void benlib::Gol::Resize(const uint64_t width, const uint64_t height)
{
  // If old grid is same size as new grid, do nothing
  if (width == GetWidth() && height == GetHeight())
    return;

  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));
  for (uint64_t i = 0; i < width; i++) {
    for (uint64_t j = 0; j < height; j++) {
      if (i < grid2D.GetWidth() && j < grid2D.GetHeight()) {
        new_grid[i][j] = grid2D.GetValue(i, j);
      } else {
        new_grid[i][j] = 0;
      }
    }
  }
  this->Clear();
  grid2D = std::move(new_grid);
}

void benlib::Gol::Reset()
{
  this->Fill(0);
}

uint64_t benlib::Gol::GetLivingCells() const
{
  uint64_t livingCell = 0;
  for (uint64_t x = 0; x < grid2D.GetWidth(); x++) {
    for (uint64_t y = 0; y < grid2D.GetHeight(); y++) {
      if (grid2D.GetValue(x, y)) {
        ++livingCell;
      }
    }
  }
  return livingCell;
}

uint64_t benlib::Gol::GetDeadCells() const
{
  uint64_t deadCell = 0;
  for (uint64_t x = 0; x < grid2D.GetWidth(); x++) {
    for (uint64_t y = 0; y < grid2D.GetHeight(); y++) {
      if (!grid2D.GetValue(x, y)) {
        ++deadCell;
      }
    }
  }
  return deadCell;
}

uint64_t benlib::Gol::GetCells() const
{
  return grid2D.GetWidth() * grid2D.GetHeight();
}

uint64_t benlib::Gol::GetGenerations() const
{
  return generations;
}

void benlib::Gol::SetGenerations(const uint64_t _generations)
{
  this->generations = _generations;
}

std::vector<std::vector<uint8_t>> benlib::Gol::GetGrid() const
{
  return grid2D.GetGrid();
}

void benlib::Gol::SetGrid(const std::vector<std::vector<uint8_t>>& _grid)
{
  grid2D = _grid;
  // this->grid.clear();
  // this->grid.shrink_to_fit();
  // this->grid.insert(this->grid.end(), grid.begin(), grid.end());
}

void benlib::Gol::SetGrid(const uint8_t** _grid, const uint64_t width, const uint64_t height)
{
  // this->grid.clear();
  // this->grid.shrink_to_fit();
  grid2D.Resize(width, height);
  for (uint64_t i = 0; i < width; i++) {
    for (uint64_t j = 0; j < height; j++) {
      grid2D.SetValue(i, j, _grid[i][j]);
    }
  }
}

void benlib::Gol::SetCell(const uint64_t x, const uint64_t y, const uint8_t alive)
{
  grid2D.SetValue(x, y, alive);
}

uint8_t benlib::Gol::GetCell(const uint64_t x, const uint64_t y) const
{
  return grid2D.GetValue(x, y);
}

void benlib::Gol::Print()
{
  for (uint64_t x = 0; x < grid2D.GetWidth(); x++) {
    for (uint64_t y = 0; y < grid2D.GetHeight(); y++) {
      if (grid2D.GetValue(x, y) == 1) {
        std::cout << " O ";
      } else {
        std::cout << " . ";
      }
      if (y == grid2D.GetHeight() - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << std::endl;
}

void benlib::Gol::Update()
{
  generations++;
  std::vector<std::vector<uint8_t>> gridB {};
  // Copy grid to gridB
  gridB = std::move(grid2D.GetGrid());
  // gridB = std::move(grid2D.GetGrid());
#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
#endif
  for (uint64_t x = 0; x < grid2D.GetWidth(); x++) {
    for (uint64_t y = 0; y < grid2D.GetHeight(); y++) {
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
          if (x + i >= grid2D.GetWidth() || y + j >= grid2D.GetHeight()) {
            continue;
          }
          // Count living neighbors
          if (gridB[x + i][y + j]) {
            ++aliveCell;
          }
        }
      }
      // Game of life rules
      if (grid2D.GetValue(x, y)) {
        if (aliveCell < 2 || aliveCell > 3) {
          grid2D.SetValue(x, y, 0);
        }
      } else {
        if (aliveCell == 3) {
          grid2D.SetValue(x, y, 1);
        }
      }
    }
  }
}

void benlib::Gol::Clear()
{
  grid2D.Clear();
  grid2D.ShrinkToFit();
}

void benlib::Gol::RandomFill()
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_int_distribution<uint32_t> dist(0, 1000);
  auto gen = [&dist, &rng]() { return dist(rng) < 500 ? 1 : 0; };

  auto grid = grid2D.GetGrid();

  for (auto& i : grid) {
    std::generate(i.begin(), i.end(), gen);
  }
  grid2D = std::move(grid);
}

void benlib::Gol::RandomFill(std::mt19937_64& rng)
{
  std::uniform_int_distribution<uint32_t> dist(0, 1000);
  auto gen = [&dist, &rng]() { return dist(rng) < 500 ? 1 : 0; };

  auto grid = grid2D.GetGrid();

  for (auto& i : grid) {
    std::generate(i.begin(), i.end(), gen);
  }
  grid2D = std::move(grid);
}

void benlib::Gol::RandomFill(const float percentage)
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  auto gen = [&dist, &rng, &percentage]() { return dist(rng) < percentage ? 1 : 0; };

  auto grid = grid2D.GetGrid();

  for (auto& i : grid) {
    std::generate(i.begin(), i.end(), gen);
  }
  grid2D = std::move(grid);
}

void benlib::Gol::Fill(const uint8_t value)
{
  grid2D.Fill(value);
}

uint8_t benlib::Gol::operator==(const benlib::Gol& other) const
{
  return grid2D.GetGrid() == other.GetGrid();
}

uint8_t benlib::Gol::operator!=(const benlib::Gol& other) const
{
  return grid2D.GetGrid() != other.grid2D.GetGrid();
}

benlib::Gol& benlib::Gol::operator=(const benlib::Gol& other)
{
  // if (this == &other)
  //     return *this;
  grid2D = other.grid2D;
  return *this;
}

uint8_t benlib::Gol::operator()(const uint64_t x, const uint64_t y) const
{
  return grid2D.GetValue(x, y);
}

void benlib::Gol::Deserialize(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open file " << filename << std::endl;
    return;
  }

  std::string line;
  std::vector<std::vector<uint8_t>> _grid {};
  while (std::getline(file, line)) {
    // std::cout << line << std::endl;
    std::vector<uint8_t> row {};
    for (char c : line) {
      if (c == '0') {
        row.push_back(1);
      } else if (c == '.') {
        row.push_back(0);
      } else if (c == '\n') {
      } else {
        // std::cout << "Unknown character: " << c << std::endl;
      }
    }
    _grid.push_back(row);
  }
  file.close();
  grid2D = std::move(_grid);
}

void benlib::Gol::Serialize(const std::string& filename)
{
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open file " << filename << std::endl;
    return;
  }

  for (uint64_t x = 0; x < grid2D.GetWidth(); x++) {
    for (uint64_t y = 0; y < grid2D.GetHeight(); y++) {
      if (grid2D.GetValue(x, y)) {
        file << "0";
      } else {
        file << ".";
      }
    }
    file << "\n";
  }
  file.close();
}
