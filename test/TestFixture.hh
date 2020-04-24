#pragma once

#include <gtest/gtest.h>

struct TestFixture : public ::testing::Test
{
  virtual void SetUp() override
  {
  }
};