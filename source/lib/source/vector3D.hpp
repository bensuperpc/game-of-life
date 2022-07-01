#ifndef BENLIB_VECTOR3D_HPP_
#define BENLIB_VECTOR3D_HPP_

#include <algorithm>  // std::copy, std::move, std::fill
#include <vector>  // std::vector

namespace benlib
{
template<class T>
class vector3D
{
public:
  using size_type = typename std::vector<T>::size_type;

  // Constructor with no arguments.
  vector3D() {}

  // Constructor with width, height and depth.
  vector3D(const size_type width, const size_type height, const size_type depth)
  {
    std::vector<std::vector<std::vector<T>>> new_grid(width,
                                                      std::vector<std::vector<T>>(height, std::vector<T>(depth, 0)));
    grid = std::move(new_grid);
  }

  // Constructor with width, height, depth and value
  vector3D(const size_type width, const size_type height, const size_type depth, const T value)
  {
    std::vector<std::vector<std::vector<T>>> new_grid(
        width, std::vector<std::vector<T>>(height, std::vector<T>(depth, value)));
    grid = std::move(new_grid);
  }

  // Constructor with a 3D vector.
  vector3D(const std::vector<std::vector<std::vector<T>>>& _grid)
  {
    this->grid = _grid;
  }

  // Constructor with a 2D vector.
  vector3D(const std::vector<T>& _grid1D, const size_type width, const size_type height, const size_type depth)
  {
    std::vector<std::vector<std::vector<T>>> new_grid(width,
                                                      std::vector<std::vector<T>>(height, std::vector<T>(depth, 0)));
    for (size_type i = 0; i < width; i++) {
      for (size_type j = 0; j < height; j++) {
        std::copy(_grid1D.begin() + i * height * depth + j * depth,
                  _grid1D.begin() + (i + 1) * height * depth + j * depth,
                  new_grid[i][j].begin());
      }
    }
    this->grid = std::move(new_grid);
  }

  // Constructor with a pointer to pointer and width and height.
  vector3D(T*** _grid, const size_type width, const size_type height, const size_type depth)
  {
    std::vector<std::vector<std::vector<T>>> new_grid(width,
                                                      std::vector<std::vector<T>>(height, std::vector<T>(depth, 0)));
    for (size_type i = 0; i < width; i++) {
      for (size_type j = 0; j < height; j++) {
        std::copy(_grid[i][j], _grid[i][j] + depth, new_grid[i][j].begin());
      }
    }
    this->grid = std::move(new_grid);
  }

  // Destructor
  ~vector3D() {}

  // Fill with value
  void Fill(const T value)
  {
    for (auto& i : grid) {
      for (auto& j : i) {
        std::fill(j.begin(), j.end(), value);
      }
    }
  }

  // Clear grid
  void Clear()
  {
    for (auto& i : grid) {
      for (auto& j : i) {
        j.clear();
      }
    }
    grid.clear();
  }

  // ShrinkToFit grid
  void ShrinkToFit()
  {
    for (auto& i : grid) {
      for (auto& j : i) {
        j.shrink_to_fit();
      }
    }
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

  // Get depth
  size_type GetDepth() const
  {
    return grid[0][0].size();
  }

  // Resize (Need more testing)
  void Resize(const size_type width, const size_type height, const size_type depth)
  {
    std::vector<std::vector<std::vector<T>>> new_grid(width,
                                                      std::vector<std::vector<T>>(height, std::vector<T>(depth, 0)));
    for (size_type i = 0; i < width; i++) {
      for (size_type j = 0; j < height; j++) {
        std::copy(grid[i][j].begin(), grid[i][j].end(), new_grid[i][j].begin());
      }
    }
    this->grid = std::move(new_grid);
  }

  // Overload == operator
  bool operator==(const vector3D<std::vector<T>>& other) const
  {
    return grid == other.grid;
  }

  // Overload != operator
  bool operator!=(const vector3D<std::vector<T>>& other) const
  {
    return grid != other.grid;
  }

  // Overload = operator
  vector3D<std::vector<T>>& operator=(const vector3D<std::vector<T>>& other)
  {
    grid = other.grid;
    return *this;
  }

  // Get grid pointer
  std::vector<std::vector<std::vector<T>>>* GetGridPtr()
  {
    return &grid;
  }

  // Get grid
  std::vector<std::vector<std::vector<T>>> GetGrid() const
  {
    return grid;
  }

  // Set grid
  void SetGrid(const std::vector<std::vector<std::vector<T>>>& _grid)
  {
    this->grid = _grid;
  }

  // Get grid 1D
  std::vector<T> GetGrid1D() const
  {
    std::vector<T> grid1D;
    for (auto& i : grid) {
      for (auto& j : i) {
        grid1D.insert(grid1D.end(), j.begin(), j.end());
      }
    }
    return grid1D;
  }

  // Get value
  T GetValue(const size_type x, const size_type y, const size_type z) const
  {
    return grid[x][y][z];
  }

  // Set value
  void SetValue(const size_type x, const size_type y, const size_type z, const T value)
  {
    grid[x][y][z] = value;
  }

  /*
  // Overload [] operator
  std::vector<T>& operator[](const size_type i)
  {
    return grid[i];
  }
  */

private:
  std::vector<std::vector<T>> grid;
};
}  // namespace benlib

#endif  // BENLIB_VECTOR2D_HPP_
