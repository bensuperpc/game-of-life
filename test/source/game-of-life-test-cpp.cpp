#include <vector>

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

  gol.Reset();

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

  gol.Reset();

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

  gol.Reset();

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

  gol.Reset();

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

  golA.Reset();
  golB.Reset();

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

  golA.Reset();
  golB.Reset();

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

  golA.Reset();
  golB.Reset();

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

TEST(gol_cpp, resize_inscrease1)
{
  const auto width = 32;
  const auto height = 32;

  const auto NewWidth = 64;
  const auto NewHeight = 64;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, resize_inscrease2)
{
  const auto width = 6;
  const auto height = 32;

  const auto NewWidth = 128;
  const auto NewHeight = 64;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, resize_inscrease3)
{
  const auto width = 16;
  const auto height = 32;

  const auto NewWidth = 128;
  const auto NewHeight = 64;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, resize_decrease1)
{
  const auto width = 64;
  const auto height = 64;

  const auto NewWidth = 32;
  const auto NewHeight = 32;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, resize_decrease2)
{
  const auto width = 32;
  const auto height = 64;

  const auto NewWidth = 32;
  const auto NewHeight = 64;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, resize_decrease3)
{
  const auto width = 64;
  const auto height = 32;

  const auto NewWidth = 64;
  const auto NewHeight = 32;

  auto gol = benlib::Gol(width, height);
  gol.RandomFill();

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());

  gol.Resize(NewWidth, NewHeight);
  gol.RandomFill();

  EXPECT_EQ(NewWidth, gol.GetWidth());
  EXPECT_EQ(NewHeight, gol.GetHeight());
}

TEST(gol_cpp, constructor1)
{
  const auto width = 32;
  const auto height = 64;

  auto gol = benlib::Gol(width, height);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
}

TEST(gol_cpp, constructor2)
{
  const auto width = 64;
  const auto height = 32;

  std::vector<std::vector<uint8_t>> new_grid(width, std::vector<uint8_t>(height, 0));

  auto gol = benlib::Gol(new_grid);

  EXPECT_EQ(width, gol.GetWidth());
  EXPECT_EQ(height, gol.GetHeight());
}
