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

double *S21Matrix::operator[](uint32_t row) {
    if (row >= _rows)
        throw std::out_of_range("Incorrect input, index is out of range");

    return row * _cols + _matrix;
}

// TODO: Need tests
S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
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

// TODO: If = works need tests
void S21Matrix::set_rows(const uint32_t &new_rows) {
    S21Matrix tmp(new_rows, _cols);
    for (uint32_t i = 0; i < _rows < new_rows ? _rows : new_rows; i++)
        for (uint32_t j = 0; j < _cols; j++)
            tmp[i][j] = (*this)[i][j];

    *this = std::move(tmp);
}

void S21Matrix::set_cols(const uint32_t &cols) {
}
