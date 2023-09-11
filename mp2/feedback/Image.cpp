#include "Image.h"
namespace cs225{
    void Image::lighten	(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
              Pixel->l=Pixel->l+0.1;
              if(Pixel->l>1){
                  Pixel->l=1;
                }
            }
        }
    }
    void Image::lighten (double amount){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->l=Pixel->l+amount;
              if(Pixel->l>1){
                  Pixel->l=1;
                }
            }
        }
    }
    void Image::darken	(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->l=Pixel->l-0.1;
              if(Pixel->l<0 ){
                  Pixel->l=0;
                }
            }
        }
    }
    void Image::darken	(double amount){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->l=Pixel->l-amount;
              if(Pixel->l<0){
                  Pixel->l=0;
                }
            }
        }
    }
    void Image::saturate(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->s=Pixel->s+0.1;
              if(Pixel->s>1){
                  Pixel->s=1;
                }
            }
        }
    }
    void Image::saturate(double amount){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->s=Pixel->s+amount;
              if(Pixel->s>1){
                  Pixel->s=1;
                }
            }
        }
    }
    void Image::desaturate(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->s=Pixel->s-0.1;
              if(Pixel->s<0){
                  Pixel->s=0;
                }
            }
        }
    }
    void Image::desaturate(double amount){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          HSLAPixel *Pixel = this->getPixel(x, y);
          Pixel->s=Pixel->s-amount;
              if(Pixel->s<0){
                  Pixel->s=0;
                }
            }
        }
    }
    void Image::grayscale (){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel *pixel = this->getPixel(x, y);
            pixel->s=0;
            }
        }
    }	 
    void Image::rotateColor	(double degrees){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel *pixel = this->getPixel(x, y);
            pixel->h=pixel->h+degrees;
            if(pixel->h>360){
                pixel->h=pixel->h-360;
                }
            if(pixel->h<0){
                pixel->h=pixel->h+360;
            }
            }
        }
    }
    void Image::illinify(){
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
        HSLAPixel *pixel = this->getPixel(x, y);
        if(pixel->h>=180.0){
            if((360-pixel->h+11)*(360-pixel->h+11)<(pixel->h-216)*(pixel->h-216)){
                pixel->h=11;
            }
            else{pixel->h=216;}
         }
        else{
            if((pixel->h-11)*(pixel->h-11)<(pixel->h-216)*(pixel->h-216)){
                pixel->h=11;
            }
            else{pixel->h=216;}
                }
            }
        }
    }
    void Image::scale(double factor){
        unsigned int w=this->width()*factor;
        unsigned int h=this->height()*factor;
        PNG new_image(w,h);
        for (unsigned x = 0; x < w; x++) {
            for (unsigned y = 0; y < h; y++) {
                HSLAPixel *new_pixel=new_image.getPixel(x,y);
                HSLAPixel *old_pixel=getPixel(x/factor,y/factor);
                *new_pixel=*old_pixel;
                }
             }
        resize(w,h);
        for (unsigned x = 0; x < w; x++) {
            for (unsigned y = 0; y < h; y++) {
                HSLAPixel *new_pixel=new_image.getPixel(x,y);
                HSLAPixel *pixel=getPixel(x,y);
                *pixel=*new_pixel;
                }
             }
    }
    void Image::scale (unsigned w,unsigned h ){
        
        double k1=w/(this->width());
        double k2=h/(this->height());
        PNG new_image(w,h);
        for (unsigned x = 0; x < w; x++) {
            for (unsigned y = 0; y < h; y++) {
                HSLAPixel *new_pixel=new_image.getPixel(x,y);
                HSLAPixel *old_pixel=getPixel(x/k1,y/k2);
                *new_pixel=*old_pixel;
                }
             }
        resize(w,h);
        for (unsigned x = 0; x < w; x++) {
            for (unsigned y = 0; y < h; y++) {
                HSLAPixel *new_pixel=new_image.getPixel(x,y);
                HSLAPixel *pixel=getPixel(x,y);
                *pixel=*new_pixel;
                }
             }
    }
}