
#include <Eigen/SparseCholesky>
#include <vector>


void Trivalent::cholesky(Trivalent *T) {
  int n=T->_E.size();
  typedef Eigen::SparseMatrix<int> SpMat;
  typedef Eigen::Triplet<int> Trip;
  std::vector<Trip> tripletList;
  tripletList.reserve(5*n);
  for (int i = 0; i < n; i++){
    for (int l = 0; l < 3; l++){
      Edge *e1=&T->_E[i];
      Edge *e2=&(e1->front->edges[l]);
      tripletList.push_back(Trip(e1->label,e2->label,e1.touches(e2));
      e2=&(e1->back->edges[l]);
      if (e1!=e2){ //sinon on a déjà compté 2...
        tripletList.push_back(Trip(e1->label,e2->label,e1.touches(e2));
      };
    };
  };

  SpMat M(n,n);
  M.setFromTriplets(tripletList.begin(), tripletList.end());
  Eigen::SimplicialCholesky<SpMat> chol(M);

  return;
}
