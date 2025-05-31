#include "Cartelera.h"

void Cartelera::read(std::istream& in) {
	for (int i = 0; i < this->c.size(); ++i) {
		in >> this->c[i];
		this->c[i].calcHoraTermina();
	}
}

void Cartelera::imprimir(std::ostream& out) const {
	for (int i = 0; i < this->c.size(); ++i)
		out << c[i];
	out << "---\n";
}

void Cartelera::ordenar() {
	std::sort(this->c.begin(), this->c.end());
}

std::istream& operator>>(std::istream& in, Cartelera& c) {
	c.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, Cartelera const& c) {
	c.imprimir(out);
	return out;
}

