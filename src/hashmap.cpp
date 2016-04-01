// [[Rcpp::depends(BH)]]
#include "../inst/include/hashmap/HashMap.hpp"

using namespace Rcpp;
using namespace hashmap;

RCPP_MODULE(hashmap_module) {
    class_<HashMap>("hashmap")

    .constructor<SEXP, SEXP>()

    .method("size", &HashMap::size)
    .method("empty", &HashMap::empty)
    .method("clear", &HashMap::clear)

    .method("set_values", &HashMap::set_values)
    .method("[[<-", &HashMap::set_values)

    .method("find_values", &HashMap::find_values)
    .method("[[", &HashMap::find_values)

    .method("all_keys", &HashMap::all_keys)
    .method("all_values", &HashMap::all_values)
    .method("data", &HashMap::data)

    .method("rehash", &HashMap::rehash)

    ;
}
