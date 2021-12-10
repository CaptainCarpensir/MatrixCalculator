#include "Fraction.h"

using namespace std;

/*
* Constructors
*/

//Default Constructor
Fraction::Fraction()
{
    num = 0;
    den = 1;
}

//Constructor w/ 1 value
Fraction::Fraction(long long numerator)
{
    num = numerator;
    den = 1;
}

//Constrict w/ values
Fraction::Fraction(long long numerator, long long denominator)
{
    num = numerator;
    den = denominator;
}

//Copy constructor
Fraction::Fraction(const Fraction& frac)
{
    num = frac.num;
    den = frac.den;
}

/*
* OSTREAM OPERATOR OVERLOAD
*/

ostream& operator<<(ostream& os, const Fraction& frac)
{
    if(frac.den == 1)
    {
        os << frac.num;
    }
    else{
        os << frac.num << "/" << frac.den;
    }
    return os;
}

/*
* PRIVATE MEMBER FUNCTIONS
*/

void Fraction::simplify()
{
    //Comput GCD
    long long gcd, temp_num, temp_den;

    //Checks if the fraction is negative, then sets both den and num to positive values for algorithm to work
    //Also sets numerator and denominator to be positive to make sure all fractions only have negative numerator
    bool neg = (num * den < 0)? true : false;
    temp_num = (num < 0)? -num : num;
    temp_den = (den < 0)? -den : den;
    num = (num < 0)? -num : num;
    den = (den < 0)? -den : den;

    //Computing GCD via euclids algorithm 
    //subtract smaller of the num/den by the larger of the two successively until they're equal
    //If numerator is 0, quit out and make den to be 1
    while(temp_num != temp_den && temp_num != 0)
    {
        if(temp_num > temp_den)
        {
            temp_num -= temp_den;
        }
        else
        {
            temp_den -= temp_num;
        }
    }
    gcd = temp_den;

    //Divide num and den by GCD
    num /= gcd;
    den /= gcd;

    
    //if fraction is negative, makes the numerator negative
    if(neg) num = -num;
}

/*
* Operator Overloads
*/

//Copy Assignment Operators
void Fraction::operator=(const Fraction& frac)
{
    num = frac.num;
    den = frac.den;
}

void Fraction::operator=(const long long& number)
{
    num = number;
    den = 1;
}

//Equivalence Operators
bool Fraction::operator==(const Fraction& frac) const
{
    bool answer = false;

    Fraction temp1(*this);
    Fraction temp2(frac);

    temp1.simplify();
    temp2.simplify();

    if(temp1.num == temp2.num && temp1.den == temp2.den) answer = true;

    return answer;
}

bool Fraction::operator==(const long long& number) const
{
    bool answer = false;

    Fraction temp1(*this);
    Fraction temp2(number, 1);

    temp1.simplify();
    temp2.simplify();

    if(temp1.num == temp2.num && temp1.den == temp2.den) answer = true;

    return answer;
}

bool Fraction::operator!=(const Fraction& frac) const
{
    bool answer = true;

    Fraction temp1(*this);
    Fraction temp2(frac);

    temp1.simplify();
    temp2.simplify();

    if(temp1.num == temp2.num && temp1.den == temp2.den) answer = false;

    return answer;
}

bool Fraction::operator!=(const long long& number) const
{
    bool answer = true;

    Fraction temp1(*this);
    Fraction temp2(number, 1);

    temp1.simplify();
    temp2.simplify();

    if(temp1.num == temp2.num && temp1.den == temp2.den) answer = false;

    return answer;
}

//Addition Operator
Fraction Fraction::operator+(const Fraction& frac) const
{
    long long new_num = (num*frac.den)+(frac.num*den);
    long long new_den = den*frac.den;

    Fraction answer(new_num, new_den);

    answer.simplify();

    return answer;
}

//Subtraction Operator
Fraction Fraction::operator-(const Fraction& frac) const
{
    long long new_num = (num*frac.den)-(frac.num*den);
    long long new_den = den*frac.den;

    Fraction answer(new_num, new_den);

    answer.simplify();

    return answer;
}
        
//Multiplication Operator
Fraction Fraction::operator*(const Fraction& frac) const
{
    Fraction answer;

    answer.num = num * frac.num;
    answer.den = den * frac.den;

    answer.simplify();

    return answer;
}
        
//Division Operator
Fraction Fraction::operator/(const Fraction& frac) const
{
    Fraction answer;

    answer.num = num * frac.den;
    answer.den = den * frac.num;

    answer.simplify();

    return answer;
}

//More Operators
void Fraction::operator+=(const Fraction& frac)
{
    *this = *this + frac;
}

void Fraction::operator-=(const Fraction& frac)
{
    *this = *this - frac;
}

void Fraction::operator*=(const Fraction& frac)
{
    *this = *this * frac;
}

void Fraction::operator/=(const Fraction& frac)
{
    *this = *this / frac;
}

//Negative operator
Fraction Fraction::operator-()
{
    Fraction answer(-num, den);
    return answer;
}