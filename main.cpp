
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;      png.readFromFile("cai.png");
  Point center(100,100);
  FloodFilledImage image(png);
  DFS dfs1(png, Point(200, 75), 0.2);
  HSLAPixel color1(231, 1, 0.5);
  SolidColorPicker solid1(color1);
  DFS dfs2(png, Point(200, 30), 0.2);
  HSLAPixel color2(231, 1,0);
  SolidColorPicker solid2(color2);
   image.addFloodFill( dfs2, solid2 );
  image.addFloodFill( dfs1, solid1 );
 
  BFS bfs1(png, Point(100, 100), 0.05);
  MyColorPicker myColorPicker(0.7,0.6,center,50.0,0,0.5);
  image.addFloodFill( bfs1, myColorPicker );
  Animation animation = image.animate(100);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  

  return 0;
}
