#include "gtest/gtest.h"
#include "../s21_matrix_oop.hpp"

TEST(test_class, basic_constructor) {
    S21Matrix m;
    EXPECT_EQ(m.get_cols(), 16);
    EXPECT_EQ(m.get_rows(), 16);
}

TEST(test_class, rc_constructor) {
    S21Matrix m(69, 420);
    EXPECT_EQ(m.get_rows(), 69);
    EXPECT_EQ(m.get_cols(), 420);
}

TEST(test_class, copy_constructor) {
    S21Matrix m(12, 12);
    S21Matrix copy(m);

    EXPECT_EQ(copy.get_cols(), 12);
    EXPECT_EQ(copy.get_rows(), 12);
}

TEST(test_class, move_constructor) {
    S21Matrix m(12, 12);
    S21Matrix moved;
    moved = std::move(m);

    EXPECT_EQ(copy.get_cols(), 12);
    EXPECT_EQ(copy.get_rows(), 12);
}
