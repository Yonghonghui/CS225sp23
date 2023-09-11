#include "StickerSheet.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
using namespace std;

namespace cs225{
        StickerSheet::StickerSheet(){
            p=new Image();
            m=1;
            ptr=new Image[m];
            X=new unsigned [m];
            Y=new unsigned [m];
            X[0]=0;
            Y[0]=0;
            count=0;
        }
        StickerSheet::StickerSheet(const Image & picture,unsigned max){
            p=new Image(picture);
            m=max;
            ptr=new Image[m];
            X=new unsigned [m];
            Y=new unsigned [m];
            X[0] = 0; 
            Y[0] = 0;
            count=0;
        }
        StickerSheet::~StickerSheet(){
            delete p;
            delete []ptr;
            delete []X;
            delete []Y;
        }
        StickerSheet::StickerSheet(const StickerSheet & other){
            *p=*other.p;
            m=other.m;
            count=other.count;
            ptr=new Image[m];
            X=new unsigned [m];
            Y=new unsigned [m];
            for(unsigned i=0;i<m;i++){
                ptr[i]=other.ptr[i];
                X[i]=other.X[i];
                Y[i]=other.Y[i];
            }
        }
        const StickerSheet& StickerSheet::operator=(const StickerSheet & 	other){
            if(this!=&other){
                m=other.m;
                *p=*other.p;
                count=other.count;
                delete p;
                delete[]ptr;
                delete[]X;
                delete[]Y;
                ptr=new Image[m];
                X=new unsigned [m];
                Y=new unsigned [m]; 
                for(unsigned i=0;i<m;i++){
                    ptr[i]=other.ptr[i];
                    X[i]=other.X[i];
                    Y[i]=other.Y[i];
                }
            }
            return *this;
        }
        void StickerSheet::changeMaxStickers	(unsigned max){
            Image* new_ptr=new Image[max];
            unsigned int* new_X=new unsigned [max];
            unsigned int* new_Y=new unsigned [max];
            if(m<=max){
                for(unsigned i=0;i<m;i++){
                    new_ptr[i]=ptr[i];
                    new_X[i]=X[i];
                    new_Y[i]=Y[i];
                }
                delete[]ptr;
                delete[]X;
                delete[]Y;
                ptr=new_ptr;
                X=new_X;
                Y=new_Y;
                m=max;
            }
            else{
                m=max;
                for(unsigned i=0;i<m;i++){
                    new_ptr[i]=ptr[i];
                    new_X[i]=X[i];
                    new_Y[i]=Y[i];
                }
                delete[]ptr;
                delete[]X;
                delete[]Y;
                ptr=new_ptr;
                X=new_X;
                Y=new_Y;
                if(count>max){count=max;}
            }
            
        }
        int StickerSheet::addSticker(Image & sticker,unsigned x,unsigned y){
            if(count==m){
                return -1;
            }
            else{
                ptr[count]=sticker;
                X[count]=x;
                Y[count]=y;
                count++;
                return count-1;
            }
        }
        bool StickerSheet::translate(unsigned index,unsigned x,unsigned y){
            if(index>count-1 || index>=m ||index<0){
                return false;
            }
            else{
                X[index]=x;
                Y[index]=y;
                return true;
            }
        }
        void StickerSheet::removeSticker(unsigned index){
                if(index>=0 & index<count){
                    for(unsigned i=index;i<m-1;i++){
                    ptr[i]=ptr[i+1];
                    X[i]=X[i+1];
                    Y[i]=Y[i+1];
                    }
                    X[m-1]=0;
                    Y[m-1]=0;
                    count=count-1;
                }
        }
        Image* StickerSheet::getSticker(unsigned 	index)	const{
            if(index>count-1 || index>=m ||index<0){
                return NULL;
            }
            else{
                Image* P=& ptr[index];
                return P;
            }
        }
        Image StickerSheet::render() const{
            Image picture(*p);
            for(unsigned i=0;i<count;i++){
                //Image& P=ptr[i];
                if((X[i]+ptr[i].width())>picture.width()){
                            picture.resize(X[i]+ptr[i].width(),picture.height());
                        }
                if((Y[i]+ptr[i].height())>picture.height()){
                            picture.resize(picture.width(),Y[i]+ptr[i].height());
                        }
                for (unsigned x =0; x < ptr[i].width(); x++) {
                    for (unsigned y = 0; y < ptr[i].height(); y++) {
                        HSLAPixel *pixel_base = picture.getPixel(x+X[i], y+Y[i]);
                        HSLAPixel *pixel_layer = ptr[i].getPixel(x, y);
                        if(pixel_layer->a!=0){
                            *pixel_base=*pixel_layer;
                        }
                    }
                }
            }
            return picture;
        }
}