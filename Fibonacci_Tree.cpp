#include <iostream>
#include <vector>
#include "Fibonacci_Tree.h"
using namespace std;

Node* FibonacciTree::Insert(int valeur){
    Node* node = new Node(valeur);
    if (!root_) {
      root_ = node;
    } else {
      Merge(node, root_);
    }
    return node;
}

Node* FibonacciTree::Merge(Node* node1, Node* node2) {
    if (!node1) return node2;
    if (!node2) return node1;

    if (node1->valeur > node2->valeur) swap(node1, node2);

    node1->fils_droit = Merge(node1->fils_droit, node2);
    if (!node1->fils_gauche || node1->fils_gauche->valeur < node1->fils_droit->valeur) {
      swap(node1->fils_gauche, node1->fils_droit);
    }
    return node1;
}

Node* FibonacciTree::PopMin() {
    if (!root_) return nullptr;

    Node* resultat = root_;
    root_ = Merge(root_->fils_gauche, root_->fils_droit);
    return resultat;
}




int main() {
  FibonacciTree fib_tree;
  vector<Node*> nodes;

  for (int i = 1; i <= 10; i++) {
    nodes.push_back(fib_tree.Insert(i));
  }

  while (fib_tree.Root()) {
    Node* min = fib_tree.PopMin();
    cout << min->valeur << " ";
  }
  cout << endl;

  return 0;
}