/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
  * modificar el c�digo contenido entre las etiquetas <answer>
  * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
  * prohibida, pues no ser� corregida.
  *
  * Tampoco esta permitido modificar las l�neas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos:
  //@ </answer>

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>
#include <utility>

/*
 Implementaci�n del TAD Conjunto mediante �rboles binarios de b�squeda
 */

template <typename T> class SetTree {
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

    // *** nuevo m�todo (implem�ntalo debajo, en el espacio reservado para ello)
    std::pair<bool, T> lower_bound(T const& elem) const;

private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right)
            : left(left), elem(elem), right(right) {}
    };

    Node* root_node;
    int num_elems;

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
    std::pair<bool, T> aux(T const& elem, Node* const& root, T & mejorHastaElMomento, bool& mejorHastaElMomentoActualizado) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}

using namespace std;
// ----------------------------------------------------------------
// �No modificar nada importante por encima de esta l�nea!

// Implementa a continuaci�n el m�todo pedido. Puedes declarar otros
// m�todos dentro de la clase (arriba), pero implement�ndolos aqu� debajo.
//@ <answer>

template<typename T>
std::pair<bool, T> SetTree<T>::aux(T const& elem, Node* const& root, T& mejorHastaElMomento, bool& mejorHastaElMomentoActualizado) const {
    if (root == nullptr) {
        if (mejorHastaElMomentoActualizado) return { true, mejorHastaElMomento };
        else return { false, {} };
    }
    else {
        if (root->elem == elem) {
            mejorHastaElMomento = elem;
            mejorHastaElMomentoActualizado = true;
            return { true, elem };
        }
        else if (root->elem > elem) {
            mejorHastaElMomento = root->elem;
            mejorHastaElMomentoActualizado = true;
            return aux(elem, root->left, mejorHastaElMomento, mejorHastaElMomentoActualizado);
        }
        else return aux(elem, root->right, mejorHastaElMomento, mejorHastaElMomentoActualizado);
    }
}

template <typename T>
std::pair<bool, T> SetTree<T>::lower_bound(T const& elem) const {
    T mejorHastaElMomento; 
    bool mejorHastaElMomentoAct = false;
    return aux(elem, this->root_node, mejorHastaElMomento, mejorHastaElMomentoAct);
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    SetTree<int> cjto;
    int elem;
    for (int i = 0; i < N; ++i) {
        cin >> elem;
        cjto.insert(elem);
    }
    int preguntas;
    cin >> preguntas;
    for (int i = 0; i < preguntas; ++i) {
        cin >> elem;
        auto res = cjto.lower_bound(elem);
        if (res.first) {
            cout << res.second << '\n';
        }
        else
            cout << "NO HAY\n";
    }
    cout << "---\n";
    return true;
}

/*@ </answer> */

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Visual Studio
    // system("PAUSE");
#endif
    return 0;
}
