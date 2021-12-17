#ifndef _CXXPROJECT_MATRIX
#define _CXXPROJECT_MATRIX 1

#include <iostream>
#include <opencv2/core/mat.hpp>

#include <vector>
#define vector std::vector

typedef int size_type;
#define ASSERT(cond) \
    if (!(cond))     \
    throw "Matrix Dimensions Error!"

//*Declare*

template <typename T>
class matrix {
   private:
    T* data;
    size_type row;
    size_type col;

    // inline T get(size_type i, size_type j) const;
    // inline void set(size_type i, size_type j, const T& tnum);

   public:
    matrix<T>(size_type row_size, size_type col_size);
    matrix<T>(const T* arrays, size_type row_size, size_type col_size);
    matrix<T>(const matrix<T>& src);
    ~matrix<T>();

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
    template <typename T1>
    friend matrix<T1> operator*(double num, const matrix<T1>& mat);
    template <typename T1>
    friend matrix<T1> operator*(T1 tnum, const matrix<T1>& mat);

    // 转置
    matrix<T> transposition() const;
    // 共轭
    matrix<T> conjugation() const;

    // 元素级乘法
    matrix<T> multiply_element_wise(const matrix<T>& other) const;
    // 矩阵乘法（向量级乘法）
    matrix<T> operator*(const matrix<T>& other) const;
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
    matrix<T> reshape(size_type row_size, size_type col_size) const;
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

    // )-----------------
    // 输出
    template <typename T1>
    friend std::ostream& operator<<(std::ostream& cout, const matrix<T1>& mat);
};

//*Implement*

// template <typename T>
// inline T matrix<T>::get(size_type i, size_type j) const {
//     return data[i * col + j];
// }
// template <typename T>
// inline void matrix<T>::set(size_type i, size_type j, const T& tnum) {
//     data[i * col + j] = tnum;
// }

// 构造器
template <typename T>
matrix<T>::matrix(size_type row_size, size_type col_size) {
    ASSERT(row_size > 0 && col_size > 0);
    row = row_size;
    col = col_size;
    data = new T[row * col];
}
template <typename T>
matrix<T>::matrix(const T* arrays, size_type row_size, size_type col_size) {
    const T* A = arrays;
    ASSERT(row_size > 0 && col_size > 0);
    row = row_size;
    col = col_size;
    data = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        data[k] = A[k];
    }
}
template <typename T>
matrix<T>::matrix(const matrix<T>& src) {
    const T* A = src.data;
    row = src.row;
    col = src.col;
    data = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        data[k] = A[k];
    }
}
template <typename T>
matrix<T>::~matrix() {
    delete[] data;
}

// 3)-----------------
// 矩阵加法
template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& other) const {
    ASSERT(this->row == other.row && this->col == other.col);
    T* A = this->data;
    T* B = other.data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] + B[k];
    }
    return matrix(R, row, col);
}
// 矩阵减法
template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& other) const {
    ASSERT(this->row == other.row && this->col == other.col);
    T* A = this->data;
    T* B = other.data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] - B[k];
    }
    return matrix(R, row, col);
}
// 标量乘法
template <typename T>
matrix<T> matrix<T>::operator*(double num) const {
    T* A = this->data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] * num;
    }
    return matrix(R, row, col);
}
template <typename T>
matrix<T> matrix<T>::operator*(T tnum) const {
    T* A = this->data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] * tnum;
    }
    return matrix(R, row, col);
}
// 标量除法
template <typename T>
matrix<T> matrix<T>::operator/(double num) const {
    T* A = this->data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] / num;
    }
    return matrix(R, row, col);
}
template <typename T>
matrix<T> matrix<T>::operator/(T tnum) const {
    T* A = this->data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] / tnum;
    }
    return matrix(R, row, col);
}
// 友元 标量乘法
template <typename T>
matrix<T> operator*(double num, const matrix<T>& mat) {
    return mat * num;
}
template <typename T>
matrix<T> operator*(T tnum, const matrix<T>& mat) {
    return mat * tnum;
}

