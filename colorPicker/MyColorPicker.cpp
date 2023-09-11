#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <cmath>

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
MyColorPicker::MyColorPicker(double l, double ratio,Point center,double radius,double hue,double increment): l(l), ratio(ratio), center(center), radius(radius),hue(0), increment(increment)  {
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double dx = x - center.x;
  double dy = y - center.y;
  double d = sqrt((dx * dx) + (dy * dy));
  double pct = d / radius;
  if(pct>1){

      HSLAPixel pixel(hue, 1, l*ratio);
      return pixel;
  }
  HSLAPixel pixel(hue, 1, 0.5);
  hue += increment;
  if (hue >= 360) { hue -= 360; }
  return pixel;
}