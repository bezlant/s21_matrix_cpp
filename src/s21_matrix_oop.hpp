#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <cmath>
#include <iostream>
#include <utility>

class S21Matrix {
  private:
    int32_t rows_, cols_;
    double *matrix_;

  public:
    S21Matrix();
    S21Matrix(int32_t rows, int32_t cols);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other) noexcept;
    ~S21Matrix();

    int32_t get_rows() const;
    int32_t get_cols() const;
    void set_rows(const int32_t &new_rows);
    void set_cols(const int32_t &new_cols);

    bool EqMatrix(const S21Matrix &other) const;
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);
    S21Matrix Transpose();
    double Determinant();
    S21Matrix CalcComplements();
    S21Matrix InverseMatrix();

    double *operator[](int32_t row) const;
    double &operator()(int32_t row, int32_t col);

    S21Matrix &operator+=(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other) const;

    S21Matrix &operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other) const;

    S21Matrix &operator*=(const S21Matrix &other);
    S21Matrix &operator*=(const double &value);
    S21Matrix operator*(const S21Matrix &other) const;
    S21Matrix operator*(const double &value) const;
    friend S21Matrix operator*(const double &value, const S21Matrix &matrix);

    bool operator==(const S21Matrix &other);

    S21Matrix &operator=(S21Matrix &&other) noexcept;
    S21Matrix &operator=(const S21Matrix &other) noexcept;
};

#endif  // SRC_S21_MATRIX_H_
