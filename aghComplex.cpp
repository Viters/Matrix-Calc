#include "aghComplex.h"

// --------------------------------------------------------------

aghComplex::aghComplex() : re(0), im(0) {}

// --------------------------------------------------------------

aghComplex::aghComplex(const double re, const double im) : re(re), im(im) {}

// --------------------------------------------------------------

aghComplex::aghComplex(const double re): re(re), im(0){}

// --------------------------------------------------------------

double aghComplex::getRe() const{
    return this->re;
}

// --------------------------------------------------------------

double aghComplex::getIm() const{
    return this->im;
}

// --------------------------------------------------------------

aghComplex aghComplex::operator+(const aghComplex &another) const{
    return aghComplex( this->re + another.re, this->im + another.im);
}

// --------------------------------------------------------------

aghComplex aghComplex::operator-(const aghComplex &another) const{
    return aghComplex( this->re - another.re, this->im - another.im);
}

// --------------------------------------------------------------

aghComplex aghComplex::operator*(const aghComplex &another) const{
    return aghComplex( this->re * another.re - this->im * another.im,
                       this->im * another.re + this->re * another.im);
}

// --------------------------------------------------------------

bool operator==(const aghComplex &complex1, const aghComplex &complex2) {
    return (complex1.re == complex2.re) && (complex1.im == complex2.im);
}

// --------------------------------------------------------------

bool operator!=(const aghComplex &complex1, const aghComplex &complex2) {
    return (complex1.re != complex2.re) || (complex1.im != complex2.im);
}

// --------------------------------------------------------------
