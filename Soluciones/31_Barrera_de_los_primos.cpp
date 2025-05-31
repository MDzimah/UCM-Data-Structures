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
  * Esta implementación utiliza smart pointers para prevenir
  * fugas de memoria y problemas con la destrucción.
  */

#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <queue>
#include <cmath>

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }
    std::tuple <bool, int, int> barreraPrimos() {
        return barreraPrimos(root_node);
    }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

    //O(n^(1/2)) en el número n
    bool es_primo(int n) {
        if (n <= 1) return false;

        int limite = std::sqrt(n);

        for (int i = 2; i <= limite; ++i) {
            if (n % i == 0)
                return false;
        }

        return true;
    }

    //bool: múltiplo encontrado
    //int1: profundidad a la que se encuentra 
    //int2: valor del múltiplo encontrado

    //a = 2, b = 2, d = 1/2. a = 2 > b^d = 2^(1/2) --> Por Th. División, O(n^logb a) = O(n)

    std::tuple <bool, int, int> barreraPrimos(NodePointer const& root_node) {
        if (root_node == nullptr) return { false, -1, -1 };
        else {
            //Realizo recorrido en anchura (BFS)
            std::queue<NodePointer> pending;
            pending.push(root_node);

            int profundidad = 1;
            while (!pending.empty()) {
                int nodos_nivel = pending.size();

                while (nodos_nivel--) {
                    NodePointer curr = pending.front();
                    pending.pop();
                    if (!es_primo(curr->elem)) {
                        if (curr->elem % 7 != 0) {
                            if (curr->left != nullptr) {
                                pending.push(curr->left);
                            }

                            if (curr->right != nullptr) {
                                pending.push(curr->right);
                            }
                        }
                        else return { true, profundidad, curr->elem };
                    }
                }
                ++profundidad;
            }

            return { false, -1, -1 };
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}


void res() {
    BinTree<int> t = read_tree<int>(std::cin);
    auto [b, p, num] = t.barreraPrimos();
    if (b) std::cout << num << ' ' << p << '\n';
    else std::cout << "NO HAY\n";
}

int main() {
    int nc; std::cin >> nc;
    while (nc--) res();
}