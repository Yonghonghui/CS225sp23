#include "HSLAPixel.h"
namespace cs225{
HSLAPixel::HSLAPixel (){
    //this->h=360;
    //this->s=1.0;
    this->a=1.0;
    this->l=1.0;

}
HSLAPixel::HSLAPixel (double hue, double saturation, double luminance){
    this->h=hue;
    this->s=saturation;
    this->l=luminance;
    this->a=1.0;
}
HSLAPixel::HSLAPixel (double hue, double saturation, double luminance,double alpha){
    this->h=hue;
    this->s=saturation;
    this->l=luminance;
    this->a=alpha;
}
}