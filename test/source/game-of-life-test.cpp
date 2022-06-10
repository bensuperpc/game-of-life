#include <vector>

#include "gol.h"
#include "gol.hpp"
#include "gtest/gtest.h"

TEST(gol_cpp, basic1)
{
  const auto width = 3;
  const auto height = 3;
  const auto cells = width * height;

  auto gol = benlib::Gol(width, height);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
  EXPECT_EQ(cells, gol.GetCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Fill(false);

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Clear();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.SetCell(0, 0, true);
  gol.SetCell(1, 1, true);
  gol.SetCell(2, 2, true);

  EXPECT_EQ(true, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(true, gol.GetCell(2, 2));

  EXPECT_EQ(3, gol.GetLivingCells());
  EXPECT_EQ(6, gol.GetDeadCells());

  gol.Update();

  EXPECT_EQ(1, gol.GetLivingCells());
  EXPECT_EQ(8, gol.GetDeadCells());
  EXPECT_EQ(false, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(false, gol.GetCell(2, 2));

  gol.Update();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());
}

TEST(gol_cpp, basic2)
{
  const auto width = 100;
  const auto height = 100;
  const auto cells = width * height;

  auto gol = benlib::Gol(width, height);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
  EXPECT_EQ(cells, gol.GetCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Fill(false);

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Clear();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.SetCell(0, 0, true);
  gol.SetCell(1, 1, true);
  gol.SetCell(2, 2, true);

  EXPECT_EQ(true, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(true, gol.GetCell(2, 2));

  EXPECT_EQ(3, gol.GetLivingCells());
  EXPECT_EQ(9997, gol.GetDeadCells());

  gol.Update();

  EXPECT_EQ(1, gol.GetLivingCells());
  EXPECT_EQ(9999, gol.GetDeadCells());
  EXPECT_EQ(false, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(false, gol.GetCell(2, 2));

  gol.Update();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());
}

TEST(gol_cpp, basic3)
{
  const auto width = 5;
  const auto height = 20;
  const auto cells = width * height;

  auto gol = benlib::Gol(width, height);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
  EXPECT_EQ(cells, gol.GetCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Fill(false);

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Clear();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.SetCell(0, 0, true);
  gol.SetCell(1, 1, true);
  gol.SetCell(2, 2, true);

  EXPECT_EQ(true, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(true, gol.GetCell(2, 2));

  EXPECT_EQ(3, gol.GetLivingCells());
  EXPECT_EQ(97, gol.GetDeadCells());

  gol.Update();

  EXPECT_EQ(1, gol.GetLivingCells());
  EXPECT_EQ(99, gol.GetDeadCells());
  EXPECT_EQ(false, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(false, gol.GetCell(2, 2));

  gol.Update();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());
}

TEST(gol_cpp, basic4)
{
  const auto width = 20;
  const auto height = 5;
  const auto cells = width * height;

  auto gol = benlib::Gol(width, height);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
  EXPECT_EQ(cells, gol.GetCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Fill(false);

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.Fill(true);

  EXPECT_EQ(cells, gol.GetLivingCells());
  EXPECT_EQ(0, gol.GetDeadCells());

  gol.Clear();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());

  gol.SetCell(0, 0, true);
  gol.SetCell(1, 1, true);
  gol.SetCell(2, 2, true);

  EXPECT_EQ(true, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(true, gol.GetCell(2, 2));

  EXPECT_EQ(3, gol.GetLivingCells());
  EXPECT_EQ(97, gol.GetDeadCells());

  gol.Update();

  EXPECT_EQ(1, gol.GetLivingCells());
  EXPECT_EQ(99, gol.GetDeadCells());
  EXPECT_EQ(false, gol.GetCell(0, 0));
  EXPECT_EQ(true, gol.GetCell(1, 1));
  EXPECT_EQ(false, gol.GetCell(2, 2));

  gol.Update();

  EXPECT_EQ(0, gol.GetLivingCells());
  EXPECT_EQ(cells, gol.GetDeadCells());
}

TEST(gol_cpp, overload_op1)
{
  const auto width = 256;
  const auto height = 256;

  auto golA = benlib::Gol(width, height);
  auto golB = benlib::Gol(width, height);

  golA.RandomFill();
  golB.RandomFill();

  EXPECT_EQ(false, golA == golB);
  EXPECT_EQ(true, golA != golB);

  golA = golB;
  EXPECT_EQ(true, golA == golB);
  EXPECT_EQ(false, golA != golB);

  golA.SetCell(0, 0, true);
  EXPECT_EQ(true, golA(0, 0));
}

TEST(gol_cpp, overload_op2)
{
  const auto width = 384;
  const auto height = 384;

  auto golA = benlib::Gol(width, height);
  auto golB = benlib::Gol(width, height);

  golA.RandomFill();
  golB.RandomFill();

  EXPECT_EQ(false, golA == golB);
  EXPECT_EQ(true, golA != golB);

  golA = golB;
  EXPECT_EQ(true, golA == golB);
  EXPECT_EQ(false, golA != golB);

  golA.SetCell(0, 0, true);
  EXPECT_EQ(true, golA(0, 0));
}

TEST(gol_cpp, huge1)
{
  const auto width = 512;
  const auto height = 512;

  auto golA = benlib::Gol(width, height);

  golA.RandomFill();
  auto golB = golA;

  for (auto i = 0; i < 5; ++i) {
    golA.Update();
  }

  EXPECT_EQ(false, golA == golB);
  EXPECT_EQ(true, golA != golB);

  golA.Clear();
  golB.Clear();

  EXPECT_EQ(0, golA.GetLivingCells());
  EXPECT_EQ(0, golB.GetLivingCells());
}

TEST(gol_cpp, huge2)
{
  const auto width = 1024;
  const auto height = 384;

  auto golA = benlib::Gol(width, height);

  golA.RandomFill();
  auto golB = golA;

  for (auto i = 0; i < 5; ++i) {
    golA.Update();
  }

  EXPECT_EQ(false, golA == golB);
  EXPECT_EQ(true, golA != golB);

  golA.Clear();
  golB.Clear();

  EXPECT_EQ(0, golA.GetLivingCells());
  EXPECT_EQ(0, golB.GetLivingCells());
}

TEST(gol_cpp, huge3)
{
  const auto width = 384;
  const auto height = 1024;

  auto golA = benlib::Gol(width, height);

  golA.RandomFill();
  auto golB = golA;

  for (auto i = 0; i < 5; ++i) {
    golA.Update();
  }

  EXPECT_EQ(false, golA == golB);
  EXPECT_EQ(true, golA != golB);

  golA.Clear();
  golB.Clear();

  EXPECT_EQ(0, golA.GetLivingCells());
  EXPECT_EQ(0, golB.GetLivingCells());
}

TEST(gol_cpp, serialization1)
{
  const auto width = 256;
  const auto height = 256;

  auto golA = benlib::Gol(width, height);
  golA.RandomFill();

  auto golB = benlib::Gol(width, height);
  golB.RandomFill();

  golA.Serialize("serialization1_cpp.txt");
  golB.Deserialize("serialization1_cpp.txt");

  EXPECT_EQ(golA, golB);
}

TEST(gol_cpp, serialization2)
{
  const auto width = 128;
  const auto height = 512;

  auto golA = benlib::Gol(width, height);
  golA.RandomFill();

  auto golB = benlib::Gol(width, height);
  golB.RandomFill();

  golA.Serialize("serialization2_cpp.txt");
  golB.Deserialize("serialization2_cpp.txt");

  EXPECT_EQ(golA, golB);
}

TEST(gol_cpp, serialization3)
{
  const auto width = 512;
  const auto height = 128;

  auto golA = benlib::Gol(width, height);
  golA.RandomFill();

  auto golB = benlib::Gol(width, height);
  golB.RandomFill();

  golA.Serialize("serialization3_cpp.txt");
  golB.Deserialize("serialization3_cpp.txt");

  EXPECT_EQ(golA, golB);
}

TEST(gol_c, basic1)
{
  const auto width = 3;
  const auto height = 3;
  const auto cells = width * height;

  bool** gol = CreateGrid(width, height);

  FillGrid(gol, width, height, true);

  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, false);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, true);
  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  ResetGrid(gol, width, height);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  gol[0][0] = true;
  gol[1][1] = true;
  gol[2][2] = true;

  EXPECT_EQ(true, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(true, gol[2][2]);

  EXPECT_EQ(3, GetLivingCells(gol, width, height));
  EXPECT_EQ(6, GetDeadCells(gol, width, height));

  UpdateGrid(gol, width, height);

  EXPECT_EQ(1, GetLivingCells(gol, width, height));
  EXPECT_EQ(8, GetDeadCells(gol, width, height));
  EXPECT_EQ(false, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(false, gol[2][2]);

  UpdateGrid(gol, width, height);
  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FreeGrid(gol, width);
}

TEST(gol_c, basic2)
{
  const auto width = 100;
  const auto height = 100;
  const auto cells = width * height;

  bool** gol = CreateGrid(width, height);

  FillGrid(gol, width, height, true);

  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, false);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, true);
  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  ResetGrid(gol, width, height);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  gol[0][0] = true;
  gol[1][1] = true;
  gol[2][2] = true;

  EXPECT_EQ(true, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(true, gol[2][2]);

  EXPECT_EQ(3, GetLivingCells(gol, width, height));
  EXPECT_EQ(9997, GetDeadCells(gol, width, height));

  UpdateGrid(gol, width, height);

  EXPECT_EQ(1, GetLivingCells(gol, width, height));
  EXPECT_EQ(9999, GetDeadCells(gol, width, height));
  EXPECT_EQ(false, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(false, gol[2][2]);

  UpdateGrid(gol, width, height);
  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FreeGrid(gol, width);
}

TEST(gol_c, basic3)
{
  const auto width = 5;
  const auto height = 20;
  const auto cells = width * height;

  bool** gol = CreateGrid(width, height);

  FillGrid(gol, width, height, true);

  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, false);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, true);
  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  ResetGrid(gol, width, height);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  gol[0][0] = true;
  gol[1][1] = true;
  gol[2][2] = true;

  EXPECT_EQ(true, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(true, gol[2][2]);

  EXPECT_EQ(3, GetLivingCells(gol, width, height));
  EXPECT_EQ(97, GetDeadCells(gol, width, height));

  UpdateGrid(gol, width, height);

  EXPECT_EQ(1, GetLivingCells(gol, width, height));
  EXPECT_EQ(99, GetDeadCells(gol, width, height));
  EXPECT_EQ(false, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(false, gol[2][2]);

  UpdateGrid(gol, width, height);
  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FreeGrid(gol, width);
}

TEST(gol_c, basic4)
{
  const auto width = 20;
  const auto height = 5;
  const auto cells = width * height;

  bool** gol = CreateGrid(width, height);

  FillGrid(gol, width, height, true);

  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, false);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FillGrid(gol, width, height, true);
  EXPECT_EQ(cells, GetLivingCells(gol, width, height));
  EXPECT_EQ(0, GetDeadCells(gol, width, height));

  ResetGrid(gol, width, height);

  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  gol[0][0] = true;
  gol[1][1] = true;
  gol[2][2] = true;

  EXPECT_EQ(true, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(true, gol[2][2]);

  EXPECT_EQ(3, GetLivingCells(gol, width, height));
  EXPECT_EQ(97, GetDeadCells(gol, width, height));

  UpdateGrid(gol, width, height);

  EXPECT_EQ(1, GetLivingCells(gol, width, height));
  EXPECT_EQ(99, GetDeadCells(gol, width, height));
  EXPECT_EQ(false, gol[0][0]);
  EXPECT_EQ(true, gol[1][1]);
  EXPECT_EQ(false, gol[2][2]);

  UpdateGrid(gol, width, height);
  EXPECT_EQ(0, GetLivingCells(gol, width, height));
  EXPECT_EQ(cells, GetDeadCells(gol, width, height));

  FreeGrid(gol, width);
}

TEST(gol_c, huge1)
{
  const auto width = 512;
  const auto height = 512;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);

  CopyGrid(golA, golB, width, height);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));
  EXPECT_EQ(true, GetLivingCells(golA, width, height) == GetLivingCells(golB, width, height));

  for (auto i = 0; i < 5; ++i) {
    UpdateGrid(golA, width, height);
  }

  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));
  EXPECT_EQ(false, GetLivingCells(golA, width, height) == GetLivingCells(golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, huge2)
{
  const auto width = 384;
  const auto height = 256;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);

  CopyGrid(golA, golB, width, height);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));
  EXPECT_EQ(true, GetLivingCells(golA, width, height) == GetLivingCells(golB, width, height));

  for (auto i = 0; i < 5; ++i) {
    UpdateGrid(golA, width, height);
  }

  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));
  EXPECT_EQ(false, GetLivingCells(golA, width, height) == GetLivingCells(golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization_empty1)
{
  const auto width = 256;
  const auto height = 256;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  std::string str = "serialization_empty1_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);

  Deserialize(golB, width, height, fileName);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization_empty2)
{
  const auto width = 255;
  const auto height = 64;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  std::string str = "serialization_empty2_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);

  Deserialize(golB, width, height, fileName);
  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization_empty3)
{
  const auto width = 64;
  const auto height = 255;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  std::string str = "serialization_empty3_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);

  Deserialize(golB, width, height, fileName);
  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization1)
{
  const auto width = 32;
  const auto height = 32;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);
  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));

  std::string str = "serialization1_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);
  Deserialize(golB, width, height, fileName);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization2)
{
  const auto width = 256;
  const auto height = 256;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);
  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));

  std::string str = "serialization2_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);
  Deserialize(golB, width, height, fileName);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization3)
{
  const auto width = 128;
  const auto height = 384;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);
  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));

  std::string str = "serialization3_c.txt";
  const char* fileName = str.data();

  Serialize(golA, width, height, fileName);
  Deserialize(golB, width, height, fileName);
  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, serialization4)
{
  const auto width = 384;
  const auto height = 128;

  bool** golA = CreateGrid(width, height);
  bool** golB = CreateGrid(width, height);

  RandomFill(golA, width, height);
  EXPECT_EQ(false, IsEqualGrid(golA, golB, width, height));

  std::string str = "serialization4_c.txt";
  const char* fileName = str.data();
  Serialize(golA, width, height, fileName);
  Deserialize(golB, width, height, fileName);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, width, height));

  FreeGrid(golA, width);
  FreeGrid(golB, width);
}

