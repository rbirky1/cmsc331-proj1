/*
 * Rachael Birky
 * 03.25.2014
 * CMSC 331
 * Spring 2014
 *
 * Coding Project 1
 * Based on "C++ Cheat Sheet for CMSC 331"
 *
 * Additions:
 * 1. Add a square root function to the rational class.
 * 2. Add a harmonic series sum function to the program.
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>
using namespace std;

#include <assert.h>

// class rational

class rational {
public:

  // Function Declarations
  rational ();
  rational (int);
  rational (int,int);

  // const = constant
  rational (const rational &);

  /* accessor functions */
  int numerator () const;
  int denominator () const;

  /* assignments */
  void operator = (const rational &);
  void operator += (const rational &);

  /* arithmetic */
  friend rational operator + (const rational &, const rational &);
  friend rational operator - (const rational &, const rational &);
  friend rational operator - (const rational &);  // unary -, i,e, negation

  /* comparison */
  friend bool operator < (const rational &, const rational &);
  friend bool operator > (const rational &, const rational &);
  friend bool operator == (const rational &left, const rational &right);

  /* output */
  friend ostream & operator << (ostream &, const rational &);

private:
  //private instance variables
  int top;
  int bottom;
};


// Constructors
rational::rational()
{
	// make zero the default value
  top = 0;
  bottom = 1;
}

rational::rational(int numerator)
{
  // integer x becomes rational x/1
  top = numerator;
  bottom = 1;
}

rational::rational(int numerator, int denominator)
{
  //input validation
  assert( denominator != 0 );

  //x,y becomes x/y
  top = numerator;
  bottom = denominator;
}

rational::rational(const rational & value)
{
  // use one rational to initialize another
  top = value.numerator();
  bottom = value.bottom;
}


// Accessors
int rational::numerator()   const { return top; }
int rational::denominator() const { return bottom; }

// Assignments
void rational::operator = (const rational &right)
{
  top =    right.numerator();
  bottom = right.denominator();
}

void rational::operator += (const rational &right)
{
  *this = (*this)+right;
}


// Arithmetic
rational operator + (const rational &left, const rational &right)
{
  rational result(
		  left.numerator() * right.denominator() +
		  right.numerator() * left.denominator(),
		  left.denominator() * right.denominator());
  return result;
}

rational operator - (const rational &left, const rational &right)
{
  rational result(
		  left.numerator() * right.denominator() -
		  right.numerator() * left.denominator(),
		  left.denominator() * right.denominator());
  return result;
}

rational operator - (const rational &r)  // unary minus is negation
{
  // create a rational == 0 using the appropriate constructor
  return (0 - r);
}

// Comparison
bool operator < (const rational &left, const rational &right)
{
  return (left.numerator() * right.denominator()) <
    (right.numerator() * left.denominator());
}

bool operator > (const rational &left, const rational &right)
{
  return (left.numerator() * right.denominator()) >
    (right.numerator() * left.denominator());
}

bool operator == (const rational &left, const rational &right)
{
  return (left.numerator() * right.denominator() ==
	  left.denominator() * right.numerator());
}


// I/O
ostream & operator << (ostream & ostr, const rational &r)
{
  ostr << r.numerator() << "/" << r.denominator();
  return ostr;
}


// Other functions - not members or friends
rational invert(const rational &r)
{
  assert( r.numerator() != 0 );
  return rational(r.denominator(), r.numerator());
}

rational abs(const rational &r)
{
  if (r < 0) {
    return -r;
  } else {
    assert( (r == 0) || (r > 0) );   // demonstrate assert
    return r;
  }
}

// **** 1.Add a square root function to the rational class. ****
rational squareRoot(const rational &r)
{
	assert(r.numerator()>0);

	double top = r.numerator();
	double bot = r.denominator();

	double topSqrt = sqrt(top);
	double botSqrt = sqrt(bot);

	// Estimate if not a perfect square
	if ((fmod(topSqrt,1)!=0) ||(fmod(botSqrt,1)!=0))
	{
		topSqrt = sqrt(100*top);
		botSqrt = sqrt(100*bot);
	}
	return rational((int)topSqrt, (int)botSqrt);
}

// **** 2.Add a harmonic series sum function to the program. ****
rational harmonicSum(const int &n)
{

	assert(n!=0);

	rational sum(0,1);

	for (int i=1; i<=n; i++){
		rational thisRational(1,i);
		sum = sum + thisRational;
	}
	return sum;
}

int countCharacters(string fileName)
{

  int nChars = 0;
  char ch;
  fstream inputStream;
  try {
    inputStream.open(fileName);
  } catch (int e) {
    cerr << "Some problem with opening " << fileName << endl;
  }

  while (inputStream.get(ch)) {
    nChars += 1;
  }

  inputStream.close();
  return nChars;
}

void swap(int& x, int& y)
{
  int t;
  t = x;
  x = y;
  y = t;
}

void testSqrt()
{
	rational aRational1(1,2);

	rational aRational2(1,100);

	cout << "Square root of " << aRational1 << ": " << squareRoot(aRational1) << endl;

	cout << "Square root of " << aRational2 << ": " << squareRoot(aRational2) << endl;

}

void testHarmonicSum()
{
	int n=12;

	cout << "Harmonic sum of " << n << ": " << harmonicSum(n) << endl;
}

int main()
{
	cout << "\nTesting the square root function:" << endl;

	testSqrt();

	cout << endl << "Testing the harmonic sum function:" << endl;

	testHarmonicSum();

	cout << endl;

	exit(0);
}
