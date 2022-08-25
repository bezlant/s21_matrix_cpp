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
    S21Matrix moved(std::move(m));

    EXPECT_EQ(m.get_cols(), 0);
    EXPECT_EQ(m.get_rows(), 0);
    EXPECT_EQ(moved.get_cols(), 12);
    EXPECT_EQ(moved.get_rows(), 12);
}

TEST(test_class, brackets_operator) {
    S21Matrix m(6, 9);
    EXPECT_EQ(m(0, 0), 0);

    m(0, 1) = 69;
    EXPECT_EQ(m(0, 1), 69);

    m(5, 8) = 69.420;
    EXPECT_EQ(m(5, 8), 69.420);
}

TEST(test_class, square_brackets_operator) {
    S21Matrix m(6, 9);
    EXPECT_EQ(m[0][0], 0);

    m[5][5] = 69;
    EXPECT_EQ(m[5][5], 69);

    m[5][8] = 69.420;
    EXPECT_EQ(m[5][8], 69.420);
}

TEST(test_setters, set_rows_up) {
    S21Matrix m(2, 2);
    m[1][1] = 6.9;

    m.set_rows(5);
    EXPECT_EQ(m.get_rows(), 5);
    EXPECT_EQ(m[1][1], 6.9);
}

TEST(test_setters, set_rows_down) {
    S21Matrix m(2, 2);
    m[0][0] = 6.9;

    m.set_rows(1);
    EXPECT_EQ(m.get_rows(), 1);
    EXPECT_EQ(m[0][0], 6.9);
}

TEST(test_setters, set_rows_zero) {
    S21Matrix m;

    EXPECT_ANY_THROW(m.set_rows(0));
}

TEST(test_setters, set_cols_up) {
    S21Matrix m(2, 2);
    m[1][1] = 6.9;

    m.set_cols(5);
    EXPECT_EQ(m.get_cols(), 5);
    EXPECT_EQ(m[1][1], 6.9);
}

TEST(test_setters, set_cols_down) {
    S21Matrix m(2, 2);
    m[0][0] = 6.9;

    m.set_cols(1);
    EXPECT_EQ(m.get_cols(), 1);
    EXPECT_EQ(m[0][0], 6.9);
}

TEST(test_setters, set_cols_zero) {
    S21Matrix m;

    EXPECT_ANY_THROW(m.set_cols(0));
}

TEST(test_overload, equal_lvalue) {
    S21Matrix m;
    S21Matrix x(3, 6);
    x(1, 2) = 3;
    x(2, 2) = 3;

    m = x;

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 6);
    EXPECT_EQ(m(1, 2), 3);
    EXPECT_EQ(m(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
    S21Matrix m(2, 2);
    S21Matrix n;

    n = std::move(m);

    EXPECT_EQ(n.get_cols(), 2);
    EXPECT_EQ(n.get_rows(), 2);
}

TEST(test_functional, eq_matrix) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    ASSERT_TRUE(m == n);
}

TEST(test_functional, eq_matrix1) {
    S21Matrix m(3, 2);
    S21Matrix n;

    m[0][1] = 69;
    n = m;

    ASSERT_TRUE(m == n);
}

TEST(test_functional, sum_matrix) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m.SumMatrix(n);

    EXPECT_EQ(m(0, 0), 2);
    EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, add_operator_overload) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m = m + n;

    EXPECT_EQ(m(0, 0), 2);
    EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, eqadd_operator_overload) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m += m + n;

    EXPECT_EQ(m(0, 0), 3);
    EXPECT_EQ(m(1, 1), 3);
}

TEST(test_functional, sub_matrix) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m.SubMatrix(n);

    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, eqsub_overloaded_operator) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m -= n;

    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_operator_overload) {
    S21Matrix m(2, 2);
    S21Matrix n(2, 2);

    m(0, 0) = 1;
    n(0, 0) = 1;

    m(1, 1) = 1;
    n(1, 1) = 1;

    m = m - n;

    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, mul_matrices) {
    const uint32_t rows = 2;
    const uint32_t cols = 3;

    S21Matrix m(rows, cols);
    S21Matrix n(cols, rows);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = c++;

    // TODO: Remove all debug prints
    // for (uint32_t i = 0; i < m.get_rows(); i++)
    //     for (uint32_t j = 0; j < m.get_cols(); j++)
    //         std::cout << "m[" << i << "][" << j << "] = " << m[i][j]
    //                   << std::endl;
    // std::cout << "--------------------------" << std::endl;

    for (int i = 0, c = 7; i < cols; i++)
        for (int j = 0; j < rows; j++)
            n[i][j] = c++;

    // for (uint32_t i = 0; i < n.get_rows(); i++)
    //     for (uint32_t j = 0; j < n.get_cols(); j++)
    //         std::cout << "n[" << i << "][" << j << "] = " << n[i][j]
    //                   << std::endl;
    // std::cout << "--------------------------" << std::endl;

    m.MulMatrix(n);

    // for (uint32_t i = 0; i < m.get_rows(); i++)
    //     for (uint32_t j = 0; j < m.get_cols(); j++)
    //         std::cout << "m[" << i << "][" << j << "] = " << m[i][j]
    //                   << std::endl;

    S21Matrix res(2, 2);
    res[0][0] = 58;
    res[0][1] = 64;
    res[1][0] = 139;
    res[1][1] = 154;

    ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator) {
    const uint32_t rows = 2;
    const uint32_t cols = 3;

    S21Matrix m(rows, cols);
    S21Matrix n(cols, rows);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = c++;

    for (int i = 0, c = 7; i < cols; i++)
        for (int j = 0; j < rows; j++)
            n[i][j] = c++;

    m *= n;

    S21Matrix res(2, 2);
    res[0][0] = 58;
    res[0][1] = 64;
    res[1][0] = 139;
    res[1][1] = 154;

    ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator_num) {
    const uint32_t rows = 2;
    const uint32_t cols = 3;

    S21Matrix m(rows, cols);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = c++;

    m *= 2;

    S21Matrix res(2, 3);
    res[0][0] = 2;
    res[0][1] = 4;
    res[0][2] = 6;
    res[1][0] = 8;
    res[1][1] = 10;
    res[1][2] = 12;

    ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_operator) {
    const uint32_t rows = 2;
    const uint32_t cols = 3;

    S21Matrix m(rows, cols);
    S21Matrix n(cols, rows);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = c++;

    for (int i = 0, c = 7; i < cols; i++)
        for (int j = 0; j < rows; j++)
            n[i][j] = c++;

    m = m * n;

    S21Matrix res(2, 2);
    res[0][0] = 58;
    res[0][1] = 64;
    res[1][0] = 139;
    res[1][1] = 154;

    ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_operator_num) {
    const uint32_t rows = 2;
    const uint32_t cols = 3;

    S21Matrix m(rows, cols);

    for (int i = 0, c = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = c++;

    m = 2 * m;

    S21Matrix res(2, 3);
    res[0][0] = 2;
    res[0][1] = 4;
    res[0][2] = 6;
    res[1][0] = 8;
    res[1][1] = 10;
    res[1][2] = 12;

    ASSERT_TRUE(m == res);
}
