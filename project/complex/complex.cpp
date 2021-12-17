#include <iostream>

#include "complex.h"

Complex::Complex() : real(0), imag(0) {}

Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex operator~(const Complex& that) {
    return Complex(that.real, -that.imag);
}
Complex conj(const Complex& that) {
    return Complex(that.real, -that.imag);
}

Complex operator-(const Complex& that) {
    return Complex(-that.real, -that.imag);
}

double operator!(const Complex& that) {
    return that.real * that.real + that.imag * that.imag;
}

Complex Complex::operator+(const Complex& that) const {
    return Complex(this->real + that.real, this->imag + that.imag);
}
Complex Complex::operator+(double real) const {
    return Complex(this->real + real, this->imag);
}
Complex operator+(double real, const Complex& that) {
    return that + real;
}
Complex Complex::operator+=(const Complex& that) {
    this->real += that.real;
    this->imag += that.imag;
    return *this;
}

Complex Complex::operator-(const Complex& that) const {
    return Complex(this->real - that.real, this->imag - that.imag);
}
Complex Complex::operator-(double real) const {
    return (*this) + (-real);
}
Complex operator-(double real, const Complex& that) {
    return real + (-that);
}
Complex Complex::operator-=(const Complex& that) {
    this->real -= that.real;
    this->imag -= that.imag;
    return *this;
}

Complex Complex::operator*(const Complex& that) const {
    return Complex(this->real * that.real - this->imag * that.imag,
                   this->imag * that.real + this->real * that.imag);
}
Complex Complex::operator*(double real) const {
    return Complex(this->real * real, this->imag * real);
}
Complex operator*(double real, const Complex& that) {
    return that * real;
}

Complex Complex::operator/(const Complex& that) const {
    return (*this) * (~that) / (!that);
}
Complex Complex::operator/(double real) const {
    return (*this) * (1 / real);
}
Complex operator/(double real, const Complex& that) {
    return real * (~that) / (!that);
}

bool Complex::operator==(const Complex& that) const {
    return this->real == that.real && this->imag == that.imag;
}
bool Complex::operator==(double real) const {
    return this->real == real && this->imag == 0;
}
bool operator==(double real, const Complex& that) {
    return that == real;
}

bool Complex::operator!=(const Complex& that) const {
    return !(this->real == that.real && this->imag == that.imag);
}
bool Complex::operator!=(double real) const {
    return !(this->real == real && this->imag == 0);
}
bool operator!=(double real, const Complex& that) {
    return that != real;
}

std::ostream& operator<<(std::ostream& cout, const Complex& that) {
    if (that.imag >= 0)
        return cout << that.real << '+' << that.imag << 'i';
    else
        return cout << that.real << '-' << -that.imag << 'i';
}

std::istream& operator>>(std::istream& cin, Complex& that) {
    std::cout << "real:";
    cin >> that.real;
    std::cout << "imaginary:";
    return cin >> that.imag;
}
