/* Your code here! */

#include "dsets.h"

/*
    * This function is default constructor for DisjointSets class,which 
    * creates n unconnected root nodes at the end of the vector and 
    * innitially the vector is empty.
*/
DisjointSets::DisjointSets()
{
    set.clear();    
}
/*
    * This function is default destructor for DisjointSets class.
*/
DisjointSets::~DisjointSets()
{
    set.clear();
}

/*
    * This function is copy constructor for DisjointSets class.
*/
DisjointSets::DisjointSets(const DisjointSets & other)
{
    set = other.set;
}

/*
    * This function is used to create num unconnected root nodes at the end of the vector.
*/
void DisjointSets::addelements(int num)
{
    for (int i = 0; i < num; i++)
    {
        set.push_back(-1);//add num unconnected root nodes at the end of the vector
    }
}

/*
    * This function is used to find the root of the up-tree in which the parameter element resides.
    * It uses path compression to flatten the structure of the up-tree.
*/
int DisjointSets::find(int elem)
{
    if (set[elem] < 0)
        return elem;//if the parameter element is the root of the up-tree,return the element
    else
    {
        int root = find(set[elem]);//find the root of the up-tree in which the parameter element resides.
        set[elem] = root;
        return root;
    }
}

/*
    * This function is used to combine two disjoint sets into a single set.
    * It uses union by size to merge the two sets.
*/
void DisjointSets::setunion(int a, int b)
{
    int rootA = find(a);//find the root of the up-tree in which the parameter element resides.
    int rootB = find(b);//find the root of the up-tree in which the parameter element resides.
    int newSize = set[rootA] + set[rootB];//calculate the new size of the up-tree
    if (set[rootA] <= set[rootB])
    {//if the size of the up-tree containing a is smaller than the size of the up-tree containing b
        set[rootB] = rootA;//set the root of the up-tree containing b to be the root of the up-tree containing a
        set[rootA] = newSize;}//set the size of the up-tree containing a to be the new size
    else
    {
        set[rootA] = rootB;//set the root of the up-tree containing a to be the root of the up-tree containing b
        set[rootB] = newSize;//set the size of the up-tree containing b to be the new size
    }
}

/*
    * This function is used to return the number of nodes in the up-tree containing the parameter element.
*/
int DisjointSets::size(int elem)
{
    return -set[find(elem)];//return the size of the up-tree
}




