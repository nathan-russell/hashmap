// [[Rcpp::depends(BH)]]
#include "../inst/include/hashmap/HashMap.hpp"

using namespace Rcpp;
using namespace hashmap;

RCPP_EXPOSED_CLASS(Hashmap)

RCPP_MODULE(hashmap_module) {
    class_<HashMap>("Hashmap")

    .constructor<SEXP, SEXP>()

    .method("size", &HashMap::size)
    .method("empty", &HashMap::empty)
    .method("clear", &HashMap::clear)
    .method("bucket_count", &HashMap::bucket_count)

    .method("hash_value", &HashMap::hash_value)

    .method("set_values", &HashMap::set_values)
    .method("[[<-", &HashMap::set_values)

    .method("erase", &HashMap::erase)

    .method("find_values", &HashMap::find_values)
    .method("[[", &HashMap::find_values)

    .method("has_key", &HashMap::has_key)

    .method("all_keys", &HashMap::all_keys)
    .method("all_values", &HashMap::all_values)
    .method("data", &HashMap::data)

    .method("rehash", &HashMap::rehash)

    ;
}
