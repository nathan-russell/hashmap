#ifndef hashmap__traits__hpp
#define hashmap__traits__hpp

#include <Rcpp.h>

namespace hashmap {
namespace traits {

template <typename T>
struct sexp_traits
    : public Rcpp::traits::r_sexptype_traits<T>
{};

template <int RTYPE>
struct cpp_traits
    : public Rcpp::traits::storage_type<RTYPE>
{};

template <>
struct cpp_traits<STRSXP> {
    typedef std::string type;
};

template <typename T>
inline T get_na() {
    return Rcpp::traits::get_na<
        traits::sexp_traits<T>::rtype>();
}

template <>
inline std::string get_na<std::string>() {
    return "NA";
}

} // traits
} // hashmap

#endif // hashmap__traits__hpp
