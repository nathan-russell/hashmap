// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// HashMap.hpp
//
// Copyright (C) 2016 Nathan Russell
//
// This file is part of hashmap.
//
// hashmap is free software: you can redistribute it and/or
// modify it under the terms of the MIT License.
//
// hashmap is provided "as is", without warranty of any kind,
// express or implied, including but not limited to the
// warranties of merchantability, fitness for a particular
// purpose and noninfringement.
//
// You should have received a copy of the MIT License
// along with hashmap. If not, see
// <https://opensource.org/licenses/MIT>.

#ifndef hashmap__HashMap__hpp
#define hashmap__HashMap__hpp

#include "HashTemplate.hpp"
#include <boost/variant.hpp>

namespace hashmap {

typedef boost::variant<
    ss_hash, sd_hash, si_hash, sb_hash, sx_hash,
    dd_hash, ds_hash, di_hash, db_hash, dx_hash,
    ii_hash, is_hash, id_hash, ib_hash, ix_hash
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

    struct keys_cached_visitor : public boost::static_visitor<bool> {
        template <typename T>
        bool operator()(const T& t) const {
            return t.keys_cached();
        }
    };

    struct values_cached_visitor : public boost::static_visitor<bool> {
        template <typename T>
        bool operator()(const T& t) const {
            return t.values_cached();
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

    struct rehash_visitor : public boost::static_visitor<> {
        std::size_t n;
        rehash_visitor(std::size_t n_)
            : n(n_)
        {}

        template <typename T>
        void operator()(T& t) {
            t.rehash(n);
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

    struct insert_visitor : public boost::static_visitor<> {
        SEXP keys, values;
        insert_visitor(SEXP keys_, SEXP values_)
            : keys(keys_), values(values_)
        {}

        template <typename T>
        void operator()(T& t) {
            t.insert(keys, values);
        }
    };

    struct keys_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.keys());
        }
    };

    struct keys_n_visitor : public boost::static_visitor<SEXP> {
        int n;
        keys_n_visitor(int n_)
            : n(n_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.keys_n(n));
        }
    };

    struct values_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.values());
        }
    };

    struct values_n_visitor : public boost::static_visitor<SEXP> {
        int n;
        values_n_visitor(int n_)
            : n(n_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.values_n(n));
        }
    };

    struct cache_keys_visitor : public boost::static_visitor<> {
        template <typename T>
        void operator()(T& t) {
            t.cache_keys();
        }
    };

    struct cache_values_visitor : public boost::static_visitor<> {
        template <typename T>
        void operator()(T& t) {
            t.cache_values();
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

    struct find_visitor : public boost::static_visitor<SEXP> {
        SEXP keys;
        find_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.find(keys));
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

    struct has_keys_visitor : public boost::static_visitor<SEXP> {
        SEXP keys;
        has_keys_visitor(SEXP keys_)
            : keys(keys_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.has_keys(keys));
        }
    };

    struct data_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.data());
        }
    };

    struct data_n_visitor : public boost::static_visitor<SEXP> {
        int n;
        data_n_visitor(int n_)
            : n(n_)
        {}

        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.data_n(n));
        }
    };

    struct data_frame_visitor : public boost::static_visitor<SEXP> {
        template <typename T>
        SEXP operator()(const T& t) const {
            return Rcpp::wrap(t.data_frame());
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
                    case CPLXSXP: {
                        variant = ix_hash(Rcpp::as<Rcpp::IntegerVector>(x),
                                          Rcpp::as<Rcpp::ComplexVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value type!");
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
                    case CPLXSXP: {
                        variant = dx_hash(Rcpp::as<Rcpp::NumericVector>(x),
                                          Rcpp::as<Rcpp::ComplexVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value type!");
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
                    case CPLXSXP: {
                        variant = sx_hash(Rcpp::as<Rcpp::CharacterVector>(x),
                                          Rcpp::as<Rcpp::ComplexVector>(y));
                        break;
                    }
                    default: {
                        Rcpp::stop("Invalid value type!");
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

    void renew(SEXP x, SEXP y) {
        HashMap tmp(x, y);
        variant = tmp.variant;
    }

    int size() const {
        return boost::apply_visitor(size_visitor(), variant);
    }

    bool empty() const {
        return boost::apply_visitor(empty_visitor(), variant);
    }

    bool keys_cached() const {
        return boost::apply_visitor(keys_cached_visitor(), variant);
    }

    bool values_cached() const {
        return boost::apply_visitor(values_cached_visitor(), variant);
    }

    void clear() {
        clear_visitor v;
        boost::apply_visitor(v, variant);
    }

    int bucket_count() const {
        return boost::apply_visitor(bucket_count_visitor(), variant);
    }

    void rehash(int n) {
        rehash_visitor v(n);
        boost::apply_visitor(v, variant);
    }

    SEXP hash_value(SEXP x) const {
        hash_value_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    void insert(SEXP x, SEXP y) {
        insert_visitor v(x, y);
        boost::apply_visitor(v, variant);
    }

    SEXP keys(/*bool cache = false*/) const {
        //keys_visitor v(cache);
        keys_visitor v;
        return boost::apply_visitor(v, variant);
    }

    SEXP keys_n(int n) const {
        keys_n_visitor v(n);
        return boost::apply_visitor(v, variant);
    }

    SEXP values(/*bool cache = false*/) const {
        //values_visitor v(cache);
        values_visitor v;
        return boost::apply_visitor(v, variant);
    }

    SEXP values_n(int n) const {
        values_n_visitor v(n);
        return boost::apply_visitor(v, variant);
    }

    void cache_keys() {
        cache_keys_visitor v;
        boost::apply_visitor(v, variant);
    }

    void cache_values() {
        cache_values_visitor v;
        boost::apply_visitor(v, variant);
    }

    void erase(SEXP x) {
        erase_visitor v(x);
        boost::apply_visitor(v, variant);
    }

    SEXP find(SEXP x) const {
        find_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    bool has_key(SEXP x) const {
        has_key_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    SEXP has_keys(SEXP x) const {
        has_keys_visitor v(x);
        return boost::apply_visitor(v, variant);
    }

    SEXP data() const {
        data_visitor v;
        return boost::apply_visitor(v, variant);
    }

    SEXP data_n(int n) const {
        data_n_visitor v(n);
        return boost::apply_visitor(v, variant);
    }

    SEXP data_frame() const {
        data_frame_visitor v;
        return boost::apply_visitor(v, variant);
    }
};

} // hashmap

#endif // hashmap__HashMap__hpp
