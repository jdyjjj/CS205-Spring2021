#ifndef _CXXPROJECT_MATRIX
#define _CXXPROJECT_MATRIX 1


#include <opencv2/core/mat.hpp>
#include <vector>
#define vector std::vector

typedef int size_type;

template <typename T>
class matrix {
   private:
    T** data;
    size_type row;
    size_type col;

   public:
    matrix<T>();
    matrix<T>(size_type row_size, size_type col_size);
    matrix<T>(const T** arrays);
    matrix<T>(const vector<T>&... vectors);
    matrix<T>(const martix<T>& src);
    // matrix<T>(const martix<T>& src, size_type s_row, size_type, s_col);

    // 3)-----------------
    // 矩阵加法
    matrix<T> operator+(const matrix<T>& other) const;
    // 矩阵减法
    matrix<T> operator-(const matrix<T>& other) const;
    // 标量乘法
    matrix<T> operator*(double num) const;
    matrix<T> operator*(T tnum) const;
    // 标量除法
    matrix<T> operator/(double num) const;
    matrix<T> operator/(T tnum) const;
    // 友元 标量乘法
    friend matrix<T> operator*(double num, const matrix<T>& mat);
    friend matrix<T> operator*(T tnum, const matrix<T>& mat);
    // 友元 标量除法
    friend matrix<T> operator/(double num, const matrix<T>& mat);
    friend matrix<T> operator/(T tnum, const matrix<T>& mat);

    // 转置
    matrix<T> transposition() const;
    // 共轭
    matrix<T> conjugation() const;

    // 元素级乘法
    matrix<T> multiply_element_wise(const matrix<T>& other) const;
    // 矩阵乘法（向量级乘法）
    matrix<T> operator*(const matrix<T>& other) const;
    // 矩阵-向量乘法
    matrix<T> operator*(const vector<T>& other) const;
    // 友元 向量-矩阵乘法
    friend matrix<T> operator*(const vector<T>& vec, const matrix<T>& mat);
    // 点积
    matrix<T> dot(const matrix<T>& other) const;
    // 叉积
    matrix<T> cross(const matrix<T>& other) const;

    // 4)-----------------
    // 最大值
    T max() const;
    T max(int row) const;
    // 最小值
    T min() const;
    T min(int row) const;
    // 求和
    T sum() const;
    T sum(int row) const;
    // 平均值
    T avg() const;
    T avg(int row) const;

    // 5)-----------------
    // 特征值
    T* eigenvalues() const;
    // 特征向量
    vector<T>* eigenvectors() const;
    // 迹
    T trace() const;
    // 逆
    matrix<T> inverse() const;
    // 行列式
    T determinant() const;

    // 6)-----------------
    // 索引
    vector<T> operator[](size_type __n) const;
    // 整形
    matrix<T> reshape() const;
    // 切片
    matrix<T> slice(size_type f, size_type r) const;

    // 7)-----------------
    // 卷积
    matrix<T> convolution(const matrix<T>& other) const;

    // 8)-----------------
    // 构造器：cv::Mat
    matrix<T>(const cv::Mat& src);
    // 转cv::mat
    cv::Mat toCVMat() const;
};

#endif
