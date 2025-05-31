#pragma once
#include <iostream>
#include <cmath>

class Complejo {

public:
	Complejo() {}
	Complejo(double parteRe, double parteIm) : re(parteRe), im(parteIm) {}
	long double getRe() const { return this->re; }
	long double getIm() const { return this->im; }
	long double modulo() const { return sqrt(this->re * this->re + this->im * this->im); }
	bool isInMandelbrot(int numIt) {
		Complejo actual(this->re, this->im), anterior(0, 0);
		if (actual.modulo() <= 2) {
			anterior = actual;
			bool res = true;
			for (int i = 2; i <= numIt && res; ++i) {
				actual = (anterior * anterior) + (*this);
				if (actual.modulo() > 2) res = false;
				else anterior = actual;
			}
			return res;
		}
		else return false;
	}
	void read(std::istream& in);
	friend Complejo operator+(Complejo const& a, Complejo const& b);
	friend Complejo operator*(Complejo const& a, Complejo const& b);

private:
	long double re, im;
};


std::istream& operator>>(std::istream& in, Complejo& c);
