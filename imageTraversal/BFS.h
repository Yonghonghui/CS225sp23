#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ~BFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  void set_visited(unsigned x, unsigned y);
  double get_tolerance();
  PNG *get_png();
  bool get_visited(unsigned x, unsigned y);

private:
  PNG png_;
  Point start_;
  double tolerance_;
  queue <Point> traversal;
  vector <vector <bool> > visited;
};

#endif
