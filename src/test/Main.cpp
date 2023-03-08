# Runner for googleTest
# This file is only needed if the IDE does not provide a runner on its own
# e.g. Clion does, NetBeans does not

#include <limits.h>
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
