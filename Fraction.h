#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
using namespace std;

class Fraction
{
    private:
        long long num;
        long long den;
    public:
        //Default Constructor
        Fraction();

		//Constructor w/ 1 value
		Fraction(long long numerator);

        //Constrict w/ values
        Fraction(long long numerator, long long denominator);

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

        void operator=(const long long& number);

        //Equivalence Operators
        bool operator==(const Fraction& frac) const;

        bool operator==(const long long& number) const;

        bool operator!=(const Fraction& frac) const;

        bool operator!=(const long long& number) const;

        //Addition Operator
        Fraction operator+(const Fraction& frac) const;

        //Subtraction Operator
        Fraction operator-(const Fraction& frac) const;
        
        //Multiplication Operator
        Fraction operator*(const Fraction& frac) const;
        
        //Division Operator
        Fraction operator/(const Fraction& frac) const;

        //More Operators
        Fraction& operator+=(const Fraction& frac);

        Fraction& operator-=(const Fraction& frac);

        Fraction& operator*=(const Fraction& frac);

        Fraction& operator/=(const Fraction& frac);

        //Negative operator
        Fraction operator-();
};

#endif