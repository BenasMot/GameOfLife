#pragma once
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

class Cell {
 private:
  bool isAlive;
  int nearbyCells;

 public:
  Cell(bool isAlive);
  ~Cell();
  // Setters
  void setIsAlive(bool isAlive);
  void setNearbyCells(int nearbyCells);
  // Getters
  bool getIsAlive();
  int getNearbyCells();
  // Actions
  void increaseNearbyCells(int count = 1);
};

Cell::Cell(bool isAlive) { this->isAlive = isAlive; }
Cell::~Cell() {}

// Setters
void Cell::setIsAlive(bool isAlive) { this->isAlive = isAlive; }
void Cell::setNearbyCells(int nearbyCells) { this->nearbyCells = nearbyCells; }

// Getters
bool Cell::getIsAlive() { return isAlive; }
int Cell::getNearbyCells() { return nearbyCells; }

// Actions
void Cell::increaseNearbyCells(int count) { this->nearbyCells += count; }
