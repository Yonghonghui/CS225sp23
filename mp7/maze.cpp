/* Your code here! */
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"
/*
    * This function is default constructor for SquareMaze class,which 
    * creates an empty maze.
*/
SquareMaze::SquareMaze()
{
    width_ = 0;
    height_ = 0;
    maze_.clear();
    solution_.clear();
}

/*
    * This function is default destructor for SquareMaze class.
*/
SquareMaze::~SquareMaze()
{
    width_ = 0;
    height_ = 0;
    maze_.clear();
    solution_.clear();
}

/*
    * This function is copy constructor for SquareMaze class.
*/
SquareMaze::SquareMaze(const SquareMaze & other)
{
    width_ = other.width_;
    height_ = other.height_;
    maze_ = other.maze_;
    solution_ = other.solution_;
}

/*
    * This function is used to make a new SquareMaze of the given height and width.
    * It uses disjoint sets to create the maze.
*/
void SquareMaze::makeMaze(int width, int height)
{
    width_ = width;
    height_ = height;
    int size = width * height;
    DisjointSets set;
    set.addelements(size);
    for (int i = 0; i < size; i++)
    {
        maze_.push_back(3);
        //11 represents the right and down walls are present,
        //01 represents the right wall is present,
        //10 represents the down wall is present,
        //00 represents no wall is present
    }
    while (set.size(0) != size)//while the maze is not fully connected
    {
        int x = rand() % width;//randomly choose a cell
        int y = rand() % height;
        int dir = rand() % 2;//randomly choose a direction rand()%2=0 or 1
        if (dir == 0)        //if direction is right
        {
            if (x != width - 1) //if its hasn't reached the rightest bound of the maze
            {
                if (set.find(y * width + x) != set.find(y * width + x + 1))
                {
                    set.setunion(y * width + x, y * width + x + 1); //union the two cells
                    setWall(x, y, dir, false); //remove the right wall at (X,Y)
                }
            }
        }
        else //if direction is down
        {
            if (y != height - 1)//if its hasn't reached the lowest bound of the maze
            {
                if (set.find(y * width + x) != set.find((y + 1) * width + x)) 
                {
                    set.setunion(y * width + x, (y + 1) * width + x);//union the two cells
                    setWall(x, y, dir, false);//remove the bottom wall at (X,Y)
                }
            }
        }
    }
}

/*
    * This function is used to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
    * It returns true if you can travel in the specified direction and false otherwise.
*/
bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (dir == 0) //if direction is right
    {
        if (x == width_ - 1) //if its at the rightest bound of the maze
            return false;
        else
        {
            if (maze_[y * width_ + x] & 1) //if the right wall is present
                return false;  //we can't travel to the right cell
            else
                return true;
        }
    }
    else if (dir == 1) //if direction is down
    {
        if (y == height_ - 1) //if its at the lowest bound of the maze
            return false;
        else
        {
            if (maze_[y * width_ + x] & 2) //if the bottom wall is present
                return false;
            else
                return true;
        }
    }
    else if (dir == 2) //if direction is left
    {
        if (x == 0) //if its at the leftest bound of the maze
            return false;
        else
        {
            if (maze_[y * width_ + x - 1] & 1) //if the right wall of the left cell is present
                return false;
            else
                return true;
        }
    }
    else //if direction is up
    {
        if (y == 0) //if its at the upper bound of the maze
            return false;
        else
        {
            if (maze_[(y - 1) * width_ + x] & 2) //if the bottom wall of the upper cell is present
                return false;
            else
                return true;
        }
    }
}

