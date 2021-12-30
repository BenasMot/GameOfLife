#include <tuple>
#include <utility>
#include <vector>

#include "Neighbour.hpp"

using namespace std;

class Cell {
 private:
  bool isAlive;
  pair<int, int> coordinates;

 public:
  Cell(int x, int y);
  ~Cell();
  pair<int, int> getCoordinates();
  bool getIsAlive();
  vector<Neighbour> getNeighbours(vector<vector<bool>> grid);
};

Cell::Cell(int x, int y) { this->coordinates = make_pair(x, y); }
Cell::~Cell() {}

pair<int, int> Cell::getCoordinates() { return coordinates; }
bool Cell::getIsAlive() { return isAlive; }
vector<Neighbour> Cell::getNeighbours(vector<vector<bool>> grid) {
  vector<Neighbour> neighbours;
  auto [x, y] = coordinates;

  neighbours.push_back(Neighbour(make_pair(x - 1, y - 1), grid[x - 1][y - 1]));
  neighbours.push_back(Neighbour(make_pair(x, y - 1), grid[x][y - 1]));
  neighbours.push_back(Neighbour(make_pair(x + 1, y - 1), grid[x + 1][y - 1]));
  neighbours.push_back(Neighbour(make_pair(x - 1, y), grid[x - 1][y]));
  neighbours.push_back(Neighbour(make_pair(x + 1, y), grid[x + 1][y]));
  neighbours.push_back(Neighbour(make_pair(x - 1, y + 1), grid[x - 1][y + 1]));
  neighbours.push_back(Neighbour(make_pair(x, y + 1), grid[x][y + 1]));
  neighbours.push_back(Neighbour(make_pair(x + 1, y + 1), grid[x + 1][y + 1]));

  return neighbours;
}
