
 /*@ <answer>

 Se itera sobre los elementos de la entrada y metiendo
 los elems hasta llegar a k. Cuando se llega a este valor,
 se pregunta al conjunto si no contiene el elem leído (no se admiten
 elementos repetidos en el conjunto) y si el mínimo del conjunto es 
 más pequeño que elem. Si sí, entonces elem ha de ser insertado porque
 es al menos el k valor más grande hasta el momento. De lo contrario, se
 ignora.

 Coste: en un árbol degenerado todas las operaciones de contains, calcular el mínimo,
 insertar y eliminar el mínimo tienen coste O(n) en los n nodos del árbol, luego el coste
 del algoritmo es claramente O(n).

 El coste en espacio es el tamaño del set, el cual siempre tiene tamaño menor o igual que k.
 Coste O(k) en espacio del set

  *@ </answer> */


#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
#include <utility>

  /*
   Implementación del TAD Conjunto mediante árboles binarios de búsqueda
   */

template <typename T>
class SetTree {
public:
    SetTree() : root_node(nullptr), num_elems(0) {}
    SetTree(const SetTree& other)
        : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
    ~SetTree() { delete_nodes(root_node); }

    void insert(const T& elem) {
        auto [new_root, inserted] = insert(root_node, elem);
        root_node = new_root;
        if (inserted) {
            num_elems++;
        }
    }

    bool contains(const T& elem) const { return search(root_node, elem); }

    void erase(const T& elem) {
        auto [new_root, removed] = erase(root_node, elem);
        root_node = new_root;
        if (removed) {
            num_elems--;
        }
    }

    int size() const { return num_elems; }
    bool empty() const { return num_elems == 0; }

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

    // nuevos métodos, impleméntalos abajo, en el sitio reservado para ello
    T min() const;
    void erase_min();

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right)
            : left(left), elem(elem), right(right) {}
    };

    Node* root_node;
    int num_elems;

    static std::pair<bool, T> lower_bound(Node* root, T const& e);

    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->elem,
                copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    static std::pair<Node*, bool> insert(Node* root, const T& elem) {
        if (root == nullptr) {
            return { new Node(nullptr, elem, nullptr), true };
        }
        else if (elem < root->elem) {
            auto [new_root_left, inserted] = insert(root->left, elem);
            root->left = new_root_left;
            return { root, inserted };
        }
        else if (root->elem < elem) {
            auto [new_root_right, inserted] = insert(root->right, elem);
            root->right = new_root_right;
            return { root, inserted };
        }
        else {
            return { root, false };
        }
    }

    static bool search(const Node* root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (elem == root->elem) {
            return true;
        }
        else if (elem < root->elem) {
            return search(root->left, elem);
        }
        else {
            return search(root->right, elem);
        }
    }

    static std::pair<Node*, bool> erase(Node* root, const T& elem) {
        if (root == nullptr) {
            return { root, false };
        }
        else if (elem < root->elem) {
            auto [new_root_left, erased] = erase(root->left, elem);
            root->left = new_root_left;
            return { root, erased };
        }
        else if (root->elem < elem) {
            auto [new_root_right, erased] = erase(root->right, elem);
            root->right = new_root_right;
            return { root, erased };
        }
        else {
            return { remove_root(root), true };
        }
    }

    static Node* remove_root(Node* root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            return nullptr;
        }
        else if (left_child == nullptr) {
            return right_child;
        }
        else if (right_child == nullptr) {
            return left_child;
        }
        else {
            auto [lowest, new_right_root] = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = new_right_root;
            return lowest;
        }
    }

    static std::pair<Node*, Node*> remove_lowest(Node* root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            return { root, root->right };
        }
        else {
            auto [removed_node, new_root_left] = remove_lowest(root->left);
            root->left = new_root_left;
            return { removed_node, root };
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

using namespace std;
// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación los métodos pedidos. Puedes declarar otros
// métodos dentro de la clase, implementándolos aquí debajo.
// Completa también la implementación de la función resuelve().
//@ <answer>

template <typename T>
T SetTree<T>::min() const {
    //Se supone conjunto no vacío
    Node* curr = this->root_node;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr->elem;
}

template <typename T>
void SetTree<T>::erase_min() {
    //Tendría mucho más sentiedo que min() devolviese un puntero a un nodo. Así
    //bastaría con pasar a esta función ese nodo y desengancharlo del árbol.
    //Sin embargo, al final el coste asintótico de ambos acaba siendo lineal
    //en el número de nodos del árbol aunque mucho más costoso en espacio
    //para lo propuesto en el enunciado (por la pila de recursión).
    this->erase(this->min());
}

template <class T>
void resuelve(T centinela) {
    int k; cin >> k;
    T elem;
    SetTree<T> conjunto;
    cin >> elem;
    while (elem != centinela) {
        if (conjunto.size() != k) conjunto.insert(elem);
        else {
            if (!conjunto.contains(elem) && conjunto.min() < elem) {
                conjunto.erase_min();
                conjunto.insert(elem);
            }
        }
        cin >> elem;
    }

    std::cout << conjunto << '\n';
}
//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    char tipo;
    cin >> tipo;

    if (!cin)
        return false;

    if (tipo == 'N') { // el caso es de números
        resuelve(-1);
    }
    else { // el caso es de cadenas
        resuelve(string("FIN"));
    }
    return true;
}

int main() {
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
