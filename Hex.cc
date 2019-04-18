#include "HexPlayer.cc"
////////////////////
using namespace std;

int main()
{
  HexBoard H(5);
  HexPlayer h;
  int k, l;
  pair<int, int>* com_move;
  Color c;
  cout<<H;
  /*do {
    cin>>k>>l;
    H.hex_move(Color::BLUE, k, l);
    cout<<endl<<H;
    com_move = h.give_move(H);
    H.hex_move(Color::RED, com_move.first, com_move.second);
    cout<<endl<<H;
  } while(c == Color::WHITE);
  cout<<endl<<static_cast<int>(c)<<" WON!";*/

  com_move = h.give_move(H);
  H.hex_move(Color::RED, com_move->first, com_move->second);
  cout<<endl<<H;
}
