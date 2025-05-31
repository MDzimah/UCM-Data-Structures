 /*@ <answer>

 LO QUE SE DEVUELVE EN LA FUNCION RECURSIVA QUEDA DEFINIDO SOBRE LA CABECERA DE LA MISMA

 Se calcula ambos subarboles recursivamente y se llega a sus hojas y se devuelve la altura que es 1, si hay
 un jugador o no (1 o -1) y el numero de partidos que es 0, ya que es solo un jugador.
 Se llama a la funcion aux con ambos subarboles:

     Si la altura de los subarbols + 1 es mayor o igual a la ronda, entonces devolvemos cada vez los partidos que ya se habian jugado
     hasta llegar a esa ronda (incluida).

     Si la altura es menor, entonces analizamos tres casos:

         1) Si ninguno se presenta, entonces el numero de partidas jugadas es 0 y como nadie juega -1
         2) Si alguno de los dos se presenta, entonces no hay partido pero se clasifica uno luego 1
         3) Si los dos juegan, entonces se juega partido que es 1 y se clasifica luego 1

     Por ultimo se devuelve si se ha clasificado alguno o no y el numero de partidos jugados que es el izquierdo mas el derecho mas
     (si es que se ha jugado) el resultado de la ronda actual. Tambien devolvemos la altura para las comparaciones.

 El arbol es completo entonces es equilibrado por lo que podemos usar el teorema de la division ya que los nodos del arbol izquierdo
 y del derecho coinciden.
 a == 2 ya que se hacen dos llamadas recursivas en el caso recursivo
 b == 2 ya que en cada llamda se analiza cada mitad del arbol que tienen igual numero de nodos (tipo divide y venceras)
 d == 0 puesto que lo que se realiza en el caso recursivo tiene coste constante
 Como 2 = a > b^d = 2^0 = 1, entonces el algoritmo tiene coste O(n^{logb a}) = O(n) en los n nodos del arbol.
 Intuitivamente, como estamos visitando cada nodo una sola vez y realizando operaciones de coste constante en cada visita, entonces
 tambien podemos concluir que debe ser lineal en el numero de nodos.
 El numero de rondas no afecta en el coste porque este se considera medidas de orden asintóticas.

  *@ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>
#include <algorithm>

  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy

template <class T>
class BinTree
{
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

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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
};

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

// int1 es la altura del arbol, int2 es 1 o -1, e int3 es el numero de partidos jugados
std::tuple<int, int, int> aux(BinTree<int> const& arbol, int rondas)
{
    if (arbol.empty())
    {
        return { 0, -1, 0 };
    }
    else if (arbol.left().empty() && arbol.right().empty())
    {
        return { 1, arbol.root(), 0 };
    }
    else
    {
        auto [h_l, clas_l, p_l] = aux(arbol.left(), rondas);
        auto [h_r, clas_r, p_r] = aux(arbol.right(), rondas);
        if (rondas + 1 <= h_l)
        {
            return { h_l + 1, 1, p_l + p_r };
        }
        else
        {
            int pJugado = 1, clas = -1;
            if (clas_l == -1 && clas_r == -1)
            {
                pJugado = 0;
            }
            else if (clas_l == -1 || clas_r == -1)
            {
                pJugado = 0;
                clas = 1;
            }
            else
            {
                pJugado = 1;
                clas = 1;
            }
            return { h_l + 1, clas, pJugado + p_l + p_r };
        }
    }
}

int partidos(BinTree<int> const& arbol, int rondas)
{
    auto [h, c, p] = aux(arbol, rondas);
    return p;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso()
{
    auto arbol = read_tree<int>(std::cin);
    int rondas;
    std::cin >> rondas;
    cout << partidos(arbol, rondas) << "\n";
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int num_casos;
    std::cin >> num_casos;

    for (int i = 0; i < num_casos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
