#include <string>
#include "cs225/PNG.h"
#include "mp1.h"
using namespace cs225;
using namespace std;
void rotate(std::string inputFile, std::string outputFile) {
cs225::PNG p1;//create a png to store the picture file
if (p1.readFromFile(inputFile)==false){
    return;//if unsuccesfully read from the inputfile,fail
}
cs225::PNG p2(p1);
for (unsigned x = 0; x < p2.width(); x++) {
    for (unsigned y = 0; y < p2.height(); y++) {
        HSLAPixel *pixel1 = p1.getPixel(p2.width()-1-x,p2.height()-1-y);
        //get the corrresponding pointers of every pixel after rotation
        HSLAPixel *pixel2 = p2.getPixel(x, y);//get the pointers of every pixel
        *pixel2=*pixel1;//update the png
        }
    }
    p2.writeToFile(outputFile);//write the picture to the outputfile
}
