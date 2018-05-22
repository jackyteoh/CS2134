#ifndef Rational_hpp
#define Rational_hpp
#include <iostream>
#include <cstdlib>

namespace CS1124 {
	class Rational {
	private:
		int numerator;
		int denominator;
	public:
		Rational();
		Rational(int denominator);
		Rational(int top / int bottom);
		int getNumerator() const;
		int getDenominator() const;

	};
}

