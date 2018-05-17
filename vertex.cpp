
#ifndef VERTEX_H_DEFINE
#define VERTEX_H_DEFINE


#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <math.h>
#include <iomanip>

#include "vertex.h"
#include "edge.h"
#include "trivalent.h"




  Vertex::Vertex(){
    this->valence=0;
    this->label=-1;
    //*(this->edges)= malloc(3 * sizeof(Edge*));
    //this->edges= NULL;
  };
  Vertex::Vertex(int k){
    this->valence=0;
    this->label=k;
    //*(this->edges)= malloc(3 * sizeof(Edge*));
    //this->edges= NULL;
  };
  Vertex::Vertex(Edge *e) {
    this->valence=1;
    this->label=-1;
    //this->edges= new Edge[3];
    this->edges[0]= e;
  };


  Vertex::~Vertex(){
    if (*edges!=NULL)
    {delete[] *edges;};
    //delete[] edges;
  }
/*  bool ajout(edge* e){ //it has to be modified so that we now if e is attached inward or backward... (here e does not point to this)
    if (valence==3)
          {return false;}
    else
      {
        edges[valence]=e;
        valence++;
        return true;
      };
  };*/

  bool Vertex::ajout_exterior(int *label_edge){
    if (valence==3)
          {return false;}
    else
      {
        edges[valence]=new Edge(*label_edge);
        edges[valence]->back=this;
        valence++;
        return true;
      };
  };

  bool Vertex::ajout_interior(int *label_edge){
    if (valence==3)
          {return false;}
    else
      {
        edges[valence]=new Edge(*label_edge);
        edges[valence]->front=this;
        valence++;
        return true;
      };
  };

  Edge* Vertex::link(Vertex *v, int *label_edge){ //add an edge going from this to v., augmente label_edge
    if (v->valence==3){ //le sommet courant est plein
      return NULL;
    }else{
      if(this->ajout_exterior(label_edge) ) {
        //delete (&v->edges[v->valence]);
        v->edges[v->valence]=this->edges[this->valence -1]; //rheir was half an edge going from "this". It is now linked to v
        this->edges[this->valence -1]->front=v;
        v->valence++;
        (*label_edge)++;
//	std::cout << "edge number " << *label_edge <<"\n";

        return (this->edges[this->valence -1]);
      }else{ //le sommet v est plein
        return NULL;
      }
    }
  };



///////////////////////////end of "vertex"/////////////////////////////////////


#endif
