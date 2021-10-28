#ifndef FRACTION_H
#define FRCTION_H

#include <iostream>
using namespace std;

class Fraction
{
    private:
        int num;
        int den;
    public:
        //Default Constructor
        Fraction();

        //Constrict w/ values
        Fraction(int numerator, int denominator);

        //Copy constructor
        Fraction(const Fraction& frac);

        //Ostream operator overload
        friend ostream& operator<<(ostream& os, const Fraction& frac);
        
        /*
        * Operator Overloads
        */

        //Copy Assignment Operator
        void operator=(const Fraction& frac);

        //Equivalence Operator
        bool operator==(const Fraction& frac) const;

        //Addition Operator
        Fraction operator+(const Fraction& frac) const;

        //Subtraction Operator
        Fraction operator-(const Fraction& frac) const;
        
        //Multiplication Operator
        Fraction operator*(const Fraction& frac) const;
        
        //Division Operator
        Fraction operator/(const Fraction& frac) const;
    private:
        //Simplifies fraction via numerator and denominator
        void simplify();
};

#endif