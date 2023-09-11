#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


using namespace cs225;
using namespace std;
//help me Initialize a depth-first ImageTraversal on a given `png` image, starting at `start`, and with a given `tolerance`.

//Returns an iterator for the traversal starting at the first point.
//Returns an iterator for the traversal one past the end of the traversal.
//Adds a Point for the traversal to visit at some point in the future.
//Removes and returns the current Point in the traversal.
//Returns the current Point in the traversal.
//Returns true if the traversal is empty.



/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) :png_(png), start_(start), tolerance_(tolerance){  
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
}
DFS::~DFS(){
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //travese the image
  DFS * DFS_ = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*DFS_, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
    return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  /* if(visited[point.x][point.y]==true){
    return;
  } */
  if(point.x<0||point.y<0||point.x>=png_.width()||point.y>=png_.height()){
    return;
  }
  traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point curr=traversal.top();
  traversal.pop();
  return curr;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return traversal.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(traversal.size()==0){return true;}
  return false;
}
void DFS::set_visited(unsigned x, unsigned y){
  visited[x][y]=true;
}
PNG* DFS::get_png(){
  return &png_;
}
double DFS::get_tolerance(){
  return tolerance_;
}
bool DFS::get_visited(unsigned x, unsigned y){
  return visited[x][y];
}