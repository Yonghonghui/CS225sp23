/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

//this function is used to compare two points in the same dimension
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
      return true;
    }else if(first[curDim] > second[curDim]){
      return false;
    }else{
      return first < second;
    }
    return false;
}
//this function is used to compare the distance between the target and 
//the current best point and the distance between the target and the potential point
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curDistSqr = 0;
    double possDistSqr = 0;
    for(int i=0; i<Dim; i++){
      curDistSqr = curDistSqr + (currentBest[i] - target[i])*(currentBest[i] - target[i]);
      possDistSqr = possDistSqr + (potential[i] - target[i])*(potential[i] - target[i]);
    }
    if(curDistSqr < possDistSqr){
      return false;
    }else if(curDistSqr > possDistSqr){
      return true;
    }else{
      return (potential < currentBest);
    }
    return false;
}
//this is the KDtree constructor
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> sortedPoints(newPoints.size());
    sortedPoints = newPoints;
    sortedPoints = _KDTree(sortedPoints, 0);
    // KDTreeNode* firstNode = new KDTreeNode;
    // firstNode->point = sortedPoints[(sortedPoints.size()+1)/2-1];
    // root = firstNode;
    root = _buildTree(sortedPoints, 0, sortedPoints.size()-1);
    size = newPoints.size();
    sortedPoints.clear();
}
//this function is the KDtree copy constructor
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  this->root = _copy(other.root);
  this->size = other.size;
}
//this function implements the operartor= for KDtree
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this->root != rhs.root){
    _delete(this->root);
  }
  this->root = _copy(rhs.root);
  this->size = rhs.size;
  return *this;
}
//this function is the KDtree destructor
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _delete(root);
}

