#include "HexBoard.cc"

using namespace std;

inline int rand_in_range(int a, int b) {
  double num = RAND_MAX/(b-a+1);
  int r = rand();
  int i = 0;
  while(r >= i*num) i++;
  i--;
  return i;
}

class HexPlayer {

public:
  const Color color;
  HexPlayer(Color c): color(c){}

  bool com_won(const HexBoard& H) {
    int* p;
    bool flag = false;
    const int s = H.size;
    if(this->color == Color::RED) {
      for(int k1 = 0; k1 < s; k1++) {
        if(H.color_matrix[k1][0] != Color::RED) continue;
        for(int k2 = 0; k2 < s; k2++) {
          if(H.color_matrix[k2][s-1] != Color::RED) continue;
          p = H.red_g->Dijkstra(k1*s + 0, k2*s + (s-1));
          if(p) {
            flag = true;
            delete[] p;
          }
          if(flag) return true;
        }
      }
      return false;
    }
    else if(this->color == Color::BLUE){
      for(int l1 = 0; l1 < s; l1++) {
        if(H.color_matrix[0][l1] != Color::BLUE) continue;
        for(int l2 = 0; l2 < s; l2++) {
          if(H.color_matrix[s-1][l2] != Color::BLUE) continue;
          p = H.blue_g->Dijkstra(0*s + l1, (s-1)*s + l2);
          if(p) {
            flag = true;
            delete[] p;
          }
          if(flag) return true;
        }
      }
      return false;
    }
  }

  void make_rand_move(HexBoard& B, Color c) {
    int k, l;
    do {
      k = rand_in_range(0, B.size - 1);
      l = rand_in_range(0, B.size - 1);
    } while(!B.hex_move(c, k, l));
  }

  pair<int, int>* give_first_move(const HexBoard& H, const int num_sims = 1000) {
    int win_count = 0, k = 0, l = 0;
    int max_wins = 0;
    cout<<"\nComputing...\n";
    HexBoard B(H.size);
    const int s = B.size;
    int count_white = 0; //number of colored hexes;
    for(int i = 0; i < s; i++)
      for(int j = 0; j < s; j++)
        if(H.color_matrix[i][j] == Color::WHITE) count_white++;
    int c_w = 0;
    const Color c = this->color;
    const Color b = (c == Color::RED ? Color::BLUE : Color::RED);
    for(int i = 0; i < s; i++) {
      for(int j = 0; j < s; j++) {
        if(H.color_matrix[i][j] == Color::WHITE) {
          win_count = 0;
          for(int n = 0; n < num_sims; n++) {
            B = H;
            c_w = count_white;
            B.hex_move(c, i, j);
            c_w--;
            B.swap_move();
            c_w--;
            for(int m = 0; m < s*s; m+=2) {
              this->make_rand_move(B, c);
              c_w--;
              if(c_w == 0) break;
              this->make_rand_move(B, b);
              c_w--;
              if(c_w == 0) break;
            }

            if(this->com_won(B)) win_count++;

          }
          if(win_count >= max_wins) {
            if(win_count == max_wins) { //coin toss to pick (k, l)
              if(rand() > (RAND_MAX*1.0)/2) {
                k = i;
                l = j;
              }
            }
            else {
              max_wins = win_count;
              k = i;
              l = j;
            }
          }
        }
      }
    }
    pair<int, int>* p = new pair<int, int>(k, l);
    return p;
  }

  pair<int, int>* give_move(const HexBoard& H, const bool swap = false, const int num_sims = 1000) {
    int win_count = 0, k = 0, l = 0;
    int max_wins = 0;
    cout<<"\nComputing...\n";
    HexBoard B(H.size);
    const int s = B.size;
    int count_white = 0; //number of colored hexes;
    for(int i = 0; i < s; i++)
      for(int j = 0; j < s; j++)
        if(H.color_matrix[i][j] == Color::WHITE) count_white++;
    int c_w = 0;
    const Color c = this->color;
    const Color b = (c == Color::RED ? Color::BLUE : Color::RED);
    for(int i = 0; i < s; i++) {
      for(int j = 0; j < s; j++) {
        if(H.color_matrix[i][j] == Color::WHITE) {
          win_count = 0;
          for(int n = 0; n < num_sims; n++) {
            B = H;
            c_w = count_white;
            B.hex_move(c, i, j);
            c_w--;
            for(int m = 0; m < s*s; m+=2) {
              this->make_rand_move(B, b);
              c_w--;
              if(c_w == 0) break;
              this->make_rand_move(B, c);
              c_w--;
              if(c_w == 0) break;
            }
            if(this->com_won(B)) win_count++;
          }

          if(win_count >= max_wins) {
            if(win_count == max_wins) { //coin toss to pick (k, l)
              if(rand() > (RAND_MAX*1.0)/2) {
                k = i;
                l = j;
              }
            }
            else {
              max_wins = win_count;
              k = i;
              l = j;
            }
          }
        }
      }
    }

    //to simaulate game with swap move
    if(swap) {
      win_count = 0;
      for(int n = 0; n < num_sims; n++) {
        B = H;
        c_w = count_white;
        B.swap_move();
        c_w--;
        for(int m = 0; m < s*s; m+=2) {
          this->make_rand_move(B, b);
          c_w--;
          if(c_w == 0) break;
          this->make_rand_move(B, c);
          c_w--;
          if(c_w == 0) break;
        }
        if(this->com_won(B)) win_count++;
      }
      if(win_count >= max_wins) {
        pair<int, int>* p = new pair<int, int>(-1, -1); //if swap_move is the best move, return pair as (-1, -1)
        return p;
      }
    }


    pair<int, int>* p = new pair<int, int>(k, l);
    return p;
  }

};
