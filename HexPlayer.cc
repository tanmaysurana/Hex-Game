//Write an AI that plays HEX
#include "HexBoard.cc"
#include <random>

using namespace std;
//COM is always RED
class HexPlayer {

public:
  HexPlayer(){}

  bool red_won(const HexBoard& H) {
    int* p;
    for(int k1 = 0; k1 < H.size; k1++) {
      if(H.color_matrix[k1][0] == Color::RED) {
        for(int k2 = 0; k2 < H.size; k2++) {
          if(H.color_matrix[k2][H.size - 1] == Color::RED) {
            p = H.red_g->Dijkstra(k1*H.size, k2*H.size + H.size - 1);
            if(p != nullptr) return true;
          }
        }
      }
    }
    return false;
  }

  void make_rand_move(HexBoard& B, Color c) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, B.size - 1);
    int k, l;
    do {
      k = dist(mt);
      l = dist(mt);
    } while(!B.hex_move(c, k, l));
  }

  pair<int, int>* give_move(const HexBoard& H) {
    const int num_sim = 100;
    int max = 0;
    HexBoard B(H.size);
    B = H;
    const int s = B.size;
    int win_count = 0;
    int k = 0, l = 0;
    cout<<endl<<"Computing...";
    for(int i = 0; i < s; i++) {
      for(int j = 0; j < s; j++) {
        B = H;
        if(B.color_matrix[i][j] == Color::WHITE) {
          B.hex_move(Color::RED, i, j);
          win_count = 0;
          for(int n = 0; n < num_sim; n++) {
            for(int m = 0; m <= s*s/2; m++) {
              this->make_rand_move(B, Color::BLUE);
              this->make_rand_move(B, Color::RED);
            }
            if(this->red_won(B)) win_count++;
          }
          if(win_count > max) {
            max = win_count;
            k = i;
            l = j;
          }
        }
      }
    }
    pair<int, int>* p;
    p->first = k;
    p->second = l;
    return p;
  }

};
