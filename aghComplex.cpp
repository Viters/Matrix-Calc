#include "aghComplex.h"

aghComplex::aghComplex() : re(0), im(0) {}

aghComplex::aghComplex(const double re, const double im) : re(re), im(im) {}

double aghComplex::getRe() const{
    return this->re;
}

double aghComplex::getIm() const{
    return this->im;
}

double aghComplex::operator+(const aghComplex &another){
    return aghComplex( this->re + another.re, this->im + another.im);
}

double aghComplex::operator-(const aghComplex &another){
    return aghComplex( this->re - another.re, this->im - another.im);
}
