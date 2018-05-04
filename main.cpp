
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <iomanip>

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



vector<vector<int> > generate(int k) //genere un graphe trivalent à 2k sommets, puis remplis une matrice de covariances
{
  srand(time(NULL));
  vector<int> E1 (3*k,0);
  vector<int> E2 (3*k,0);
  vector<bool> E3 (3*k,true); //"sommet gauche est univalent"
  vector<bool> E4 (3*k,true); //"sommet gauche est bivalent"
  int p=0;
  for(int i=0 ;i<3*k ;i++){ //on regarde la i eme arete
    bool b=true;
    p=rand()%(3*k);
    int count=0; //securité...
    while(b){
      if (p==i){p++;};
      count++;
      if (E3[p]){
        b=false;
        E1[i]=p;
        E3[p]=false;
      }
      else if  (E4[p]){
        b=false;
        E1[i]=p;
        E4[p]=false;
      }
      else if(p!=3*k-1){
        p++;
      }
      else{
        p=0;
      }

      try{
        if(count> 3*k+2){ //grossierman
          b=false;
          throw string("plus de sommets libres...");
        }
      }
      catch(string const& chaine){
        cerr << chaine << endl;
      };
    };
  }
  for(int i=0 ;i<3*k ;i++){ //on regarde la i eme arete
    bool b=true;
    p=rand()%(3*k);
    int count=0; //securité...
    while(b){
      if (p==i){p++;};
      count++;
      if (E3[p]){
        b=false;
        E2[i]=p;
        E3[p]=false;
      }
      else if  (E4[p]){
        b=false;
        E2[i]=p;
        E4[p]=false;
      }
      else if(p!=3*k-1){
        p++;
      }
      else{
        p=0;
      }

      try{
        if(count> 3*k+2){ //grossierman
          b=false;
          throw string("plus de sommets libres...");
        }
      }
      catch(string const& chaine){
        cerr << chaine << endl;
      };
    };
  }
  vector<vector<int> > M (3*k,vector<int>(3*k,0));
    for (int l = 0; l < 3*k; l++){
    M[l][l]=2;
    M[l][E1[l]]=-1;
    M[l][E2[l]]=-1;
    M[E1[l]][l]=-1;
    M[E2[l]][l]=-1;
  }
  print_matrix(M,3*k);
  return M;
}

int main()
{
  int k;
  cin >> k;
  vector<vector<int> > M= generate(k);

  vector<vector<float> > L=cholesky(M,3*k);

  print_matrix(L,3*k);

  // (E1,E2)(k): les numeros deux arêtes connectées à la sortie de l'arête k
return 0;
//vector<vector<int> > Cov (E.size(),vector<int>(E.size(),0));
  //for( int i=0 ;i<E.size() ;i++) i
}
