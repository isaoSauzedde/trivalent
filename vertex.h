#ifndef VERTEX_H_DECLARE
#define VERTEX_H_DECLARE

class Edge;

class Vertex{
  friend class Edge;
  friend class Trivalent;

protected:
  Edge* edges[3];
  int valence;
  int label;
public:
  Vertex();
  Vertex(int k);
  Vertex(Edge *e);
  ~Vertex();

  bool ajout_exterior(int *label_edge);
  bool ajout_interior(int *label_edge);
  Edge*  link(Vertex *v, int *label_edge); //augmente *label_edge, APRES avoir mis un label
};

#endif






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