TEST(gol_c, resizegrid_same1)
{
  const auto width = 32;
  const auto height = 32;

  const auto newWidth = 32;
  const auto newHeight = 32;

  bool** golA = CreateGrid(width, height);

  RandomFill(golA, width, height);

  bool** golB = CreateGrid(newWidth, newHeight);

  CopyGrid(golA, golB, (width < newWidth) ? width : newWidth, (height < newHeight) ? height : newHeight);

  golA = ResizeGrid(golA, width, height, newWidth, newHeight);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, newWidth, newHeight));

  FreeGrid(golA, newWidth);
  FreeGrid(golB, newWidth);
}

TEST(gol_c, resizegrid_increase1)
{
  const auto width = 32;
  const auto height = 32;

  const auto newWidth = 64;
  const auto newHeight = 64;

  bool** golA = CreateGrid(width, height);

  RandomFill(golA, width, height);

  bool** golB = CreateGrid(newWidth, newHeight);

  CopyGrid(golA, golB, (width < newWidth) ? width : newWidth, (height < newHeight) ? height : newHeight);

  golA = ResizeGrid(golA, width, height, newWidth, newHeight);

  EXPECT_EQ(false, IsEqualGrid(golA, golB, newWidth, newHeight));

  FreeGrid(golA, newWidth);
  FreeGrid(golB, newWidth);
}

