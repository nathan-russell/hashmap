// [[Rcpp::depends(BH)]]
#include "../inst/include/hashmap/HashMap.hpp"

using namespace Rcpp;
using namespace hashmap;

RCPP_MODULE(Hashmap) {
    class_<HashMap>("Hashmap")

    .constructor<SEXP, SEXP>()

    .method("size", &HashMap::size)
    .method("empty", &HashMap::empty)
    .method("clear", &HashMap::clear)
    .method("bucket_count", &HashMap::bucket_count)
    .method("rehash", &HashMap::rehash)

    .method("hash_value", &HashMap::hash_value)

    .method("insert", &HashMap::insert)
    .method("[[<-", &HashMap::insert)

    .method("erase", &HashMap::erase)

    .method("find", &HashMap::find)
    .method("[[", &HashMap::find)

    .method("has_key", &HashMap::has_key)
    .method("has_keys", &HashMap::has_keys)

    .method("keys", &HashMap::keys)
    .method("values", &HashMap::values)
    .method("data", &HashMap::data)

    .method("renew", &HashMap::renew)

    ;
}
