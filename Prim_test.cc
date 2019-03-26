
//RANDOMLY GENERATES A GRAPH APPLIES PRIM'S ALGORITHM TO IT

#include <iostream>
#include "graph.cc"

using namespace std;

int main()
{
	const int size = 10, range = 10;
	graph g(size, range);
	g.rand_graph_gen(1);
	cout<<g;
	graph* mst;
	mst = g.Prim();
	cout<<endl<<endl<<*mst;
	delete mst;
}
