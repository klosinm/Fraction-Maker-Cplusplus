#define CATCH_CONFIG_MAIN

#include "Fraction.h"

#include "catch.hh"
#include <sstream>

using std::istringstream;
using std::ostringstream;

TEST_CASE("Constructor")
{

    SECTION("Default")
    {
        Fraction x;

        CHECK(x.whole() == 0);
        CHECK(x.numerator() == 0);
        CHECK(x.denominator() == 1);
    }

    SECTION("Construct from whole number", "Positive")
    {
        Fraction z{2};

        CHECK(z.whole() == 2);
        CHECK(z.numerator() == 0);
        CHECK(z.denominator() == 1);
        CHECK(z.isPositive());
    }

    SECTION("Construct from whole number", "Negative")
    {
        Fraction z{-2};

        CHECK(z.whole() == 2);
        CHECK(z.numerator() == 0);
        CHECK(z.denominator() == 1);
        CHECK_FALSE(z.isPositive());
    }

    SECTION("Construct from std::string", "Positive")
    {
        Fraction a{"3"};
        Fraction b{"1 7/13"};
        Fraction c{"8/17"};

        CHECK(a.whole() == 3);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
        CHECK(a.isPositive());

        CHECK(b.whole() == 1);
        CHECK(b.numerator() == 7);
        CHECK(b.denominator() == 13);
        CHECK(b.isPositive());

        CHECK(c.whole() == 0);
        CHECK(c.numerator() == 8);
        CHECK(c.denominator() == 17);
        CHECK(b.isPositive());
    }

    SECTION("Construct from std::string", "Negative")
    {
        Fraction a{"-3"};
        Fraction b{"-1 7/13"};
        Fraction c{"-8/17"};

        CHECK(a.whole() == 3);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
        CHECK_FALSE(a.isPositive());

        CHECK(b.whole() == 1);
        CHECK(b.numerator() == 7);
        CHECK(b.denominator() == 13);
        CHECK_FALSE(b.isPositive());

        CHECK(c.whole() == 0);
        CHECK(c.numerator() == 8);
        CHECK(c.denominator() == 17);
        CHECK_FALSE(b.isPositive());
    }

    SECTION("Construct from std::string", "Zero denominator")
    {
        std::unique_ptr<Fraction> tmp;
        CHECK_THROWS_AS(tmp.reset(new Fraction{"2/0"}), std::invalid_argument);
    }
}

TEST_CASE("Conversion")
{
    SECTION("Proper whole value")
    {
        Fraction testvalue{2};

        auto oldVal = testvalue.whole();
        auto oldNum = testvalue.numerator();
        auto oldDenom = testvalue.denominator();
        CHECK_FALSE(testvalue.isProper());
        testvalue.makeProper();

        CHECK(testvalue.whole() == oldVal);
        CHECK(testvalue.numerator() == oldNum);
        CHECK(testvalue.denominator() == oldDenom);
    }

    SECTION("Always improper")
    {
        Fraction a{"3 12/3"};

        CHECK_FALSE(a.isProper());
        a.makeProper();
        CHECK_FALSE(a.isProper());
        CHECK(a.whole() == 7);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
    }

    SECTION("Proper fraction")
    {
        Fraction testvalue{"6/13"};

        auto oldVal = testvalue.whole();
        auto oldNum = testvalue.numerator();
        auto oldDenom = testvalue.denominator();
        testvalue.makeProper();

        CHECK(testvalue.whole() == oldVal);
        CHECK(testvalue.numerator() == oldNum);
        CHECK(testvalue.denominator() == oldDenom);
        CHECK(testvalue.isProper());
    }

    SECTION("Improper fraction")
    {
        Fraction testvalue{"37/4"};

        auto oldVal = testvalue.whole();
        auto oldNum = testvalue.numerator();
        auto oldDenom = testvalue.denominator();

        CHECK_FALSE(testvalue.isProper());

        testvalue.makeProper();

        CHECK(testvalue.whole() != oldVal);
        CHECK(testvalue.whole() == 9);
        CHECK(testvalue.numerator() != oldNum);
        CHECK(testvalue.numerator() == 1);
        CHECK(testvalue.denominator() == oldDenom);
    }

    SECTION("makeProper on wholenumber")
    {
        Fraction a{51};

        a.makeProper();
        CHECK(a.whole() == 51);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
    }

    SECTION("makeproper into whole number")
    {
        Fraction testvalue{"36/4"};

        testvalue.makeProper();

        CHECK(testvalue.whole() == 9);
        CHECK(testvalue.numerator() == 0);
        CHECK(testvalue.denominator() == 1);
    }

    SECTION("toProper on proper fraction")
    {
        Fraction testValue{"13/79"};
        Fraction out = testValue.toProper();

        CHECK(out.whole() == 0);
        CHECK(out.numerator() == 13);
        CHECK(out.denominator() == 79);
    }

    SECTION("toProper")
    {
        Fraction testValue{"130/12"};
        Fraction out = testValue.toProper();

        CHECK(out.whole() == 10);
        CHECK(out.numerator() == 10);
        CHECK(out.denominator() == 12);
    }
}

