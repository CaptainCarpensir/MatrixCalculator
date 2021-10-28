#ifndef FRACTION_H
#define FRACTION_H

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
 
        //Simplifies fraction via numerator and denominator
        void simplify();
        
        /*
        * Operator Overloads
        */

        //Copy Assignment Operators
        void operator=(const Fraction& frac);

        void operator=(const int& number);

        //Equivalence Operators
        bool operator==(const Fraction& frac) const;

        bool operator==(const int& number) const;

        bool operator!=(const Fraction& frac) const;

        bool operator!=(const int& number) const;

        //Addition Operator
        Fraction operator+(const Fraction& frac) const;

        //Subtraction Operator
        Fraction operator-(const Fraction& frac) const;
        
        //Multiplication Operator
        Fraction operator*(const Fraction& frac) const;
        
        //Division Operator
        Fraction operator/(const Fraction& frac) const;

        //More Operators
        void operator+=(const Fraction& frac);

        void operator-=(const Fraction& frac);

        void operator*=(const Fraction& frac);

        void operator/=(const Fraction& frac);

        //Negative operator
        Fraction operator-();
};

#endif