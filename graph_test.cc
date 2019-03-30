#include "HexBoard.cc"
////////
using namespace std;

int main()
{
  const int size = 4;
  graph g(size*size);
  int i{}, j{}; //positon of hexagon as (i, j)
  int n{}; //Node number derived from i and j (n = i*size + j)
  const int s = size;
  for(i = 0; i < s; i++) {
    for(j = 0; j < s; j++) {
      n = i*s + j;
      if(i == 0 && j == 0) { //Corner Hexagon
        g.put_edge(n, (i+1)*s + j);
        g.put_edge(n, i*s + (j+1));
      }
      else if(i == 0 && j == s-1) { //Corner Hexagon
        g.put_edge(n, i*s + (j-1));
        g.put_edge(n, (i+1)*s + (j-1));
        g.put_edge(n, (i+1)*s + j);
      }
      else if(i == s-1 && j == 0) { //Corner Hexagon
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, (i-1)*s + (j+1));
        g.put_edge(n, i*s + (j+1));
      }
      else if(i == s-1 && j == s-1) { //Corner Hexagon
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, i*s + (j-1));
      }
      else if(i == 0) { //Edge Hexagon
        g.put_edge(n, (i*s + (j-1)));
        g.put_edge(n, (i*s + (j+1)));
        g.put_edge(n, ((i+1)*s + (j-1)));
        g.put_edge(n, ((i+1)*s + j));
      }
      else if(i == s-1) { //Edge Hexagon
        g.put_edge(n, i*s + (j-1));
        g.put_edge(n, i*s + (j+1));
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, (i-1)*s + (j+1));
      }
      else if(j == 0) { //Edge Hexagon
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, (i+1)*s + j);
        g.put_edge(n, (i-1)*s + (j+1));
        g.put_edge(n, i*s + (j+1));
      }
      else if(j == s-1) { //Edge Hexagon
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, (i+1)*s + j);
        g.put_edge(n, i*s + (j-1));
        g.put_edge(n, (i+1)*s + (j-1));
      }
      else { //Internal Hexagon
        g.put_edge(n, (i-1)*s + j);
        g.put_edge(n, (i+1)*s + j);
        g.put_edge(n, i*s + (j-1));
        g.put_edge(n, (i+1)*s + (j-1));
        g.put_edge(n, i*s + (j+1));
        g.put_edge(n, (i-1)*s + (j+1));
      }
    }
  }
  graph* h = &g;
  cout<<*h;
}
