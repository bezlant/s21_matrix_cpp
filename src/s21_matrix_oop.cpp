#include "s21_matrix_oop.hpp"

S21Matrix::S21Matrix() : _rows(16), _cols(16) {
    std::cout << "Basic Constructor" << std::endl;
    _matrix = new double[_rows * _cols]();
}

S21Matrix::S21Matrix(uint32_t rows, uint32_t cols) : _rows(rows), _cols(cols) {
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
        throw std::length_error("Array size can't be zero or below");

    S21Matrix tmp(new_rows, _cols);
    for (uint32_t i = 0; i < (_rows < new_rows ? _rows : new_rows); i++)
        for (uint32_t j = 0; j < _cols; j++)
            tmp[i][j] = (*this)[i][j];

    *this = std::move(tmp);
}

void S21Matrix::set_cols(const uint32_t &new_cols) {
    if (!new_cols)
        throw std::length_error("Array size can't be zero or below");

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
