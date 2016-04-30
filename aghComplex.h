#ifndef AGHCOMPLEX_H
#define AGHCOMPLEX_H

class aghComplex{
private:
    double re;
    double im;
public:
    aghComplex();
    aghComplex(const double re, const double im);
    double getRe() const;
    double getIm() const;
    aghComplex operator+(const aghComplex &another) const;
    aghComplex operator-(const aghComplex &another) const;
    aghComplex operator*(const aghComplex &another) const;
    friend bool operator==(const aghComplex &complex1, const aghComplex &complex2);
    friend bool operator!=(const aghComplex &complex1, const aghComplex &complex2);
};

#endif
