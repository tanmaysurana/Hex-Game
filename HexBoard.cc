#include "graph.cc"

using namespace std;

enum class Color : short{WHITE = 1, RED = 2, BLUE = 3};

class HexBoard: public graph {

protected:
  const int size; //size of the Hex board
  graph* hex_board; //Hex Board as a graph
  Color** color_matrix;

public:
  HexBoard(int size): size(size) {
    this->hex_board = new graph((this->size) * (this->size), 4);  //Range is 4
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
          this->hex_board->put_edge(n, (i+1)*s + j);
          this->hex_board->put_edge(n, (i-1)*s + j);
          this->hex_board->put_edge(n, i*s + (j-1));
          this->hex_board->put_edge(n, (i+1)*s + (j-1));
          this->hex_board->put_edge(n, i*s + (j+1));
          this->hex_board->put_edge(n, (i-1)*s + (j+1));
        }
      }
    }

    color_matrix = new Color*[this->size];
    for(int k = 0; k < this->size; k++) color_matrix[k] = new Color[this->size];
    for(int k = 0; k < this->size; k++)
      for(int l = 0; l < this->size; l++)
        color_matrix[k][l] = Color::WHITE;
  }

  //Ostream Operator
  friend ostream& operator << (ostream& hout, const HexBoard& h) {
    hout<<"   ";
		for(int k{}; k < h.size; k++)
			hout<<k<<" ";
		hout<<endl;
    for(int k{}; k < h.size; k++) {
			if(k/10 > 0) hout<<k<<" ";
			else hout<<k<<"  ";

			for(int l{}; l < h.size; l++) {
				hout<<static_cast<int>(h.color_matrix[k][l]);
				if(l/10 > 0) hout<<"  ";
				else hout<<" ";
			}
			hout<<endl;
		}
    return hout;
  }

  void hex_move(Color c, int k, int l) {
    if(this->color_matrix[k][l] == Color::WHITE) {
      this->color_matrix[k][l] = c;
    }
    else {
      cout<<endl<<"Illegal Move: Hexagon is already ";
      if(this->color_matrix[k][l] == Color::BLUE) cout<<"BLUE\n";
      else cout<<"RED\n";
      return;
    }
  }
};
