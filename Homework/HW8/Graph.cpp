#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

void Graph::addEdge(string v1, string v2){
  adjVertex* newEdge = new adjVertex;
  for (int i = 0; i < vertices.size(); i++){
    if (vertices[i]-> name == v1){
      for (int j = 0; j < vertices.size(); j++){
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

void Graph::displayEdges(){
  int temp1 = vertices.size();
  for (int i = 0; i < temp1; i++){
    cout << vertices[i] -> name << " --> ";
    int temp2 = vertices[i]->adj.size();
    for (int j = 0; j < temp2; j++){
      cout << vertices[i]->adj[j].v -> name << " ";
    }
    cout << endl;
  }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex* start = NULL;
    int sz = vertices.size();
	for (int i=0; i<sz; i++) {
		if (vertices[i]->name == sourceVertex) {
			start = vertices[i];
		}
	}
	if (start == NULL) return;

	start->visited = true;
	start->distance = 0;
	queue<vertex*> q;
	q.push(start);
	cout <<"Starting vertex (root): ";
	cout << start -> name<< "-> ";
    int count = 0;
	while (!q.empty()) {
		vertex* curr = q.front(); // get access to first element
		q.pop(); // actually remove that element
		int sz2 = curr -> adj.size();
		for (int i=0; i<sz2; i++) {
			if (!(curr->adj[i].v)->visited) {
				(curr->adj[i].v)->distance = curr->distance + 1;
				(curr->adj[i].v)->visited = true;
				//(curr->adj[i].v)->parent = curr;
				q.push(curr->adj[i].v);
			}
		}
		if (count>0){
		    cout << curr->name << "(" << curr->distance << ") ";
        }
		curr->visited = true;
		count++;
	}
}

int Graph::getConnectedComponents() {
  int count = 0;
  int sz = vertices.size();
  for(int i = 0; i < sz; i++) {
      vertices[i]->visited = false;
  }
  for (int i = 0; i < sz; i++) {
    if (vertices[i] -> visited == false) {
      vertices[i] -> visited = true;
      queue <vertex*> newvert;
      newvert.push(vertices[i]);
      vertex *vert;
      while(!newvert.empty()) {
        vert = newvert.front();
        newvert.pop();
        int sz2 = vert -> adj.size();
        for(int j = 0; j < sz2; j++) {
          if (!vert -> adj[j].v -> visited) {
            vert -> adj[j].v -> distance = vert -> distance++;
            vert -> adj[j].v -> visited = true;
            newvert.push(vert->adj[j].v);
          }
        }
      }
      count++;
    }
  }
  return count;
}

void isRed(vertex* temp){
  temp->visited = true;
  temp->color = "green";
  temp->distance = temp->distance + 1;
}

void isGreen(vertex* temp){
  temp->visited = true;
  temp->color = "red";
  temp->distance = temp->distance + 1;
}

bool Graph::checkBipartite() {
  bool isBi = true;
  int sz = vertices.size();
  for (int i = 0; i < sz; i++) {
    vertices[i] -> visited = false;
  }
  for (int j = 0; j < sz; j++) {
    if (!vertices[j] -> visited) {
      vertices[j] -> visited = true;
      vertices[j] -> color = "red";
      queue<vertex*> newvert;
      newvert.push(vertices[j]);
      vertex *vert;
      while(!newvert.empty() && isBi) {
        vert = newvert.front();
        newvert.pop();
        int sz2 = vert -> adj.size();
        for(int k = 0; k < sz2; k++ ){
          if (vert -> color == "red") {
            if (vert -> adj[k].v -> color == "red") {
              isBi = false;
            }
            if (!vert -> adj[k].v -> visited) {
              vert -> adj[k].v->visited = true;
              vert -> adj[k].v->color = "green";
              vert -> adj[k].v->distance = vert->distance + 1;              newvert.push(vert -> adj[k].v);
              newvert.push(vert -> adj[k].v);
            }
          }
          if (vert -> color == "green") {
            if (vert -> adj[k].v -> color == "green") {
              isBi = false;
            }
            if (!vert->adj[k].v -> visited) {
              vert -> adj[k].v->visited = true;
              vert -> adj[k].v->color = "red";
              vert -> adj[k].v->distance = vert->distance + 1;
              newvert.push(vert -> adj[k].v);
            }
          }
        }
      }
    }
  }
  return isBi;
}
