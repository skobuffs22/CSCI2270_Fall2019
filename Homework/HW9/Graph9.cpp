#include <iostream>
#include <vector>
#include <stack>
#include "Graph.hpp"

using namespace std;

void Graph::addEdge(string v1, string v2, int num){
  adjVertex* newEdge = new adjVertex;
  newEdge -> weight = num;
  int sz = vertices.size();
  for (int i = 0; i < sz; i++){
    if (vertices[i]-> name == v1){
      for (int j = 0; j < sz; j++){
        if (vertices[j] -> name == v2){
          newEdge -> v = vertices[j];
          vertices[i] -> adj.push_back(*newEdge);
          newEdge ->v = vertices[i];
          vertices[j] -> adj.push_back(*newEdge);
        }
      }
    }
  }
}

void Graph::addVertex(string name){
  vertex* newVertex = new vertex;
  newVertex -> name = name;
  vertices.push_back(newVertex);
}


void displayEdges();

void Graph::depthFirstTraversal(string sourceVertex){
  vertex* start = NULL;
  int sz = vertices.size();
  for (int i=0; i<sz; i++) {
        if (vertices[i]->name == sourceVertex) {
			start = vertices[i];
  	    }
  }
  if (start == NULL) return;
  queue<vertex*> q;
  start -> visited = true;
  start -> distance = 0;
  q.push(start);
  bool emty = q.empty();
  while (!emty){
    vertex* curr = q.front();
    q.pop();
    cout << curr -> name << " --> ";
  }
}

void DFT(vertex* curr){
  curr -> visited = true;
  int sz = curr -> adj.size();
  for (int i = 0; i < sz; i++){
    if (!curr -> adj[i].v -> visited){
      cout << curr -> adj[i].v -> name << " --> ";
      DFT(curr -> adj[i].v);
    }
  }
}
void Graph:: depthFirstTraversal(string sourceVertex){
  int sz = vertices.size();
  for (int i = 0; i< sz; i++){
    if (vertices[i] -> name == sourceVertex){
      cout << vertices[i] -> name << " --> ";
      DFT (vertices[i]);
      cout << "Done";
    }
  }
}


vertex* Graph::DijkstraAlgorithm(string start, string end){
    setAllVerticesUnvisited();
    vertex* startV = NULL;
    vertex* endV = NULL;
    vector<vertex*> solved;
    int sz = vertices.size();
    for (int i=0; i<sz; i++) {
      if (vertices[i]->name == start) {
        startV = vertices[i];
      }
    }
    for (int i=0; i<sz; i++) {
      if (vertices[i]->name == end) {
        endV = vertices[i];
      }
    }
    startV->visited = true;
  	startV->distance = 0;
    solved.push_back(startV);
    vertex* solvedV;
    int dist;
    while (!endV->visited){
        int minDistance = 10000000;
        solvedV = NULL;
        int sz1 = solved.size();
        for (int i = 0; i < sz1; i++){
            vertex* s = solved[i];
            int sz2 = s -> adj.size();
            for (int j = 0; j < sz2; j++){
                if (!s -> adj[j].v -> visited){
                  dist = s -> distance + s -> adj[j].weight;
                  if (dist < minDistance){
                    minDistance = dist;
                    solvedV = s->adj[j].v;
                    s -> adj[j].v -> pred = s;
                    solvedV -> pred = s;
                  }
                }
            }
        }
        solvedV -> distance = minDistance;
        solvedV -> visited = true;
        solved.push_back(solvedV);
    }
    endV -> distance = solvedV -> distance;
    return endV;
}

void shortestpath(string start, string end){
  vertex* endV = NULL;
  vertex*<string> arr;
  int sz = vertices.size();
  for (int i=0; i<sz; i++) {
    if (vertices[i]->name == end) {
      endV = vertices[i];
    }
  }
  arr.push_back(endV -> name);
  while (endV -> name != start) {
      arr.push_back(endV -> pred-> name);
      enddV = endV -> pred;
  }
  int sz1 = arr.size();
  for (int j=sz1; i> 0; j--) {
    cout << arr[j-1] << " ";
  }
}


void Graph::setAllVerticesUnvisited() {
  int i;
  for(i=0; i<vertices.size(); i++) {
    vertices[i]->visited = false;
  }
}
