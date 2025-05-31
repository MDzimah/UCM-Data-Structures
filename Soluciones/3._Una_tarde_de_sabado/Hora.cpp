#include "Hora.h"
#include <assert.h>

bool Hora::operator<(Hora const& o) const {
	if (this->hh < o.hh) return true;
	else if (this->hh == o.hh) {
		if (this->mm < o.mm) return true;
		else if (this->mm == o.mm) {
			if (this->ss < o.ss) return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

bool Hora::operator==(Hora const& o) const {
	return this->hh == o.hh && this->mm == o.mm && this->ss == o.ss;
}

void Hora::print(std::ostream& out) const {
	out << std::setfill('0') << std::setw(2) << this->hh << ':' << std::setw(2) << this->mm << ':' << std::setw(2) << this->ss;
}

void Hora::read(std::istream& in) {
	char aux;
	in >> this->hh >> aux >> this->mm >> aux >> this->ss;
}

Hora Hora::operator+(Hora const& b) {
	Hora aux; 
	int ss, mm, hh, sum_ss, sum_mm, sum_hh;

	sum_ss = this->ss + b.ss;
	aux.ss = sum_ss%60;

	sum_mm = sum_ss / 60 + this->mm + b.mm;
	aux.mm = sum_mm % 60;

	sum_hh = sum_mm / 60 + this->hh + b.hh;
	aux.hh = sum_hh % 24;

	assert(sum_hh/24 == 0);
	return aux;
}

std::istream& operator>>(std::istream& in, Hora& h) {
	h.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Hora& h) {
	h.print(out);
	return out;
}