/*
    * This function is used to set whether or not the specified wall exists.
    * This function should be fast (constant time).
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if (dir == 0) //if direction is right
    {
        if (exists) //if the wall exists
            maze_[y * width_ + x] = maze_[y * width_ + x] | 1; //set the right wall to 1
        else
            maze_[y * width_ + x] = maze_[y * width_ + x] & 2; //set the right wall to 0
    }
    else //if direction is down
    {
        if (exists) //if the wall exists
            maze_[y * width_ + x] = maze_[y * width_ + x] | 2; //set the bottom wall to 1
        else
            maze_[y * width_ + x] = maze_[y * width_ + x] & 1; //set the bottom wall to 0
    }
}

/*
    * This function is used to solve this SquareMaze.
    * It modifies the internal state of this SquareMaze object so that the solveMaze and drawMaze functions will produce a solution.
    * This function should run in time proportional to the number of cells in the maze.
*/
vector<int> SquareMaze::solveMaze(){
    solution_.clear();
    vector<int> distance;
    vector<int> prev;
    vector<bool> visited;
    //using BFS to find the longest path from the source to the destination
    for (int i = 0; i < width_ * height_; i++)
    {
        //initialize the total distance, prev cell and visited cells vectors
        distance.push_back(0);
        prev.push_back(-1);
        visited.push_back(false);
    }
    queue<int> q;//create a queue to store the cells
    q.push(0);//push the source cell into the queue
    visited[0] = true;//mark the source cell as visited
    while(!q.empty()){
    int i= q.front();//while the queue is not empty, pop the front cell
    q.pop();
    int x = i % width_;
    int y = i / width_;
    if(canTravel(x,y,0) && !visited[i+1]){ //if we can travel to the right cell
            q.push(i+1);
            visited[i+1] = true;
            distance[i+1]=distance[i]+1;
            prev[i+1] = i;
        }
    if(canTravel(x,y,1) && !visited[i+width_]){ //if we can travel to the bottom cell
            q.push(i+width_);
            visited[i+width_] = true;
            distance[i+width_]=distance[i]+1;
            prev[i+width_] = i;
        }
    if(canTravel(x,y,2) && !visited[i-1]){ //if we can travel to the left cell
            q.push(i-1);
            visited[i-1] = true;
            distance[i-1]=distance[i]+1;
            prev[i-1] = i;

        }
    if(canTravel(x,y,3) && !visited[i-width_]){ //if we can travel to the upper cell
            q.push(i-width_);
            visited[i-width_] = true;
            distance[i-width_]=distance[i]+1;
            prev[i-width_] = i;
        }
    } 
    //find the cell with the longest distance
    int max = 0;
    int max_index = 0;
    for(int i = 0; i < width_; i++){ //find the cell with the longest distance
        if(distance[(height_-1)*width_+i] > max){ 
            //if the distance of the cell is greater than the max distance
            max = distance[(height_-1)*width_+i];
            //set the max distance to the distance of the cell
            max_index = (height_-1)*width_+i;
            //set the max index to the index of the cell
        }
    }
    //using the prev vector to find the solution
    int index = max_index;
    while(index != 0){ //while the index is not the source cell
        int prev_index = prev[index];
        if(prev_index == index - 1){ //if the previous cell is the left cell
            solution_.push_back(0); //push 0 into the solution vector
        }
        else if(prev_index == index + 1){ //if the previous cell is the right cell
            solution_.push_back(2); //push 2 into the solution vector
        }
        else if(prev_index == index - width_){ //if the previous cell is the upper cell
            solution_.push_back(1); //push 1 into the solution vector
        }
        else if(prev_index == index + width_){ //if the previous cell is the bottom cell
            solution_.push_back(3); //push 3 into the solution vector
        }
        index = prev_index; //set the index to the previous index
    }
    reverse(solution_.begin(), solution_.end()); //reverse the solution vector
    return solution_;
}

/*
    * This function is used to draw the maze without the solution.
    * It indicates whether each cell is visited, and whether each wall is present.
    * drawMaze calls drawMazeWithSolution, so your code should not call drawMazeWithSolution directly.
    * This function should run in time proportional to width height (linear time).
*/
cs225::PNG * SquareMaze::drawMaze() const{
    cs225::PNG * maze = new cs225::PNG(width_*10+1, height_*10+1);//create a new PNG
    //set the color of the upper bound wall to black
    for(int i = 10; i < width_*10+1; i++){
        cs225::HSLAPixel * pixel = maze->getPixel(i,0);
        pixel->l = 0;
    }
    //set the color of the left bound wall to black
    for(int i = 0; i < height_*10+1; i++){
        cs225::HSLAPixel * pixel = maze->getPixel(0,i);
        pixel->l = 0;
    }
    //set the color of the other walls to black
    for(int i=0;i<width_*height_;i++){
        int x = i % width_;
        int y = i / width_;
        if(!(canTravel(x,y,0))){ //if the right wall exists
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel((x+1)*10,y*10+j);
                pixel->l = 0;
            }
        }
        if(!(canTravel(x,y,1))){ //if the bottom wall exists
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel(x*10+j,(y+1)*10);
                pixel->l = 0;
            }
        }
    }
    return maze;
}

/*
    * This function is used to draw the maze with the solution vector.
    * It modifies the PNG from drawMaze, and indicates the solution by changing the color of the pixels in the solution vector.
    * This function should run in time proportional to the length of the solution vector.
*/
cs225::PNG * SquareMaze::drawMazeWithSolution(){
    cs225::PNG* maze = drawMaze(); //draw the maze without the solution
    vector<int> solution = solveMaze(); //get the solution vector
    int x = 5; //set the starting point to (5,5)
    int y = 5;
    while(!solution.empty()){
        int i=solution.front(); //get the first element in the solution vector
        solution.erase(solution.begin()); //erase the first element in the solution vector
        if(i==0){ //if the first element is 0, move to the right
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel(x+j,y);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            x+=10;
        }
        else if(i==1){ //if the first element is 1, move to the bottom
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel(x,y+j);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            y+=10;
        }
        else if(i==2){ //if the first element is 2, move to the left
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel(x-j,y);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;
            }
            x-=10;
        }
        else if(i==3){ //if the first element is 3, move to the upper
            for(int j=0;j<=10;j++){
                cs225::HSLAPixel * pixel = maze->getPixel(x,y-j);
                pixel->h = 0;
                pixel->s = 1;
                pixel->l = 0.5;
                pixel->a = 1;   
            }
            y-=10;
        }
    }
    //set the color of the exit to white
    if(y==height_*10-5){
        for(int j=1;j<=9;j++){
            cs225::HSLAPixel * pixel = maze->getPixel(x-5+j,y+5);
            pixel->h = 0;
            pixel->s = 0;
            pixel->l = 1;
        }
    }
    return maze;
}