// 转置
template <typename T>
matrix<T> matrix<T>::transposition() const {
    T* A = this->data;
    T* R = new T[col * row];
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R[j * row + i] = A[i * col + j];
        }
    }
    return matrix(R, col, row);
}
// 共轭
template <typename T>
matrix<T> matrix<T>::conjugation() const {
    T* A = this->data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k].real - A[k].imag;
    }
    return matrix(R, row, col).transposition();
}

// 元素级乘法
template <typename T>
matrix<T> matrix<T>::multiply_element_wise(const matrix<T>& other) const {
    ASSERT(this->row == other.row && this->col == other.col);
    T* A = this->data;
    T* B = other.data;
    T* R = new T[row * col];
    for (size_type k = 0; k < row * col; k++) {
        R[k] = A[k] * B[k];
    }
    return matrix(R, row, col);
}
// 矩阵乘法（向量级乘法）
template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& other) const {
    ASSERT(this->col == other.row);
    T* A = this->data;
    T* B = other.data;
    T* R = new T[this->row * other.col];
    for (size_type i = 0; i < this->row; i++) {
        for (size_type j = 0; j < other.col; j++) {
            for (size_type k = 0; k < this->col; k++) {
                R[i * other.col + j] +=
                    A[i * this->col + k] * B[k * other.col + j];
            }
        }
    }
    return matrix(R, this->row, other.col);
}
// 矩阵-向量乘法
template <typename T>
vector<T> matrix<T>::operator*(const vector<T>& other) const {
    ASSERT(this->col == other.size);
    T* A = this->data;
    vector<T> B = other;
    vector<T> R(this->row);
    for (size_type i = 0; i < this->row; i++) {
        for (size_type k = 0; k < this->col; k++) {
            R[i] += A[i * this->col + k] * B[k];
        }
    }
    return R;
}
// 友元 向量-矩阵乘法
template <typename T>
vector<T> operator*(const vector<T>& vec, const matrix<T>& mat) {
    ASSERT(mat.size == mat.row);
    vector<T> A = mat;
    T* B = mat.data;
    vector<T> R(mat.col);
    for (size_type j = 0; j < mat.col; j++) {
        for (size_type k = 0; k < mat.row; k++) {
            R[j] += A[k] * B[k * mat.col + j];
        }
    }
    return R;
}
// 点积
template <typename T>
matrix<T> matrix<T>::dot(const matrix<T>& other) const {
    // TODO::

    return this->multiply_element_wise(other);
}
// 叉积
template <typename T>
matrix<T> matrix<T>::cross(const matrix<T>& other) const {
    // TODO::

    return *this * other;
}

