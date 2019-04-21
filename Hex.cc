#include "HexPlayer.cc"

using namespace std;

int main()
{

  const int num_sims = 1000;

  srand(time(nullptr));
  int board_size;
  cout<<"Board Size (>=2): ";
  do {
    cin>>board_size;
  } while(board_size < 2);
  HexBoard H(board_size);
  char b, r;
  cout<<endl<<"RED plays first"<<endl<<endl;
  cout<<"Enter H for Human and C for Computer"<<endl;
  cout<<"BLUE Player: ";
  cin>>b;
  cout<<"RED Player: ";
  cin>>r;
  cout<<endl<<H<<endl;
  Color c;
  if((b == 'C' || b == 'c') && (r == 'C' || r == 'c')) {
    HexPlayer h1(Color::RED);
    HexPlayer h2(Color::BLUE);
    pair<int, int>* com_move;
    com_move = h1.give_first_move(H, num_sims);
    H.hex_move(h1.color, com_move->first, com_move->second);
    cout<<endl<<H<<endl;
    com_move = h2.give_move(H, true, num_sims);
    if(com_move->first == -1 && com_move->second == -1) H.swap_move();
    else H.hex_move(h2.color, com_move->first, com_move->second);
    cout<<endl<<H<<endl;
    while(true){
      com_move = h1.give_move(H, num_sims);
      H.hex_move(h1.color, com_move->first, com_move->second);
      cout<<endl<<H<<endl;
      c = H.who_won();
      if(c == Color::RED) {
        cout<<"RED WON!"<<endl;
        break;
      }
      else if(c == Color::BLUE) {
        cout<<"BLUE WON!"<<endl;
        break;
      }

      com_move = h2.give_move(H, num_sims);
      H.hex_move(h2.color, com_move->first, com_move->second);
      cout<<endl<<H<<endl;
      c = H.who_won();
      if(c == Color::RED) {
        cout<<"RED WON!"<<endl;
        break;
      }
      else if(c == Color::BLUE) {
        cout<<"BLUE WON!"<<endl;
        break;
      }
    }
  }
  else if((b == 'c' || b == 'C') || (r == 'c' || r == 'C')) {
    if(b == 'c' || b == 'C') c = Color::BLUE;
    else c = Color::RED;
    HexPlayer h(c);
    Color hu = (h.color == Color::RED) ? Color::BLUE : Color::RED;
    pair<int, int>* com_move;
    char ck, cl;
    int k, l;
    if(h.color == Color::RED) {
      com_move = h.give_first_move(H, num_sims);
      H.hex_move(h.color, com_move->first, com_move->second);
      cout<<endl<<H<<endl;
      char swap;
      cout<<"Swap Move? (y/n): ";
      cin>>swap;
      if(swap == 'y' || swap == 'Y') H.swap_move();
      else {
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
        while(!H.hex_move(hu, k, l)) {
          cout<<"Illegal Move, try again\n";
          cin>>ck>>cl;
          k = ck - '0';
          l = cl - '0';
        }
      }
      cout<<endl<<H<<endl;
      while(true) {
        com_move = h.give_move(H, num_sims);
        H.hex_move(h.color, com_move->first, com_move->second);
        cout<<endl<<H<<endl;
        c = H.who_won();
        if(c == Color::RED) {
          cout<<"RED WON!"<<endl;
          break;
        }
        else if(c == Color::BLUE) {
          cout<<"BLUE WON!"<<endl;
          break;
        }
        cin>>ck>>cl;
        k = ck - '0';
        l = ck - '0';
        while(!H.hex_move(hu, k, l)) {
          cout<<"Illegal Move, try again\n";
          cin>>ck>>cl;
          k = ck - '0';
          l = cl - '0';
        }
        cout<<endl<<H<<endl;
        c = H.who_won();
        if(c == Color::RED) {
          cout<<"RED WON!"<<endl;
          break;
        }
        else if(c == Color::BLUE) {
          cout<<"BLUE WON!"<<endl;
          break;
        }
      }
    }
    else if(hu == Color::RED) {
      cin>>ck>>cl;
      k = ck - '0';
      l = cl - '0';
      while(!H.hex_move(hu, k, l)) {
        cout<<"Illegal Move, try again\n";
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
      }
      cout<<endl<<H<<endl;
      com_move = h.give_move(H, true, num_sims);
      if(com_move->first == -1 && com_move->second == -1) H.swap_move();
      else H.hex_move(h.color, com_move->first, com_move->second);
      cout<<endl<<H<<endl;
      while(true) {
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
        while(!H.hex_move(hu, k, l)) {
          cout<<"Illegal Move, try again\n";
          cin>>ck>>cl;
          k = ck - '0';
          l = cl - '0';
        }
        cout<<endl<<H<<endl;
        c = H.who_won();
        if(c == Color::RED) {
          cout<<"RED WON!"<<endl;
          break;
        }
        else if(c == Color::BLUE) {
          cout<<"BLUE WON!"<<endl;
          break;
        }
        com_move = h.give_move(H, num_sims);
        H.hex_move(h.color, com_move->first, com_move->second);
        cout<<endl<<H<<endl;
        c = H.who_won();
        if(c == Color::RED) {
          cout<<"RED WON!"<<endl;
          break;
        }
        else if(c == Color::BLUE) {
          cout<<"BLUE WON!"<<endl;
          break;
        }
      }
    }
  }
  else {
    char ck, cl;
    int k, l;
    Color rhu = Color::RED;
    Color bhu = Color::BLUE;
    cin>>ck>>cl;
    k = ck - '0';
    l = cl - '0';
    while(!H.hex_move(rhu, k, l)) {
      cout<<"Illegal Move, try again\n";
      cin>>ck>>cl;
      k = ck - '0';
      l = cl - '0';
    }
    cout<<endl<<H<<endl;
    cout<<"Swap Move? (y/n): ";
    char swap;
    cin>>swap;
    if(swap == 'y' || swap == 'Y') H.swap_move();
    else {
      cin>>ck>>cl;
      k = ck - '0';
      l = cl - '0';
      while(!H.hex_move(bhu, k, l)) {
        cout<<"Illegal Move, try again\n";
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
      }
    }
    cout<<endl<<H<<endl;
    while(true) {
      cin>>ck>>cl;
      k = ck - '0';
      l = cl - '0';
      while(!H.hex_move(rhu, k, l)) {
        cout<<"Illegal Move, try again\n";
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
      }
      cout<<endl<<H<<endl;
      c = H.who_won();
      if(c == Color::RED) {
        cout<<"RED WON!"<<endl;
        break;
      }
      else if(c == Color::BLUE) {
        cout<<"BLUE WON!"<<endl;
        break;
      }
      cin>>ck>>cl;
      k = ck - '0';
      l = cl - '0';
      while(!H.hex_move(bhu, k, l)) {
        cout<<"Illegal Move, try again\n";
        cin>>ck>>cl;
        k = ck - '0';
        l = cl - '0';
      }
      cout<<endl<<H<<endl;
      c = H.who_won();
      if(c == Color::RED) {
        cout<<"RED WON!"<<endl;
        break;
      }
      else if(c == Color::BLUE) {
        cout<<"BLUE WON!"<<endl;
        break;
      }
    }
  }

}
