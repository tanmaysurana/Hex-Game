//RANDOMLY GENERATES A GRAPH AND APPLIES DIJKSTRA'S ALGORITHM TO IT

#include <iostream>
#include "graph.cc"

using namespace std;

int main()
{
	const int size = 25;
	graph g(size);
	g.rand_graph_gen(0.15);
	cout<<g<<endl;
	int* d = g.Dijkstra(0, 24);
	if(d == nullptr) return 0;
	cout<<endl;
	for(int i{size-1}; i >= 0; i--)
		if(d[i] != -1)
			cout<<"->"<<d[i];
	cout<<endl;
	delete[] d;
}
