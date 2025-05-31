#include <iostream>
#include <unordered_map>
#include <vector>

bool res() {
	int N; std::cin >> N;
	if (!std::cin) return false;

	//Nombre juego a vector donde pos i+1: es la vez jugada y v[i] es el día q se jugó
	std::unordered_map<std::string, std::vector<int>> m;
	for (int i = 1; i <= N; ++i) {
		std::string j; std::cin >> j;
		m[j].push_back(i);
	}

	int M; std::cin >> M;
	while (M--) {
		int vez; std::string j;
		std::cin >> vez >> j;
		auto pair = m.find(j);
		if (pair == m.end() || vez > pair->second.size()) std::cout << "NO JUEGA\n";
		else std::cout << pair->second[vez-1] << '\n';
	}
	std::cout << "---\n";
	return true;
}

int main() {
	while (res());
	return 0;
}