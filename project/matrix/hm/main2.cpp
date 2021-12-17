#ifndef _CXXPROJECT_MATRIX
#define _CXXPROJECT_MATRIX 1

#include <math.h>
#include <cstring>
#include <iostream>
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

   public:
    matrix<T>(size_type row_size = 0, size_type col_size = 0);
    matrix<T>(const T* arrays, size_type row_size, size_type col_size);
    matrix<T>(const matrix<T>& src);
    ~matrix<T>();

    matrix<T>& operator=(const matrix<T>& that);

    inline T& operator()(size_type i, size_type j) { return data[i * col + j]; }
    inline T operator()(size_type i, size_type j) const {
        return data[i * col + j];
    }

    // 3)-----------------
    // ����ӷ�
    matrix<T> operator+(const matrix<T>& other) const;
    // �������
    matrix<T> operator-(const matrix<T>& other) const;
    // �����˷�
    matrix<T> operator*(T tnum) const;
    // ��������
    matrix<T> operator/(T tnum) const;
    // ��Ԫ �����˷�
    template <typename T1>
    friend matrix<T1> operator*(T1 tnum, const matrix<T1>& mat);

    // ת��
    matrix<T> transposition() const;
    // ����
    matrix<T> conjugation() const;
    // 2����
    T norm2() const;

    // Ԫ�ؼ��˷�
    matrix<T> multiply_element_wise(const matrix<T>& other) const;
    // ����˷����������˷���
    matrix<T> operator*(const matrix<T>& other);
    // ���
    matrix<T> dot(const matrix<T>& other) const;
    // ���
    matrix<T> cross(const matrix<T>& other) const;

    // 5)-----------------
    template <typename T1>
    friend void QR(const matrix<T1>& A, matrix<T1>& Q, matrix<T1>& R);
    template <typename T1>
    friend void Eig(const matrix<T1>& A,
                    matrix<T1>& eigenVector,
                    matrix<T1>& eigenValue);
    // ����ֵ
    matrix<T> eigenvalues() const;
    // ��������
    matrix<T> eigenvectors() const;
    // ��
    T trace() const;
    // ��������ʽ
    T algebraic_cofactor(size_type i, size_type j) const;
    // ��
    matrix<T> inverse() const;
    // ����ʽ
    T determinant() const;

    // 6)-----------------
    // ����
    vector<T> operator[](size_type n) const;
    // ����
    matrix<T> reshape(size_type row_size, size_type col_size) const;
    // ��Ƭ
    matrix<T> slice_row(size_type, size_type) const;
    matrix<T> slice_col(size_type, size_type) const;
    matrix<T> slice(size_type, size_type, size_type, size_type) const;

    // )-----------------
    // ���
    template <typename T1>
    friend std::ostream& operator<<(std::ostream& cout, const matrix<T1>& mat);
};

// ������
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
    delete[] data;
}
template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& that) {
    SIZE_CHECK(this->row == that.row && this->col == that.col);
    memcpy(data, that.data, row * col * sizeof(T));
    return (*this);
}

// 3)-----------------
// ����ӷ�
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
// �������
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
// �����˷�
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
// ��������
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
// ��Ԫ �����˷�
template <typename T>
matrix<T> operator*(T tnum, const matrix<T>& mat) {
    return mat * tnum;
}
// ת��
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
// ����
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
// 2����
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

// Ԫ�ؼ��˷�
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
// ����˷����������˷���
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
// ���
template <typename T>
matrix<T> matrix<T>::dot(const matrix<T>& other) const {
    return this->multiply_element_wise(other);
}
// ���
template <typename T>
matrix<T> matrix<T>::cross(const matrix<T>& other) const {
    return (*this) * other;
}

// 5)-----------------
// ��
template <typename T>
T matrix<T>::trace() const {
    SQUARE_CHECK(this->col == this->row);
    T result;
    for (int i = 0; i < row; i++) {
        result = result + (*this)(i, i);
    }
    return result;
}
// ��������ʽ
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
// ��
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
// ����ʽ
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
// ����
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
// ����
template <typename T>
matrix<T> matrix<T>::reshape(size_type row_size, size_type col_size) const {
    SIZE_CHECK(row * col == row_size * col_size);
    matrix<T> copy((*this));
    copy.row = row_size;
    copy.col = col_size;
    return copy;
}
// ��Ƭ
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
// ���
template <typename T>
std::ostream& operator<<(std::ostream& cout, const matrix<T>& mat) {
    for (size_type i = 0; i < mat.row; i++) {
        std::cout << ((i == 0) ? '[' : ' ');
        for (size_type j = 0; j < mat.col; j++) {
            std::cout << mat(i, j);
            if (j < mat.col - 1)
                std::cout << ", ";
        }
        std::cout << ((i < mat.row - 1) ? ";\n" : "]\n");
    }
    return cout;
}

