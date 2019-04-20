#include "graph.cc"

using namespace std;

enum class Color : short{WHITE = 1, RED = 2, BLUE = 3};

class HexBoard: public graph {

protected:
  const int size; //size of the Hex board
  Color** color_matrix;
  graph* blue_g;
  graph* red_g;

public:
  HexBoard(int size): size(size) {
    int i{}, j{}; //positon of hexagon as (i, j)
    int n{}; //Node number derived from i and j (n = i*size + j)

    this->color_matrix = new Color*[this->size];
    for(int k = 0; k < this->size; k++) this->color_matrix[k] = new Color[this->size];
    for(int k = 0; k < this->size; k++)
      for(int l = 0; l < this->size; l++)
        this->color_matrix[k][l] = Color::WHITE;

    this->blue_g = new graph((this->size) * (this->size));
    this->red_g = new graph((this->size) * (this->size));
  }

  ~HexBoard() {
    for(int i = 0; i < this->size; i++) delete[] this->color_matrix[i];
    delete[] this->color_matrix;
    delete blue_g;
    delete red_g;
  }

  bool hex_move(Color c, int k, int l) {
    if(k < 0 || k >= this->size || l < 0 || l >= this->size) {
      cout<<"("<<k<<", "<<l<<")"<<": "<<"Illegal Move: Hexagon Doesn't Exist\n\n";
      return false;
    }
    const int s = this->size;
    int n = k*s + l;
    if(this->color_matrix[k][l] == Color::WHITE) this->color_matrix[k][l] = c;
    else return false;
    //To build the blue_g and red_g matrices with every move
    if(this->color_matrix[k][l] == Color::BLUE) {
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

  void swap_move() {
    const int s = this->size - 1;
    bool flag = false;
    for(int i = 0; i <= s; i++) {
      for(int j = 0; j <= s; j++) {
        if(this->color_matrix[i][j] == Color::BLUE) {
          this->color_matrix[i][j] = Color::WHITE;
          this->color_matrix[j][i] = Color::RED;
          flag = true;
          break;
        }
        else if(this->color_matrix[i][j] == Color::RED) {
          this->color_matrix[i][j] = Color::WHITE;
          this->color_matrix[j][i] = Color::BLUE;
          flag = true;
          break;
        }
      }
      if(flag) break;
    }
  }

  //Applies Dijkstra's Algorithm to check if a path exists between the blue edges or the red edges
  Color who_won() {
  int* p;
  for(int k1 = 0; k1 < this->size; k1++) {
    if(this->color_matrix[k1][0] != Color::RED) continue;
    for(int k2 = 0; k2 < this->size; k2++) {
      if(this->color_matrix[k2][this->size - 1] != Color::RED) continue;
      p = this->red_g->Dijkstra(k1*this->size, k2*this->size + this->size - 1);
      if(p != nullptr) return Color::RED;
    }
  }
  for(int l1 = 0; l1 < this->size; l1++) {
    if(this->color_matrix[0][l1] != Color::BLUE) continue;
    for(int l2 = 0; l2 < this->size; l2++) {
      if(this->color_matrix[this->size - 1][l2] != Color::BLUE) continue;
      p = this->blue_g->Dijkstra(l1, (this->size - 1)*this->size + l2);
      if(p != nullptr) return Color::BLUE;
    }
  }
  return Color::WHITE; //returns white if nobody won yet
}

  //Ostream Operator (Prints a rhombus with the indices of each hexagon, and its current color)
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
        if(i == 1 && s == sz/2) hout<<"RED    ";
        else if(i == 2*sz - 1 && s == sz/2) hout<<"BLUE   ";
        else hout<<"       ";
      }
      char c;
      n = i>sz?(2*sz-i):i;
      for(int j = 1; j <= n; j++) {
        if(color_matrix[k][l] == Color::RED) c = 'R';
        else if(color_matrix[k][l] == Color::BLUE) c = 'B';
        else c = '0';
        hout<<"("<<k<<","<<l<<"):"<<c;
        hout<<"       ";
        k++;
        l++;
      }
      hout<<endl;
    }
    return hout;
  }

  void operator = (const HexBoard& H) {
    if(this->size == H.size) {
      *this->blue_g = *H.blue_g;
      *this->red_g = *H.red_g;
      for(int i = 0; i < this->size; i++) {
        for(int j = 0; j < this->size; j++) {
          this->color_matrix[i][j] = H.color_matrix[i][j];
        }
      }
    }
  }

  friend class HexPlayer;
};
