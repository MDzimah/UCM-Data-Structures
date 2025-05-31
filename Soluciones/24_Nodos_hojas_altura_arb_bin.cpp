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
    void nodos_hojas_altura(int& nodos, int& hojas, int& altura) {
        nodos_hojas_altura(root_node, nodos, hojas, altura);
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

    void nodos_hojas_altura(const NodePointer& root, int& nodos, int& hojas, int& altura) {
        //Árbol vacío
        if (root == nullptr) {
            nodos = hojas = altura = 0;
            return;
        }
        //Árbol con al menos 1 elem
        else {
            if (root->left == nullptr && root->right == nullptr) nodos = hojas = altura = 1;
            else {
                int nodos_L, hojas_L, altura_L;
                if (root->left != nullptr) {
                    nodos_L = 1, hojas_L = 0, altura_L = 1;
                    nodos_hojas_altura(root->left, nodos_L, hojas_L, altura_L);
                }
                else nodos_L = hojas_L = altura_L = 0;

                int nodos_R, hojas_R, altura_R;
                if (root->right != nullptr) {
                    nodos_R = 1, hojas_R = 0, altura_R = 1;
                    nodos_hojas_altura(root->right, nodos_R, hojas_R, altura_R);
                }
                else nodos_R = hojas_R = altura_R = 0;

                //" + 1 " Pq tomo en cuenta el nodo padre de los hermanos
                nodos = nodos_L + nodos_R + 1;
                hojas = hojas_L + hojas_R;
                altura = std::max(altura_L, altura_R) + 1;
            }
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

/*
Como función externa:

template <typename T>
void nodos_hojas_altura(const BinTree<T>& t) {

* Usas t.left(), t.right() en lugar de root->left y root->right

}

*/


void res() {
    BinTree<char> t = read_tree<char>(std::cin);
    int n, h, a;
    t.nodos_hojas_altura(n, h, a);
    std::cout << n << ' ' << h << ' ' << a << '\n';
}

int main() {
    int nc; std::cin >> nc;
    while (nc--) res();
}