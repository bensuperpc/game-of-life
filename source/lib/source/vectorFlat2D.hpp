#ifndef BENLIB_VECTORFLAT2D_HPP_
#define BENLIB_VECTORFLAT2D_HPP_

#include <algorithm>  // std::copy, std::move, std::fill
#include <vector>  // std::vector

namespace benlib
{
template<class T>
class vectorFlat2D
{
public:
  using size_type = typename std::vector<T>::size_type;

  // Constructor with no arguments.
  vectorFlat2D() {}

  // Constructor with width and height.
  vectorFlat2D(const size_type width, const size_type height)
  {
    this->width = width;
    this->height = height;
    std::vector<T> new_grid(width * height, 0);
    grid = std::move(new_grid);
  }

  // Constructor with width, height and value
  vectorFlat2D(const size_type width, const size_type height, const T value)
  {
    this->width = width;
    this->height = height;
    std::vector<T> new_grid(width * height, value);
    grid = std::move(new_grid);
  }

  // Constructor with a 2D vector.
  vectorFlat2D(const std::vector<std::vector<T>>& _grid)
  {
    this->width = _grid.size();
    this->height = _grid[0].size();
    std::vector<T> new_grid(width * height, 0);
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid[i].begin(), _grid[i].end(), new_grid.begin() + i * height);
    }
  }

  // Constructor with a 1D vector.
  vectorFlat2D(const std::vector<T>& _grid1D, const size_type width, const size_type height)
  {
    this->width = width;
    this->height = height;
    std::vector<T> new_grid(width * height, 0);
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid1D.begin() + i * height, _grid1D.begin() + (i + 1) * height, new_grid.begin() + i * height);
    }
  }

  // Constructor with a pointer to pointer and width and height.
  vectorFlat2D(T** _grid, const size_type width, const size_type height)
  {
    this->width = width;
    this->height = height;
    std::vector<T> new_grid(width * height, 0);
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid[i], _grid[i] + height, new_grid.begin() + i * height);
    }
  }

  // Destructor
  ~vectorFlat2D() {}

  // Fill with value
  void Fill(const T value)
  {
    std::fill(grid.begin(), grid.end(), value);
  }

  // Clear grid
  void Clear()
  {
    grid.clear();
  }

  // ShrinkToFit grid
  void ShrinkToFit()
  {
    grid.shrink_to_fit();
  }

  // Get width
  size_type GetWidth() const
  {
    return width;
  }

  // Get height
  size_type GetHeight() const
  {
    return height;
  }

  // Resize (Need more testing)
  void Resize(const size_type width, const size_type height)
  {
    // If old grid is same size as new grid, do nothing
    if (width == GetWidth() && height == GetHeight()) {
      return;

      std::vector<T> new_grid(width * height, 0);
      for (size_type i = 0; i < width; i++) {
        std::copy(grid.begin() + i * height, grid.begin() + (i + 1) * height, new_grid.begin() + i * height);
      }
      grid = std::move(new_grid);
    }
  }

  // Get grid pointer
  std::vector<T>* GetGridPtr()
  {
    return &grid;
  }

  // Get grid
  std::vector<std::vector<T>> GetGrid() const
  {
    std::vector<std::vector<T>> new_grid(width, std::vector<T>(height, 0));
    for (size_type i = 0; i < width; i++) {
      std::copy(grid.begin() + i * height, grid.begin() + (i + 1) * height, new_grid[i].begin());
    }
    return new_grid;
  }

  // Set grid
  void SetGrid(const std::vector<std::vector<T>>& _grid)
  {
    this->width = _grid.size();
    this->height = _grid[0].size();
    std::vector<T> new_grid(width * height, 0);
    for (size_type i = 0; i < width; i++) {
      std::copy(_grid[i].begin(), _grid[i].end(), new_grid.begin() + i * height);
    }
    grid = std::move(new_grid);
  }

  // Set grid
  void SetGrid(const std::vector<T>& _grid)
  {
    this->grid = _grid;
  }

  // Get grid 1D
  std::vector<T> GetGrid1D() const
  {
    return grid;
  }

  std::vector<T> GetGrid2D() const
  {
    std::vector<T> grid2D(width, 0);
    for (size_type i = 0; i < width; i++) {
      std::copy(grid.begin() + i * height, grid.begin() + (i + 1) * height, grid2D.begin() + i * height);
    }
    return grid2D;
  }

  // Get value
  T GetValue(const size_type x, const size_type y) const
  {
    return grid[x * height + y];
  }

  // Set value
  void SetValue(const size_type x, const size_type y, const T value)
  {
    grid[x * height + y] = value;
  }

  // Overload == operator
  bool operator==(const vectorFlat2D<T>& other) const
  {
    return grid == other.grid;
  }

  // Overload == operator
  bool operator==(const std::vector<std::vector<T>>& other) const
  {
    return GetGrid() == other;
  }

  // Overload != operator
  bool operator!=(const vectorFlat2D<T>& other) const
  {
    return grid != other.grid;
  }

  // Overload != operator
  bool operator!=(const std::vector<std::vector<T>>& other) const
  {
    return GetGrid() != other;
  }

  // Overload = operator
  vectorFlat2D<T>& operator=(const vectorFlat2D<T>& other)
  {
    grid = other.grid;
    return *this;
  }

  // Overload = operator
  vectorFlat2D<T>& operator=(const std::vector<std::vector<T>>& other)
  {
    SetGrid(other);
    return *this;
  }

  /*
  // Overload [] operator
  std::vector<T>& operator[](const size_type i)
  {
    return grid[i];
  }
  */

private:
  std::vector<T> grid;
  size_type width = 0;
  size_type height = 0;
};
}  // namespace benlib

#endif  // BENLIB_VECTORFLAT2D_HPP_
