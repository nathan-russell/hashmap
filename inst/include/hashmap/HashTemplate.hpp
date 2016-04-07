#ifndef hashmap__HashTemplate__hpp
#define hashmap__HashTemplate__hpp

#include "traits.hpp"
#include <boost/unordered_map.hpp>
#include <boost/functional/hash.hpp>

namespace hashmap {

template <int RTYPE>
inline typename traits::cpp_traits<RTYPE>::type
extractor(const Rcpp::Vector<RTYPE>& vec, R_xlen_t i) {
    return vec[i];
}

template <>
inline std::string
extractor<STRSXP>(const Rcpp::Vector<STRSXP>& vec, R_xlen_t i) {
    return Rcpp::as<std::string>(vec[i]);
}

template <typename KeyType, typename ValueType>
class HashTemplate {
public:
    typedef KeyType key_t;
    typedef ValueType value_t;
    typedef boost::unordered_map<key_t, value_t> map_t;

    enum { key_rtype = traits::sexp_traits<key_t>::rtype };
    enum { value_rtype = traits::sexp_traits<value_t>::rtype };

    typedef Rcpp::Vector<key_rtype> key_vec;
    typedef Rcpp::Vector<value_rtype> value_vec;

    typedef typename map_t::size_type size_type;
    typedef typename map_t::const_iterator const_iterator;
    typedef typename map_t::iterator iterator;
    typedef typename map_t::hasher hasher;

private:
    map_t map;

    key_t key_na() const { return traits::get_na<key_t>(); }
    value_t value_na() const { return traits::get_na<value_t>(); }

    /*mutable*/ bool keys_cached_;
    /*mutable*/ bool values_cached_;

    /*mutable*/ key_vec kvec;
    /*mutable*/ value_vec vvec;

    mutable bool date_keys;
    mutable bool date_values;

    struct posix_t {
        bool is;
        Rcpp::RObject tz;

        template <int RTYPE>
        posix_t(const Rcpp::Vector<RTYPE>& x)
            : is(Rf_inherits(x, "POSIXt")),
              tz(R_NilValue)
        {
            if (!is) return;
            tz = Rf_isNull(x.attr("tzone")) ?
                Rcpp::wrap("UTC") : x.attr("tzone");
        }

        posix_t()
            : is(false), tz(R_NilValue)
        {}
    };

    posix_t posix_keys;
    posix_t posix_values;

public:
    HashTemplate()
        : keys_cached_(false), values_cached_(false),
          date_keys(false), date_values(false),
          posix_keys(posix_t()), posix_values(posix_t())
    {
        kvec = key_vec(0);
        vvec = value_vec(0);
    }

    HashTemplate(const key_vec& keys_, const value_vec& values_)
        : keys_cached_(false), values_cached_(false),
          posix_keys(keys_), posix_values(values_)
    {
        R_xlen_t nk = keys_.size(), nv = values_.size(), i = 0, n;
        if (nk != nv) {
            Rcpp::warning("length(keys) != length(values)!");
        }
        n = nk < nv ? nk : nv;

        map.reserve(n);
        kvec = key_vec(n);
        vvec = value_vec(n);

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map[extractor(keys_, i)] = extractor(values_, i);
        }

        date_keys = Rf_inherits(keys_, "Date");
        date_values = Rf_inherits(values_, "Date");
    }

//     HashTemplate& operator=(const HashTemplate& other) {
//         if (this == &other) return *this;
//
//         map = other.map;
//         values_cached_ = other.values_cached_;
//         keys_cached_ = other.keys_cached_;
//         kvec = Rcpp::clone(other.kvec);
//         vvec = Rcpp::clone(other.vvec);
//
//         return *this;
//     }

    size_type size() const { return map.size(); }
    bool empty() const { return map.empty(); }
    bool keys_cached() const { return keys_cached_; }
    bool values_cached() const { return values_cached_; }

    void clear() {
        map.clear();
        keys_cached_ = false;
        values_cached_ = false;
    }

    size_type bucket_count() const { return map.bucket_count(); }
    void rehash(size_type n) { map.rehash(n); }

    Rcpp::Vector<INTSXP> hash_value(const key_vec& keys_) const {
        R_xlen_t i = 0, nk = keys_.size();
        Rcpp::Vector<INTSXP> res = Rcpp::no_init_vector(nk);
        hasher h;

        for ( ; i < nk; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i] = h(extractor(keys_, i));
        }