//this function is used to find the nearest neighbor of the target point,
  //and return the nearest neighbor
  //the algorithm is to compare the target point with the current node
  //if the target point is smaller than the current node, then go to the left subtree
  //if the target point is larger than the current node, then go to the right subtree
  //if the target point is equal to the current node, then return the current node
  //if the target point is not equal to the current node, then compare the distance between the target point and the current node
  //and the distance between the target point and the current best point
  //if the distance between the target point and the current node is smaller than the distance between the target point and the current best point
  //then go to the other subtree
  //if the distance between the target point and the current node is larger than the distance between the target point and the current best point
  //then return the current best point
  //if the distance between the target point and the current node is equal to the distance between the target point and the current best point 
  //then compare the current node and the current best point
  //if the current node is smaller than the current best point, then go to the other subtree 
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    // Point<Dim> temp;
    // temp = query;
    KDTreeNode* result;
    result = _findNearestNeighbor(query, root, 0);

    return result->point;
}
//this function is a KDtree constructor helper function by using recursion
//the algorithm is to sort the points in the same dimension
//then find the median point
//then sort the points in the subregion 1 and subregion 2
//then recursively call the function to sort the points in the subregion 1 and subregion 2
//then return the sorted points
template <int Dim>
vector<Point<Dim>> KDTree<Dim>::_KDTree(vector<Point<Dim>>& points, int dim){
  if(points.size() <= 1){         // no need to sort
    return points;
  }
  points = _fastSort(points, dim);
  dim = (dim+1) % Dim;

  if((points.size()+1)/2-1 > 0){
    vector<Point<Dim>> L1((points.size()+1)/2-1);         // sort subregion 1
    vector<Point<Dim>> L1A((points.size()+1)/2-1);
    for(unsigned i=0; i<(points.size()+1)/2-1; i++){
      L1[i] = points[i];
    }
    L1A = _KDTree(L1, dim);
    for(unsigned j=0; j<(points.size()+1)/2-1; j++){
      points[j] = L1A[j];
    }
    L1.clear();
    L1A.clear();
  }
  
  if(points.size()/2 > 0){
    vector<Point<Dim>> L2(points.size()/2);         // sort subregion 2
    vector<Point<Dim>> L2A(points.size()/2);
    for(unsigned i=0; i<points.size()/2; i++){
      L2[i] = points[(points.size()+1)/2+i];
    }
    L2A = _KDTree(L2, dim);
    for(unsigned j=0; j<points.size()/2; j++){
      points[(points.size()+1)/2+j] = L2A[j];
    }
    L2.clear();
    L2A.clear();
  }
  
  return points;
}
//this function is a fastsort function used to sort the points in the same dimension by using recursion
template <int Dim>
vector<Point<Dim>> KDTree<Dim>::_fastSort(vector<Point<Dim>>& points, int dim){
  if(points.size() <= 1){         // no need to sort
    return points;
  }
  unsigned Lptr = 0;        // sort itself
  unsigned Rptr = points.size() - 1;
  Point<Dim> val = points[Lptr];
  int flag=0;           // left is empty
  while(Lptr != Rptr){      
    if(flag == 0){          // if left is empty then need to search from right 
      if(points[Rptr][dim] < val[dim]){
        points[Lptr] = points[Rptr];
        Lptr++;
        flag = 1;           // right is empty
      }else if(points[Rptr][dim] > val[dim]){
        Rptr--;
      }else{
        if(points[Rptr] < val){
          points[Lptr] = points[Rptr];
          Lptr++;
          flag = 1;         // right is empty
        }else{
          Rptr--;
        }
      }
    }else{                  // if right is empty then need to search from left 
      if(points[Lptr][dim] > val[dim]){
        points[Rptr] = points[Lptr];
        Rptr--;
        flag = 0;           // left is empty
      }else if(points[Lptr][dim] < val[dim]){
        Lptr++;
      }else{
        if(val < points[Lptr]){
          points[Rptr] = points[Lptr];
          Rptr--;
          flag = 0;           // left is empty
        }else{
          Lptr++;
        }
      }
    }
  }
  points[Lptr] = val;

  if(Lptr != 0){
    vector<Point<Dim>> leftVec(Lptr);         // sort left
    vector<Point<Dim>> leftVec2(Lptr);
    for(unsigned i=0; i<Lptr; i++){
      leftVec[i] = points[i];
    }
    leftVec2 = _fastSort(leftVec, dim);
    for(unsigned j=0; j<Lptr; j++){
      points[j] = leftVec[j];
    }
    leftVec.clear();
    leftVec2.clear();
  }
  
  if(Lptr != points.size()-1){
    vector<Point<Dim>> rightVec(points.size()-Lptr-1);         // sort right
    vector<Point<Dim>> rightVec2(points.size()-Lptr-1);
    for(unsigned i=0; i<points.size()-Lptr-1; i++){
      rightVec[i] = points[Lptr+1+i];
    }
    rightVec2 = _fastSort(rightVec, dim);
    for(unsigned j=0; j<points.size()-Lptr-1; j++){
      points[Lptr+1+j] = rightVec[j];
    }
    rightVec.clear();
    rightVec2.clear();
  }
  
  return points;
}
//this function a also a KDtree constructor helper function by using the sorted arry to 
//build the KDtree
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_buildTree(const vector<Point<Dim>>& points, int start, int end){
  if(points.size() <= 0 || end-start < 0){           // no nodes to build
    return NULL;
  }
  if(start == end){           // only one node in a subregion
    KDTreeNode* firstNode = new KDTreeNode;
    firstNode->point = points[start];
    return firstNode;
  }
  // if(end - start == 1){             // only two nodes in a subregion
  //   KDTreeNode* firstNode = new KDTreeNode;
  //   firstNode->point = points[start];
  //   KDTreeNode* secondNode = new KDTreeNode;
  //   secondNode->point = points[end];
  //   return;
  // }
  KDTreeNode* midNode = new KDTreeNode;
  midNode->point = points[(start+end)/2];
  midNode->left = _buildTree(points, start, (start+end)/2-1);
  midNode->right = _buildTree(points, (start+end)/2+1, end);
  return midNode;
}
//this function is a helper function to find the nearest neighbor of a target point
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_findNearestNeighbor(const Point<Dim>& target, KDTreeNode* curr, int dim) const{
  if(curr == NULL){            // stop condition, after leaf node
    return NULL;
  }
  KDTreeNode* best;
  if(curr->point[dim] > target[dim]){
    best = _findNearestNeighbor(target, curr->left, (dim+1)%Dim);
  }else if(curr->point[dim] < target[dim]){
    best = _findNearestNeighbor(target, curr->right, (dim+1)%Dim);
  }else{
    if(curr->point < target){
      best = _findNearestNeighbor(target, curr->right, (dim+1)%Dim);
    }else{
      best = _findNearestNeighbor(target, curr->left, (dim+1)%Dim);
    }
  }
  if(best == NULL){         // leaf node
    return curr;
  }
  if(shouldReplace(target, best->point, curr->point)){
    best = curr;
  }

  Point<Dim> Try = curr->point;
  for(int i=0; i<Dim; i++){
    if(i == dim){
      continue;
    }else{
      Try[i] = target[i];
    }
  }
  if(shouldReplace(target, best->point, Try)){           // another subtree should be checked
    KDTreeNode* temp;
    if(curr->point[dim] > target[dim]){
      temp = _findNearestNeighbor(target, curr->right, (dim+1)%Dim);
    }else if(curr->point[dim] < target[dim]){
      temp = _findNearestNeighbor(target, curr->left, (dim+1)%Dim);
    }else{
      if(curr->point < target){
        temp = _findNearestNeighbor(target, curr->left, (dim+1)%Dim);
      }else{
        temp = _findNearestNeighbor(target, curr->right, (dim+1)%Dim);
      }
    }
    if(temp == NULL){         // leaf node
      return curr;
    }
    if(shouldReplace(target, best->point, temp->point)){
      best = temp;
    }
  }
  return best;
}
//this is the copy constructor helper function
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(KDTreeNode* curr){
  if(curr == NULL){         // invalid node
    return NULL;
  }
  KDTreeNode* temp = new KDTreeNode;
  temp->point = curr->point;
  if(curr->left == NULL && curr->right == NULL){
    temp->left = NULL;
    temp->right = NULL;
    return temp;
  }
  if(curr->left != NULL){
    temp->left = _copy(curr->left);
  }
  if(curr->right != NULL){
    temp->right = _copy(curr->right);
  }
  return temp;
}
//this is the destructor helper function
template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode* curr){
  if(curr == NULL){         // invalid curr
    return;
  }
  if(curr->left == NULL && curr->right == NULL){        // stop condition, leaf node
    delete(curr);
    curr = NULL;
    return;
  }
  if(curr->left != NULL){
    _delete(curr->left);
  }
  if(curr->right != NULL){
    _delete(curr->right);
  }
  delete(curr);
  curr = NULL;
  return;
}