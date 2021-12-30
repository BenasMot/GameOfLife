#include <omp.h>

#include <iostream>
#include <map>

#include "src/Cell.hpp"

using namespace std;

int main() {
  map<pair<int, int>, Cell> zemelapis;
  Cell cell = Cell(1, 2);
  pair<int, int> coords = make_pair(1,2);
  zemelapis[coords] = cell;
  zemelapis.at[coords];
  

  
  return 0;
}