#include <iostream>
#include <string>
#include "Rational.h"

using namespace std;

namespace CS1124 {
	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}
	void Rational::getNumerator() const {
		return numerator;
	}
	void Rational::getDenominator() const {
		return denominator;
	}
	Rational& Rational::operator++() {
		numerator += denominator;
		return *this;
	}
	Rational& Rational::operator++(int anyVariable) {
		Rational temp = *this;
		numerator += denominator;
		return *this;
	}
	Rational& Rational::operator+=() {

	}
}
