#include "hw07.h"

#include <algorithm>
#include <stdexcept>

namespace cppclass {

Fraction::Fraction(int numerator, int denominator) 
        : _numerator(numerator), 
        _denominator(denominator) {
        if (_denominator == 0) {
                throw std::runtime_error("Attempted to divide by zero");
        }
        _simplify();
}

void Fraction::_simplify() {
        if (_numerator == 0) {
                _denominator = 1;
                return;
        }
        if (_denominator < 0) {
                _numerator = _numerator * -1;
                _denominator = _denominator * -1;
        }
        int gcd = _gcd(_numerator, _denominator);
        _numerator = _numerator / gcd;
        _denominator = _denominator / gcd;
}

int Fraction::_gcd(int a, int b) {
        for (int i = abs(a); i > 0; i--) {
                if (a % i == 0 && b % i == 0) {
                        return i;
                }
        }
        return 1;
}

int Fraction::_lcm(int a, int b) {
        return a * b / _gcd(a, b);
}

Fraction Fraction::operator+(const Fraction &other) const {
        int lcm = _lcm(this->_denominator, other._denominator);
        int denominator = lcm;
        int numerator = (this->_numerator * lcm / this->_denominator)
                + (other._numerator * lcm / other._denominator);
        Fraction answer(numerator, denominator);
        return answer;
}

Fraction Fraction::operator-(const Fraction &other) const {
        int lcm = _lcm(this->_denominator, other._denominator);
        int denominator = lcm;
        int numerator = (this->_numerator * lcm / this->_denominator)
                - (other._numerator * lcm / other._denominator);
        Fraction answer(numerator, denominator);
        return answer;
}

Fraction Fraction::operator*(const Fraction &other) const {
        int numerator = this->_numerator * other._numerator;
        int denominator = this->_denominator * other._denominator;
        Fraction answer(numerator, denominator);
        return answer;
}

Fraction Fraction::operator/(const Fraction &other) const {
        int numerator = this->_numerator * other._denominator;
        int denominator = this->_denominator * other._numerator;
        Fraction answer(numerator, denominator);
        return answer;
}

bool Fraction::operator==(const Fraction &other) const {
        Fraction local_other = other;
        Fraction local_this(this->_numerator, this->_denominator);
        if (local_other._denominator == local_this._denominator &&
                local_other._numerator == local_this._numerator) {
                return true;
        }
        return false;
}

bool Fraction::operator!=(const Fraction &other) const {
        Fraction local_other = other;
        Fraction local_this(this->_numerator, this->_denominator);
        if (local_other._denominator != local_this._denominator ||
                local_other._numerator == local_this._numerator) {
                return true;
        }
        return false;
}

} // namespace cppclass
