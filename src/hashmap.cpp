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
    .method("reserve", &HashMap::reserve)

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
    .method("keys_n", &HashMap::keys_n)
    .method("values_n", &HashMap::values_n)
    .method("data_n", &HashMap::data_n)

    .method("keys_cached", &HashMap::keys_cached)
    .method("values_cached", &HashMap::values_cached)
    .method("cache_keys", &HashMap::cache_keys)
    .method("cache_values", &HashMap::cache_values)

    .method("renew", &HashMap::renew)
    .method("data.frame", &HashMap::data_frame)

    ;
}
