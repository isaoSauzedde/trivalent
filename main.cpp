
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include "trivalent.h"
#include "vertex.h"


using namespace std;









void print_matrix(vector<vector<float> > L, int n){
  for(int i=0 ; i<n ; i++){
      for(int j=0 ; j<n ; j++){
        std::cout << std::setprecision(1) << L[i][j] << "     ";
      }
      std::cout << '\n';
  }
}
void print_matrix(vector<vector<int> > L, int n){
  for(int i=0 ; i<n ; i++){
      for(int j=0 ; j<n ; j++){
          printf("%d   ",L[i][j]);
      }
        printf("\n");
  }
}

vector<vector<float> > cholesky(vector<vector<int> > A, int n) {

  vector<vector<float> > L (n,vector<float>(n,0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < (i+1); j++) {
      double s = 0;
      for (int k = 0; k < j; k++){
        s += L[i][k] * L[j][k];
      }
      if ( i == j ){
        L[i][j] =sqrt(A[i][i] - s);
      }
      else{
        L[i][j] =(1.0 / L[j][j] * (A[i][j] - s));
      }
    }
  return L;
}


int main()
{
  int k;
  cin >> k;
  Trivalent *T= Trivalent::generate(k);

  //vector<vector<float> > L=cholesky(M,3*k);

  //print_matrix(L,3*k);

  // (E1,E2)(k): les numeros deux arêtes connectées à la sortie de l'arête k
return 0;
//vector<vector<int> > Cov (E.size(),vector<int>(E.size(),0));
  //for( int i=0 ;i<E.size() ;i++) i
}
