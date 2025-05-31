#pragma once
#include <iomanip>
#include <iostream>

class Hora {
public:
	bool operator<(Hora const& o) const;
	bool operator==(Hora const& o) const;
	void print(std::ostream& out) const;
	void read(std::istream& in);
	Hora operator+(Hora const& b);
private:
	int hh, mm, ss;
};

std::istream& operator>>(std::istream& in, Hora& h);
std::ostream& operator<<(std::ostream& out, const Hora& h);