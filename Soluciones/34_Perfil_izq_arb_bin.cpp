 /*@ <answer>

  Es un recorrido BFS (en profundidad) con coste lineal en el número de nodos del árbol.
  Se lleva constancia del nivel actual llevando una variable auxiliar llamada nodos_nivel y
  se mete un while para tratarlos. Antes de empezar ese while se hace push_back del front, que es 
  el primer nodo del nivel. Así obtenemos el perfil izquierdo.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>

  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy

template <class T>
class BinTree
{

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const
    {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const
    {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const
    {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

    template <typename U>
    void preorder(U func) const
    {
        preorder(root_node, func);
    }

    template <typename U>
    void inorder(U func) const { inorder(root_node, func); }

    template <typename U>
    void postorder(U func) const
    {
        postorder(root_node, func);
    }

    template <typename U>
    void levelorder(U func) const;

private:
    struct TreeNode
    {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out)
    {
        if (root == nullptr)
        {
            out << ".";
        }
        else
        {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

    template <typename U>
    static void preorder(const NodePointer& node, U func);

    template <typename U>
    static void inorder(const NodePointer& node, U func);

    template <typename U>
    static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func)
{
    if (node != nullptr)
    {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func)
{
    if (node != nullptr)
    {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func)
{
    if (node != nullptr)
    {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const
{
    std::queue<NodePointer> pending;
    if (root_node != nullptr)
    {
        pending.push(root_node);
    }
    while (!pending.empty())
    {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr)
        {
            pending.push(current->left);
        }
        if (current->right != nullptr)
        {
            pending.push(current->right);
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree)
{
    tree.display(out);
    return out;
}

template <typename T>
BinTree<T> read_tree(std::istream& in)
{
    char c;
    in >> c;
    if (c == '.')
    {
        return BinTree<T>();
    }
    else
    {
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

using namespace std;

// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas
//@ <answer>

std::vector<int> perfil(BinTree<int> arbol)
{
    std::queue<BinTree<int>> q;
    std::vector<int> lista;
    if (!arbol.empty())
    {
        q.push(arbol);
        while (!q.empty()) {
            int nodosNivel = q.size();
            lista.push_back(q.front().root());
            while (nodosNivel--) {
                BinTree<int> aux = q.front();
                q.pop();
                if (!aux.left().empty()) {
                    q.push(aux.left());
                }
                if (!aux.right().empty()) {
                    q.push(aux.right());
                }
            }
        }
    }
    return lista;
}




//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelveCaso()
{
    BinTree<int> arbol = read_tree<int>(cin);

    std::vector<int> vperfil = perfil(arbol);

    if (!vperfil.empty())
    {
        cout << vperfil[0];
        for (int i = 1; i < vperfil.size(); ++i)
        {
            cout << ' ' << vperfil[i];
        }
    }
    cout << '\n';
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    // Resolvemos
    while (casos--)
    {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}