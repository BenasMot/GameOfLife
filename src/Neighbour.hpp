#include <utility>
using namespace std;

class Neighbour {
 private:
  pair<int, int> coordinates;
  bool isAlive;
  int countOfAliveAdjacent;

 public:
  Neighbour(pair<int, int> coordinates, bool isAlive);
  ~Neighbour();
  int getCountOfAliveAdjacent();
  void increaseCountOfAliveAdjacent();
};

Neighbour::Neighbour(pair<int, int> coordinates, bool isAlive) {
  this->coordinates = coordinates;
  this->isAlive = isAlive;
}
Neighbour::~Neighbour() {}

int Neighbour::getCountOfAliveAdjacent() { return countOfAliveAdjacent; }
void Neighbour::increaseCountOfAliveAdjacent() { countOfAliveAdjacent++; }
