#ifndef BENLIB_MULTIDIMVECTOR_HPP_
#define BENLIB_MULTIDIMVECTOR_HPP_

#include <algorithm>  // std::move, std::copy, std::fill
#include <cstdarg>  // std::va_list, std::va_start, std::va_end
#include <numeric>  // std::reduce
#include <vector>  // std::vector

namespace benlib
{
template<typename T>
class MultiVector;

template<typename T>
class MultiVectorView
{
public:
  MultiVectorView(MultiVector<T>& vec_, size_t index_, size_t dimension_)
      : vec(vec_)
      , index(index_)
      , dimension(dimension_)
  {
  }

  MultiVector<T>& vec;
  size_t index;
  size_t dimension;

  MultiVectorView& operator[](std::size_t n_index)
  {
    size_t index_multiplyer = 1;
    for (size_t i = 0; i < dimension; ++i)
      index_multiplyer *= vec.dimensions[i];
    index += n_index * index_multiplyer;
    dimension++;
    return *this;
  }

  operator T()
  {
    return vec.content[index];
  }

  MultiVectorView& operator=(T val)
  {
    vec.content[index] = val;
    return *this;
  }
  ~MultiVectorView() {}
};

template<typename T>
class MultiVector
{
public:
  MultiVector() {}

  MultiVector(std::vector<size_t> dimensions_)
      : dimensions(dimensions_)
  {
    /*
    size_t size = dimensions[0];
    for (size_t i = 1; i < dimensions.size(); ++i)
      size *= dimensions[i];
    */
    size_t size = std::reduce(dimensions_.begin(), dimensions_.end(), 1, std::multiplies<size_t>());

    content.resize(size);
  }

  MultiVector(std::vector<size_t> dimensions_, std::vector<T> content_)
      : dimensions(dimensions_)
      , content(content_)
  {
    /*
    if (content.size() != std::reduce(dimensions_.begin(), dimensions_.end(), 1, std::multiplies<size_t>()))
      throw std::runtime_error("MultiVector: content size does not match dimensions");
    */
  }

  // Variadic constructor
  MultiVector(int argSize, ...)
  {
    va_list args;
    va_start(args, argSize);
    dimensions.resize(argSize);
    for (int i = 0; i < argSize; ++i)
      dimensions[i] = va_arg(args, int);
    va_end(args);

    size_t size = dimensions[0];
    for (size_t i = 1; i < dimensions.size(); ++i)
      size *= dimensions[i];

    content.resize(size);
  }

  // Resize
  void Resize(std::vector<size_t> dimensions_)
  {
    dimensions = dimensions_;
    size_t size = dimensions[0];
    for (size_t i = 1; i < dimensions.size(); ++i)
      size *= dimensions[i];

    content.resize(size);
  }

  void Fill(const T value)
  {
    std::fill(content.begin(), content.end(), value);
  }

  void Clear()
  {
    content.clear();
  }

  std::vector<T>& GetGrid()
  {
    return content;
  }

  void SetGrid(const std::vector<T>& grid_)
  {
    content = grid_;
  }

  std::vector<T>* GetGridPtr()
  {
    return &content;
  }

  std::vector<T> CopyGrid()
  {
    return content;
  }

  std::vector<size_t>& GetDim()
  {
    return dimensions;
  }

  void SetDim(const std::vector<size_t>& dimensions_)
  {
    dimensions = dimensions_;
  }

  T GetValue(const std::vector<size_t>& indices)
  {
    size_t index = 0;
    size_t index_multiplyer = 1;
    for (size_t i = 0; i < dimensions.size(); ++i) {
      index += indices[i] * index_multiplyer;
      index_multiplyer *= dimensions[i];
    }
    return content[index];
  }

  T GetValue(const size_t index)
  {
    return content[index];
  }

  void SetValue(const std::vector<size_t>& indices, T value)
  {
    size_t index = 0;
    size_t index_multiplyer = 1;
    for (size_t i = 0; i < dimensions.size(); ++i) {
      index += indices[i] * index_multiplyer;
      index_multiplyer *= dimensions[i];
    }
    content[index] = value;
  }

  void SetValue(size_t index, T value)
  {
    content[index] = value;
  }

  bool IsEqual(const MultiVector<T>& other)
  {
    if (dimensions != other.dimensions) {
      return false;
    }
    if (content != other.content) {
      return false;
    }
    return true;
  }

  MultiVectorView<T> operator[](size_t index)
  {
    return MultiVectorView<T>(*this, index, 1);
  }

  // Overload = operator
  MultiVector<T>& operator=(const MultiVector<T>& other)
  {
    if (this != &other) {
      content = other.content;
      dimensions = other.dimensions;
    }
    return *this;
  }

  // Overload == operator
  bool operator==(const MultiVector<T>& other) const
  {
    return content == other.content && dimensions == other.dimensions;
  }

  // Overload != operator
  bool operator!=(const MultiVector<T>& other) const
  {
    return content != other.content || dimensions != other.dimensions;
  }

  std::vector<T> content;
  std::vector<size_t> dimensions;
};

}  // namespace benlib
#endif  // BENLIB_VECTORFLAT2D_HPP_
