
#ifndef TRIVALENT_H
#define TRIVALENT_H

#include <vector>
#include <cstdlib>
#include "vertex.h"
#include "edge.h"

class Trivalent {
protected:
    std::vector<Vertex *> _V;
    std::vector<Edge *> _E;
public:

    Trivalent(){};

    std::vector<Vertex *> getVertices() { return _V; };
    std::vector<Edge *> getEdges() { return _E; };

    Trivalent(int k);
    ~Trivalent();

    void addVertex(Vertex *s);

    void addEdge(Edge *e);

    bool link(int i,int j,int *label_edge);

    static void draw (const char* filename, Trivalent *T);
    static void draw_directed (const char* filename, Trivalent *T);

    static std::vector<std::vector<int> > matrix (const char* filename, Trivalent *T); // indexed by edges. diagonal components: 2. others:

    static Trivalent *generate(int k) ;

    static std::vector<std::vector<int> > matrix(Trivalent *T);
    static std::vector<std::vector<float> > cholesky(Trivalent *T);
    static void sparse_cholesky(Trivalent *T) ;

};


#endif