// Refer to https://github.com/HuMeng11/matrix
/************************************************************************
�������ܣ���һ������A����QR�ֽ�
���룺��Ҫ�ֽ�ľ���A���ֽ�����������Q�������Ǿ���R
�������
************************************************************************/
template <typename T>
void QR(const matrix<T>& A, matrix<T>& Q, matrix<T>& R) {
    SQUARE_CHECK(A.row == A.col);
    matrix<T> col_A(A.row, 1);  //������A��ÿһ��
    matrix<T> col_Q(A.row, 1);  //������Q��ÿһ��
    //ʩ����������
    for (size_type j = 0; j < A.col; j++) {
        for (size_type i = 0; i < A.row; i++) {  //��A�ĵ�j�д���col_A��
            col_A(i, 0) = A(i, j);               // A.slice_col(j, j + 1);
            col_Q(i, 0) = A(i, j);               // A.slice_col(j, j + 1);
        }
        for (size_type k = 0; k < j; k++) {  //�����j����ǰ
            R(k, j) = (T)0;
            for (size_type i1 = 0; i1 < col_A.row; i1++) {
                // R=Q'A(Q'��Q��ת��) ��Q�ĵ�k�к�A�ĵ�j�����ڻ�
                R(k, j) += col_A(i1, 0) * Q(i1, k);  // Q�ĵ�k��
            }
            for (size_type i2 = 0; i2 < A.col; i2++) {
                col_Q(i2, 0) -= R(k, j) * Q(i2, k);
            }
        }
        T temp = col_Q.norm2();
        R(j, j) = temp;
        for (size_type i3 = 0; i3 < Q.col; i3++) {
            //��λ��Q
            Q(i3, j) = col_Q(i3, 0) / temp;
        }
    }
}

// ����ֵ
template <typename T>
matrix<T> matrix<T>::eigenvalues() const {
    SQUARE_CHECK(row == col);
    int NUM = 10;
    //ʹ��QR�ֽ����������ֵ
    matrix<T> temp(*this), temp_Q(row, col), temp_R(row, col);
    for (size_type k = 0; k < NUM; ++k) {
        QR(temp, temp_Q, temp_R);
        temp = temp_R * temp_Q;  // R*Q
    }
    //��ȡ����ֵ����֮�洢��eValue
    matrix<T> values(row, 1);
    for (size_type k = 0; k < temp.col; ++k) {
        values(k, 0) = temp(k, k);
    }
    return values;
}

// Refer to https://github.com/HuMeng11/matrix
/************************************************************************
�������ܣ���֪һ�����������ֵ���Ӧ����������
���룺һ������A��������������������eigenVector����֪������ֵeigenValue
�������
************************************************************************/
template <typename T>
void Eig(const matrix<T>& A, matrix<T>& eigenVector, matrix<T>& eigenValue) {
    T eValue;
    matrix<T> temp(A.row, A.col);
    for (size_type count = 0; count < A.col; count++) {
        eValue = eigenValue(count, 0);  //��ǰ������ֵ
        temp = A;  //���ÿ�ζ�Ҫ���¸��ƣ���Ϊ������ƻ�ԭ����
        for (size_type i = 0; i < temp.row; i++) {
            temp(i, i) -= eValue;
        }
        //��temp��Ϊ�����;���(��һ��)�Խ���ֵΪһ
        for (size_type i = 0; i < temp.row - 1; i++) {
            T coe = temp(i, i);
            for (size_type j = i; j < temp.col; j++) {
                temp(i, j) /= coe;  //�öԽ���ֵΪһ
            }
            for (size_type i1 = i + 1; i1 < temp.row; i1++) {
                coe = temp(i1, i);
                for (size_type j1 = i; j1 < temp.col; j1++) {
                    temp(i1, j1) -= coe * temp(i, j1);
                }
            }
        }
        //�����һ��Ϊ1
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
        sum1 = sqrt(sum1);  //��ǰ�е�ģ
        for (size_type i = 0; i < eigenVector.row; i++) {
            //��λ��
            eigenVector(i, count) /= sum1;
        }
    }
}

// ��������
template <typename T>
matrix<T> matrix<T>::eigenvectors() const {
    SQUARE_CHECK(row == col);
    matrix<T> values = eigenvalues();
    matrix<T> vectors(row, col);
    Eig(*this, vectors, values);
    return vectors;
}

#endif

int main() {
    using namespace std;

    double arr1[]{1, 1, 1, 
                  1, 2, 10, 
                  1, 10, 1};
    matrix<double> mat1(arr1, 3, 3);
    cout << mat1;

    cout << mat1.eigenvalues();
    cout << mat1.eigenvectors();
}
