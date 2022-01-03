#pragma once
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

class Cell {
 private:
  bool isAlive;
  bool willDie = false;
  bool willAppear = false;
  int currentNearby = 0;
  int nextNearby = 0;

 public:
  Cell(bool isAlive = false);
  ~Cell();
  
  // Setters
  void setIsAlive(bool isAlive);
  void setWillDie(bool willDie = true);
  void setWillAppear(bool willAppear = true);

  // Getters
  bool getIsAlive();
  bool getWillDie();
  bool getWillAppear();
  int getNearbyCells();

  // Actions
  void increaseNearbyCells(int count = 1);
  void updateNearby();
  void appear();
  void die();
};

Cell::Cell(bool isAlive) { this->isAlive = isAlive; }
Cell::~Cell() {}

// Setters
void Cell::setIsAlive(bool isAlive) { this->isAlive = isAlive; }
void Cell::setWillDie(bool willDie) { this->willDie = willDie; }
void Cell::setWillAppear(bool willAppear) { this->willAppear = willAppear; }
// Getters
bool Cell::getIsAlive() { return isAlive; }
bool Cell::getWillDie() { return willDie; }
bool Cell::getWillAppear() { return willAppear; }
int Cell::getNearbyCells() { return currentNearby; }

// Actions
void Cell::increaseNearbyCells(int count) { this->nextNearby += count; }
void Cell::updateNearby() {
  currentNearby = nextNearby;
}
void Cell::appear() {
  if (willAppear && !isAlive) {
    isAlive = true;
    willAppear = false;
  }
}
void Cell::die() {
  if (willDie && isAlive) {
    isAlive = false;
    willDie = false;
  }
}