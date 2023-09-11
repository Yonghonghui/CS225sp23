/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    
    // convert pixels of tiles to points and build std::map
    vector<Point<3>> TilesPoints(theTiles.size());
    std::map<Point<3>, TileImage*> TilesPointsMap;
    for(unsigned i=0; i<theTiles.size(); i++){
        TilesPoints[i] = convertToLAB(theTiles[i].getAverageColor());
        // TilesPoints[i][0] = theTiles[i].getAverageColor().h / 360;
        // TilesPoints[i][1] = theTiles[i].getAverageColor().s;
        // TilesPoints[i][2] = theTiles[i].getAverageColor().l;
        TilesPointsMap[TilesPoints[i]] = &theTiles[i];
    }

    // build KDtree
    KDTree<3>* TilesTree = new KDTree<3>(TilesPoints);

    // create mosaic canvas
    MosaicCanvas* result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // find nearest neighbor
    Point<3> real;
    Point<3> nearest;
    for(int i=0; i<theSource.getRows(); i++){
        for(int j=0; j<theSource.getColumns(); j++){
            real[0] = theSource.getRegionColor(i, j).h / 360;
            real[1] = theSource.getRegionColor(i, j).s;
            real[2] = theSource.getRegionColor(i, j).l;
            nearest = TilesTree->findNearestNeighbor(real);

            result->setTile(i, j, TilesPointsMap[nearest]);
        }
    }

    // clean memory
    TilesPointsMap.clear();
    TilesPoints.clear();
    return result;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
