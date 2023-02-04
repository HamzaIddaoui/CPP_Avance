#include <iostream>
#include <vector>

class Graph {

 private:
  int num_vertices_;
  std::vector<std::vector<int>> adj_list_; 
 public:
  Graph(int num_vertices);
  void AddEdge(int from, int to);

  void PrintAdjacencyList();
};