// 4)-----------------
// 最大值
template <typename T>
T matrix<T>::max(size_type rowi, size_type coli) const {
    if (rowi >= 0 && coli >= 0) {
        return data[rowi * col + coli];
    } else if (rowi >= 0) {
        T max = data[rowi * col + 0];
        for (size_type j = 1; j < col; j++) {
            if (data[rowi * col + j] > max)
                max = data[rowi * col + j];
        }
        return max;
    } else if (coli >= 0) {
        T max = data[0 * col + coli];
        for (size_type i = 1; i < row; i++) {
            if (data[i * col + coli] > max)
                max = data[i * col + coli];
        }
        return max;
    } else {
        T max = data[0 * col + 0];
        for (size_type i = 0; i < row; i++) {
            for (size_type j = 0; j < col; j++) {
                if (data[i * col + j] > max)
                    max = data[i * col + j];
            }
        }
        return max;
    }
}
// 最小值
template <typename T>
T matrix<T>::min(size_type rowi, size_type coli) const {
    if (rowi >= 0 && coli >= 0) {
        return data[rowi * col + coli];
    } else if (rowi >= 0) {
        T min = data[rowi * col + 0];
        for (size_type j = 1; j < col; j++) {
            if (data[rowi * col + j] < min)
                min = data[rowi * col + j];
        }
        return min;
    } else if (coli >= 0) {
        T min = data[0 * col + coli];
        for (size_type i = 1; i < row; i++) {
            if (data[i * col + coli] < min)
                min = data[i * col + coli];
        }
        return min;
    } else {
        T min = data[0 * col + 0];
        for (size_type i = 0; i < row; i++) {
            for (size_type j = 0; j < col; j++) {
                if (data[i * col + j] < min)
                    min = data[i * col + j];
            }
        }
        return min;
    }
}
// 求和
template <typename T>
T matrix<T>::sum(size_type rowi, size_type coli) const {
    if (rowi >= 0 && coli >= 0) {
        return data[rowi * col + coli];
    } else if (rowi >= 0) {
        T sum = data[rowi * col + 0];
        for (size_type j = 1; j < col; j++) {
            sum += data[rowi * col + j];
        }
        return sum;
    } else if (coli >= 0) {
        T sum = data[0 * col + coli];
        for (size_type i = 1; i < row; i++) {
            sum += data[i * col + coli];
        }
        return sum;
    } else {
        T sum = data[0 * coli + 0];
        for (size_type i = 0; i < row; i++) {
            for (size_type j = 0; j < col; j++) {
                sum += data[i * col + j];
            }
        }
        return sum;
    }
}
// 平均值
template <typename T>
T matrix<T>::avg(size_type rowi, size_type coli) const {
    T avg = sum(rowi, coli);
    if (rowi >= 0 && coli >= 0) {
        return avg;
    } else if (rowi >= 0) {
        return avg / row;
    } else if (coli >= 0) {
        return avg / col;
    } else {
        return avg / row / col;
    }
}

// 5)-----------------
// 特征值
template <typename T>
T* matrix<T>::eigenvalues() const {}
// 特征向量
template <typename T>
vector<T>* matrix<T>::eigenvectors() const {}
// 迹
template <typename T>
T matrix<T>::trace() const {}
// 逆
template <typename T>
matrix<T> matrix<T>::inverse() const {}
// 行列式
template <typename T>
T matrix<T>::determinant() const {}

// 6)-----------------
// 索引
template <typename T>
vector<T> matrix<T>::operator[](size_type __n) const {
    ASSERT(0 <= __n && __n < row);
    T* A = this->data;
    vector<T> vec(col);
    for (size_type j = 0; j < col; j++) {
        vec[j] = A[__n * this->col + j];
    }
    return vec;
}
// 整形
template <typename T>
matrix<T> matrix<T>::reshape(size_type row_size, size_type col_size) const {
    ASSERT(row * col == row_size * col_size);
    matrix<T> copy(*this);
    copy.row = row_size;
    copy.col = col_size;
    return copy;
}
// 切片
template <typename T>
matrix<T> matrix<T>::slice(size_type f, size_type r) const {
    ASSERT(0 <= f && f < r && r <= row);
    size_type sub_row = r - f;
    T* A = this->data;
    T* R = new T[sub_row * col];
    for (size_type k = f * col; k < r * col; k++) {
        R[k] = A[k];
    }
    return matrix(R, sub_row, col);
}

// 7)-----------------
// 卷积
template <typename T>
matrix<T> matrix<T>::convolution(const matrix<T>& other) const {
    // TODO::

    return matrix(*this);
}
// 输出
template <typename T>
std::ostream& operator<<(std::ostream& cout, const matrix<T>& mat) {
    size_type row = mat.row, col = mat.col;
    T* A = mat.data;
    for (size_type i = 0; i < row; i++) {
        cout << ((i == 0) ? '[' : ' ');
        for (size_type j = 0; j < col; j++) {
            cout << A[i * col + j];
            if (j < col - 1)
                cout << ", ";
        }
        cout << ((i < row - 1) ? ";\n" : "]\n");
    }
    return cout;
}

#endif
