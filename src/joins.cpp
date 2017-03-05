// [[Rcpp::depends(BH)]]
#include "../inst/include/hashmap/HashMapClass.h"

//' Hashmap internal functions
//'
//' @title Hashmap internal functions
//'
//' @name internal-functions
//' @rdname internal-functions
//'
//' @aliases .left_outer_join_impl
//' @aliases .right_outer_join_impl
//' @aliases .inner_join_impl
//' @aliases .full_outer_join_impl
//'
//' @param x an external pointer to a \code{HashMap}
//' @param y an external pointer to a \code{HashMap}
//'
//' @details These functions are intended for internal use only; do not
//'   call them directly.

//' @rdname internal-functions
// [[Rcpp::export(".left_outer_join_impl")]]
Rcpp::DataFrame left_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x,
                                     const Rcpp::XPtr<hashmap::HashMap>& y)
{ return x->left_outer_join(y); }

//' @rdname internal-functions
// [[Rcpp::export(".right_outer_join_impl")]]
Rcpp::DataFrame right_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x,
                                      const Rcpp::XPtr<hashmap::HashMap>& y)
{ return x->right_outer_join(y); }

//' @rdname internal-functions
// [[Rcpp::export(".inner_join_impl")]]
Rcpp::DataFrame inner_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x,
                                const Rcpp::XPtr<hashmap::HashMap>& y)
{ return x->inner_join(y); }

//' @rdname internal-functions
// [[Rcpp::export(".full_outer_join_impl")]]
Rcpp::DataFrame full_outer_join_impl(const Rcpp::XPtr<hashmap::HashMap>& x,
                                     const Rcpp::XPtr<hashmap::HashMap>& y)
{ return x->full_outer_join(y); }
