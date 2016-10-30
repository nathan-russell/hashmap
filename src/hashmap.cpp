// [[Rcpp::depends(BH)]]
#include "../inst/include/hashmap/HashMapClass.h"

using namespace Rcpp;

RCPP_MODULE(Hashmap) {
    class_<hashmap::HashMap>("Hashmap")

    .constructor<SEXP, SEXP>()
    .constructor<Rcpp::XPtr<hashmap::HashMap> >()

    .method("size", &hashmap::HashMap::size)
    .method("empty", &hashmap::HashMap::empty)
    .method("clear", &hashmap::HashMap::clear)
    .method("bucket_count", &hashmap::HashMap::bucket_count)
    .method("rehash", &hashmap::HashMap::rehash)
    .method("reserve", &hashmap::HashMap::reserve)

    .method("hash_value", &hashmap::HashMap::hash_value)

    .method("insert", &hashmap::HashMap::insert)
    .method("[[<-", &hashmap::HashMap::insert)

    .method("erase", &hashmap::HashMap::erase)

    .method("find", &hashmap::HashMap::find)
    .method("[[", &hashmap::HashMap::find)

    .method("has_key", &hashmap::HashMap::has_key)
    .method("has_keys", &hashmap::HashMap::has_keys)

    .method("keys", &hashmap::HashMap::keys)
    .method("values", &hashmap::HashMap::values)
    .method("data", &hashmap::HashMap::data)
    .method("keys_n", &hashmap::HashMap::keys_n)
    .method("values_n", &hashmap::HashMap::values_n)
    .method("data_n", &hashmap::HashMap::data_n)

    .method("keys_cached", &hashmap::HashMap::keys_cached)
    .method("values_cached", &hashmap::HashMap::values_cached)
    .method("cache_keys", &hashmap::HashMap::cache_keys)
    .method("cache_values", &hashmap::HashMap::cache_values)

    .method("key_sexptype", &hashmap::HashMap::key_sexptype)
    .method("value_sexptype", &hashmap::HashMap::value_sexptype)

    .method("renew", &hashmap::HashMap::renew)
    .method("data.frame", &hashmap::HashMap::data_frame)

    ;
}
