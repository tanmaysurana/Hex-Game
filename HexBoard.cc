#include "graph.cc"

using namespace std;

enum class Color : short{WHITE = 1, RED = 2, BLUE = 3};

class HexBoard: public graph {

protected:
  const int size; //size of the Hex board
  graph* hex_board; //Hex Board as a graph
  Color** color_matrix;
  graph* blue_g;
  graph* red_g;

public:
  HexBoard(int size): size(size) {
    this->hex_board = new graph((this->size) * (this->size));  //Range is 4
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

    this->blue_g = new graph((this->size) * (this->size));
    this->red_g = new graph((this->size) * (this->size));
  }

  bool hex_move(Color c, int k, int l) {
      if(k < 0 || k >= this->size || l < 0 || l >= this->size) {
        cout<<"("<<k<<", "<<l<<")"<<": "<<"Illegal Move: Hexagon Doesn't Exist\n\n";
        return false;
      }
      const int s = this->size;
      int n = 0;
      if(this->color_matrix[k][l] == Color::WHITE) {
        this->color_matrix[k][l] = c;
        if(this->color_matrix[k][l] == Color::BLUE) {
          n = k*s + l;
          if(k == 0 && l == 0) { //Corner Hexagon
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l+1));
          }
          else if(k == 0 && l == s-1) { //Corner Hexagon
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + (l-1));
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + l);
          }
          else if(k == s-1 && l == 0) { //Corner Hexagon
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + (l+1));
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l+1));
          }
          else if(k == s-1 && l == s-1) { //Corner Hexagon
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l-1));
          }
          else if(k == 0) { //Edge Hexagon
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, (k*s + (l-1)));
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, (k*s + (l+1)));
            if(this->color_matrix[k+1][l-1] == Color::BLUE) this->blue_g->put_edge(n, ((k+1)*s + (l-1)));
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, ((k+1)*s + l));
          }
          else if(k == s-1) { //Edge Hexagon
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l+1));
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + (l+1));
          }
          else if(l == 0) { //Edge Hexagon
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + (l+1));
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l+1));
          }
          else if(l == s-1) { //Edge Hexagon
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + (l-1));
          }
          else { //Internal Hexagon
            if(this->color_matrix[k+1][l] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k-1][l] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k][l-1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::BLUE) this->blue_g->put_edge(n, (k+1)*s + (l-1));
            if(this->color_matrix[k][l+1] == Color::BLUE) this->blue_g->put_edge(n, k*s + (l+1));
            if(this->color_matrix[k-1][l+1] == Color::BLUE) this->blue_g->put_edge(n, (k-1)*s + (l+1));
          }
        }
        else if(this->color_matrix[k][l] == Color::RED) {
          if(k == 0 && l == 0) { //Corner Hexagon
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, k*s + (l+1));
          }
          else if(k == 0 && l == s-1) { //Corner Hexagon
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::RED) this->red_g->put_edge(n, (k+1)*s + (l-1));
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, (k+1)*s + l);
          }
          else if(k == s-1 && l == 0) { //Corner Hexagon
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::RED) this->red_g->put_edge(n, (k-1)*s + (l+1));
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, k*s + (l+1));
          }
          else if(k == s-1 && l == s-1) { //Corner Hexagon
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, k*s + (l-1));
          }
          else if(k == 0) { //Edge Hexagon
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, (k*s + (l-1)));
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, (k*s + (l+1)));
            if(this->color_matrix[k+1][l-1] == Color::RED) this->red_g->put_edge(n, ((k+1)*s + (l-1)));
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, ((k+1)*s + l));
          }
          else if(k == s-1) { //Edge Hexagon
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, k*s + (l+1));
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::RED) this->red_g->put_edge(n, (k-1)*s + (l+1));
          }
          else if(l == 0) { //Edge Hexagon
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k-1][l+1] == Color::RED) this->red_g->put_edge(n, (k-1)*s + (l+1));
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, k*s + (l+1));
          }
          else if(l == s-1) { //Edge Hexagon
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::RED) this->red_g->put_edge(n, (k+1)*s + (l-1));
          }
          else { //Internal Hexagon
            if(this->color_matrix[k+1][l] == Color::RED) this->red_g->put_edge(n, (k+1)*s + l);
            if(this->color_matrix[k-1][l] == Color::RED) this->red_g->put_edge(n, (k-1)*s + l);
            if(this->color_matrix[k][l-1] == Color::RED) this->red_g->put_edge(n, k*s + (l-1));
            if(this->color_matrix[k+1][l-1] == Color::RED) this->red_g->put_edge(n, (k+1)*s + (l-1));
            if(this->color_matrix[k][l+1] == Color::RED) this->red_g->put_edge(n, k*s + (l+1));
            if(this->color_matrix[k-1][l+1] == Color::RED) this->red_g->put_edge(n, (k-1)*s + (l+1));
          }
        }
        return true;
      }
      else {
        cout<<"("<<k<<", "<<l<<")"<<": "<<endl<<"Illegal Move: Hexagon is already ";
        if(this->color_matrix[k][l] == Color::BLUE) cout<<"BLUE\n\n";
        else cout<<"RED\n\n";
        return false;
      }
  }

  Color who_won() {
  int* p;
  for(int k1 = 0; k1 < this->size; k1++) {
    if(this->color_matrix[k1][0] == Color::RED) {
      for(int k2 = 0; k2 < this->size; k2++) {
        if(this->color_matrix[k2][this->size - 1] == Color::RED) {
          p = this->red_g->Dijkstra(k1*this->size, k2*this->size + this->size - 1);
          if(p != nullptr) return Color::RED;
        }
      }
    }
  }
  for(int l1 = 0; l1 < this->size; l1++) {
    if(this->color_matrix[0][l1] == Color::BLUE) {
      for(int l2 = 0; l2 < this->size; l2++) {
        if(this->color_matrix[this->size - 1][l2] == Color::BLUE) {
          p = this->blue_g->Dijkstra(l1, (this->size - 1)*this->size + l2);
          if(p != nullptr) return Color::BLUE;
        }
      }
    }
  }
  return Color::WHITE;
}

  //Ostream Operator
  friend ostream& operator << (ostream& hout, const HexBoard& h) {
    const int sz = h.size;
    int k = sz;
    int l = 0;
    int n{};
    for(int i = 1; i <= 2*sz - 1; i++) {
      if(i <= sz) {
        k = sz - i;
        l = 0;
      }
      else {
        k = 0;
        l = i - sz;
      }
      n = i>sz?(i-sz):(sz-i);
      for(int s = 1; s <= n; s++) {
        if(i == 1 && s == sz/2) hout<<"RED(2) ";
        else if(i == 2*sz - 1 && s == sz/2) hout<<"BLUE(3)";
        else hout<<"       ";
      }
      n = i>sz?(2*sz-i):i;
      for(int j = 1; j <= n; j++) {
        hout<<"("<<k<<","<<l<<"):"<<static_cast<int>(h.color_matrix[k][l]);
        hout<<"       ";
        k++;
        l++;
      }
      hout<<endl;
    }
    return hout;
  }

};
