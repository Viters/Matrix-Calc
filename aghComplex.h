#ifndef AGHCOMPLEX_H
#define AGHCOMPLEX_H


/*
* \class aghComplex
* \authors Łukasz Mielczarek, Łukasz Szcześniak
* \date 
* \brief The declaration of aghComplex class that allow for using complex number
*/
class aghComplex{
private:
    double re; ///<Stores real part of number
    double im; ///<Stores imaginary part of number
public:

    /// \brief The default class constructor
    aghComplex();

    /// \brief The class constructor
    ///
    /// \param re - real part of new number
    /// \param im - imaginary part of new number
    aghComplex(const double re, const double im);

    /// \brief The class constructor which converts int to aghComplex
    ///
    /// \param re - real part of new number
    aghComplex(const double re);

    /// \brief Function that returns real part of number
    ///
    /// \return real part of number (value stored by 're')
    double getRe() const;

    /// \brief Function that returns imaginary part of number
    ///
    /// \return imaginary part of number (value stored by 'im')
    double getIm() const;

    /// \brief Adding operator
    ///
    /// \param another - aghComplex object which we want to be added
    /// \return aghComplex object that represents a sum of complex numbers
    aghComplex operator+(const aghComplex &another) const;

    /// \brief Subtracting operator
    ///
    /// \param another - aghComplex object which we want to be subtracted
    /// \return aghComplex object that represents a difference of complex numbers
    aghComplex operator-(const aghComplex &another) const;

    /// \brief Multiplying operator
    ///
    /// \param another - aghComplex object which we want to be multiplied
    /// \return aghComplex object that represents a muliplication of complex numbers
    aghComplex operator*(const aghComplex &another) const;

    /// \brief Comparison operators
    ///
    /// \param complex1, complex2 - complex number which we want to compare
    /// \return logical value which says if the numbers are equal
    friend bool operator==(const aghComplex &complex1, const aghComplex &complex2);
    //return logical value which says if the numbers are not equal
    friend bool operator!=(const aghComplex &complex1, const aghComplex &complex2);
};

#endif
