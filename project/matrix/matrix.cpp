#ifndef _CXXPROJECT_MATRIX
#define _CXXPROJECT_MATRIX 1

#include <math.h>
#include <cstring>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

typedef int size_type;
#define vector std::vector

class ZeroDet : std::exception {
   public:
    const char* what() { return "The determinant is zero\n"; }
};
class DiffSize : std::exception {
   public:
    const char* what() { return "matrix row or col do not match\n"; }
};
class NotSquare : std::exception {
   public:
    const char* what() { return "matrix is not a square\n"; }
};
class OutOfRange : std::exception {
   public:
    const char* what() { return "Index out of range\n"; }
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
        T default_value = T();
        struct node {
            T val;
            size_type i;
            size_type j;
            node* next;
        } * head, *tail;
        data_list() { head = tail = new node{}; }
        ~data_list() {
            node *last, *tmp = head;
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
            tail = tail->next = new node{v, i, j, NULL};
        }
    } * sparseData;
    bool isSparse = false;

   public:
    matrix<T>(size_type row_size = 0, size_type col_size = 0);
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
    bool toSparseMatrix(T default_value = T());
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
    enum { FULL, SAME, VALID };
    matrix<T> convolution(const matrix<T>& other, int mode = FULL) const;

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

// 构造器
template <typename T>
matrix<T>::matrix(size_type row_size, size_type col_size)
    : row(row_size), col(col_size), data(new T[row_size * col_size]()) {}
template <typename T>
matrix<T>::matrix(const T* arrays, size_type row_size, size_type col_size)
    : row(row_size), col(col_size), data(new T[row_size * col_size]()) {
    memcpy(data, arrays, row * col * sizeof(T));
}
template <typename T>
matrix<T>::matrix(const matrix<T>& src)
    : row(src.row), col(src.col), data(new T[src.row * src.col]()) {
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            (*this)(i, j) = src(i, j);
        }
    }
}
template <typename T>
matrix<T>::~matrix() {
    if (isSparse) {
        delete sparseData;
    } else {
        delete[] data;
    }
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& that) {
    SIZE_CHECK(this->row == that.row && this->col == that.col);
    memcpy(data, that.data, row * col * sizeof(T));
    return (*this);
}

// 1)-----------------
// 稀疏矩阵转换
template <typename T>
bool matrix<T>::toSparseMatrix(T default_value) {
    if (!isSparse) {
        sparseData = new data_list();
        sparseData->default_value = default_value;
        for (size_type i = 0; i < row; i++) {
            for (size_type j = 0; j < col; j++) {
                T val = (*this)(i, j);
                if (val != default_value) {
                    sparseData->set(val, i, j);
                }
            }
        }
        delete[] data;
        isSparse = true;
        return true;
    } else {
        return false;
    }
}
template <typename T>
bool matrix<T>::toNormalMatrix() {
    if (isSparse) {
        isSparse = false;
        data = new T[row * col]();
        for (size_type k = 0; k < row * col; k++) {
            data[k] = sparseData->default_value;
        }
        auto* tmp = sparseData->head->next;
        while (tmp != NULL) {
            (*this)(tmp->i, tmp->j) = tmp->val;
            tmp = tmp->next;
        }
        delete sparseData;
        return true;
    } else {
        return false;
    }
}

// 3)-----------------
// 矩阵加法
template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& other) const {
    SIZE_CHECK(this->row == other.row && this->col == other.col);
    matrix R(row, col);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return R;
}
// 矩阵减法
template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& other) const {
    SIZE_CHECK(this->row == other.row && this->col == other.col);
    matrix R(row, col);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return R;
}
// 标量乘法
template <typename T>
matrix<T> matrix<T>::operator*(T tnum) const {
    matrix R(row, col);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i, j) = (*this)(i, j) * tnum;
        }
    }
    return R;
}
// 标量除法
template <typename T>
matrix<T> matrix<T>::operator/(T tnum) const {
    matrix R(row, col);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i, j) = (*this)(i, j) / tnum;
        }
    }
    return R;
}
// 友元 标量乘法
template <typename T>
matrix<T> operator*(T tnum, const matrix<T>& mat) {
    return mat * tnum;
}

