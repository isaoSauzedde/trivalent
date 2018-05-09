
#ifndef TRIVALENT_H
#define TRIVALENT_H

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include "vertex.h"


class Edge {
  friend class Vertex;
protected:
  Vertex * front;
  Vertex * back;

public:
  Edge(){
    this->front= new Vertex(this);
    this->back= new Vertex(this);
  };


  ~Edge(){} //doesn't destruct adjacent vertices

};





using namespace std;


class Trivalent {
protected:
    std::vector<Vertex *> _V;
    std::vector<Edge *> _E;
public:

    Trivalent(){};

    Trivalent(int k){
      for (int j=0; j<k;j++){
        Vertex * p=new Vertex(j);
        this->_V.push_back(p);
      }
    };

    void addVertex(Vertex *s) { _V.push_back(s); }

    void addEdge(Edge *e) { _E.push_back(e); }

    bool link(int i,int j){
      Edge* e=this->_V[i]->link(this->_V[j]);
      bool b=(e==NULL);
      if (!b){this->_E.push_back(e);};
      return b;
    }

    std::vector<Vertex *> getVertices() { return _V; };
    std::vector<Edge *> getEdges() { return _E; };


  /*  void deleteEdge(Edge *e)
    std::vector<int>::iterator it;
    for (int i=0, i< this->_E.size(),i++){if (*e=*(this->_E[i])){}}
    it = find (this->_E.begin(), this->_E.end(), e); //attention: il ne faut pas chercher le pointeur, mais le contenu...
*/



    ~Trivalent() {
      for (std::vector<Vertex *>::iterator it = _V.begin(); it != _V.end(); it++){
        if (*it!=NULL){
          delete *it;
          *it=NULL;
        };
      };
      for (std::vector<Edge *>::iterator it = _E.begin(); it != _E.end(); it++){
        if (*it!=NULL){
          delete *it;
          *it=NULL;
        };
      };
    }


    static Trivalent *generate(int k) //genere un graphe trivalent à 2k sommets, puis remplis une matrice de covariances
    {
      srand(time(NULL));
      Trivalent *T= new Trivalent(2*k);
      std::cout << "T created" << '\n';
      for (int i= 0; i <(2*k-3); i++){ //on rajoute des aretes sur le sommet i jusqu'à ce qu'il en ait 3. On construit d'abord un graph sur les 2k-2 premiers sommets
        std::cout << "we look at the vertex number " << i << '\n';
        int val=(T->_V)[i]->valence;
        while( val<3){
          std::cout << "valence" <<val << '\n';
          bool b=true;
          int p=rand()%(2*k-2); //on va essayer de connecter i et p
          int count=0; //securité: si le graphe est "déjà plein" par erreur, on s'arrete quand meme après trop de tours de boucle
          while(b){
            if (p==i){p++;};
            count++;
            b=T->link(i,p);
            //ajouter au graphe maintenant
            if(p!=2*k-3){ //si on a pas réussi à attacher p et i, on essaye le suivant
              p++;
            }
            else{
              p=0;
            }
            try{
              if(count> 2*k+4){ //grossierman
                b=false;
                throw string("plus de sommets libres...");
              }
            }
            catch(string const& chaine){
              cerr << chaine << endl;
            };
          };
          val++;
        };
      };
//here we deal with the last vertex v, which may be of valence 1. In this case, we modify it as follow: v is attached to v2 by e, which is attached to a third vertex v3 by e2. We delete e and e2, and we add two edges from v to v2 and one from v to v3 instead
//on complete les trois derniers sommets pour qu'ils soient tous trivalent
      try{
        if ((T->_V)[(2*k-3)]->valence==3){ //on rajoute un "theta"
          int b2=T->link(2*k-2,2*k-1);
          b2=T->link(2*k-2,2*k-1);
          b2=T->link(2*k-2,2*k-1);
        }else if((T->_V)[(2*k-3)]->valence==1){
          int b2=T->link(2*k-3,2*k-2);
          b2=T->link(2*k-3,2*k-1);
          b2=T->link(2*k-2,2*k-1);
          b2=T->link(2*k-2,2*k-1);
        }else{
          throw string("probleme de valence... is %d\n", (T->_V)[(2*k-3)]->valence);
        };
      }
      catch(string const& chaine){
        cerr << chaine << endl;
      };
      return T;
    };

  /*  print(){
      for (int i=0; i<this.size(); i++){


      }

    }
*/


};

















#endif
