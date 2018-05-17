
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include "trivalent.h"
#include "vertex.h"


using namespace std;



void print_matrix(vector<vector<float> > L){ //matrice carré
  for(int i=0 ; i<L.size() ; i++){
      for(int j=0 ; j<L.size() ; j++){
        std::cout << std::setprecision(1) << L[i][j] << "     ";
      }
      std::cout << '\n';
  }
}


void print_matrix(vector<vector<int> > L){
  for(int i=0 ; i<L.size() ; i++){
      for(int j=0 ; j<L.size() ; j++){
          printf("%d   ",L[i][j]);
      }
        printf("\n");
  }
}











int main()
{
  int k;
  cin >> k;
  Trivalent *T= Trivalent::generate(k);
  char name[] = "/Users/admin/Desktop/singularCS/gauss_copie/test.dot";
  const char *ptr_name=name;
  Trivalent::draw(ptr_name,T);
  //char neato[]= "neato -Tjpg "+ name .....
  //system("cd /Users/admin/Desktop/singularCS/gauss_copie");
  //system("neato -Tjpg /Users/admin/Desktop/singularCS/gauss_copie/test.dot -o /Users/admin/Desktop/singularCS/gauss_copie/test.jpg");





  Trivalent::sparse_cholesky(T);

  //print_matrix(Trivalent::matrix(T));



  //vector<vector<float> > L=cholesky(M,3*k);

  //print_matrix(L,3*k);

  // (E1,E2)(k): les numeros deux arêtes connectées à la sortie de l'arête k
return 0;
//vector<vector<int> > Cov (E.size(),vector<int>(E.size(),0));
  //for( int i=0 ;i<E.size() ;i++) i
}