TEST_CASE("Input")
{
    SECTION("Whole number only")
    {
        istringstream source("[0]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 0); //0
        CHECK(num.numerator() == 0);
        CHECK(num.denominator() == 1);
        CHECK(num.isPositive());
    }

    SECTION("Whole number only")
    {
        istringstream source("[3]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 3);
        CHECK(num.numerator() == 0);
        CHECK(num.denominator() == 1);
        CHECK(num.isPositive());
    }

    SECTION("Negative whole number only")
    {
        istringstream source("[-3]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 3);
        CHECK(num.numerator() == 0);
        CHECK(num.denominator() == 1);
        CHECK_FALSE(num.isPositive());
    }

    SECTION("Read whole number only among other data")
    {
        istringstream source("text [3]234");
        Fraction num;
        string before;
        int after;

        source >> before >> num >> after;
        CHECK(before == "text");
        CHECK(after == 234);
        CHECK(num.whole() == 3);
        CHECK(num.numerator() == 0);
        CHECK(num.denominator() == 1);
        CHECK(num.isPositive());
    }

    SECTION("Fraction only")
    {
        istringstream source("[113/219]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 0);
        CHECK(num.numerator() == 113);
        CHECK(num.denominator() == 219);
        CHECK(num.isPositive());
    }

    SECTION("Negative Fraction only")
    {
        istringstream source("[-113/219]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 0);
        CHECK(num.numerator() == 113);
        CHECK(num.denominator() == 219);
        CHECK_FALSE(num.isPositive());
    }

    SECTION("Whole and fraction")
    {
        istringstream source("[27 113/219]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 27);
        CHECK(num.numerator() == 113);
        CHECK(num.denominator() == 219);
        CHECK(num.isPositive());
    }

    SECTION("Negative Whole and fraction")
    {
        istringstream source("[-27 113/219]");
        Fraction num;

        source >> num;

        CHECK(num.whole() == 27);
        CHECK(num.numerator() == 113);
        CHECK(num.denominator() == 219);
        CHECK_FALSE(num.isPositive());
    }

    SECTION("zero denonimator")
    {
        istringstream source("[14/0]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("zero denonimator")
    {
        istringstream source("[2 14/0]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }
}

TEST_CASE("Invalid Input")
{
    SECTION("Whole number missing [")
    {
        istringstream source("283]"); // Missing '['
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Whole number missing ]")
    {
        istringstream source("[13");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Whole number missing ], found invalid character")
    {
        istringstream source("[13?");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Invalid numerator")
    {
        istringstream source("[13 abc/45]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Invalid denominator")
    {
        istringstream source("[13 20/abd]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Invalid character after whole number")
    {
        istringstream source("[13,5/7]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Invalid character between num/denum")
    {
        istringstream source("[13 5#7]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Invalid character at the end")
    {
        istringstream source("[13 5/7$");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Non numeric character")
    {
        istringstream source("[abcd]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("No numbers")
    {
        istringstream source("[]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("No numbers, got invalid character")
    {
        istringstream source("[#");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("No numbers only negative sign")
    {
        istringstream source("[-]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Negative numerator")
    {
        istringstream source("20 -5/17]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }

    SECTION("Negative denominator")
    {
        istringstream source("20 5/-17]");
        Fraction num;
        CHECK_THROWS_AS(source >> num, std::invalid_argument);
    }
}

TEST_CASE("Reduction")
{
    SECTION("Verify if fraction is reduced")
    {
        Fraction a{"15/35"};
        Fraction b{"35/15"};
        CHECK_FALSE(a.isReduced());
        CHECK_FALSE(b.isReduced());
    }

    SECTION("reduce()")
    {
        Fraction a{"270/390"};
        a.reduce();

        CHECK(a.whole() == 0);
        CHECK(a.numerator() == 9);
        CHECK(a.denominator() == 13);
    }

    SECTION("reduce() relative prime")
    {
        Fraction a{"270/391"};
        a.reduce();

        CHECK(a.isReduced());
        CHECK(a.whole() == 0);
        CHECK(a.numerator() == 270);
        CHECK(a.denominator() == 391);
    }

    SECTION("toReduced() relative prime")
    {
        Fraction a{"270/390"};
        Fraction b = a.toReduced();

        CHECK(b.whole() == 0);
        CHECK(b.numerator() == 9);
        CHECK(b.denominator() == 13);
    }

    SECTION("Reduction big number")
    {
        Fraction a{"13 400/1000"};
        a.reduce();

        CHECK(a.isPositive());
        CHECK(a.whole() == 13);
        CHECK(a.numerator() == 2);
        CHECK(a.denominator() == 5);
    }

    SECTION("Reduction big number (negative)")
    {
        Fraction a{"-13 400/1000"};
        a.reduce();

        CHECK_FALSE(a.isPositive());
        CHECK(a.whole() == 13);
        CHECK(a.numerator() == 2);
        CHECK(a.denominator() == 5);
    }
}

TEST_CASE("Output")
{

    SECTION("zero")
    {
        Fraction x;
        ostringstream out;
        out << x;
        CHECK(out.str() == "[0]");
    }

    SECTION("positive whole number")
    {
        Fraction x{3};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[3]");
    }

    SECTION("positive fraction only")
    {
        Fraction x{"7/19"};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[7/19]");
    }

    SECTION("positive whole and fraction")
    {
        Fraction x{"5 8/19"};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[5 8/19]");
    }

    SECTION("Negative whole number")
    {
        Fraction x{-3};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[-3]");
    }

    SECTION("Negative whole and fraction")
    {
        Fraction x{"-5 8/19"};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[-5 8/19]");
    }

    SECTION("Negative fraction only")
    {
        Fraction x{"-7/19"};
        ostringstream out;
        out << x;
        CHECK(out.str() == "[-7/19]");
    }
}

TEST_CASE("Operator Assignment")
{
    SECTION("Move Assignment")
    {
        Fraction one{"-3 7/19"};
        Fraction two;

       
        two = std::move(one);
        CHECK(two.whole() == 3);
        CHECK_FALSE(two.isPositive());
        CHECK(two.numerator() == 7);
        CHECK(two.denominator() == 19);
    }

    SECTION("Copy Assignment")
    {
        Fraction one{"-8 6/19"};
        Fraction two;
        two = one;
        CHECK(two.whole() == 8);
        CHECK_FALSE(two.isPositive());
        CHECK(two.numerator() == 6);
        CHECK(two.denominator() == 19);
    }
}

TEST_CASE("Operator +")
{
    SECTION("Fraction as first operand")
    {
        Fraction one{"2 6/13"};
        Fraction sum;

        sum = one + 5;
        CHECK(sum.whole() == 7);
        CHECK(sum.numerator() == 6);
        CHECK(sum.denominator() == 13);
        CHECK(sum.isPositive());
    }

    SECTION("Fraction as second operand")
    {
        Fraction one{"2 6/13"};
        Fraction sum;

        sum = 15 + one;
        CHECK(sum.whole() == 17);
        CHECK(sum.numerator() == 6);
        CHECK(sum.denominator() == 13);
        CHECK(sum.isPositive());
    }

    SECTION("With negative number and fraction as second operand")
    {
        Fraction one{"2 6/13"};
        Fraction sum;

        sum = -14 + one; // -11 7/13
        CHECK(sum.whole() == 12);
        CHECK(sum.numerator() == 6);
        CHECK(sum.denominator() == 13);
        CHECK_FALSE(sum.isPositive());
    }

    SECTION("Add two positive fractions")
    {
        Fraction a{"21 5/6"};
        Fraction b{"9 3/4"};
        Fraction sum = a + b; // 21 10/12 + 9 9/12 = 30 19/12 = 31 7/12

        CHECK(sum.isPositive());
        CHECK(sum.whole() == 31);
        CHECK(sum.numerator() == 7);
        CHECK(sum.denominator() == 12);
    }

    SECTION("Add two negative fractions")
    {
        Fraction a{"-17 5/8"};
        Fraction b{"-3 3/14"};
        Fraction sum = a + b; // -17 35/56 - 3 12/56 = -20 47/56

        CHECK_FALSE(sum.isPositive());
        CHECK(sum.whole() == 20);
        CHECK(sum.numerator() == 47);
        CHECK(sum.denominator() == 56);
    }

    SECTION("Add two fractions with different sign, negative result")
    {
        Fraction a{"-10 5/7"};
        Fraction b{"5 3/14"};
        Fraction sum = a + b; // -10 10/14 + 5 3/14 =

        CHECK_FALSE(sum.isPositive());
        CHECK(sum.whole() == 5);
        CHECK(sum.numerator() == 1);
        CHECK(sum.denominator() == 2);
    }

    SECTION("Add two fractions with different sign, positive result")
    {
        Fraction a{"11 5/7"};
        Fraction b{"-9 3/14"};
        Fraction sum = a + b;

        CHECK(sum.isPositive());
        CHECK(sum.whole() == 2);
        CHECK(sum.numerator() == 1);
        CHECK(sum.denominator() == 2);
    }
}

TEST_CASE("Operator -")
{
    SECTION("Fraction as first operand")
    {
        Fraction one{"2 6/13"};
        Fraction sum;

        sum = one - 5;
        CHECK(sum.whole() == 2);
        CHECK(sum.numerator() == 7);
        CHECK(sum.denominator() == 13);
        CHECK_FALSE(sum.isPositive());
    }

    SECTION("Fraction as second operand")
    {
        Fraction one{"2 6/13"};
        Fraction sum;

        sum = 15 - one;
        CHECK(sum.whole() == 12);
        CHECK(sum.numerator() == 7);
        CHECK(sum.denominator() == 13);
        CHECK(sum.isPositive());
    }

    SECTION("Subtract two positive fractions. positive result")
    {
        Fraction a{"33 5/6"};
        Fraction b{"9 3/4"};
        Fraction sum = a - b; // 33 10/12 - 9 9/12 = 33 19/12 = 24 1/12

        CHECK(sum.isPositive());
        CHECK(sum.whole() == 24);
        CHECK(sum.numerator() == 1);
        CHECK(sum.denominator() == 12);
    }

    SECTION("Subtract two positive fractions. negative result")
    {
        Fraction a{"33 5/6"};
        Fraction b{"9 3/4"};
        Fraction sum;
        sum = b - a; 
        // -33 10/12 + 9 9/12 =
        // -33 19/12 = 
        //-24 1/12

        CHECK_FALSE(sum.isPositive());
        CHECK(sum.whole() == 24);
        CHECK(sum.numerator() == 1);
        CHECK(sum.denominator() == 12);
    }

    SECTION("Subtract two negative fractions")
    {
        Fraction a{"-17 5/8"};
        Fraction b{"-3 3/14"};
        Fraction sum;
        sum = a - b; // -17 35/56 + 3 12/56 = -14 23/56

        CHECK_FALSE(sum.isPositive());
        CHECK(sum.whole() == 14);
        CHECK(sum.numerator() == 23);
        CHECK(sum.denominator() == 56);
    }

    SECTION("Subtract to zero")
    {
        Fraction one{"4 17/30"};

        Fraction zero;
        zero = one - one;
        CHECK(zero.isPositive());
        CHECK(zero.whole() == 0);
        CHECK(zero.numerator() == 0);
        CHECK(zero.denominator() == 1);
    }
}

TEST_CASE("Operator - (unary)")
{
    SECTION("Flip positive whole number")
    {
        Fraction a{"517"};
        Fraction b;
        b = -a;
        CHECK_FALSE(b.isPositive());
        CHECK(b.whole() == 517);
        CHECK(b.numerator() == 0);
        CHECK(b.denominator() == 1);
    }

    SECTION("Flip negative whole number")
    {
        Fraction a{"-517"};
        Fraction b;
        b = -a;
        CHECK(b.isPositive());
        CHECK(b.whole() == 517);
        CHECK(b.numerator() == 0);
        CHECK(b.denominator() == 1);
    }

    SECTION("Flip positive fraction only")
    {
        Fraction a{"51/73"};
        Fraction b;
        b = -a;
        CHECK_FALSE(b.isPositive());
        CHECK(b.whole() == 0);
        CHECK(b.numerator() == 51);
        CHECK(b.denominator() == 73);
    }

    SECTION("Flip negative fraction only")
    {
        Fraction a{"-51/73"};
        Fraction b;
        b = -a;
        CHECK(b.isPositive());
        CHECK(b.whole() == 0);
        CHECK(b.numerator() == 51);
        CHECK(b.denominator() == 73);
    }

    SECTION("Flip positive mixed fraction")
    {
        Fraction a{"23 51/73"};
        Fraction b;
        b = -a;
        CHECK_FALSE(b.isPositive());
        CHECK(b.whole() == 23);
        CHECK(b.numerator() == 51);
        CHECK(b.denominator() == 73);
    }

    SECTION("Flip positive mixed fraction")
    {
        Fraction a{"-23 51/73"};
        Fraction b;
        b = -a;
        CHECK(b.isPositive());
        CHECK(b.whole() == 23);
        CHECK(b.numerator() == 51);
        CHECK(b.denominator() == 73);
    }
}

TEST_CASE("Multiplication")
{
    SECTION("Multiplication with scalar on right")
    {
        Fraction one{"2 9/15"};

        Fraction prod;
        prod = one * 4;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 10);
        CHECK(prod.numerator() == 2);
        CHECK(prod.denominator() == 5);
    }

    SECTION("Multiplication with scalar on left")
    {
        Fraction one{"2 9/15"};

        Fraction prod;
        prod = 4 * one;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 10);
        CHECK(prod.numerator() == 2);
        CHECK(prod.denominator() == 5);
    }

    SECTION("Multiplication with zero on left")
    {
        Fraction one{"2 9/15"};

        Fraction prod;
        prod = 0 * one;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 0);
        CHECK(prod.denominator() == 1);
    }

    SECTION("Multiplication with zero on right")
    {
        Fraction one{"2 9/15"};

        Fraction prod;
        prod = one * 0;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 0);
        CHECK(prod.numerator() == 0);
        CHECK(prod.denominator() == 1);
    }

    SECTION("Multiplication with -1")
    {
        Fraction one{"2 9/15"};

        Fraction prod;
        prod = one * -1;

        CHECK_FALSE(prod.isPositive());
        CHECK(prod.whole() == 2);
        CHECK(prod.numerator() == 3);
        CHECK(prod.denominator() == 5);
    }

    SECTION("Multiply two positive fractions")
    {
        Fraction one{"3 7/11"};
        Fraction two{"5 8/9"};

        Fraction prod;
        prod = one * two;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 21);
        CHECK(prod.numerator() == 41);
        CHECK(prod.denominator() == 99);
    }

    SECTION("Multiply two negative fractions")
    {
        Fraction one{"-3 7/11"};
        Fraction two{"-5 8/9"};

        Fraction prod;
        prod = one * two;

        CHECK(prod.isPositive());
        CHECK(prod.whole() == 21);
        CHECK(prod.numerator() == 41);
        CHECK(prod.denominator() == 99);
    }

    SECTION("Multiply two fractions of different sign")
    {
        Fraction one{"3 7/11"};
        Fraction two{"-5 8/9"};

        Fraction prod;
        prod = one * two;

        CHECK_FALSE(prod.isPositive());
        CHECK(prod.whole() == 21);
        CHECK(prod.numerator() == 41);
        CHECK(prod.denominator() == 99);
    }
}

TEST_CASE("Operator[]")
{
    SECTION("Positive whole number")
    {
        Fraction a{"4"};

        CHECK(a[0].has_value());
        CHECK(a[0] == 4);
        CHECK_FALSE(a[1].has_value());
        CHECK_FALSE(a[2].has_value());
    }

    SECTION("Positive fraction")
    {
        Fraction a{"4/19"};

        CHECK_FALSE(a[0].has_value());
        CHECK(a[1].has_value());
        CHECK(a[1] == 4);
        CHECK(a[2].has_value());
        CHECK(a[2] == 19);
    }

    SECTION("Positive mixed fraction")
    {
        Fraction a{"21 4/19"};
        INFO("Tested fraction 21 4/19");

        CHECK(a[0].has_value());
        CHECK(a[0] == 21);
        CHECK(a[1].has_value());
        CHECK(a[1] == 4);
        CHECK(a[2].has_value());
        CHECK(a[2] == 19);
    }

    SECTION("Negative whole number")
    {
        Fraction a{"-4"};

        CHECK(a[0].has_value());
        CHECK(a[0] == -4);
        CHECK_FALSE(a[1].has_value());
        CHECK_FALSE(a[2].has_value());
    }

    SECTION("Negative fraction")
    {
        Fraction a{"-4/19"};
        INFO("Tested fraction -4/19");

        CHECK_FALSE(a[0].has_value());
        CHECK(a[1].has_value());
        CHECK(a[1] == -4);
        CHECK(a[2].has_value());
        CHECK(a[2] == 19);
    }

    SECTION("Positive mixed fraction")
    {
        Fraction a{"-21 4/19"};

        INFO("Tested fraction -21 4/19");
        CHECK(a[0].has_value());
        CHECK(a[0] == -21);
        CHECK(a[1].has_value());
        CHECK(a[1] == 4);
        CHECK(a[2].has_value());
        CHECK(a[2] == 19);
    }
}

TEST_CASE("Arithmetic result must be proper and reduced")
{
    SECTION("Add two fractions with reduced result")
    {
        Fraction a{"5 3/40"};
        Fraction b{"9 27/40"};

        a = a + b;
        CHECK(a.isPositive());
        CHECK(a.whole() == 14);
        CHECK(a.numerator() == 3);
        CHECK(a.denominator() == 4);
    }

    SECTION("Multiple two fractions with who result")
    {
        Fraction a{"-3/40"};
        Fraction b{"40/3"};

        a = a * b;
        CHECK_FALSE(a.isPositive());
        CHECK(a.whole() == 1);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
    }

    SECTION("Multiply with int")
    {
        Fraction a{"6 4/7"};

        a = a * 7;
        CHECK(a.isPositive());
        CHECK(a.whole() == 46);
        CHECK(a.numerator() == 0);
        CHECK(a.denominator() == 1);
    }

    SECTION("Multiply two fractions")
    {
        Fraction a{"2/5"};
        Fraction b{"5 1/3"};

        a = a * b;
        CHECK(a.isPositive());
        CHECK(a.whole() == 2);
        CHECK(a.numerator() == 2);
        CHECK(a.denominator() == 15);
    }
}

TEST_CASE("operator==")
{
    SECTION("Different sign")
    {
        Fraction a{"-4 7/8"};
        Fraction b{"6 3/10"};

        CHECK_FALSE(a == b);
    }

    SECTION("Positive fractions: equal")
    {
        Fraction a{"4 7/8"};
        Fraction b{"4 77/88"};

        CHECK(a == b);
    }

    SECTION("Negative fractions: equal")
    {
        Fraction a{"-4 7/8"};
        Fraction b{"-4 91/104"};

        CHECK(a == b);
    }

    SECTION("Positive fractions: not equal")
    {
        Fraction a{"4 7/8"};
        Fraction b{"4 74/88"};

        CHECK_FALSE(a == b);
    }

    SECTION("Negative fractions: not equal")
    {
        Fraction a{"-33 5/8"};
        Fraction b{"-33 74/88"};

        CHECK_FALSE(a == b);
    }
}

TEST_CASE("Operator<")
{
    SECTION("Different sign")
    {
        Fraction a{"-10 5/7"};
        Fraction b{"3 17/20"};
        CHECK(a < b);
        CHECK_FALSE(b < a);
    }

    SECTION("Both positive")
    {
        //75/7
        //1500/140
        Fraction a{"10 5/7"};
        //77/20
        //539/140
        Fraction b{"3 17/20"};

        CHECK(a.numerator() == 1500);
        CHECK(a.denominator() == 140);
        CHECK(b.numerator() == 539);
        CHECK(b.denominator() == 140);
        CHECK_FALSE(a < b);
        CHECK(b < a);
    }

    SECTION("Both negative: mixed and fraction")
    {
        Fraction a{"-5/6"};
        Fraction b{"-1 17/20"};
        CHECK_FALSE(a < b);
        CHECK(b < a);
    }

    SECTION("Both positive: mixed and fraction only")
    {
        Fraction a{"15/3"};
        Fraction b{"1 20/20"};
        CHECK_FALSE(a < b);
        CHECK(b < a);
    }
}

TEST_CASE("Fraction arithmetic")
{
    Fraction one{"3 12/25"};
    Fraction two{"11 4/5"};
    Fraction result;

    result = one + two - two * one;
    CHECK_FALSE(result.isPositive());
    CHECK(result.whole() == 25);
    CHECK(result.numerator() == 98);
    CHECK(result.denominator() == 125);
}

#if I_DO_EXTRA_CREDIT

TEST_CASE("Repeating Fraction")
{
    std::map<int, string> repeating;
    repeating[3] = "0.3";
    repeating[6] = "0.16";
    repeating[7] = "0.142857";
    repeating[9] = "0.1";
    repeating[11] = "0.09";
    repeating[12] = "0.083";
    repeating[13] = "0.076923";
    repeating[14] = "0.0714285";
    repeating[15] = "0.06";
    repeating[17] = "0.0588235294117647";
    repeating[18] = "0.05";
    repeating[19] = "0.052631578947368421";
    optional<string> out;
    for (int k = 2; k < 20; k++)
    {
        Fraction a{"1/" + std::to_string(k)};
        out = a.isRepeating();
        auto r = repeating.find(k);
        if (r != repeating.end())
        {
            CHECK(out.has_value());
            CHECK(r->second == *out);
        }
        else
        {
            CHECK_FALSE(out.has_value());
        }
    }
}

TEST_CASE("Operator()")
{
    SECTION("Positive mixed")
    {
        Fraction a{"123 1/2"};

        CHECK(a(2) == "124");
        CHECK(a(3) == "124");
        CHECK(a(4) == "124.");
        CHECK(a(5) == "123.5");
        CHECK(a(6) == "123.50");
        CHECK(a(7) == "123.500");
    }

    SECTION("Negative mixed")
    {
        Fraction a{"-123 1/2"};

        CHECK(a(2) == "-124");
        CHECK(a(3) == "-124");
        CHECK(a(4) == "-124");
        CHECK(a(5) == "-124.");
        CHECK(a(6) == "-123.5");
        CHECK(a(7) == "-123.50");
        CHECK(a(8) == "-123.500");
    }

    SECTION("Positive repeating")
    {
        Fraction a{"10 2/3"};

        CHECK(a(1) == "11");
        CHECK(a(2) == "11");
        CHECK(a(3) == "11.");
        CHECK(a(4) == "10.7");
        CHECK(a(5) == "10.67");
        CHECK(a(6) == "10.667");
        CHECK(a(7) == "10.6667");
    }

    SECTION("Negative repeating")
    {
        Fraction a{"-10 2/3"};

        CHECK(a(1) == "-11");
        CHECK(a(2) == "-11");
        CHECK(a(3) == "-11");
        CHECK(a(4) == "-11.");
        CHECK(a(5) == "-10.7");
        CHECK(a(6) == "-10.67");
        CHECK(a(7) == "-10.667");
    }

    SECTION("Positive repeating fration only")
    {
        Fraction a{"2/3"};

        CHECK(a(1) == ".7");
        CHECK(a(2) == ".7");
        CHECK(a(3) == ".67");
        CHECK(a(4) == ".667");
        CHECK(a(5) == ".6667");
    }

    SECTION("Positive repeating fraction only")
    {
        Fraction a{"1/7"};
        // 0.142857
        CHECK(a(1) == ".1");
        CHECK(a(2) == ".1");
        CHECK(a(3) == ".14");
        CHECK(a(4) == ".143");
        CHECK(a(5) == ".1429");
        CHECK(a(6) == ".14286");
        CHECK(a(7) == ".142857");
        CHECK(a(8) == ".1428571");
        CHECK(a(9) == ".14285714");
        CHECK(a(10) == ".142857143");
        CHECK(a(11) == ".1428571429");
        CHECK(a(12) == ".14285714286");
        CHECK(a(13) == ".142857142857");
    }

    SECTION("Zero")
    {
        Fraction zero;

        for (int k = 1; k < 20; k++)
            CHECK(zero(k) == "0");
    }
}
#endif