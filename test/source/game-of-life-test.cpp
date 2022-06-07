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
