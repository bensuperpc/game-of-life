#ifndef BENLIB_VECTOR2D_HPP_
#define BENLIB_VECTOR2D_HPP_

#include <algorithm>  // std::copy, std::move, std::fill
#include <vector>  // std::vector

namespace benlib
{
template<class T>
class vector2D
{
public:
  using size_type = typename std::vector<T>::size_type;

  // Constructor with no arguments.
  vector2D() {}

  // Constructor with width and height.
  vector2D(const size_type width, const size_type height)
  {
    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, 0));
    grid = std::move(new_grid);
  }

  // Constructor with width, height and value
  vector2D(const size_type width, const size_type height, const T value)
  {
    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, value));
    grid = std::move(new_grid);
  }

  // Constructor with a 2D vector.
  vector2D(const std::vector<std::vector<T>>& _grid)
  {
    this->grid = _grid;
  }

  // Constructor with a 1D vector.
  vector2D(const std::vector<T>& _grid1D, const size_type width, const size_type height)
  {
    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, 0));
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid1D.begin() + i * height, _grid1D.begin() + (i + 1) * height, new_grid[i].begin());
    }
    this->grid = std::move(new_grid);
  }

  // Constructor with a pointer to pointer and width and height.
  vector2D(T** _grid, const size_type width, const size_type height)
  {
    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, 0));
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid[i], _grid[i] + height, new_grid[i].begin());
    }
    this->grid = std::move(new_grid);
  }

  // Destructor
  ~vector2D() {}

  // Fill with value
  void Fill(const T value)
  {
    for (auto& i : grid) {
      std::fill(i.begin(), i.end(), value);
    }
  }

  // Clear grid
  void Clear()
  {
    for (auto& i : grid) {
      i.clear();
    }
    grid.clear();
  }

  // ShrinkToFit grid
  void ShrinkToFit()
  {
    for (auto& i : grid) {
      i.shrink_to_fit();
    }
    grid.shrink_to_fit();
  }

  // Get width
  size_type GetWidth() const
  {
    return grid.size();
  }

  // Get height
  size_type GetHeight() const
  {
    return grid[0].size();
  }

  // Resize (Need more testing)
  void Resize(const size_type width, const size_type height)
  {
    // If old grid is same size as new grid, do nothing
    if (width == GetWidth() && height == GetHeight())
      return;

    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, 0));
    for (size_type i = 0; i < width; i++) {
      std::copy(grid[i].begin(), grid[i].end(), new_grid[i].begin());
    }
    this->Clear();
    grid = std::move(new_grid);
  }

  // Get grid pointer
  std::vector<std::vector<T>>* GetGridPtr()
  {
    return &grid;
  }

  // Get grid
  std::vector<std::vector<T>> GetGrid() const
  {
    return grid;
  }

  // Set grid
  void SetGrid(const std::vector<std::vector<T>>& _grid)
  {
    this->grid = _grid;
  }

  // Get grid 1D
  std::vector<T> GetGrid1D() const
  {
    std::vector<T> grid1D;
    for (auto& i : grid) {
      grid1D.insert(grid1D.end(), i.begin(), i.end());
    }
    return grid1D;
  }

  // Get value
  T GetValue(const size_type x, const size_type y) const
  {
    return grid[x][y];
  }

  // Set value
  void SetValue(const size_type x, const size_type y, const T value)
  {
    grid[x][y] = value;
  }

  // Overload == operator
  bool operator==(const vector2D<T>& other) const
  {
    return grid == other.grid;
  }

  // Overload == operator
  bool operator==(const std::vector<std::vector<T>>& other) const
  {
    return grid == other;
  }

  // Overload != operator
  bool operator!=(const vector2D<T>& other) const
  {
    return grid != other.grid;
  }

  // Overload != operator
  bool operator!=(const std::vector<std::vector<T>>& other) const
  {
    return grid != other;
  }

  // Overload = operator
  vector2D<T>& operator=(const vector2D<std::vector<T>>& other)
  {
    grid = other.grid;
    return *this;
  }

  // Overload = operator
  vector2D<T>& operator=(const std::vector<std::vector<T>>& other)
  {
    grid = other;
    return *this;
  }
    /*
  // Overload [] operator
  std::vector<T>& operator[](const size_type i)
  {
    return grid[i];
  }*/

private:
  std::vector<std::vector<T>> grid;
};
}  // namespace benlib

#endif  // BENLIB_VECTOR2D_HPP_
