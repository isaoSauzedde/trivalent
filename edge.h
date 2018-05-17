
#ifndef EDGE_H
#define EDGE_H


#include "vertex.h"

class Edge {
  friend class Vertex;
  friend class Trivalent;
protected:
  Vertex * front;
  Vertex * back;
  int label;//dans graph, commence à 0
public:
  Edge(){
    this->front= new Vertex(this);
    this->back= new Vertex(this);
    this->label=-1;
  };

    Edge(int k){
      this->front= new Vertex(this);
      this->back= new Vertex(this);
      this->label =k;
    };


  ~Edge(){} //doesn't destruct adjacent vertices

  int touches(Edge * e){ //2 if this=e; -1 if this->front=e->front or back/back; 1 if this->back=e->front or front/back; 0 else
    int Lik=0;
    if(this==e){
      Lik=2;
    }else if(this->front==e->front||this->back==e->back){
      Lik=-1;
    }else if(this->back==e->front||this->front==e->back){
      Lik=1;
    }
    return Lik;
  };
};


#endif
