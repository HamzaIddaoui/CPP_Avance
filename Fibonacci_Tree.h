using namespace std;

#include <iostream>
#include <vector>

struct Node {
  int valeur;
  Node* fils_gauche;
  Node* fils_droit;

  Node(int valeur) : valeur(valeur), fils_gauche(nullptr), fils_droit(nullptr) {}
};

class FibonacciTree {
 private:
  Node* root_;
 public:
  FibonacciTree() : root_(nullptr) {}

  Node* Insert(int valeur);

  Node* Merge(Node* node1, Node* node2);

  Node* PopMin();

  Node* Root() { return root_; }
};


