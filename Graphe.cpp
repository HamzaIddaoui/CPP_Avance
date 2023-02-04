#include <iostream>
#include <vector>
#include "Graphe.h"
using namespace std;

Graph::Graph(int num_vertices): num_vertices_(num_vertices) {
    adj_list_.resize(num_vertices_);
}

void Graph::AddEdge(int from, int to) {
    adj_list_[from].push_back(to);
}

void Graph::PrintAdjacencyList(){
  for (int i = 0; i < num_vertices_; i++) {
    std::cout << i << ": ";
    for (int j : adj_list_[i]) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  Graph g(4);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 3);
  g.PrintAdjacencyList();

  return 0;
}


