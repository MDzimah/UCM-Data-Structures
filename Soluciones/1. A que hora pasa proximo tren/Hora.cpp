#include "Hora.h"

void Hora::print(std::ostream& out) const {
	out << std::setfill('0') << std::setw(2) << this->hh << ':' << std::setw(2) << this->mm << ':' << std::setw(2) << this->ss;
}

void Hora::read(std::istream& in) {
	char aux;
	in >> this->hh >> aux >> this->mm >> aux >> this->ss;
}

std::istream& operator>>(std::istream& in, Hora& h) {
	h.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Hora& h) {
	h.print(out);
	return out;
}