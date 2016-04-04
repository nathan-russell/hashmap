#ifndef hashmap__HashMap__hpp
#define hashmap__HashMap__hpp

#include "HashTemplate.hpp"
#include <boost/variant.hpp>

namespace hashmap {

typedef boost::variant<
    ss_hash, sd_hash, si_hash, sb_hash,
    dd_hash, ds_hash, di_hash, db_hash,
    ii_hash, is_hash, id_hash, ib_hash
> variant_hash;

class HashMap {
private:
    variant_hash variant;

    struct size_visitor : public boost::static_visitor<std::size_t> {
        template <typename T>
        std::size_t operator()(const T& t) const {
            return t.size();
        }
    };

    struct empty_visitor : public boost::static_visitor<bool> {
        template <typename T>
        bool operator()(const T& t) const {
            return t.empty();
        }
    };

    struct clear_visitor : public boost::static_visitor<> {
        template <typename T>
        void operator()(T& t) {
            t.clear();
        }
    };

    struct bucket_count_visitor : public boost::static_visitor<std::size_t> {
        template <typename T>
        std::size_t operator()(const T& t) const {
            return t.bucket_count();
        }
    };

    struct hash_value_visitor : public boost::static_visitor<SEXP> {
        SEXP keys;
        hash_value_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.hash_value(keys));
        }
    };

    struct set_values_visitor : public boost::static_visitor<> {
        SEXP keys, values;
        set_values_visitor(SEXP keys_, SEXP values_)
            : keys(keys_), values(values_)
        {}

        template <typename T>
        void operator()(T& t) {
            t.set_values(keys, values);
        }
    };

    struct all_keys_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.all_keys());
        }
    };

    struct all_values_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.all_values());
        }
    };

    struct erase_visitor : public boost::static_visitor<> {
        SEXP keys;
        erase_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        void operator()(T& t) {
            t.erase(keys);
        }
    };

    struct find_values_visitor : public boost::static_visitor<SEXP> {
        SEXP keys;
        find_values_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.find_values(keys));
        }
    };

    struct has_key_visitor : public boost::static_visitor<bool> {
        SEXP keys;
        has_key_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        bool operator()(const T& t) const {
            return t.has_key(keys);
        }
    };

    struct data_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.data());
        }
    };

public:
    HashMap(SEXP x, SEXP y) {
        switch (TYPEOF(x)) {
            case INTSXP: {
                switch (TYPEOF(y)) {
                    case INTSXP: {
                        variant = ii_hash(Rcpp::as<Rcpp::IntegerVector>(x),
                                          Rcpp::as<Rcpp::IntegerVector>(y));
                        break;
                    }
                    case REALSXP: {
                        variant = id_hash(Rcpp::as<Rcpp::IntegerVector>(x),
                                          Rcpp::as<Rcpp::NumericVector>(y));
                        break;
                    }
                    case STRSXP: {
                        variant = is_hash(Rcpp::as<Rcpp::IntegerVector>(x),
                                          Rcpp::as<Rcpp::CharacterVector>(y));
                        break;
                    }
                    case LGLSXP: {
                        variant = ib_hash(Rcpp::as<Rcpp::IntegerVector>(x),
                                          Rcpp::as<Rcpp::LogicalVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value_type!");
                        break;
                    }
                }
                break;
            }

            case REALSXP: {
                switch (TYPEOF(y)) {
                    case INTSXP: {
                        variant = di_hash(Rcpp::as<Rcpp::NumericVector>(x),
                                          Rcpp::as<Rcpp::IntegerVector>(y));
                        break;
                    }
                    case REALSXP: {
                        variant = dd_hash(Rcpp::as<Rcpp::NumericVector>(x),
                                          Rcpp::as<Rcpp::NumericVector>(y));
                        break;
                    }
                    case STRSXP: {
                        variant = ds_hash(Rcpp::as<Rcpp::NumericVector>(x),
                                          Rcpp::as<Rcpp::CharacterVector>(y));
                        break;
                    }
                    case LGLSXP: {
                        variant = db_hash(Rcpp::as<Rcpp::NumericVector>(x),
                                          Rcpp::as<Rcpp::LogicalVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value_type!");
                        break;
                    }
                }
                break;
            }

            case STRSXP: {
                switch (TYPEOF(y)) {
                    case INTSXP: {
                        variant = si_hash(Rcpp::as<Rcpp::CharacterVector>(x),
                                          Rcpp::as<Rcpp::IntegerVector>(y));
                        break;
                    }
                    case REALSXP: {
                        variant = sd_hash(Rcpp::as<Rcpp::CharacterVector>(x),
                                          Rcpp::as<Rcpp::NumericVector>(y));
                        break;
                    }
                    case STRSXP: {
                        variant = ss_hash(Rcpp::as<Rcpp::CharacterVector>(x),
                                          Rcpp::as<Rcpp::CharacterVector>(y));
                        break;
                    }
                    case LGLSXP: {
                        variant = sb_hash(Rcpp::as<Rcpp::CharacterVector>(x),
                                          Rcpp::as<Rcpp::LogicalVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value_type!");
                        break;
                    }
                }
                break;
            }
            default: {
                Rcpp::stop("Invalid key type!");
                break;
            }
        }
    }

    void rehash(SEXP x, SEXP y) {
        HashMap tmp(x, y);
        variant = tmp.variant;
    }

    int size() const {
        return boost::apply_visitor(size_visitor(), variant);
    }

    bool empty() const {
        return boost::apply_visitor(empty_visitor(), variant);
    }

    void clear() {
        clear_visitor v;
        boost::apply_visitor(v, variant);
    }

    int bucket_count() const {
        return boost::apply_visitor(bucket_count_visitor(), variant);
    }

    SEXP hash_value(SEXP x) const {
        hash_value_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    void set_values(SEXP x, SEXP y) {
        set_values_visitor v(x, y);
        boost::apply_visitor(v, variant);
    }

    SEXP all_keys() const {
        return boost::apply_visitor(all_keys_visitor(), variant);
    }

    SEXP all_values() const {
        return boost::apply_visitor(all_values_visitor(), variant);
    }

    void erase(SEXP x) {
        erase_visitor v(x);
        boost::apply_visitor(v, variant);
    }

    SEXP find_values(SEXP x) const {
        find_values_visitor v(x);
        //return boost::apply_visitor(find_values_visitor(x), variant);
        return boost::apply_visitor(v, variant);
    }

    bool has_key(SEXP x) const {
        has_key_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    SEXP data() const {
        data_visitor v;
        return boost::apply_visitor(v, variant);
    }
};

} // hashmap

#endif // hashmap__HashMap__hpp
