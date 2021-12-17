#ifndef _MYCOMPLEX_H
#define _MYCOMPLEX_H

class Complex {
   private:
    double real;
    double imag;

   public:
    Complex();
    Complex(double r, double i);

    friend Complex operator~(const Complex& that);
    friend Complex conj(const Complex& that);

    friend Complex operator-(const Complex& that);

    friend double operator!(const Complex& that);

    friend Complex operator+(double real, const Complex& that);
    Complex operator+(const Complex& other) const;
    Complex operator+(double real) const;
    Complex operator+=(const Complex& other);

    friend Complex operator-(double real, const Complex& that);
    Complex operator-(const Complex& other) const;
    Complex operator-(double real) const;
    Complex operator-=(const Complex& other);

    friend Complex operator*(double real, const Complex& that);
    Complex operator*(const Complex& other) const;
    Complex operator*(double real) const;

    friend Complex operator/(double real, const Complex& that);
    Complex operator/(const Complex& other) const;
    Complex operator/(double real) const;
    
    friend bool operator==(double real, const Complex& that);
    bool operator==(const Complex& other) const;
    bool operator==(double real) const;

    friend bool operator!=(double real, const Complex& that);
    bool operator!=(const Complex& other) const;
    bool operator!=(double real) const;
    
    friend std::istream& operator>>(std::istream& cin, Complex& that);
    friend std::ostream& operator<<(std::ostream& cout, const Complex& that);
};

#endif  //_MYCOMPLEX_H
