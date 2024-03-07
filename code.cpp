#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <chrono> using namespace std;
using namespace chrono; struct Edge {    
int u, v, weight; 
}; 
// Union-Find data structure with path compression class UnionFind { public: 
    UnionFind(int n) {       
      parent.resize(n);         
      rank.resize(n);         
      for (int i = 0; i < n; i++) {  
        parent[i] = i;            
        rank[i] = 0; 
        }     
    }    
int find(int x) {        
  if (parent[x] != x) {            
    parent[x] = find(parent[x]); 
        }        
  return parent[x]; 
    } 
    void unite(int x, int y) {        
      int rootX = find(x);         
      int rootY = find(y);        
      if (rootX == rootY) {             
        return; 
        } 
        if (rank[rootX] < rank[rootY]) {            
          parent[rootX] = rootY;        
        } else if (rank[rootX] > rank[rootY]) { 
          parent[rootY] = rootX; 
        } else {           
          parent[rootY] = rootX;             
          rank[rootX]++; 
        } 
    } 
private: 
    vector<int> parent;    
vector<int> rank; 
}; 
// Comparator function to sort edges by their weight bool edgeComparator(const Edge& e1, const Edge& e2) {     return e1.weight < e2.weight; 
} vector<Edge> kruskalMST(int n, vector<Edge>& edges) { 
    // Sort edges by their weight 
    sort(edges.begin(), edges.end(), edgeComparator);   
  UnionFind uf(n);     
  vector<Edge> res;     
  for (Edge e : edges) {        
    int rootU = uf.find(e.u);         
    int rootV = uf.find(e.v);        
    if (rootU != rootV) {             
      res.push_back(e); 
            uf.unite(rootU, rootV); 
        }    
  }     
  return res; 
} 
 
int main() {  
  auto start = high_resolution_clock::now();    
            int n = 5; // number of vertices in the graph     vector<Edge> edges = {{0, 1, 3}, 
                          {0, 4, 4}, 
                          {1, 3, 1}, 
                          {1, 4, 2}, 
                          {2, 3, 2}, 
                          {2, 4, 1}}; 
    vector<Edge> mst = kruskalMST(n, edges); 
 
    cout << "Edges in the minimum spanning tree:\n";     
for (Edge e : mst) {        
  cout << e.u << " -- " << e.v << " : " << e.weight << "\n"; 
    } 
  auto stop = high_resolution_clock::now();  
auto duration = duration_cast<microseconds>(stop - start);
cout << "Duration: " << duration.count() << " microseconds"<<endl;     return 0; 
} 
