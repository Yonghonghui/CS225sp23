
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance):png_(png), start_(start), tolerance_(tolerance) {  
  /** @todo [Part 1] */
  traversal.push(start_);
  visited.resize(png_.width());
  for (unsigned i = 0; i < visited.size(); i++) {
    visited[i].resize(png_.height());
      for (unsigned j = 0; j < visited[i].size(); j++) {
        visited[i][j] = false;
      }
  }
  visited[start_.x][start_.y] = true;
  /* visited.resize(png.width(), vector<bool>(png.height(), false));  */
  /* visited[start_.x][start_.y]=true; */
}
BFS::~BFS(){
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * BFS_ = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*BFS_, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(point.x<0||point.y<0||point.x>=png_.width()||point.y>=png_.height()){
    return;
  }
  traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point temp = traversal.front();
  traversal.pop();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return traversal.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(traversal.size()==0){return true;}
  return false;
}


void BFS::set_visited(unsigned x, unsigned y){
  visited[x][y]=true;
}
PNG* BFS::get_png(){
  return &png_;
}
double BFS::get_tolerance(){
  return tolerance_;
}
bool BFS::get_visited(unsigned x, unsigned y){
  return visited[x][y];
}