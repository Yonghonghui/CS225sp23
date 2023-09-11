#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace cs225;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */

ImageTraversal::Iterator::Iterator():traversal(NULL), end_flag(true) {
  /** @todo [Part 1] */

}
ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) 
	:traversal(&traversal), start(start), end_flag(false) {
	curr = traversal.peek();
  //cout<<curr.x<<endl;
  }
ImageTraversal::Iterator::~Iterator() {
	if (traversal != NULL) {delete traversal;}
	traversal = NULL;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //std::cout << "line 53" << std::endl;  
  
  //std::cout << "line 58" << std::endl;
    if (traversal->empty()) {
    end_flag = true;
    return *this; 
  }
  curr = traversal->pop();
  traversal->set_visited(curr.x, curr.y);
    Point X=Point(curr.x + 1, curr.y);//right
    Point Y=Point(curr.x, curr.y + 1);//up
    Point x=Point(curr.x - 1, curr.y);//left
    Point y=Point(curr.x, curr.y - 1);//down
    PNG* png_ = traversal->get_png();
    if(X.x>=0&&X.y>=0&&X.x<png_->width()&&X.y<png_->height()){
    if(traversal->calculateDelta(*(traversal->get_png()->getPixel(X.x, X.y)),*(traversal->get_png()->getPixel(start.x, start.y))) < traversal->get_tolerance()) {
      traversal->add(X);
    }
    }
    if(Y.x>=0&&Y.y>=0&&Y.x<png_->width()&&Y.y<png_->height()){
    if(traversal->calculateDelta(*(traversal->get_png()->getPixel(Y.x, Y.y)),*(traversal->get_png()->getPixel(start.x, start.y))) < traversal->get_tolerance()) {
      traversal->add(Y);
    }
    }
    if(x.x>=0&&x.y>=0&&x.x<png_->width()&&x.y<png_->height()){
    if(traversal->calculateDelta(*(traversal->get_png()->getPixel(x.x, x.y)),*(traversal->get_png()->getPixel(start.x, start.y))) < traversal->get_tolerance()) {
      traversal->add(x);
    }
    }
    if(y.x>=0&&y.y>=0&&y.x<png_->width()&&y.y<png_->height()){
    if(traversal->calculateDelta(*(traversal->get_png()->getPixel(y.x, y.y)),*(traversal->get_png()->getPixel(start.x, start.y))) < traversal->get_tolerance()) {
      traversal->add(y);
    }
    }
  while ( !(traversal->empty()) && (traversal->get_visited(traversal->peek().x, traversal->peek().y))) {
  		traversal->pop();
  	}
    if (traversal->empty()) {
    end_flag = true;
    return *this; 
  } 
  if(!traversal->empty()){curr=traversal->peek();}
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (end_flag==true ) {return false;}
  return true;
}
