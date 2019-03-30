#include "graph.cc"

using namespace std;

class HexBoard: public graph {
protected:
  const int size; //size of the Hex board
  graph* hex_board; //Hex Board as a graph

public:
  HexBoard(int size): size(size) {
    this->hex_board = new graph((this->size) * (this->size));
    int i{}, j{}; //positon of hexagon as (i, j)
    int n{}; //Node number derived from i and j (n = i*size + j)
    const int s = this->size;
    for(i = 0; i < s; i++) {
      for(j = 0; j < s; j++) {
        n = i*s + j;
        if(i == 0 && j == 0) { //Corner Hexagon
          this->hex_board->put_edge(n, (i+1)*s + j);
          this->hex_board->put_edge(n, i*s + (j+1));
        }
        else if(i == 0 && j == s-1) { //Corner Hexagon
          this->hex_board->put_edge(n, i*s + (j-1));
          this->hex_board->put_edge(n, (i+1)*s + (j-1));
          this->hex_board->put_edge(n, (i+1)*s + j);
        }
        else if(i == s-1 && j == 0) { //Corner Hexagon
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, (i-1)*s + (j+1));
          this->hex_board->put_edge(n, i*s + (j+1));
        }
        else if(i == s-1 && j == s-1) { //Corner Hexagon
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, i*s + (j-1));
        }
        else if(i == 0) { //Edge Hexagon
          this->hex_board->put_edge(n, (i*s + (j-1)));
          this->hex_board->put_edge(n, (i*s + (j+1)));
          this->hex_board->put_edge(n, ((i+1)*s + (j-1)));
          this->hex_board->put_edge(n, ((i+1)*s + j));
        }
        else if(i == s-1) { //Edge Hexagon
          this->hex_board->put_edge(n, i*s + (j-1));
          this->hex_board->put_edge(n, i*s + (j+1));
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, (i-1)*s + (j+1));
        }
        else if(j == 0) { //Edge Hexagon
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, (i+1)*s + j);
          this->hex_board->put_edge(n, (i-1)*s + (j+1));
          this->hex_board->put_edge(n, i*s + (j+1));
        }
        else if(j == s-1) { //Edge Hexagon
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, (i+1)*s + j);
          this->hex_board->put_edge(n, i*s + (j-1));
          this->hex_board->put_edge(n, (i+1)*s + (j-1));
        }
        else { //Internal Hexagon
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, (i+1)*s + j);
          this->hex_board->put_edge(n, i*s + (j-1));
          this->hex_board->put_edge(n, (i+1)*s + (j-1));
          this->hex_board->put_edge(n, i*s + (j+1));
          this->hex_board->put_edge(n, (i-1)*s + (j+1));
        }
      }
    }
  }

  //Ostream Operator
  friend ostream& operator << (ostream& hout, const HexBoard& h) {
    hout<<*h.hex_board;
    return hout;
  }
};
