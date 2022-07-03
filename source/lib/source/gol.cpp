#include "gol.hpp"

benlib::Gol::Gol() {}

benlib::Gol::Gol(const uint64_t width, const uint64_t height)
{
  std::vector<uint64_t> v = {width, height};
  this->grid2D = benlib::MultiVector<uint8_t>(v);
}

benlib::Gol::Gol(uint8_t** _grid, const uint64_t width, const uint64_t height)
{
  std::vector<uint8_t> new_grid(width * height, 0);
  for (uint64_t i = 0; i < width; i++) {
    std::copy(_grid[i], _grid[i] + height, new_grid.begin() + i * height);
  }
  std::vector<uint64_t> dim = {width, height};
  this->grid2D = benlib::MultiVector<uint8_t>(dim, new_grid);
}

benlib::Gol::Gol(bool** _grid, const uint64_t width, const uint64_t height)
{
  std::vector<uint8_t> new_grid(width * height, 0);
  for (uint64_t i = 0; i < width; i++) {
    std::copy(_grid[i], _grid[i] + height, new_grid.begin() + i * height);
  }
  std::vector<uint64_t> dim = {width, height};
  this->grid2D = benlib::MultiVector<uint8_t>(dim, new_grid);
}

benlib::Gol::Gol(const std::vector<uint8_t>& _grid1D, const uint64_t width, const uint64_t height)
{
  std::vector<uint64_t> v = {width, height};
  this->grid2D = benlib::MultiVector<uint8_t>(v);
  this->grid2D.SetGrid(_grid1D);
}

benlib::Gol::Gol(const std::vector<std::vector<uint8_t>>& _grid)
{
  // Convert to 1D vector.
  std::vector<uint8_t> new_grid;
  for (auto& i : _grid) {
    new_grid.insert(new_grid.end(), i.begin(), i.end());
  }
  std::vector<uint64_t> dim = {_grid.size(), _grid[0].size()};
  this->grid2D = benlib::MultiVector<uint8_t>(dim, new_grid);
  this->grid2D.SetGrid(new_grid);
}

benlib::Gol::~Gol() {}

uint64_t benlib::Gol::GetWidth()
{
  return grid2D.GetDim()[0];
}

uint64_t benlib::Gol::GetHeight()
{
  return grid2D.GetDim()[1];
}

void benlib::Gol::Resize(const uint64_t width, const uint64_t height)
{
  // If old grid is same size as new grid, do nothing
  if (width == GetWidth() && height == GetHeight())
    return;
  std::vector<uint64_t> v = {width, height};
  grid2D.Resize(v);
}

void benlib::Gol::Reset()
{
  this->Fill(0);
}

uint64_t benlib::Gol::GetLivingCells()
{
  auto& gridPtr = grid2D.GetGrid();
  uint64_t livingCell = 0;
  for (uint64_t x = 0; x < GetWidth() * GetHeight(); x++) {
    if (gridPtr[x]) {
      ++livingCell;
    }
  }

  return livingCell;
}

uint64_t benlib::Gol::GetDeadCells()
{
  auto& gridPtr = grid2D.GetGrid();
  uint64_t deadCell = 0;
  for (uint64_t x = 0; x < GetWidth() * GetHeight(); x++) {
    if (!gridPtr[x]) {
      ++deadCell;
    }
  }

  return deadCell;
}

uint64_t benlib::Gol::GetCells()
{
  return GetWidth() * GetHeight();
}

uint64_t benlib::Gol::GetGenerations()
{
  return generations;
}

void benlib::Gol::SetGenerations(const uint64_t _generations)
{
  this->generations = _generations;
}

std::vector<uint8_t>& benlib::Gol::GetGrid()
{
  return grid2D.GetGrid();
}

void benlib::Gol::SetGrid(const std::vector<uint8_t>& _grid)
{
  grid2D.SetGrid(_grid);
}

void benlib::Gol::SetCell(const uint64_t x, const uint64_t y, const uint8_t alive)
{
  grid2D.SetValue(x * GetHeight() + y, alive);
}

uint8_t benlib::Gol::GetCell(const uint64_t x, const uint64_t y)
{
  return grid2D.GetValue(x * GetHeight() + y);
}

