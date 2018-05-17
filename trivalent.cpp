
#ifndef TRIVALENT_H_DEFINE
#define TRIVALENT_H_DEFINE


#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <Eigen/Sparse>

#include "vertex.h"
#include "edge.h"
#include "trivalent.h"



void Trivalent::draw (const char* filename, Trivalent *T){
	FILE *file = fopen(filename, "w");

	try{
	  if(file)
	  {
			fprintf(file, "graph G{\n node[label=\"\" shape=none width=0 height=0 margin=0];\n");
	    for (int i=0; i<T->_V.size(); i++){
	      fprintf(file, "%d\n",i);
	    }
	    for (int i=0; i<T->_E.size(); i++){
	      fprintf(file, "%d -- %d\n",T->_E[i]->back->label,T->_E[i]->front->label );
	    }
	    fprintf(file, "}\n");
	  }else{
				throw std::string("problème ouverture fichier");
			};
		}
	catch(std::string const& chaine){
		std::cerr << chaine << std::endl;
	};
	return;
}
void Trivalent::draw_directed (const char* filename, Trivalent *T){
	FILE *file = fopen(filename, "w");

	try{
	  if(file)
	  {
			fprintf(file, "digraph G{\n node[label=\"\" shape=none width=0 height=0 margin=0];\n");
	    for (int i=0; i<T->_V.size(); i++){
	      fprintf(file, "%d\n",i);
	    }
	    for (int i=0; i<T->_E.size(); i++){
	      fprintf(file, "%d -> %d\n",T->_E[i]->back->label,T->_E[i]->front->label );
	    }
	    fprintf(file, "}\n");
	  }else{
				throw std::string("problème ouverture fichier");
			};
		}
	catch(std::string const& chaine){
		std::cerr << chaine << std::endl;
	};
	fclose(file);
	return;
}


Trivalent::Trivalent(int k){
  for (int j=0; j<k;j++){
    Vertex * p=new Vertex(j);
    this->_V.push_back(p);
  }
};

void Trivalent::addVertex(Vertex *s) { _V.push_back(s); };

void Trivalent::addEdge(Edge *e) { _E.push_back(e); };

bool Trivalent::link(int i,int j, int *label_edge){
  Edge* e=this->_V[i]->link(this->_V[j], label_edge);
  bool b=(e==NULL);
  if (!b){this->_E.push_back(e);};
  return b;
};



  /*  void deleteEdge(Edge *e)
    std::vector<int>::iterator it;
    for (int i=0, i< this->_E.size(),i++){if (*e=*(this->_E[i])){}}
    it = find (this->_E.begin(), this->_E.end(), e); //attention: il ne faut pas chercher le pointeur, mais le contenu...
*/



Trivalent::~Trivalent() {
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


Trivalent *Trivalent::generate(int k){ //genere un graphe trivalent à 2k sommets, puis remplis une matrice de covariances
  srand(time(NULL));
	int unpoint_label_edge=0;
	int *label_edge=&unpoint_label_edge;
  Trivalent *T= new Trivalent(2*k); //graphe vide
  //std::cout << "T created" << '\n';
  for (int i= 0; i <(2*k-3); i++){ //on rajoute des aretes sur le sommet i jusqu'à ce qu'il en ait 3. On construit d'abord un graph sur les 2k-2 premiers sommets
    //std::cout << "we look at the vertex number " << i << '\n';
    int val=(T->_V)[i]->valence;
    while( val<3){
      //std::cout << "valence" <<val << '\n';
      bool b=true;
      int p=rand()%(2*k-2); //on va essayer de connecter i et p
      int count=0; //securité: si le graphe est "déjà plein" par erreur, on s'arrete quand meme après trop de tours de boucle
      while(b){
        if (p==i){p++;};
        count++;
        b=T->link(i,p,label_edge);

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
            throw std::string("plus de sommets libres...");
          }
        }
        catch(std::string const& chaine){
          std::cerr << chaine << std::endl;
        };
      };
      val++;
    };
  };
