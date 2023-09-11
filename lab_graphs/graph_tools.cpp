/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    for(auto it = vertices.begin(); it != vertices.end(); it++){
      graph.setVertexLabel(*it, "UNEXPLORED");
    }
    vector<Edge> edges = graph.getEdges();
    for(auto it = edges.begin(); it != edges.end(); it++){
      graph.setEdgeLabel(it->source, it->dest, "UNEXPLORED");
    }
    queue<Vertex> q;
    Vertex start = graph.getStartingVertex();
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Vertex end;
    Vertex curr;
    int min = 100000;
    while(!q.empty()){
      curr = q.front();
      q.pop();
      vector<Vertex> adj = graph.getAdjacent(curr);
      for(auto it = adj.begin(); it != adj.end(); it++){
        if(graph.getVertexLabel(*it) == "UNEXPLORED"){
            graph.setVertexLabel(*it, "VISITED");
            q.push(*it);
            graph.setEdgeLabel(curr, *it, "DISCOVERY");
            Edge e = graph.getEdge(curr, *it);
            if(e.weight < min){
              min = e.weight;
              start = curr;
              end = *it;
            }
        }
        else if(graph.getEdgeLabel(curr, *it) == "UNEXPLORED"){
          graph.setEdgeLabel(curr, *it, "CROSS");
          Edge e = graph.getEdge(curr, *it);
            if(e.weight < min){
              min = e.weight;
              start = curr;
              end = *it;
            }
        }
      }
    }
    graph.setEdgeLabel(start, end, "MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    queue<Vertex> q;
    q.push(start);
    unordered_map<Vertex, Vertex> parent;
    unordered_map<Vertex, int> dist;
    unordered_map<Vertex,bool> visited;
    vector <Vertex> vertices = graph.getVertices();
    for(auto it = vertices.begin(); it != vertices.end(); it++){
      parent[*it] = *it;
      dist[*it] = 100000;
      visited[*it] = false;
    }
    dist[start] = 0;
    visited[start] = true;
    while(!q.empty()){
        Vertex curr = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(curr);
        for(auto it = adj.begin(); it != adj.end(); it++){
          if(!visited[*it]){
            visited[*it] = true;
            dist[*it] = dist[curr] + 1;
            parent[*it] = curr;
            q.push(*it);
          }
          else if(dist[*it] > dist[curr] + 1){
            dist[*it] = dist[curr] + 1;
            parent[*it] = curr;
          }
        }
    }
    int count = 0;
    while(parent[end] != end){
      graph.setEdgeLabel(end, parent[end], "MINPATH");
      end = parent[end];
      count++;
    }
    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());//sort edges by weight from smallest to largest
    DisjointSets dsets;
    vector<Vertex> vertices = graph.getVertices();
    for(auto it = vertices.begin(); it != vertices.end(); it++){
      dsets.addelements(*it);//add all vertices to the disjoint set
    }
    for(auto it = edges.begin(); it != edges.end(); it++){
      if(dsets.find(it->source) != dsets.find(it->dest)){//if the source and dest are not in the same set
        dsets.setunion(it->source, it->dest);
        graph.setEdgeLabel(it->source, it->dest, "MST");
      }
    }
}

