#include<RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
#include"RunCont.h"
#include"Utilities.h"

using namespace Rcpp;
using namespace arma;
//using namespace R;

// [[Rcpp::export()]]
arma::mat ContGrid(arma::mat const &xc, arma::mat const &xg, arma::vec const &y, arma::mat const &x2, arma::vec const &y2, arma::vec lamb1, arma::vec lamb2, arma::vec bc0, arma::vec bg0, double r, arma::mat const &a, int p, int pc, bool robust, char method)
{
  arma::vec btmp;
  arma::mat CVM(lamb1.n_elem, lamb2.n_elem, fill::zeros);
  
  for(unsigned int j=0; j<lamb2.n_elem ; j++){
    for(unsigned int i=0; i<lamb1.n_elem ; i++){
		Rcpp::checkUserInterrupt();
		if(robust){
			btmp = RunCont_robust(xc, xg, y, lamb1(i), lamb2(j), bc0, bg0, r, a, p, pc, method);
			CVM(i, j) = validation_LAD(x2, y2, btmp);
		}else{
			btmp = RunCont(xc, xg, y, lamb1(i), lamb2(j), bc0, bg0, r, a, p, pc, method);
			CVM(i, j) = validation_LS(x2, y2, btmp);
		}
    }
  }
  return CVM;
}
