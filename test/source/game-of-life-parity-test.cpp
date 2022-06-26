#include <vector>

#include "gol.h"
#include "gol.hpp"
#include "gtest/gtest.h"

TEST(gol_parity, basic1)
{
  const auto width = 64;
  const auto height = 64;
  const auto cells = width * height;

  bool** golC = CreateGrid(width, height);
  ResetGrid(golC, width, height);

  benlib::Gol golCPP(width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golCPP.SetCell(i, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 10; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  ResetGrid(golC, width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golC[width - i - 1][i] = true;

    golCPP.SetCell(i, i, 1);
    golCPP.SetCell(width - i - 1, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 50; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  FreeGrid(golC, width);
}

TEST(gol_parity, basic2)
{
  const auto width = 128;
  const auto height = 128;
  const auto cells = width * height;

  bool** golC = CreateGrid(width, height);
  ResetGrid(golC, width, height);

  benlib::Gol golCPP(width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golCPP.SetCell(i, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 10; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  ResetGrid(golC, width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golC[width - i - 1][i] = true;

    golCPP.SetCell(i, i, 1);
    golCPP.SetCell(width - i - 1, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 50; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  FreeGrid(golC, width);
}

TEST(gol_parity, basic3)
{
  const auto width = 128;
  const auto height = 64;
  const auto cells = width * height;

  bool** golC = CreateGrid(width, height);
  ResetGrid(golC, width, height);

  benlib::Gol golCPP(width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golCPP.SetCell(i, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 10; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  ResetGrid(golC, width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golC[width - i - 1][i] = true;

    golCPP.SetCell(i, i, 1);
    golCPP.SetCell(width - i - 1, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 50; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  FreeGrid(golC, width);
}

TEST(gol_parity, basic4)
{
  const auto width = 64;
  const auto height = 128;
  const auto cells = width * height;

  bool** golC = CreateGrid(width, height);
  ResetGrid(golC, width, height);

  benlib::Gol golCPP(width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golCPP.SetCell(i, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 10; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  ResetGrid(golC, width, height);
  golCPP.Reset();

  for (uint64_t i = 0; i < std::min(height, width); i++) {
    golC[i][i] = true;
    golC[width - i - 1][i] = true;

    golCPP.SetCell(i, i, 1);
    golCPP.SetCell(width - i - 1, i, 1);
  }

  EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));

  // Update
  for (uint64_t i = 0; i < 50; i++) {
    UpdateGrid(golC, width, height);
    golCPP.Update();
    EXPECT_EQ(golCPP.GetLivingCells(), GetLivingCells(golC, width, height));
  }

  FreeGrid(golC, width);
}
