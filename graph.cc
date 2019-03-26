#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class graph {
	private:
	const int size; //Number of Vertices
	bool** A; //Adjacency matrix
	const int range; //For range of weights
	int** Cost; //Cost (or Weight) Matrix

	public:
	graph(int size, int range = 0): size(size), range(range) {
		A = new bool*[size];
		for(int i{}; i < this->size; i++)
			A[i] = new bool[this->size];
		for(int i{}; i < this->size; i++)
			for(int j = 0; j < this->size; j++)
				A[i][j] = false;

		if(range) {
			Cost = new int*[size];
			for(int i{}; i < this->size; i++)
				Cost[i] = new int[this->size];
			for(int i{}; i < this->size; i++)
				for(int j{}; j < this->size; j++)
					Cost[i][j] = 0;

		}
	}

	friend ostream& operator<< (ostream& out, const graph& g) {
		if(g.range) {
			out<<"   ";
			for(int i{}; i < g.size; i++)
				out<<i<<" ";
			out<<endl;

			for(int i{}; i < g.size; i++) {
				if(i/10 > 0) out<<i<<" ";
				else out<<i<<"  ";

				for(int j{}; j < g.size; j++) {
					out<<g.Cost[i][j];
					if(j/10 > 0) out<<"  ";
					else out<<" ";
				}
				out<<endl;
			}
		}
		else {
			out<<"   ";
			for(int i{}; i < g.size; i++)
				out<<i<<" ";
			out<<endl;

			for(int i{}; i < g.size; i++) {
				if(i/10 > 0) out<<i<<" ";
				else out<<i<<"  ";

				for(int j{}; j < g.size; j++) {
					out<<static_cast<int>(g.A[i][j]);
					if(j/10 > 0) out<<"  ";
					else out<<" ";
				}
				out<<endl;
			}
		}
		return out;
	}

	void operator= (const graph& g2) {
		if(this->size == g2.size && this->range == g2.range) {
			this->A = g2.A;

			if(this->range) {
				this->Cost = g2.Cost;
			}
		}
		else {
			cout<<"Illegal Assignment: Graph size and/or range don't match";
			return;
		}
	}

	void rand_graph_gen(double density) { //generates an undirected graph
		if(density > 1) density = 1.1;
		else if(density < 0) density = -1;

		const int rand_max = RAND_MAX;

		//seeding the pseudo-random number generator
		srand(time(nullptr));

		double prob{};
		for(int i{}; i < this->size; i++) {
			for(int j{i}; j < this->size; j++) {
				if(i == j) this->A[i][j] = false; //no loops
				else this->A[i][j] = this->A[j][i] = (rand() <= (density*rand_max));
			}
		}

		if(this->range) {
			for(int i{}; i < this->size; i++) {
				for(int j{i}; j < this->size; j++) {
					if(this->A[i][j]) {
						prob = static_cast<double>(rand())/rand_max;
						this->Cost[i][j] = this->Cost[j][i] = static_cast<int>(range*prob) == 0 ? 1 : range*prob; //No zero costs if A[i][j] is 1.
					}
				}
			}
		}
	}

	//Dijkstra's declaration
	int* Dijkstra(int source, int destination);

	//Prim's declaration
	graph* Prim();

	~graph() {
		for(int i{}; i < this->size; i++) {
			delete[] this->A[i];
			delete[] this->Cost[i];
		}
		delete[] this->A;
		delete[] this->Cost;
	}
};

//Dijkstra's Shortest Path Algorithm for Unweighted graphs
int* graph :: Dijkstra(const int src, const int dst) {
	if(src >= this->size || dst >= this->size) {
		cout<<"Source/Destination do not exist in the graph.\n";
		return nullptr;
	}

	int* node_info[2];
	node_info[0] = new int[this->size]; //stores distance from src (-1 is the stand-in for infinity)
	node_info[1] = new int[this->size]; //stores the node current node is reached from (if no such node, stores -1)
	node_info[0][src] = 0;
	node_info[1][src] = 0;
	for(int i{}; i < 2; i++) {
		for(int j{}; j < this->size; j++) {
			if(j != src) {
				node_info[i][j] = -1;
			}
		}
	}

	bool* is_computed = new bool[this->size];
	for(int i{}; i < this->size; i++) is_computed[i] = false;

	int compute{src};
	int computed_last{compute};
	int j{compute + 1};
	int i{};
	int min_dist{this->size};
	while(!is_computed[dst]) {
		//to compute the given node (to update the distances from this node)
		j = compute + 1;
		if(j == this->size) j = 0;
		while(j != compute) {
			if(!is_computed[compute] && this->A[compute][j]) {
				if(node_info[0][j] == -1) {
					node_info[0][j] = node_info[0][compute] + 1;
					node_info[1][j] = compute;
				}
				else if(node_info[0][compute] + 1 < node_info[0][j]) {
					node_info[0][j] = node_info[0][compute] + 1;
					node_info[1][j] = compute;
				}
			}
			j++;
			if(j == this->size) j = 0;
		}

		is_computed[compute] = true;

		//to find out the next node to be computed
		computed_last = compute;
		min_dist = this->size;
		for(j = 0; j < this->size; j++) {
			if(!is_computed[j] && (node_info[0][j] != -1)) {
				if(node_info[0][j] < min_dist) {
					min_dist = node_info[0][j];
					compute = j;
				}
			}
		}

		if(compute == computed_last && compute != dst) {
			cout<<endl<<dst<<" is not reachable."<<endl;
			return nullptr;
		}
	}

	//to store the path by backtracking from dst
	int* path = new int[this->size];
	for(i = 0; i < this->size; i++) path[i] = -1;
	i = dst;
	j = 0;
	while(i != src) {
		path[j] = i;
		j++;
		i = node_info[1][i];
	}
	path[j] = src;

	delete[] node_info[0];
	delete[] node_info[1];
	delete[] is_computed;

	return path;
}

//Prim's Minimum Spanning Tree Algorithm (This is most likely a very bad implementation)
graph* graph :: Prim() {
	graph* MST = new graph(this->size, this->range);

	vector<bool> visited(this->size, false);

	vector<pair<int, pair<int, int>>> edges; //stores (cost, (start node, end node)) of the edge

	int compute = 0; //the node being computed
	while(true) {
		if(!visited[compute]) {
			for(int i = 0; i < this->size; i++) {
				if(!visited[i]) {
					if(this->Cost[compute][i])
						edges.push_back(make_pair(this->Cost[compute][i], make_pair(compute, i)));
				}
			}
			visited[compute] = true;
		}

		if(edges.size() > 0) {
			sort(edges.begin(), edges.end());
			if(!visited[edges[0].second.second]) {
				MST->Cost[edges[0].second.first][edges[0].second.second] = MST->Cost[edges[0].second.second][edges[0].second.first] = edges[0].first;
				compute = edges[0].second.second;
			}
			edges.erase(edges.begin());
		}
		else {
			compute++;
			if(compute == this->size) compute = 0;
		}

		bool check = true;
		for(int i = 0; i < this->size; i++) check = check && visited[i];
		if(check) break;
	}

	for(int i = 0; i < this->size; i++)
		for(int j = i; j < this->size; j++)
			if(MST->Cost[i][j])
				MST->A[i][j] = MST->A[j][i] = true;
	return MST;
}
