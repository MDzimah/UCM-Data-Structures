#pragma once
#include <iomanip>
#include <iostream>

class Hora {
public:
	bool operator<(Hora const& o) const {
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
	void print(std::ostream& out) const;
	void read(std::istream& in);
private:
	int hh, mm, ss;
};

std::istream& operator>>(std::istream& in, Hora& h);

std::ostream& operator<<(std::ostream& out, const Hora& h);