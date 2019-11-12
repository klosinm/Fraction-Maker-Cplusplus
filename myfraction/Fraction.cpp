#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>
#include <sstream>

using namespace std;

/* Fwriend functions */
Fraction operator+(int val, const Fraction &f)
{   
    return f + val;
}
Fraction operator-(int val, const Fraction &f)
{
    return f - val;
   
}
Fraction operator*(int val, const Fraction &f)
{
    return f * val;
   //  *f;
    
}
//----------------------------------------------------------------------------------------
//base clarifcation
Fraction::Fraction()
{
    x = 0;
    y = 1;
    w = 0;
    isPos = true;
}
//input of whole number
Fraction::Fraction(int v)
{
    x = 0;
    y = 1;
    w = (v);
    if (v < 0)
    {
        isPos = false;
    }
    else{
        isPos = true;
    }
}
//copy
Fraction::Fraction(const Fraction &other)
{
    this->x = other.numerator();
    this->y = other.denominator();
    this->w = other.whole();
    if(this->x < 0 || this->w < 0){
        this->isPos = false;
    }
    else{
        this->isPos = true;
    }
}
//move
Fraction::Fraction(Fraction &&other)
{
    this->x = other.numerator();
    this->y = other.denominator();
    this->w = other.whole();
    this->isPos = other.isPositive();
}
//parscing from string output
Fraction::Fraction(std::string s)
{
    int isSpace = s.find(" "); //return location where space is
    int isSlash = s.find("/"); //return location where "/" is
    int startFract = 0;
    std::string delimiter = "/";
    std::string num = "0";
    std::string dem = "1";
    std::string whole = "0";

    //int num = 0;
    //int dem = 1;
    //int whole = 0;

    // whole number
    if (isSpace != std::string::npos)
    {
        startFract = isSpace + 1;
        whole = s.substr(0, isSpace);
    }
    else
    {
        whole = "0";
    }

    //fraction
    //see if slash
    if (isSlash != std::string::npos)
    {
        num = s.substr(startFract, isSlash - startFract);
        dem = s.substr((isSlash + 1), (s.size()));
    }
    else
    {
        whole = s.substr(0, s.size());
        num = "0";
        dem = "1";
    }

    this->w = stoi(whole);
    
    this->x = stoi(num);
    this->y = stoi(dem);

    if (this->y == 0)
    {
        throw std::invalid_argument("Can't divide by 0!");
    }
    if(this->w <0 || this->x < 0){
        this->isPos = false;
    }
    else{
        this->isPos = true;
    }

    //std::istringstream Input{"[" + s + "]"};
    //readFrom(Input);
}
//----------------------------------------------------------------------------------------
int Fraction::whole() const
{
    return abs(w);
}
int Fraction::numerator() const
{
    return abs(x); //% y);
}
int Fraction::denominator() const
{
    return abs(y);
}
bool Fraction::isPositive() const
{
    //return !(this->x < 0 || this->y < 0 || this->w < 0);
    return isPos;
}
//----------------------------------------------------------------------------------------
// Copy assignment
Fraction &Fraction::operator=(const Fraction &other)
{
    this->x = other.numerator();
    this->y = other.denominator();
    this->w = other.whole();
    this->isPos = other.isPositive();
    return *this;
}
// Move assignment
Fraction &Fraction::operator=(Fraction &&other)
{
    this->x = other.numerator();
    this->y = other.denominator();
    this->w = other.whole();
    this->isPos = other.isPositive();

    return *this;
}
//----------------------------------------------------------------------------------------
//greatest common factor
int Fraction::gcf(int a, int b) const
{
    if (a % b == 0)
    {
        return abs(b);
    }
    else
    {
        return gcf(b, a % b);
    }
}
//least common mutiple
int Fraction::lcm(int a, int b) const
{
    return (a / gcf(a, b)) * b;
}
//----------------------------------------------------------------------------------------
// Add Fraction + int
Fraction Fraction::operator+(int num) const
{
    Fraction fract = *this;
    fract.w = fract.w + num;

    return fract;
}
// Add Fraction + Fraction
Fraction Fraction::operator+(const Fraction &other) const
{
    Fraction fract = *this;  //a
    Fraction fract2 = other; //b
    int temp1 = 0;
    int temp2 = 0;
    int numerator1 = 0;
    int numerator2 = 0;

    //finding consistent denominator
    int lcd = lcm(fract.denominator(), fract2.denominator());

    //change first fraction if needed
    if (fract.denominator() < lcd)
    {
        temp1 = lcd / fract.denominator();
        numerator1 = temp1 * fract.numerator();
    }

    //change second fraction if needed
    if (fract2.denominator() < lcd)
    {
        temp2 = lcd / fract2.denominator();
        numerator2 = temp2 * fract2.numerator();
    }

    //New numerator
    int sumNum = numerator1 + numerator2;
    //Return Value
    if(fract.w < 0){
        fract.w = (fract2.w - fract.w);
    }
    else if(fract2.w < 0){
        fract.w = (fract.w - fract2.w);
    }
    else{
    fract.w = fract.w + fract2.w;
    }

    Fraction f;
    f.x = sumNum;
    f.y = lcd;
    f.w = fract.w;

    f.makeProper();
    f.reduce();
    return f;
    
}
//make negative/postive
Fraction Fraction::operator-() const
{
    Fraction fract = *this;
    return (-1) * fract;
}
// binary minus: Frac - int
Fraction Fraction::operator-(int val) const
{
    Fraction fract = *this;
    //make fraction a improper
    // x = 6 + (2 * 13) == 32
    int num1 = fract.x + (fract.w * fract.y);

    //15 * 13 = 195
    int valNum = val * fract.y;

    int newNum = valNum - num1;
  //  -valNum;
    fract.w = 0;
    fract.x = newNum;
    fract.makeProper();
    fract.reduce();
    return fract;
}
// binary minus: Frac - Frac
Fraction Fraction::operator-(const Fraction &other) const
{
    Fraction fract = *this;
    Fraction fract2 = other;
    int temp = 0;
    int numerator1 = 0;
    int numerator2 = 0;

    //finding consistent denominator
    int lcd = lcm(fract.denominator(), fract2.denominator());

    //change first fraction if needed
    if (fract.denominator() < lcd)
    {
        temp = lcd / fract.denominator();
        numerator1 = temp * fract.numerator();
    }

    //change second fraction if needed
    if (fract2.denominator() < lcd)
    {
        temp = lcd / fract2.denominator();
        numerator2 = temp * fract2.numerator();
    }

    //New numerator
    int sumNum = (numerator1 - numerator2);
    if (fract.w < 0)
    {
        fract.w = (fract2.w - fract.w);
    
    }
    else
    {
        fract.w = fract.w - fract2.w;
    }

    fract.x = sumNum;
    fract.y = lcd;
    fract.reduce();

    if (fract.w < 0 || fract.x < 0)
    {
        fract.isPos = false;
    }
    else{
        fract.isPos = true;
    }

    fract.makeProper();
    return fract;
}
// Multiply: Frac * int
Fraction Fraction::operator*(int val) const
{
    Fraction fract = *this;

        fract.w = fract.w * val;
        fract.x = fract.x * val;
 
    fract.makeProper();
    fract.reduce();
    return fract;
}
// Multiply: Frac * Frac
Fraction Fraction::operator*(const Fraction &other) const
{
    Fraction fract = *this;

    Fraction fract2 = other;
    //make fraction a improper
    int num1 = fract.x + (fract.w * fract.y);
    int num2 = fract2.x + (fract2.w * fract2.y);

    int dem = fract2.y* fract.y; //finding  denominator
    int num = num1 * num2;       //finding  numerator
    //Return Value
    Fraction f{};
   
    f.x = num;
    f.y = dem;
   
    
    f.makeProper();
    f.reduce();
    return f;
}
//----------------------------------------------------------------------------------------
// Component access Frac[i]
optional<int> Fraction::operator[](int pos) const
{
    //case 0 check if whole num equals 0, return non, otherwise rturn whole
    switch (pos)
    {
    //whole
    case 0:

    //numer
    case 1:;
    //demon
    case 2:;
    

    }

    return 1;
    //this;
}
// Compare Frac < Frac
bool Fraction::operator<(const Fraction &other) const
{
    Fraction fract = *this;
    Fraction fract2 = other;
    //make fraction a improper
    int num1 = fract.x + (fract.w * fract.y) * fract2.y;
    int num2 = fract2.x + (fract2.w * fract2.y) * fract.y;

    fract.x = num1;
    fract2.x = num2;
    fract.w = 0;
    fract2.w = 0;

    fract.reduce();
    fract2.reduce();

    if (fract.w < fract2.w)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Compare Frac == Frac
bool Fraction::operator==(const Fraction &other) const
{
    Fraction fract = *this;
    Fraction fract2 = other;
    //make fraction a improper
    int num1 = fract.x + (fract.w * fract.y);
    int num2 = fract2.x + (fract2.w * fract2.y);

    fract.x = num1;
    fract2.x = num2;
    fract.w = 0;
    fract2.w = 0;

    fract.reduce();
    fract2.reduce();

   if(fract.x == fract2.x && fract.y == fract2.y){
       return true;
   }
   else{
       return false;
   }
}
//----------------------------------------------------------------------------------------
//Proper
void Fraction::makeProper()
{
    Fraction f;
    int num = 0;
    int whole = 0;

    //just whole number is provided
    if (this->x == 0 && this->y == 1)
    {
        return;
    }
    //numerator is greater than denominator
    else if (this->x > this->y)
    {
        num = this->x % this->y;
        whole = this->w + (this->x - num) / this->y;
        this->x = num;
        this->w = whole;
        if (this->x == 0)
        {
            this->y = 1;
        }
    }
    else if( this-> x == this->y){
        this->x = 0;
        this->y = 1;
        this->w = 1;
    }
    else{
        return;
    }
}
Fraction Fraction::toProper() const
{
    Fraction funct = *this;
    funct.makeProper();
    return funct;
}
bool Fraction::isProper() const
{
    Fraction f;

    if (this->x > this->y || this->x == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//----------------------------------------------------------------------------------------
// Reduce
void Fraction::reduce()
{
   
    int top = 0;
    int bottom = 0;
    int divide = gcf(this->x, this->y);

    top = this->x / divide;
    bottom = this->y / divide;

    this->x = top;
    this->y = bottom;
}
Fraction Fraction::toReduced() const
{
    Fraction funct = *this;
    funct.reduce();
    return funct;
}
bool Fraction::isReduced() const
{
    int a = gcf(this->x, this->y);

    if (a == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//----------------------------------------------------------------------------------------
ostream &Fraction::writeTo(ostream &os) const
{

    return os;
}

istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */
{
    char ch;
    string a = "";
    ch = sr.get(); //

    //goes untill you find the start
    if ('[' != std::string::npos || ']' != std::string::npos)
    {
        throw std::invalid_argument("Doesn't have a []!");
    }
    else
    {

        while (ch != '[')
        {
            ch = sr.get();
        }

        ch = sr.get();
        //get middle input of fraction goodness
        while (ch != ']')
        {
            a = a + ch;
            ch = sr.get();
        }
    }
    //*this = Fraction{a};
    Fraction f = Fraction{a};
    this->x = f.x;
    this->y = f.y;
    this->w = f.w;

    return sr;
}

ostream &operator<<(ostream &os, const Fraction &f)
{
    return f.writeTo(os);
}

istream &operator>>(istream &s, Fraction &f)
{
    return f.readFrom(s);
}

#if I_DO_EXTRA_CREDIT
optional<string> Fraction::isRepeating() const
{
    return {};
}

string Fraction::operator()(int len) const { return {}; }
#endif
