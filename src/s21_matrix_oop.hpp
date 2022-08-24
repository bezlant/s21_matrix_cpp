#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <iostream>

class S21Matrix {
  private:
    uint32_t _rows, _cols;
    double *_matrix;

  public:
    S21Matrix();
    S21Matrix(uint32_t rows, uint32_t cols);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other);
    ~S21Matrix();

    uint32_t get_rows() const;
    uint32_t get_cols() const;
    void set_rows(const uint32_t &new_rows);
    void set_cols(const uint32_t &new_cols);

    bool eq_matrix(const S21Matrix &other);
    void sum_matrix(const S21Matrix &other);
    void sub_matrix(const S21Matrix &other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix &other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    double *operator[](uint32_t row);
    double &operator()(uint32_t row, uint32_t col);
    S21Matrix &operator+=(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other);
    S21Matrix &operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other);
};

#endif  // SRC_S21_MATRIX_H_
