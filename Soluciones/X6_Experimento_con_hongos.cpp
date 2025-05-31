#include <iostream>
#include <queue>

bool res() {
    int N, M, T; std::cin >> N >> M >> T;

    if (!std::cin) return false;

    int sumaNumH = 0;

    //Pos i = hongos q se reproducen dentro de i-horas (front() ~ ahora)
    std::queue<int> adultos;

    //Inicialmente no hay adultos listos para reproducirse hasta dentro de N horas
    for (int i = 0; i < N - 1; ++i) 
        adultos.push(0);

    //Hongo adulto inicial
    adultos.push(1);

    //Pos i = yemas q se convierten en adultos dentro de i-horas (front() ~ ahora)
    std::queue<int> yemas;

    //M-N pq el resto del tiempo (N) se simula en la cola de adultos
    for (int i = 0; i < M - N; ++i)
        yemas.push(0);

    for (int i = 0; i < T; ++i) {
        yemas.push(adultos.front()); //Se meten las yemas generadas por los adultos de esta hora
        adultos.push(adultos.front() + yemas.front()); //Se meten las yemas que se convierten en adultos y los adultos que ya había en esta hora

        //Avance de 1h
        adultos.pop();
        yemas.pop(); 
    }

    //Suma hongos adultos
    while (!adultos.empty()) {
        sumaNumH += adultos.front();
        adultos.pop();
    }

    //Sumamos hongos yemas
    while (!yemas.empty()) {
        sumaNumH += yemas.front();
        yemas.pop();
    }

    std::cout << sumaNumH << '\n';

    return true;
}


int main() {
	while (res());
	return 0;
}