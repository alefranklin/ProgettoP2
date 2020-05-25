#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ScrapedInfo {
  string name;
  int lvl;
  string file;
  ScrapedInfo(string n, int l, string f): name(n), lvl(l), file(f) {}
};

int main() {

  vector<ScrapedInfo> v;
  v.push_back(ScrapedInfo("test", 1, "file"));


  int w = 30;
  int h = 30;
  char mappa[w][h];

  for (int i = 0; i < w; i++) {
      for(int j = 0; j < h; j++) {
        mappa[i][j] = '#';
      }
  }

  mappa[15][15] = '@';
  mappa[10][20] = '$';

  for (int i = 0; i < w; i++) {
      for(int j = 0; j < h; j++) {
        cout << mappa[i][j];
      }
      cout << endl;
  }

  return 0;
}

/*
//
Game.getInventory().getItems() -> vector<Items>.getInfo()

//
Game.getInventory().getItem() -> vector<int> id
Game.getItem(id).getInfo()
Geme.GetCharacter(id).getInfo()


//interfaccia classe Game


Game {
  stream out_stream
  stream in_stream
  stream choice_stream

  Container<Entity*> istances

  instances.getItem(id)
  instnces.getCharacter(id)

  //mappa
  Chracter move(char) // w a s d


}

Game.move("w")

     Game
       |
       |
    entity
  /        \
 /          \
character   Item*/
