#pragma once
#define _CXXPROJECT_MATRIX 1

#include <math.h>
#include <cstring>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

typedef int size_type;
#define vector std::vector

class ZeroDet : public std::exception {
    const char* what() const throw() { return "The determinant is zero\n"; }
};
class DiffSize : public std::exception {
    const char* what() const throw() { return "Matrix row or col do not match\n"; }
};
class NotSquare : public std::exception {
    const char* what() const throw() { return "Matrix is not a square\n"; }
};
class OutOfRange : public std::exception {
    const char* what() const throw() { return "Index out of range\n"; }
};

#define DET_CHECK(cond) \
    if (!(cond))        \
    throw ZeroDet()
#define SIZE_CHECK(cond) \
    if (!(cond))         \
    throw DiffSize()
#define SQUARE_CHECK(cond) \
    if (!(cond))           \
    throw NotSquare()
#define RANGE_CHECK(cond) \
    if (!(cond))          \
    throw OutOfRange()

//*Declare*

template <typename T>
class matrix {
private:
    T* data;
    size_type row;
    size_type col;

    class data_list {
    public:
        T default_value = (T)0;
        struct node {
            T val;
            size_type i;
            size_type j;
            node* next;
        } *head, * tail;
        data_list() { head = tail = new node{}; }
        ~data_list() {
            node* last, * tmp = head;
            while (tmp != NULL) {
                last = tmp;
                tmp = tmp->next;
                delete last;
            }
        }
        T& get(size_type i, size_type j) {
            node* tmp = head;
            while (tmp != NULL) {
                if (tmp->i == i && tmp->j == j)
                    return tmp->val;
                tmp = tmp->next;
            }
            return default_value;
        }
        void set(T v, size_type i, size_type j) {
            tail = tail->next = new node{ v, i, j, NULL };
        }
    } *sparseData;
    bool isSparse = false;

public:
    matrix<T>(size_type row_size = 1, size_type col_size = 1);
    matrix<T>(const T* arrays, size_type row_size, size_type col_size);
    matrix<T>(const matrix<T>& src);
    ~matrix<T>();

    matrix<T>& operator=(const matrix<T>& that);
    inline T& operator()(size_type i, size_type j) { return data[i * col + j]; }
    inline T operator()(size_type i, size_type j) const {
        return (isSparse) ? sparseData->get(i, j) : data[i * col + j];
    }


    // 1)-----------------
    // 稀疏矩阵转换
    bool toSparseMatrix(T default_value = (T)0);
    bool toNormalMatrix();

    // 3)-----------------
    // 矩阵加法
    matrix<T> operator+(const matrix<T>& other) const;
    // 矩阵减法
    matrix<T> operator-(const matrix<T>& other) const;
    // 标量乘法
    matrix<T> operator*(T tnum) const;
    // 标量除法
    matrix<T> operator/(T tnum) const;
    // 友元 标量乘法
    template <typename T1>
    friend matrix<T1> operator*(T1 tnum, const matrix<T1>& mat);

    // 转置
    matrix<T> transposition() const;
    // 共轭
    matrix<T> conjugation() const;
    // 2范数
    T norm2() const;

    // 元素级乘法
    matrix<T> multiply_element_wise(const matrix<T>& other) const;
    // 矩阵乘法（向量级乘法）
    matrix<T> operator*(const matrix<T>& other);
    // 矩阵-向量乘法
    vector<T> operator*(const vector<T>& other) const;
    // 友元 向量-矩阵乘法
    template <typename T1>
    friend vector<T1> operator*(const vector<T1>& vec, const matrix<T1>& mat);
    // 点积
    matrix<T> dot(const matrix<T>& other) const;
    // 叉积
    matrix<T> cross(const matrix<T>& other) const;

    // 4)-----------------
    // 最大值
    T max(size_type rowi = -1, size_type coli = -1) const;
    // 最小值
    T min(size_type rowi = -1, size_type coli = -1) const;
    // 求和
    T sum(size_type rowi = -1, size_type coli = -1) const;
    // 平均值
    T avg(size_type rowi = -1, size_type coli = -1) const;

    // 5)-----------------
    template <typename T1>
    friend void QR(const matrix<T1>& A, matrix<T1>& Q, matrix<T1>& R);
    template <typename T1>
    friend void Eig(const matrix<T1>& A,
        matrix<T1>& eigenVector,
        matrix<T1>& eigenValue);
    // 特征值
    matrix<T> eigenvalues() const;
    // 特征向量
    matrix<T> eigenvectors() const;
    // 迹
    T trace() const;
    // 代数余子式
    T algebraic_cofactor(size_type i, size_type j) const;
    // 逆
    matrix<T> inverse() const;
    // 行列式
    T determinant() const;

    // 6)-----------------
    // 索引
    vector<T> operator[](size_type n) const;
    // 整形
    matrix<T> reshape(size_type row_size, size_type col_size) const;
    // 切片
    matrix<T> slice_row(size_type, size_type) const;
    matrix<T> slice_col(size_type, size_type) const;
    matrix<T> slice(size_type, size_type, size_type, size_type) const;

    // 7)-----------------
    // 卷积
    typedef unsigned int Mode;
    enum { FULL, SAME, VALID };
    matrix<T> convolution(const matrix<T>& other, Mode mode = FULL) const;

    // 8)-----------------
    // 构造器：cv::Mat
    matrix<T>(const cv::Mat& src);
    // 转cv::mat
    cv::Mat toCVMat() const;

    // )-----------------
    // 输出
    template <typename T1>
    friend std::ostream& operator<<(std::ostream& cout, const matrix<T1>& mat);
};