        return res;
    }

    void insert(const key_vec& keys_, const value_vec& values_) {
        R_xlen_t nk = keys_.size(), nv = values_.size(), i = 0, n;
        if (nk != nv) {
            Rcpp::warning("length(keys) != length(values)!");
        }
        n = nk < nv ? nk : nv;
        keys_cached_ = false;
        values_cached_ = false;

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map[extractor(keys_, i)] = extractor(values_, i);
        }
    }

    void insert(SEXP keys_, SEXP values_) {
        insert(Rcpp::as<key_vec>(keys_), Rcpp::as<value_vec>(values_));
    }

    key_vec keys() const {
        if (keys_cached_) return kvec;

        const_iterator first = map.begin(), last = map.end();
        key_vec res(map.size());

        for (R_xlen_t i = 0; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i++] = first->first;
        }

        if (date_keys) {
            res.attr("class") = "Date";
        } else if (posix_keys.is) {
            res.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            res.attr("tzone") = posix_keys.tz;
        }

        return res;
    }

    value_vec values() const {
        if (values_cached_) return vvec;

        const_iterator first = map.begin(), last = map.end();
        value_vec res(map.size());

        for (R_xlen_t i = 0; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i++] = first->second;
        }

        if (date_values) {
            res.attr("class") = "Date";
        } else if (posix_values.is) {
            res.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            res.attr("tzone") = posix_values.tz;
        }

        return res;
    }

    void cache_keys() {
        if (keys_cached_) return;

        R_xlen_t i = 0, n = map.size();
        if (kvec.size() != n) {
            kvec = key_vec(n);
        }

        const_iterator first = map.begin(), last = map.end();
        for ( ; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            kvec[i++] = first->first;
        }

        keys_cached_ = true;

        if (date_keys) {
            kvec.attr("class") = "Date";
        } else if (posix_keys.is) {
            kvec.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            kvec.attr("tzone") = posix_keys.tz;
        }
    }

    void cache_values() {
        if (values_cached_) return;

        R_xlen_t i = 0, n = map.size();
        if (vvec.size() != n) {
            vvec = value_vec(n);
        }

        const_iterator first = map.begin(), last = map.end();
        for ( ; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            vvec[i++] = first->second;
        }

        values_cached_ = true;

        if (date_values) {
            vvec.attr("class") = "Date";
        } else if (posix_values.is) {
            vvec.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            vvec.attr("tzone") = posix_values.tz;
        }
    }

    void erase(const key_vec& keys_) {
        R_xlen_t i = 0, n = keys_.size();

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            map.erase(extractor(keys_, i));
        }

        keys_cached_ = false;
        values_cached_ = false;
    }

    value_vec find(const key_vec& keys_) const {
        R_xlen_t i = 0, n = keys_.size();
        value_vec res(n);
        const_iterator last = map.end();

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            const_iterator pos = map.find(extractor(keys_, i));
            if (pos != last) {
                res[i] = pos->second;
            } else {
                res[i] = Rcpp::traits::get_na<value_rtype>();
            }
        }

        if (date_values) {
            res.attr("class") = "Date";
        } else if (posix_values.is) {
            res.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            res.attr("tzone") = posix_values.tz;
        }

        return res;
    }

    value_vec find(SEXP keys_) const {
        return find(Rcpp::as<key_vec>(keys_));
    }

    bool has_key(const key_vec& keys_) const {
        return map.find(extractor(keys_, 0)) != map.end();
    }

    bool has_key(SEXP keys_) const {
        return has_key(Rcpp::as<key_vec>(keys_));
    }

    Rcpp::Vector<LGLSXP> has_keys(const key_vec& keys_) const {
        R_xlen_t i = 0, n = keys_.size();
        Rcpp::Vector<LGLSXP> res = Rcpp::no_init_vector(n);
        const_iterator last = map.end();

        for ( ; i < n; i++) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            res[i] = (map.find(extractor(keys_, i)) != last) ?
                true : false;
        }

        return res;
    }

    Rcpp::Vector<LGLSXP> has_keys(SEXP keys_) const {
        return has_keys(Rcpp::as<key_vec>(keys_));
    }

    value_vec data() const {
        if (values_cached_ && keys_cached_) {
            value_vec res(vvec);
            res.names() = kvec;
            return res;
        }

        R_xlen_t i = 0, n = map.size();

        value_vec res(n);
        key_vec knames(n);

        const_iterator first = map.begin(), last = map.end();

        for ( ; first != last; ++first) {
            HASHMAP_CHECK_INTERRUPT(i, 50000);
            knames[i] = first->first;
            res[i] = first->second;
            ++i;
        }

        if (date_keys) {
            knames.attr("class") = "Date";
        } else if (posix_keys.is) {
            knames.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            knames.attr("tzone") = posix_keys.tz;
        }

        SEXP snames;
        PROTECT(snames = Rf_coerceVector(knames, STRSXP));
        Rcpp::Vector<STRSXP> names(snames);
        UNPROTECT(1);

        if (date_values) {
            res.attr("class") = "Date";
        } else if (posix_values.is) {
            res.attr("class") =
                Rcpp::CharacterVector::create("POSIXct", "POSIXt");
            res.attr("tzone") = posix_values.tz;
        }

        res.names() = names;
        return res;
    }
};

typedef HashTemplate<std::string, std::string> ss_hash;
typedef HashTemplate<std::string, double> sd_hash;
typedef HashTemplate<std::string, int> si_hash;
typedef HashTemplate<std::string, bool> sb_hash;
typedef HashTemplate<std::string, Rcomplex> sx_hash;

typedef HashTemplate<double, double> dd_hash;
typedef HashTemplate<double, std::string> ds_hash;
typedef HashTemplate<double, int> di_hash;
typedef HashTemplate<double, bool> db_hash;
typedef HashTemplate<double, Rcomplex> dx_hash;

typedef HashTemplate<int, int> ii_hash;
typedef HashTemplate<int, std::string> is_hash;
typedef HashTemplate<int, double> id_hash;
typedef HashTemplate<int, bool> ib_hash;
typedef HashTemplate<int, Rcomplex> ix_hash;

} // hashmap

#endif // hashmap__HashTemplate__hpp
