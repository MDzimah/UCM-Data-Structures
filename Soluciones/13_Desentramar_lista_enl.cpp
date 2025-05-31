/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
  El metodo recorre la lista this pasando por todos los nodos. En las posiciones pares no hace nada mientras que si la posicion
  es impar, se quita el nodo de la lista this y se mete al final de la lista other.
  Coste de la funcion: O(n) siendo n = this.num_elems porque itera sobre la lista realizando operaciones de coste constante.

 *@ </answer> */

/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */

#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedDouble {
private:
   struct Node {
      int value;
      Node *next;
      Node *prev;
   };
   
public:
   ListLinkedDouble() : num_elems(0) {
      head = new Node;
      head->next = head;
      head->prev = head;
   }
   
   ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
      copy_nodes_from(other);
      num_elems = other.num_elems;
   }
   
   ~ListLinkedDouble() { delete_nodes(); }
   
   void push_front(const int &elem) {
      Node *new_node = new Node{elem, head->next, head};
      head->next->prev = new_node;
      head->next = new_node;
      num_elems++;
   }
   
   void push_back(const int &elem) {
      Node *new_node = new Node{elem, head, head->prev};
      head->prev->next = new_node;
      head->prev = new_node;
      num_elems++;
   }
   
   void pop_front() {
      assert(num_elems > 0);
      Node *target = head->next;
      head->next = target->next;
      target->next->prev = head;
      delete target;
      num_elems--;
   }
   
   void pop_back() {
      assert(num_elems > 0);
      Node *target = head->prev;
      target->prev->next = head;
      head->prev = target->prev;
      delete target;
      num_elems--;
   }
   
   int size() const { return num_elems; }
   
   bool empty() const { return num_elems == 0; };
   
   const int &front() const {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   int &front() {
      assert(num_elems > 0);
      return head->next->value;
   }
   
   const int &back() const {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   int &back() {
      assert(num_elems > 0);
      return head->prev->value;
   }
   
   const int &operator[](int index) const {
      assert(0 <= index && index < num_elems);
      Node *result_node = nth_node(index);
      return result_node->value;
   }
   
   int &operator[](int index) {
      assert(0 <= index && index < num_elems);
      Node *result_node = nth_node(index);
      return result_node->value;
   }
   
   ListLinkedDouble &operator=(const ListLinkedDouble &other) {
      if (this != &other) {
         delete_nodes();
         head = new Node;
         head->next = head->prev = head;
         copy_nodes_from(other);
         num_elems = other.num_elems;
      }
      return *this;
   }
   
   void display(std::ostream &out) const;
   
   void display() const {
      display(std::cout);
   }
   
   void display_reverse(std::ostream &out) const;
   
   void display_reverse() const {
      display_reverse(std::cout);
   }
   
   // Nuevo método. Debe implementarse abajo
   void unzip(ListLinkedDouble &other);
   
private:
   Node *head;
   int num_elems;
   
   Node *nth_node(int n) const;
   void delete_nodes();
   void copy_nodes_from(const ListLinkedDouble &other);
   // Nuevos metodos privados para la implementacion del metodo unzip
   void attach(Node* node, Node* pos);
   void detach(Node* node);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
   int current_index = 0;
   Node *current = head->next;
   
   while (current_index < n && current != head) {
      current_index++;
      current = current->next;
   }
   
   return current;
}

void ListLinkedDouble::delete_nodes() {
   Node *current = head->next;
   while (current != head) {
      Node *target = current;
      current = current->next;
      delete target;
   }
   
   delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
   Node *current_other = other.head->next;
   Node *last = head;
   
   while (current_other != other.head) {
      Node *new_node = new Node{current_other->value, head, last};
      last->next = new_node;
      last = new_node;
      current_other = current_other->next;
   }
   head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
   out << "[";
   if (head->next != head) {
      out << head->next->value;
      Node *current = head->next->next;
      while (current != head) {
         out << ", " << current->value;
         current = current->next;
      }
   }
   out << "]";
}

void ListLinkedDouble::display_reverse(std::ostream &out) const {
   out << "[";
   if (head->prev != head) {
      out << head->prev->value;
      Node *current = head->prev->prev;
      while (current != head) {
         out << ", " << current->value;
         current = current->prev;
      }
   }
   out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
   l.display(out);
   return out;
}


// ----------------------------------------------------------------
// ¡No modificar nada por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

void ListLinkedDouble::unzip(ListLinkedDouble & other) {
    Node* current = head->next;
    Node* next_current;

    int cont = 0;
    while (current != head) {
        next_current = current->next; //es necesario almacenarlo
        if (cont % 2 == 1) { //el nodo se pasa a la otra lista
            detach(current);
            attach(current, other.head->prev);
        }
        ++cont;
        current = next_current; //avanzar
    }
}

void ListLinkedDouble::attach(Node* node, Node* pos) { // coloca el nodo despues del nodo pos
    node->next = pos->next;
    node->prev = pos;
    pos->next->prev = node;
    pos->next = node;
}
void ListLinkedDouble::detach(Node* node) { // quita el nodo de la lista
    node->next->prev = node->prev;
    node->prev->next = node->next;
} //podria implementarse la reasignacion de los punteros next y prev pero en este caso no es necesario


using namespace std;

ListLinkedDouble leerLista() {
  ListLinkedDouble lista;
  int num;
  cin >> num;
  while (num != 0) {
    lista.push_back(num);
    cin >> num;
  }
  return lista;
}


void resuelveCaso() {
  auto lista1 = leerLista();
  auto lista2 = leerLista();
  
  lista1.unzip(lista2);
  
//  for (int i = 0; i < lista1.size(); ++i) {
//     auto elem = lista1.front(); lista1.pop_front();
//     lista1.push_back(elem);
//  }

  std::cout << lista1 << '\n';
  std::cout << lista2 << '\n';
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
  int casos;
  cin >> casos;
  while (casos--) {
     resuelveCaso();
  }

   
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   // Descomentar si se necesita
   // system("PAUSE");
#endif
   
   return 0;
}


