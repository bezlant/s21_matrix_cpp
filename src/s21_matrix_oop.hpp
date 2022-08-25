#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <iostream>
#include <cmath>

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

    bool EqMatrix(const S21Matrix &other) const;
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    // TODO: All below
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();
    // TODO: All Above

    double *operator[](uint32_t row) const;
    double &operator()(uint32_t row, uint32_t col);

    S21Matrix &operator+=(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other) const;

    S21Matrix &operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other) const;

    // TODO: All below
    S21Matrix &operator*=(const S21Matrix &other);
    S21Matrix &operator*=(const double &value);
    S21Matrix operator*(const S21Matrix &other) const;
    S21Matrix operator*(const double &value) const;
    friend S21Matrix operator*(const double &value, const S21Matrix &matrix);
    // TODO: All above

    bool operator==(const S21Matrix &other);

    S21Matrix &operator=(S21Matrix &&other);
    S21Matrix &operator=(const S21Matrix &other);
};

#endif  // SRC_S21_MATRIX_H_
