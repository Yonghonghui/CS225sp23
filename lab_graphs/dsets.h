/* Your code here! */
#ifndef dsets_H
#define dsets_H

#include <vector>



class DisjointSets
{
public:
/*
    * This function is default constructor for DisjointSets class,which 
    * creates n unconnected root nodes at the end of the vector and 
    * innitially the vector is empty.
*/
  DisjointSets();
/*
    * This function is default destructor for DisjointSets class.
*/
  ~DisjointSets();
/*
    * This function is copy constructor for DisjointSets class.
*/
  DisjointSets(const DisjointSets & other);
/*
    * This function is used to create num unconnected root nodes at the end of the vector.
*/
  void addelements(int num);
/*
    * This function is used to find the root of the up-tree in which the parameter element resides.
    * It uses path compression to flatten the structure of the up-tree.
*/
  int find(int elem);
/*
    * This function is used to combine two disjoint sets into a single set.
    * It uses union by size to merge the two sets.
*/
  void setunion(int a, int b);
/*
    * This function is used to return the number of nodes in the up-tree containing the parameter element.
*/
  int size(int elem);
private:
    std::vector<int> set;
};

#endif