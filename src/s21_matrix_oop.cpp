#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : _rows(16), _cols(16) {
    std::cout << "Basic Constructor" << std::endl;
    _matrix = new double[_rows * _cols]();
}

S21Matrix::S21Matrix(uint32_t rows, uint32_t cols) : _rows(rows), _cols(cols) {
    if (_rows == 0 || _cols == 0)
        throw std::length_error("Array size can't be zero");

    std::cout << "Rows & Cols Constructor" << std::endl;
    _matrix = new double[_rows * _cols]();
}

S21Matrix::~S21Matrix() {
    std::cout << "Destructor" << std::endl;
    delete[] _matrix;
}

S21Matrix::S21Matrix(const S21Matrix &other) {
    std::cout << "Copy Constructor" << std::endl;
    _rows = other._rows;
    _cols = other._cols;

    _matrix = new double[_rows * _cols]();
    std::memcpy(_matrix, other._matrix, _rows * _cols * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&other) {
    std::cout << "Move Constructor" << std::endl;
    _rows = other._rows;
    _cols = other._cols;
    _matrix = other._matrix;

    other._matrix = nullptr;
    other._rows = 0;
    other._cols = 0;
}

uint32_t S21Matrix::get_rows() const {
    return _rows;
}

uint32_t S21Matrix::get_cols() const {
    return _cols;
}

double &S21Matrix::operator()(uint32_t row, uint32_t col) {
    if (row >= _rows || col >= _cols)
        throw std::out_of_range("Incorrect input, index is out of range");

    return _matrix[row * _cols + col];
}

double *S21Matrix::operator[](uint32_t row) const {
    if (row >= _rows)
        throw std::out_of_range("Incorrect input, index is out of range");

    return row * _cols + _matrix;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
    std::cout << "[rvalue] equal operator" << std::endl;
    if (this != &other) {
        delete[] _matrix;

        _rows = other._rows;
        _cols = other._cols;
        _matrix = other._matrix;

        other._matrix = nullptr;
        other._rows = 0;
        other._cols = 0;
    }
    return *this;
}

void S21Matrix::set_rows(const uint32_t &new_rows) {
    if (!new_rows)
        throw std::length_error("Array size can't be zero");

    S21Matrix tmp(new_rows, _cols);
    for (uint32_t i = 0; i < (_rows < new_rows ? _rows : new_rows); i++)
        for (uint32_t j = 0; j < _cols; j++)
            tmp[i][j] = (*this)[i][j];

    *this = std::move(tmp);
}

void S21Matrix::set_cols(const uint32_t &new_cols) {
    if (!new_cols)
        throw std::length_error("Array size can't be zero");

    S21Matrix tmp(_rows, new_cols);
    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < (_cols < new_cols ? _cols : new_cols); j++)
            tmp[i][j] = (*this)[i][j];

    *this = std::move(tmp);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
    std::cout << "[lvalue] equal operator" << std::endl;
    if (this != &other) {
        delete[] _matrix;

        _rows = other._rows;
        _cols = other._cols;

        _matrix = new double[_rows * _cols]();
        std::memcpy(_matrix, other._matrix, _rows * _cols * sizeof(double));
    }
    return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
    return EqMatrix(other);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        return false;

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            if (std::fabs((*this)[i][j] - other[i][j]) > 1e-07)
                return false;

    return true;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
    SumMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        throw "Can't sum matrices of different dimensions";

    S21Matrix res(_rows, _cols);

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            res[i][j] = (*this)[i][j] + other[i][j];

    return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        throw "Can't sum matrices of different dimensions";

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            (*this)[i][j] += other[i][j];
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        throw "Can't subtract matrices of different dimensions";
    SubMatrix(other);
    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        throw "Can't subtract matrices of different dimensions";

    S21Matrix res(_rows, _cols);

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            res[i][j] = (*this)[i][j] - other[i][j];

    return res;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    if (_rows != other.get_rows() || _cols != other.get_cols())
        throw "Can't subtract matrices of different dimensions";

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            (*this)[i][j] -= other[i][j];
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
    MulMatrix(other);
    return *this;
}