//here we deal with the last vertex v, which may be of valence 1. In this case, we modify it as follow: v is attached to v2 by e, which is attached to a third vertex v3 by e2. We delete e and e2, and we add two edges from v to v2 and one from v to v3 instead
//on complete les trois derniers sommets pour qu'ils soient tous trivalent
  try{
    if ((T->_V)[(2*k-3)]->valence==3){ //on rajoute un "theta"
      int b2=T->link(2*k-2,2*k-1,label_edge);
      b2=T->link(2*k-2,2*k-1,label_edge);
      b2=T->link(2*k-2,2*k-1,label_edge);
    }else if((T->_V)[(2*k-3)]->valence==1){
      int b2=T->link(2*k-3,2*k-2,label_edge);
      b2=T->link(2*k-3,2*k-1,label_edge);
      b2=T->link(2*k-2,2*k-1,label_edge);
      b2=T->link(2*k-2,2*k-1,label_edge);
    }else{
      throw std::string("probleme de valence... is %d\n", (T->_V)[(2*k-3)]->valence);
    };
  }
  catch(std::string const& chaine){
    std::cerr << chaine << std::endl;
  };
  return T;
};



std::vector<std::vector<float> > Trivalent::cholesky(Trivalent *T) { // the matrix element is 2 between l and l, -1 between l and l' if l and l' are connected fronty to a common vertex, 1 if l and l' are successive (l->front=l'->back for exemple), 0 else
	//have to be adapted for double/triple edges...
  int n=T->_E.size();
  std::vector<std::vector<float> > L (n,std::vector<float> (n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < (i+1); j++) {
      double s = 0;
      for (int k = 0; k < j; k++){
          s += L[i][k] * L[j][k];
      }
      if ( i == j ){
        L[i][j] =sqrt(2 - s);//2 parce que diagonale
      }
      else{
        L[i][j] =(1.0 / L[j][j] * (double)(T->_E[i]->touches(T->_E[j]) - s)); //Lij toujours inverse d'un entier
      }
    }
  return L;
}


std::vector<std::vector<int> > Trivalent::matrix(Trivalent *T) { // the matrix element is 2 between l and l, -1 between l and l' if l and l' are connected fronty to a common vertex, 1 if l and l' are successive (l->front=l'->back for exemple), 0 else
//have to be adapted for double/triple edges...
  int n=T->_E.size();
  std::vector<std::vector<int> > L (n,std::vector<int> (n, 0));

	  for (int i = 0; i < n; i++){
	    for (int l = 0; l < 3; l++){
	      Edge *e1=T->_E[i];
	      Edge *e2=(e1->front->edges[l]);
	      L[(e1->label)][e2->label]=e1->touches(e2);
	      e2=(e1->back->edges[l]);
	      if (e1!=e2){ //sinon on a déjà compté 2...
	      	L[(e1->label)][e2->label]=e1->touches(e2);
	      };
	    };
	  };
		return L;
};



void Trivalent::sparse_cholesky(Trivalent *T) {
  int n=T->_E.size();
  typedef Eigen::SparseMatrix<float> SpMat;
  typedef Eigen::Triplet<float> Trip;
  std::vector<Trip> tripletList;
  tripletList.reserve(5*n);

  for (int i = 0; i < n; i++){
    for (int l = 0; l < 3; l++){
      Edge *e1=T->_E[i];
      Edge *e2=(e1->front->edges[l]);
      tripletList.push_back(Trip(e1->label,e2->label,(float)e1->touches(e2))); //bon e1->label ca doit juste etre i mais ...
      e2=(e1->back->edges[l]);//il faut bien faire le "back" car il faut remplir la partie inférieure ET la partie supérieure de la matrice
      if (e1!=e2 && e1->front!=e2->back &&e1->front!=e2->front){ //si e1=e2 on a déjà compté 2, si arete multiple il faut juste compter 1
        tripletList.push_back(Trip(e1->label,e2->label,(float)e1->touches(e2)));
      };
    };
  };

  SpMat M(n,n);
  M.setFromTriplets(tripletList.begin(), tripletList.end());
	std::cout << M;
	Eigen::SimplicialLDLT<SpMat> solver(M);
//  Eigen::SimplicialLDLT<SpMat> A=solver.compute();
  Eigen::VectorXf diag=solver.vectorD();
	std::sort(diag.data(), diag.data()+diag.size());
	std::cout << diag.transpose() << "\n" << "\n";
  return;
}


#endif