// 转置
template <typename T>
matrix<T> matrix<T>::transposition() const {
    matrix R(col, row);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(j, i) = (*this)(i, j);
        }
    }
    return R;
}
// 共轭
template <typename T>
inline T conj(T n) {
    return n;
}
template <typename T>
matrix<T> matrix<T>::conjugation() const {
    matrix R(col, row);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(j, i) = conj((*this)(i, j));
        }
    }
    return R;
}
// 2范数
template <typename T>
T matrix<T>::norm2() const {
    T t = (T)0;
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            t += (*this)(i, j) * (*this)(i, j);
        }
    }
    return sqrt(t);  // TODO::
}

// 元素级乘法
template <typename T>
matrix<T> matrix<T>::multiply_element_wise(const matrix<T>& other) const {
    SIZE_CHECK(this->row == other.row && this->col == other.col);
    matrix R(row, col);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return R;
}
// 矩阵乘法（向量级乘法）
template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& other) {
    SIZE_CHECK(this->col == other.row);
    matrix<T> R(this->row, other.col);
    for (size_type i = 0; i < this->row; i++) {
        for (size_type j = 0; j < other.col; j++) {
            for (size_type k = 0; k < this->col; k++) {
                R(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return R;
}
// 矩阵-向量乘法
template <typename T>
vector<T> matrix<T>::operator*(const vector<T>& other) const {
    SIZE_CHECK(this->col == other.row);
    vector<T> R(this->row);
    for (size_type i = 0; i < this->row; i++) {
        for (size_type k = 0; k < this->col; k++) {
            R[i] += (*this)(i, k) * other[k];
        }
    }
    return R;
}
// 友元 向量-矩阵乘法
template <typename T>
vector<T> operator*(const vector<T>& vec, const matrix<T>& mat) {
    SIZE_CHECK(mat.col == mat.row);
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
    return this->multiply_element_wise(other);
}
// 叉积
template <typename T>
matrix<T> matrix<T>::cross(const matrix<T>& other) const {
    return (*this) * other;
}

// 4)-----------------
// 最大值
template <typename T>
T matrix<T>::max(size_type rowi, size_type coli) const {
    size_type r1 = 0, r2 = row, c1 = 0, c2 = col;
    if (rowi >= 0) {
        r1 = rowi;
        r2 = rowi + 1;
    }
    if (coli >= 0) {
        c1 = coli;
        c2 = coli + 1;
    }
    T t = (*this)(r1, c1);
    for (size_type i = r1; i < r2; i++) {
        for (size_type j = c1; j < c2; j++) {
            if ((*this)(i, j) > t)
                t = (*this)(i, j);
        }
    }
    return t;
}
// 最小值
template <typename T>
T matrix<T>::min(size_type rowi, size_type coli) const {
    size_type r1 = 0, r2 = row, c1 = 0, c2 = col;
    if (rowi >= 0) {
        r1 = rowi;
        r2 = rowi + 1;
    }
    if (coli >= 0) {
        c1 = coli;
        c2 = coli + 1;
    }
    T t = (*this)(r1, c1);
    for (size_type i = r1; i < r2; i++) {
        for (size_type j = c1; j < c2; j++) {
            if ((*this)(i, j) > t)
                t = (*this)(i, j);
        }
    }
    return t;
}
// 求和
template <typename T>
T matrix<T>::sum(size_type rowi, size_type coli) const {
    size_type r1 = 0, r2 = row, c1 = 0, c2 = col;
    if (rowi >= 0) {
        r1 = rowi;
        r2 = rowi + 1;
    }
    if (coli >= 0) {
        c1 = coli;
        c2 = coli + 1;
    }
    T t = (T)0;
    for (size_type i = r1; i < r2; i++) {
        for (size_type j = c1; j < c2; j++) {
            t += (*this)(i, j);
        }
    }
    return t;
}
// 平均值
template <typename T>
T matrix<T>::avg(size_type rowi, size_type coli) const {
    T avg = sum(rowi, coli);
    if (rowi >= 0 && coli >= 0) {
        return avg;
    } else if (rowi >= 0) {
        return avg / col;
    } else if (coli >= 0) {
        return avg / row;
    } else {
        return avg / row / col;
    }
}

// 5)-----------------
// // 特征值
// template <typename T>
// matrix<T> matrix<T>::eigenvalues() const {
//     cv::Mat cvmat = toCVMat();
//     cv::Mat values;
//     eigen(cvmat, values);
//     return matrix(values);
// }
// // 特征向量
// template <typename T>
// matrix<T> matrix<T>::eigenvectors() const {
//     cv::Mat cvmat = toCVMat();
//     cv::Mat values, vectors;
//     eigen(cvmat, values, vectors);
//     return matrix(vectors);
// }

// Refer to https://github.com/HuMeng11/matrix
/************************************************************************
函数功能：对一个方阵A进行QR分解
输入：需要分解的矩阵A、分解后的正交矩阵Q和上三角矩阵R
输出：无
************************************************************************/
template <typename T>
void QR(const matrix<T>& A, matrix<T>& Q, matrix<T>& R) {
    SQUARE_CHECK(A.row == A.col);
    matrix<T> col_A(A.row, 1);  //用来存A的每一列
    matrix<T> col_Q(A.row, 1);  //用来存Q的每一列
    //施密特正交化
    for (size_type j = 0; j < A.col; j++) {
        for (size_type i = 0; i < A.row; i++) {  //把A的第j列存入col_A中
            col_A(i, 0) = A(i, j);               // A.slice_col(j, j + 1);
            col_Q(i, 0) = A(i, j);               // A.slice_col(j, j + 1);
        }
        for (size_type k = 0; k < j; k++) {  //计算第j列以前
            R(k, j) = (T)0;
            for (size_type i1 = 0; i1 < col_A.row; i1++) {
                // R=Q'A(Q'即Q的转置) 即Q的第k列和A的第j列做内积
                R(k, j) += col_A(i1, 0) * Q(i1, k);  // Q的第k列
            }
            for (size_type i2 = 0; i2 < A.col; i2++) {
                col_Q(i2, 0) -= R(k, j) * Q(i2, k);
            }
        }
        T temp = col_Q.norm2();
        R(j, j) = temp;
        for (size_type i3 = 0; i3 < Q.col; i3++) {
            //单位化Q
            Q(i3, j) = col_Q(i3, 0) / temp;
        }
    }
}

// 特征值
template <typename T>
matrix<T> matrix<T>::eigenvalues() const {
    SQUARE_CHECK(row == col);
    int NUM = 50;
    matrix<T> temp(*this), temp_Q(row, col), temp_R(row, col);
    for (size_type k = 0; k < NUM; ++k) {
        QR(temp, temp_Q, temp_R);  // A = Q*R
        temp = temp_R * temp_Q;    // A'= R*Q
        // std::cout << temp;
    }
    matrix<T> values(row, 1);
    for (size_type k = 0; k < temp.col; ++k) {
        values(k, 0) = temp(k, k);
    }
    return values;
}

// Refer to https://github.com/HuMeng11/matrix
/************************************************************************
函数功能：已知一个矩阵的特征值求对应的特征向量
输入：一个矩阵A、用来存结果的特征向量eigenVector、已知的特征值eigenValue
输出：无
************************************************************************/
template <typename T>
void Eig(const matrix<T>& A, matrix<T>& eigenVector, matrix<T>& eigenValue) {
    SQUARE_CHECK(A.row == A.col);
    T eValue;
    matrix<T> temp(A.row, A.col);
    for (size_type count = 0; count < A.col; count++) {
        eValue = eigenValue(count, 0);  //当前的特征值
        temp = A;  //这个每次都要重新复制，因为后面会破坏原矩阵
        for (size_type i = 0; i < temp.row; i++) {
            temp(i, i) -= eValue;
        }
        //将temp化为阶梯型矩阵(归一性)对角线值为一
        for (size_type i = 0; i < temp.row - 1; i++) {
            T coe = temp(i, i);
            for (size_type j = i; j < temp.col; j++) {
                temp(i, j) /= coe;  //让对角线值为一
            }
            for (size_type i1 = i + 1; i1 < temp.row; i1++) {
                coe = temp(i1, i);
                for (size_type j1 = i; j1 < temp.col; j1++) {
                    temp(i1, j1) -= coe * temp(i, j1);
                }
            }
        }
        //让最后一行为1
        T sum1 = eigenVector((eigenVector.row - 1), count) = (T)1;
        for (size_type i2 = temp.row - 2; i2 >= 0; i2--) {
            T sum2 = (T)0;
            for (size_type j2 = i2 + 1; j2 < temp.col; j2++) {
                sum2 += temp(i2, j2) * eigenVector(j2, count);
            }
            sum2 = -sum2 / temp(i2, i2);
            sum1 += sum2 * sum2;
            eigenVector(i2, count) = sum2;
        }
        sum1 = sqrt(sum1);  //当前列的模
        for (size_type i = 0; i < eigenVector.row; i++) {
            //单位化
            eigenVector(i, count) /= sum1;
        }
    }
}

// 特征向量
template <typename T>
matrix<T> matrix<T>::eigenvectors() const {
    SQUARE_CHECK(row == col);
    matrix<T> values = eigenvalues();
    matrix<T> vectors(row, col);
    Eig(*this, vectors, values);
    return vectors;
}
// 迹
template <typename T>
T matrix<T>::trace() const {
    SQUARE_CHECK(this->col == this->row);
    T result;
    for (int i = 0; i < row; i++) {
        result = result + (*this)(i, i);
    }
    return result;
}
// 代数余子式
template <typename T>
T matrix<T>::algebraic_cofactor(size_type rowi, size_type coli) const {
    matrix submatrix(row - 1, col - 1);
    for (int i = 0, si = 0; i < row; i++, si++) {
        if (i == rowi)
            i++;
        for (int j = 0, sj = 0; j < col; j++, sj++) {
            if (j == coli)
                j++;
            submatrix(si, sj) = (*this)(i, j);
        }
    }
    if ((rowi + coli) % 2 == 0) {
        return submatrix.determinant();
    } else {
        return -submatrix.determinant();
    }
}
// 逆
template <typename T>
matrix<T> matrix<T>::inverse() const {
    SQUARE_CHECK(this->row == this->col);
    T det = determinant();
    DET_CHECK(det != (T)0);
    matrix adjugate_matrix(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            adjugate_matrix(i, j) = algebraic_cofactor(i, j) / det;
        }
    }
    return adjugate_matrix.transposition();
}
// 行列式
template <typename T>
T matrix<T>::determinant() const {
    SQUARE_CHECK(this->row == this->col);
    if (row == 1) {
        return (*this)(0, 0);
    } else if (row == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
    } else {
        T result;
        for (int j = 0; j < col; j++) {
            result += (*this)(0, j) * algebraic_cofactor(0, j);
        }
        return result;
    }
}

// 6)-----------------
// 索引
template <typename T>
vector<T> matrix<T>::operator[](size_type n) const {
    RANGE_CHECK(0 <= n && n < row);
    T* A = this->data;
    vector<T> vec(col);
    for (size_type j = 0; j < col; j++) {
        vec[j] = A[n * this->col + j];
    }
    return vec;
}
// 整形
template <typename T>
matrix<T> matrix<T>::reshape(size_type row_size, size_type col_size) const {
    SIZE_CHECK(row * col == row_size * col_size);
    matrix<T> copy((*this));
    copy.row = row_size;
    copy.col = col_size;
    return copy;
}
// 切片
template <typename T>
matrix<T> matrix<T>::slice_row(size_type r1, size_type r2) const {
    RANGE_CHECK(0 <= r1 && r1 < r2 && r2 <= row);
    matrix R(r2 - r1, col);
    for (size_type i = r1; i < r2; i++) {
        for (size_type j = 0; j < col; j++) {
            R(i - r1, j) = (*this)(i, j);
        }
    }
    return R;
}
template <typename T>
matrix<T> matrix<T>::slice_col(size_type c1, size_type c2) const {
    RANGE_CHECK(0 <= c1 && c1 < c2 && c2 <= col);
    matrix R(row, c2 - c1);
    for (size_type i = 0; i < row; i++) {
        for (size_type j = c1; j < c2; j++) {
            R(i, j - c1) = (*this)(i, j);
        }
    }
    return R;
}
template <typename T>
matrix<T> matrix<T>::slice(size_type c1,
                           size_type c2,
                           size_type r1,
                           size_type r2) const {
    return slice_col(c1, c2).slice_row(r1, r2);
}

// 7)-----------------
// 卷积
template <typename T>
matrix<T> matrix<T>::convolution(const matrix<T>& other, int mode) const {
    int r1 = this->row;
    int r2 = other.row;
    int c1 = this->col;
    int c2 = other.col;
    int new_r = r1 + r2 - 1;
    int new_c = c1 + c2 - 1;
    matrix<T> result(new_r, new_c);
    for (int i = 0; i < new_r; i++) {
        for (int j = 0; j < new_c; j++) {
            T temp = 0;
            for (int m = 0; m < r1; m++)
                for (int n = 0; n < c1; n++)
                    if ((i - m) >= 0 && (i - m) < r2 && (j - n) >= 0 &&
                        (j - n) < c2) {
                        temp = temp + (*this)(m, n) * other((i - m), (j - n));
                    }
            result(i, j) = temp;
        }
    }

    if (mode == SAME) {
        return result.slice((new_r - r1) / 2, new_r - (new_r - r1) / 2,
                            (new_c - c1) / 2, new_c - (new_c - c1) / 2);
    } else if (mode == VALID) {
        return result.slice((new_r - r2) / 2, new_r - (new_r - r2) / 2,
                            (new_c - c2) / 2, new_c - (new_c - c2) / 2);
    } else {
        return result;
    }
}

// 8)-----------------
// 构造器：cv::Mat
template <typename T>
matrix<T>::matrix(const cv::Mat& src)
    : row(src.rows), col(src.cols), data(new T[src.rows * src.cols]()) {
    for (size_type i = 0; i < row; i++) {
        for (size_type j = 0; j < col; j++) {
            (*this)(i, j) = src.at<T>(i, j);
        }
    }
}
// 转cv::mat
template <typename T>
cv::Mat matrix<T>::toCVMat() const {
    int CV_TYPE;
    if (typeid(T) == typeid(unsigned char)) {
        CV_TYPE = CV_8U;
    } else if (typeid(T) == typeid(char)) {
        CV_TYPE = CV_8S;
    } else if (typeid(T) == typeid(unsigned short)) {
        CV_TYPE = CV_16U;
    } else if (typeid(T) == typeid(short)) {
        CV_TYPE = CV_16S;
    } else if (typeid(T) == typeid(int)) {
        CV_TYPE = CV_32S;
    } else if (typeid(T) == typeid(float)) {
        CV_TYPE = CV_32F;
    } else if (typeid(T) == typeid(double)) {
        CV_TYPE = CV_64F;
    } else {
        CV_TYPE = CV_USRTYPE1;
    }
    T* copy = new T[row * col];
    memcpy(copy, data, row * col * sizeof(T));
    return cv::Mat(row, col, CV_TYPE, copy);
}

// 输出
template <typename T>
std::ostream& operator<<(std::ostream& cout, const matrix<T>& mat) {
    if (!mat.isSparse) {
        for (size_type i = 0; i < mat.row; i++) {
            std::cout << ((i == 0) ? '[' : ' ');
            for (size_type j = 0; j < mat.col; j++) {
                std::cout << mat(i, j);
                if (j < mat.col - 1)
                    std::cout << ", ";
            }
            std::cout << ((i < mat.row - 1) ? ";\n" : "]\n");
        }
    } else {
        auto* tmp = mat.sparseData->head->next;
        std::cout << '[';
        while (tmp != NULL) {
            std::cout << '(' << tmp->i << ',' << tmp->j << "):" << tmp->val;
            tmp = tmp->next;
            if (tmp != NULL)
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    return cout;
}

#endif