TEST(gol_c, resizegrid_increase2)
{
  const auto width = 128;
  const auto height = 32;

  const auto newWidth = 16;
  const auto newHeight = 64;

  bool** golA = CreateGrid(width, height);

  RandomFill(golA, width, height);

  bool** golB = CreateGrid(newWidth, newHeight);

  CopyGrid(golA, golB, (width < newWidth) ? width : newWidth, (height < newHeight) ? height : newHeight);

  golA = ResizeGrid(golA, width, height, newWidth, newHeight);

  EXPECT_EQ(false, IsEqualGrid(golA, golB, newWidth, newHeight));

  FreeGrid(golA, newWidth);
  FreeGrid(golB, newWidth);
}

TEST(gol_c, resizegrid_reduce1)
{
  const auto width = 64;
  const auto height = 64;

  const auto newWidth = 32;
  const auto newHeight = 32;

  bool** golA = CreateGrid(width, height);

  RandomFill(golA, width, height);

  bool** golB = CreateGrid(newWidth, newHeight);

  CopyGrid(golA, golB, (width < newWidth) ? width : newWidth, (height < newHeight) ? height : newHeight);

  golA = ResizeGrid(golA, width, height, newWidth, newHeight);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, newWidth, newHeight));

  FreeGrid(golA, newWidth);
  FreeGrid(golB, newWidth);
}

TEST(gol_c, resizegrid_reduce2)
{
  const auto width = 64;
  const auto height = 128;

  const auto newWidth = 32;
  const auto newHeight = 96;

  bool** golA = CreateGrid(width, height);

  RandomFill(golA, width, height);

  bool** golB = CreateGrid(newWidth, newHeight);

  CopyGrid(golA, golB, (width < newWidth) ? width : newWidth, (height < newHeight) ? height : newHeight);

  golA = ResizeGrid(golA, width, height, newWidth, newHeight);

  EXPECT_EQ(true, IsEqualGrid(golA, golB, newWidth, newHeight));

  FreeGrid(golA, newWidth);
  FreeGrid(golB, newWidth);
}
