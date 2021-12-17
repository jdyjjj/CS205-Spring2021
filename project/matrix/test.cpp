#include <complex>
#include <iostream>
#include "matrix.cpp"
#define USER_TYPE
#ifdef USER_TYPE
#include "../complex/complex.h"
#endif
using namespace std;

#define TEST_ALL(ts)                                         \
    for (int i = 0; i < (sizeof(ts) / sizeof(ts[0])); i++) { \
        cout << "\nTEST " << i << " :\n\n";                  \
        ts[i]();                                             \
    }

typedef void (*Test)(void);

void basicTest();
void sparseTest();
void conjTest();
void operatorTest();
void cvTest();
void determinantTest();
void inverseTest();
void convolutionTest();
void eigenTest();

static Test tests[] = {basicTest,    sparseTest,     conjTest,
                       operatorTest, cvTest,         determinantTest,
                       inverseTest,  convolutionTest, eigenTest};

int main(void) {
    TEST_ALL(tests);
    return 0;
}

void basicTest() {
    double arr0[]{1.1, 2.2, 1.3, 3.3, 6.6, 9.9};
    matrix<double> mat0(arr0, 2, 3);
    cout << mat0;

#ifdef USER_TYPE
    Complex arr1[]{Complex(1, 1), Complex(2, 1), Complex(3, 1),
                   Complex(1, 1), Complex(2, 2), Complex(3, 3)};
    matrix<Complex> mat1(arr1, 2, 3);
    cout << mat1;
#endif

    matrix<int> mat2(3, 3);
    cout << mat2;
}

void sparseTest() {
    int arr0[]{1, 0, 3, 0, 0, 6, 0, 0};
    matrix<int> mat0(arr0, 2, 4);
    cout << mat0;

    mat0.toSparseMatrix();
    cout << mat0;

    mat0.toNormalMatrix();
    cout << mat0;
}

void conjTest() {
    // short
    short arr0[]{1, 2, 1, 3, 6, 3};
    matrix<short> mat0(arr0, 2, 3);
    cout << mat0;
    cout << mat0.conjugation();

#ifdef USER_TYPE
    // Complex (user define type)
    Complex arr1[]{Complex(1, 1), Complex(2, 1), Complex(3, 1),
                   Complex(1, 1), Complex(2, 2), Complex(3, 3)};
    matrix<Complex> mat1(arr1, 2, 3);
    cout << mat1;
    cout << mat1.conjugation();
#endif
    // complex<short>
    complex<short> arr2[]{complex<short>(1, 1), complex<short>(2, 2),
                          complex<short>(1, 1), complex<short>(2, 2),
                          complex<short>(1, 1), complex<short>(3, 3)};
    matrix<complex<short>> mat2(arr2, 2, 3);
    cout << mat2;
    cout << mat2.conjugation();
}

void operatorTest() {
    double arr0[]{1.1, 2.2, 1.3, 3.3, 6.6, 9.9};
    matrix<double> mat0(arr0, 2, 3);
    cout << mat0;

    double arr2[]{1, 2, 1, 3, 6, 3};
    matrix<double> mat2(arr2, 3, 2);
    cout << mat2;
    cout << mat2.avg() << '\n';
    cout << mat2.avg(1) << '\n';
    cout << mat2.avg(1, 1) << '\n';

    cout << mat0 * mat2;
    cout << mat0;

    int arr3[]{1, 2, 1, 3};
    matrix<int> mat3(arr3, 2, 2);
    cout << mat3;

    int arr4[]{2, 2, 3, 3};
    matrix<int> mat4(arr4, 2, 2);
    cout << mat4;

    mat3 = mat4 * mat3;
    mat3 = mat3 * mat4;
    cout << mat3;
}

void cvTest() {
    // Matrix to cv::Mat
    double arr0[]{7.1, 2.2, 7.2, 3.3, 7.3, 4.4};
    matrix<double> mat0(arr0, 3, 2);
    cout << mat0;

    cv::Mat cvmat0 = mat0.toCVMat();
    cout << cvmat0 << '\n';

    // cv::Mat to Matrix
    double arr1[]{7.1, 2.2, 7.2, 3.3, 7.3, 4.4};
    cv::Mat cvmat1(2, 3, CV_64F, arr1);
    cout << cvmat1 << '\n';

    matrix<double> mat1(cvmat1);
    cout << mat1;
}

void determinantTest() {
    double arr0[]{1, 2, 1, 1};
    matrix<double> mat0(arr0, 2, 2);
    cout << mat0;
    cout << mat0.determinant() << '\n';  // -1

    double arr1[]{4, 9, 2, 3, 5, 7, 8, 1, 6};
    matrix<double> mat1(arr1, 3, 3);
    cout << mat1;
    cout << mat1.determinant() << '\n';  // 360

    complex<float> arr2[]{
        complex<float>(1, 1), complex<float>(2, 2), complex<float>(2, 2),
        complex<float>(1, 1), complex<float>(2, 2), complex<float>(3, 3),
        complex<float>(1, 1), complex<float>(3, 3), complex<float>(2, 2)};
    matrix<complex<float>> mat2(arr2, 3, 3);
    cout << mat2;
    cout << mat2.determinant() << '\n';
}

void inverseTest() {
    double arr0[]{1, 2, 1, 1};
    matrix<double> mat0(arr0, 2, 2);
    cout << mat0;
    cout << mat0.inverse();
    /*
    -1  2
     1 -1
    */

    double arr1[]{4, 9, 2, 3, 5, 7, 8, 1, 6};
    // double arr1[]{1, 2, 2, 1, 2, 3, 1, 3, 2};
    matrix<double> mat1(arr1, 3, 3);
    cout << mat1;
    cout << mat1.inverse();
    /*
    0.0639   	-0.1444   	0.1472
    0.1056   	0.0222   	-0.0611
    -0.1028   	0.1889   	-0.0194
    */

    complex<float> arr2[]{
        complex<float>(1, 1), complex<float>(1, 1), complex<float>(1, 1),
        complex<float>(1, 1), complex<float>(2, 2), complex<float>(3, 3),
        complex<float>(1, 1), complex<float>(3, 3), complex<float>(2, 2)};
    matrix<complex<float>> mat2(arr2, 3, 3);
    cout << mat2;
    cout << mat2.inverse();
}

void convolutionTest() {
    double arr0[]{4, 9, 2, 3, 5, 7, 8, 1, 6, 1, 4, 9, 2,
                  3, 5, 7, 8, 1, 6, 1, 7, 8, 1, 6, 1};
    matrix<double> mat0(arr0, 5, 5);
    cout << mat0;

    double arr1[]{1, 0, 0, 0, 1, 0, 0, 1, 0};
    matrix<double> mat1(arr1, 3, 3);
    cout << mat1;

    cout << mat0.convolution(mat1);
}

void eigenTest() {
    
    double arr0[]{1, 1, 1, 1, 2, 10, 1, 10, 1};
    matrix<double> mat0(arr0, 3, 3);
    cout << mat0;

    cout << mat0.eigenvalues();
    cout << mat0.eigenvectors();
    /*
    特征值：
    特征值1：	11.6993
    特征值2：	0.8133
    特征值3：	-8.5126
    特征向量：
    向量1   	向量2   	向量3   
    0.1310   	0.9914   	0.0038   
    0.7181   	-0.0975   	0.6890   
    0.6835   	-0.0876   	-0.7247   
    */
}
