#include "Complejo.h"

Complejo operator+(Complejo const& a, Complejo const& b) {
    return Complejo(a.getRe() + b.getRe(), a.getIm() + b.getIm());
}

Complejo operator*(Complejo const& a, Complejo const& b) {
    return Complejo(a.getRe()*b.getRe() - a.getIm()*b.getIm(), a.getRe()*b.getIm() + b.getRe()*a.getIm());
}

std::istream& operator>>(std::istream& in, Complejo& c){
    c.read(in);
    return in;
}

void Complejo::read(std::istream& in) {
    in >> this->re >> this->im;
}