void benlib::Gol::Print()
{
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      if (grid2D.GetValue(x * GetHeight() + y) == 1) {
        std::cout << " O ";
      } else {
        std::cout << " . ";
      }
      if (y == GetHeight() - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << std::endl;
}

uint64_t benlib::Gol::GetNeighborsCount(const uint64_t x, const uint64_t y)
{
  uint64_t neighbors = 0;
  for (uint64_t i = -1; i <= 1; i++) {
    for (uint64_t j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;
      if (x + i < GetWidth() && y + j < GetHeight()) {
        if (grid2D.GetValue((x + i) * GetHeight() + (y + j)) == 1) {
          neighbors++;
        }
      }
    }
  }
  return neighbors;
}

void benlib::Gol::Update()
{
  generations++;
  // Copy grid to gridB
  std::vector<uint8_t>&& gridB = grid2D.CopyGrid();
  int64_t aliveCell = 0;
#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto) firstprivate(aliveCell)
#endif
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      // Count living neighbors
      aliveCell = 0;
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
          if (x + i >= GetWidth() || y + j >= GetHeight()) {
            continue;
          }
          // Count living neighbors
          if (gridB[(x + i) * GetHeight() + y + j]) {
            ++aliveCell;
          }
        }
      }
      // Game of life rules
      if (grid2D.GetValue(x * GetHeight() + y)) {
        if (aliveCell < 2 || aliveCell > 3) {
          grid2D.SetValue(x * GetHeight() + y, 0);
        }
      } else {
        if (aliveCell == 3) {
          grid2D.SetValue(x * GetHeight() + y, 1);
        }
      }
    }
  }
}

void benlib::Gol::Clear()
{
  grid2D.Clear();
  // grid2D.ShrinkToFit();
}

void benlib::Gol::RandomFill()
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_int_distribution<uint32_t> dist(0, 1000);
  auto gen = [&dist, &rng]() { return dist(rng) < 500 ? 1 : 0; };

  auto& grid = grid2D.GetGrid();
  std::generate(grid.begin(), grid.end(), gen);
}

void benlib::Gol::RandomFill(std::mt19937_64& rng)
{
  std::uniform_int_distribution<uint32_t> dist(0, 1000);
  auto gen = [&dist, &rng]() { return dist(rng) < 500 ? 1 : 0; };

  auto& grid = grid2D.GetGrid();
  std::generate(grid.begin(), grid.end(), gen);
}

void benlib::Gol::RandomFill(const float percentage)
{
  std::mt19937_64 rng;
  std::random_device rnd_device;
  rng.seed(rnd_device());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  auto gen = [&dist, &rng, &percentage]() { return dist(rng) < percentage ? 1 : 0; };

  auto& grid = grid2D.GetGrid();
  std::generate(grid.begin(), grid.end(), gen);
}

void benlib::Gol::Fill(const uint8_t value)
{
  grid2D.Fill(value);
}

bool benlib::Gol::operator==(const benlib::Gol& other) const
{
  return grid2D == other.grid2D;
}

bool benlib::Gol::operator!=(const benlib::Gol& other) const
{
  return grid2D != other.grid2D;
}

benlib::Gol& benlib::Gol::operator=(const benlib::Gol& other)
{
  // if (this == &other)
  //     return *this;
  grid2D = other.grid2D;
  return *this;
}

uint8_t benlib::Gol::operator()(const uint64_t x, const uint64_t y)
{
  std::vector<uint64_t> coor {x, y};
  return grid2D.GetValue(coor);
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

  std::vector<uint8_t> new_grid;
  for (auto& i : _grid) {
    new_grid.insert(new_grid.end(), i.begin(), i.end());
  }
  std::vector<uint64_t> dim = {_grid.size(), _grid[0].size()};
  this->grid2D = benlib::MultiVector<uint8_t>(dim, new_grid);
  this->grid2D.SetGrid(new_grid);
}

void benlib::Gol::Serialize(const std::string& filename)
{
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open file " << filename << std::endl;
    return;
  }

  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      if (grid2D.GetValue(x * GetHeight() + y)) {
        file << "0";
      } else {
        file << ".";
      }
    }
    file << "\n";
  }
  file.close();
}
