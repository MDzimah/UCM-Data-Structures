#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

std::map<std::string, int> read() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream ss(line);
	std::map<std::string, int> dicc;
	std::string K;
	int V;
	while (ss >> K >> V){
		dicc.insert({ K, V });
	}
	return dicc;
}

void display(std::vector<std::string> v, char c) {
	std::cout << c;
	for (int i = 0; i < v.size(); i++) {
		std::cout << ' ' << v[i];
	}
	std::cout << '\n';
}

void res() {
	std::map<std::string, int> old = read();
	std::map<std::string, int> rec = read();
	auto itOld = old.begin();
	auto itRec = rec.begin();
	std::vector<std::string> plus;
	std::vector<std::string> minus;
	std::vector<std::string> star;

	while (itOld != old.end() && itRec != rec.end()) {
		if (itOld->first == itRec->first) {
			if (itOld->second != itRec->second) {
				star.push_back(itOld->first);
			}
			++itOld;
			++itRec;
		}
		else {
			if (itOld->first < itRec->first) {
				minus.push_back(itOld->first);
				++itOld;
			}
			else {
				plus.push_back(itRec->first);
				++itRec;
			}
		}
	}
	while (itOld != old.end()) {
		minus.push_back(itOld->first);
		++itOld;
	}
	while (itRec != rec.end()) {
		plus.push_back(itRec->first);
		++itRec;
	}
	bool flag = false;
	if (!plus.empty()) {
		display(plus, '+');
		flag = true;
	}
	if (!minus.empty()) {
		display(minus, '-');
		flag = true;
	}
	if (!star.empty()) {
		display(star, '*');
		flag = true;
	}
	
	if (!flag) std::cout << "Sin cambios\n";
	std::cout << "---\n";
}

int main() {
	int nc; std::cin >> nc;
	std::cin.ignore();
	while (nc--) res();
	return 0;
}