#include <iostream>
#include <vector>
#include <fstream>
/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Conjunto mediante árboles binarios de búsqueda.
  *
  * Esta versión incorpora parametricidad con respecto a la relación de orden.
  */

#include <cassert>


template <typename T, typename ComparatorFunction = std::less<T>>
class SetTree {
public:
    SetTree(ComparatorFunction less_than) : root_node(nullptr), num_elems(0), less_than(less_than) { }
    SetTree() : root_node(nullptr), num_elems(0) { }
    SetTree(const SetTree& other) : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) { }
    ~SetTree() {
        delete_nodes(root_node);
    }

    void insert(const T& elem) {
        bool inserted = insert(root_node, elem);
        if (inserted) { num_elems++; }
    }

    bool contains(const T& elem) const {
        return search(root_node, elem);
    }

    void erase(const T& elem) {
        bool removed = erase(root_node, elem);
        if (removed) { num_elems--; }
    }

    int size() const {
        return num_elems;
    }
    bool empty() const {
        return num_elems == 0;
    }

    SetTree& operator=(const SetTree& other) {
        if (this != &other) {
            num_elems = other.num_elems;
            delete_nodes(root_node);
            root_node = copy_nodes(other.root_node);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        display(root_node, out);
        out << "}";
    }

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right) : left(left), elem(elem), right(right) { }
    };

    Node* root_node;
    int num_elems;

    ComparatorFunction less_than;


    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->elem, copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    bool insert(Node*& root, const T& elem) {
        if (root == nullptr) {
            root = new Node(nullptr, elem, nullptr);
            return true;
        }
        else if (less_than(elem, root->elem)) {
            return insert(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return insert(root->right, elem);
        }
        else {
            return false;
        }
    }

    bool search(const Node* root, const T& elem) const {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return search(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return search(root->right, elem);
        }
        else {
            return true;
        }
    }

    bool erase(Node*& root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (less_than(elem, root->elem)) {
            return erase(root->left, elem);
        }
        else if (less_than(root->elem, elem)) {
            return erase(root->right, elem);
        }
        else {
            remove_root(root);
            return true;
        }
    }

    static void remove_root(Node*& root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            root = nullptr;
        }
        else if (left_child == nullptr) {
            root = right_child;
        }
        else if (right_child == nullptr) {
            root = left_child;
        }
        else {
            Node* lowest = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = right_child;
            root = lowest;
        }
    }


    static Node* remove_lowest(Node*& root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            Node* result = root;
            root = root->right;
            return result;
        }
        else {
            return remove_lowest(root->left);
        }
    }

    static void display(Node* root, std::ostream& out) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                display(root->left, out);
                out << ", ";
            }
            out << root->elem;
            if (root->right != nullptr) {
                out << ", ";
                display(root->right, out);
            }
        }
    }

};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}

/*
Coste:
El primer bucle while tiene coste O(N) en los N jugadores
El segundo bucle tiene en el caso peor coste O((M-N)*Ai)
donde Ai es, en el caso peor, 1 para el primer elemento insertado
2 para el segundo, 3 para el tercero, etc. hasta un máximo de (M-N)/N
redondeado hacia arriba (a alguien le toca como máximo una carta más que el
resto de jugadores). El coste asintótico es claramento cuadrático en M
número de cartas. Como M >= N, se concluye que el algoritmo tiene
coste cuadrático en los M número de cartas a repartir
*/
void repartoJuegoMona(int N, std::vector<int> const& cartas) {
    int i = 0;
    std::vector<SetTree<int>> jugs;
    while (i < N) {
        SetTree<int> aux;
        aux.insert(cartas[i]);
        jugs.push_back(aux);
        ++i;
    }

    for (int j = i; j < cartas.size(); ++j) {
        if (jugs[j % N].contains(cartas[j])) {
            jugs[j % N].erase(cartas[j]);
        }
        else jugs[j % N].insert(cartas[j]);
    }

    for (int i = 1; i <= N; ++i) {
        std::cout << 'J' << i << ": " << jugs[i - 1] << '\n';
    }
    std::cout << "---\n";
}

bool resuelveCaso() {
    int N; std::cin >> N;
    if (!std::cin) return false;
    int M; std::cin >> M;
    std::vector<int> cartas(M);
    for (int& i : cartas) {
        std::cin >> i;
    }
    repartoJuegoMona(N, cartas);
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}