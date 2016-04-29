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
        double operator+(const aghComplex &another);
        double operator-(const aghComplex &another);
        double operator*(const aghComplex &another);
        bool operator==(const aghComplex &another);
        bool operator!=(const aghComplex &another);
}

#endif
