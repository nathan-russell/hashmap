#ifndef hashmap__tools__hpp
#define hashmap__tools__hpp

#include "traits.hpp"
#include <boost/lexical_cast.hpp>

namespace hashmap {
namespace tools {

template <int RTYPE, bool NA, typename T>
class AsCharacter
    : public Rcpp::VectorBase<STRSXP, false, AsCharacter<RTYPE, NA, T> > {
public:
    typedef Rcpp::VectorBase<RTYPE, NA, T> VEC;
    typedef typename Rcpp::traits::storage_type<RTYPE>::type stored_t;
    typedef Rcpp::String result_t;

private:
    const VEC& vec;

public:
    AsCharacter(const VEC& vec_)
        : vec(vec_)
    {}

    R_xlen_t size() const { return vec.size(); }

    result_t operator[](R_xlen_t i) const {
        return boost::lexical_cast<std::string>(vec[i]);
    }
};

template <bool NA, typename T>
class AsCharacter<CPLXSXP, NA, T>
    : public Rcpp::VectorBase<STRSXP, false, AsCharacter<CPLXSXP, NA, T> > {
public:
    typedef Rcpp::VectorBase<CPLXSXP, NA, T> VEC;
    typedef Rcomplex stored_t;
    typedef Rcpp::String result_t;

private:
    const VEC& vec;

public:
    AsCharacter(const VEC& vec_)
        : vec(vec_)
    {}

    R_xlen_t size() const { return vec.size(); }

    result_t operator[](R_xlen_t i) const {
        Rcomplex cx = vec[i];

        return boost::lexical_cast<std::string>(cx.r) +
            (cx.i < 0 ? "" : "+") +
            boost::lexical_cast<std::string>(cx.i) + "i";
    }
};

template <bool NA, typename T>
class AsCharacter<STRSXP, NA, T>
    : public Rcpp::VectorBase<STRSXP, false, AsCharacter<STRSXP, NA, T> > {
public:
    typedef Rcpp::VectorBase<STRSXP, NA, T> VEC;
    typedef Rcpp::String stored_t;
    typedef Rcpp::String result_t;

private:
    const VEC& vec;

public:
    AsCharacter(const VEC& vec_)
        : vec(vec_)
    {}

    R_xlen_t size() const { return vec.size(); }

    result_t operator[](R_xlen_t i) const {
        return vec[i];
    }
};

// Not currently used
// lexical_cast produces different precision than
// coerceVector even though it is ~twice as fast

template <int RTYPE, bool NA, typename T>
inline AsCharacter<RTYPE, NA, T>
as_character(const Rcpp::VectorBase<RTYPE, NA, T>& x) {
    return AsCharacter<RTYPE, NA, T>(x);
}

} // tools
} // hashmap

#endif // hashmap__tools__hpp
