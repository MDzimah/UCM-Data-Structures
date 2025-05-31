#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <climits>

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

//bool: es arbol de búsqueda
//int1: mínimo elem del árbol
//int2: máximo elem del árbol
template <typename T> std::tuple<bool,T,T> arbDeBusqueda(BinTree<T> t, T const max_abs, T const min_abs) {
    if (t.empty()) return { true,max_abs,min_abs };
    else {
        auto [busL, minL, maxL] = arbDeBusqueda(t.left(), max_abs, min_abs);
        if (!busL || (!t.left().empty() && t.root() <= maxL)) return { false, T{}, T{}};
        
        auto [busR, minR, maxR] = arbDeBusqueda(t.right(), max_abs, min_abs);
        if (!busR || (!t.right().empty() && t.root() >= minR)) return { false, T{}, T{}};

        return {true, std::min(std::min(minL, minR), t.root()), std::max(std::max(maxL, maxR), t.root())};
    }
}

bool resuelveCaso() {
    char op; std::cin >> op;
    if (!std::cin) return false;
    bool res;
    if (op == 'N') {
        BinTree<int> t = read_tree<int>(cin);
        res = std::get<0>(arbDeBusqueda(t, INT_MAX, INT_MIN));
    }
    else {
        BinTree<std::string> t = read_tree<std::string>(cin);
        std::string MIN = " ";
        std::string MAX = "²";
        res = std::get<0>(arbDeBusqueda(t, MAX, MIN));
    }

    if (res) std::cout << "SI\n";
    else std::cout << "NO\n";

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