S21Matrix &S21Matrix::operator*=(const double &value) {
    MulNumber(value);
    return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
    if (_cols != other.get_rows() || _rows != other.get_cols())
        throw "Dimensions don't fit for the multiplication";

    S21Matrix res(_rows, other._cols);

    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < other.get_cols(); j++)
            for (uint32_t k = 0; k < _cols; k++)
                res[i][j] += (*this)[i][k] * other[k][j];

    return res;
}

S21Matrix S21Matrix::operator*(const double &value) const {
    S21Matrix res(_rows, _cols);

    for (uint32_t i = 0; i < (*this).get_rows(); i++)
        for (uint32_t j = 0; j < (*this).get_cols(); j++)
            res[i][j] = (*this)[i][j] * value;

    return res;
}

S21Matrix operator*(const double &value, const S21Matrix &matrix) {
    uint32_t rows = matrix.get_rows();
    uint32_t cols = matrix.get_cols();
    S21Matrix res(rows, cols);

    for (uint32_t i = 0; i < rows; i++)
        for (uint32_t j = 0; j < cols; j++)
            res[i][j] = matrix[i][j] * value;

    return res;
}

void S21Matrix::MulNumber(const double num) {
    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < _cols; j++)
            (*this)[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
    if (_cols != other.get_rows() || _rows != other.get_cols())
        throw "Dimensions don't fit for the multiplication";

    S21Matrix res((*this)._rows, other.get_cols());

    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < other.get_cols(); j++)
            for (uint32_t k = 0; k < _cols; k++)
                res[i][j] += (*this)[i][k] * other[k][j];

    *this = std::move(res);
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix res(_cols, _rows);

    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < _cols; j++)
            res[j][i] = (*this)[i][j];

    return res;
}

namespace {

void get_cofactor(const S21Matrix &m, S21Matrix &tmp, uint32_t skip_row,
                  uint32_t skip_col, uint32_t size) {
    for (uint32_t i = 0, row = 0; row < size; row++) {
        for (uint32_t j = 0, col = 0; col < size; col++) {
            if (row != skip_row && col != skip_col) {
                tmp[i][j] = m[row][col];
                j++;
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double det(const S21Matrix &m, uint32_t size) {

    double res = 0;

    if (size == 1)
        return m[0][0];

    S21Matrix tmp(size, size);

    int sign = 1;
    for (uint32_t i = 0; i < size; i++) {
        get_cofactor(m, tmp, 0, i, size);
        res += sign * m[0][i] * det(tmp, size - 1);
        sign = -sign;
    }

    return res;
}

S21Matrix calc_complements(const S21Matrix &m) {
    const uint32_t rows = m.get_rows();
    const uint32_t cols = m.get_cols();

    if (rows == 1) {
        m[0][0] = 1;
        return m;
    }

    S21Matrix tmp(rows, cols);
    S21Matrix res(rows, cols);

    for (uint32_t i = 0; i < rows; i++) {
        for (uint32_t j = 0; j < cols; j++) {
            get_cofactor(m, tmp, i, j, rows);

            int sign = ((i + j) % 2 == 0) ? 1 : -1;

            res[i][j] = sign * det(tmp, rows - 1);
        }
    }
    return res;
}
}  // namespace

double S21Matrix::Determinant() {
    if ((*this)._rows != (*this)._cols)
        throw "The matrix is not square to calculate determinant";

    return det(*this, _rows);
}

S21Matrix S21Matrix::CalcComplements() {
    if ((*this)._rows != (*this)._cols)
        throw "The matrix is not square to calculate the complements";
    return calc_complements(*this);
}

S21Matrix S21Matrix::InverseMatrix() {
    double det = this->Determinant();
    if (_rows != _cols)
        throw "The matrix is not square to calculate the inverse";

    if (std::fabs(det) < 1e-06)
        throw "Determinant can't be zero to calculate inverse";

    S21Matrix adj_transposed = this->CalcComplements().Transpose();
    S21Matrix res(_rows, _cols);

    for (uint32_t i = 0; i < _rows; i++)
        for (uint32_t j = 0; j < _cols; j++)
            res[i][j] = adj_transposed[i][j] / det;

    return res;
}
