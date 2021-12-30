#include <omp.h>

#include <iostream>
#include <map>

#include "src/Cell.hpp"

using namespace std;

int main() {
  map<pair<int, int>, Cell> zemelapis;
  Cell cell = Cell(1, 2);
  pair<int, int> coords = make_pair(1,2);
  zemelapis.insert(make_pair(coords, cell)); 

  Cell rastas = zemelapis.find(coords);

  
  return 0;
}