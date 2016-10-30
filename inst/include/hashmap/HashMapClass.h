// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// HashMapClass.h
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

#ifndef hashmap__HashMapClass__h
#define hashmap__HashMapClass__h

#include <Rcpp.h>
#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>

namespace hashmap {

template <typename KeyType, typename ValueType>
class HashTemplate;

#define MAKE_PTR_TYPE(__TYPE__)                                \
    typedef boost::shared_ptr<__TYPE__> __TYPE__##_ptr

typedef HashTemplate<std::string, std::string> ss_hash;
MAKE_PTR_TYPE(ss_hash);

typedef HashTemplate<std::string, double> sd_hash;
MAKE_PTR_TYPE(sd_hash);

typedef HashTemplate<std::string, int> si_hash;
MAKE_PTR_TYPE(si_hash);

typedef HashTemplate<std::string, bool> sb_hash;
MAKE_PTR_TYPE(sb_hash);

typedef HashTemplate<std::string, Rcomplex> sx_hash;
MAKE_PTR_TYPE(sx_hash);

typedef HashTemplate<double, double> dd_hash;
MAKE_PTR_TYPE(dd_hash);

typedef HashTemplate<double, std::string> ds_hash;
MAKE_PTR_TYPE(ds_hash);

typedef HashTemplate<double, int> di_hash;
MAKE_PTR_TYPE(di_hash);

typedef HashTemplate<double, bool> db_hash;
MAKE_PTR_TYPE(db_hash);

typedef HashTemplate<double, Rcomplex> dx_hash;
MAKE_PTR_TYPE(dx_hash);

typedef HashTemplate<int, int> ii_hash;
MAKE_PTR_TYPE(ii_hash);

typedef HashTemplate<int, std::string> is_hash;
MAKE_PTR_TYPE(is_hash);

typedef HashTemplate<int, double> id_hash;
MAKE_PTR_TYPE(id_hash);

typedef HashTemplate<int, bool> ib_hash;
MAKE_PTR_TYPE(ib_hash);

typedef HashTemplate<int, Rcomplex> ix_hash;
MAKE_PTR_TYPE(ix_hash);

#undef MAKE_PTR_TYPE

typedef boost::variant<
    ss_hash_ptr, sd_hash_ptr, si_hash_ptr, sb_hash_ptr, sx_hash_ptr,
    dd_hash_ptr, ds_hash_ptr, di_hash_ptr, db_hash_ptr, dx_hash_ptr,
    ii_hash_ptr, is_hash_ptr, id_hash_ptr, ib_hash_ptr, ix_hash_ptr
> variant_hash;

class HashMap {
private:
    variant_hash variant;

    struct clone_visitor
        : public boost::static_visitor<variant_hash>
    {
        template <typename T>
        variant_hash operator()(const T& t) const;
    };

    struct size_visitor
        : public boost::static_visitor<std::size_t>
    {
        template <typename T>
        std::size_t operator()(const T& t) const;
    };

    struct empty_visitor
        : public boost::static_visitor<bool>
    {
        template <typename T>
        bool operator()(const T& t) const;
    };

    struct keys_cached_visitor
        : public boost::static_visitor<bool>
    {
        template <typename T>
        bool operator()(const T& t) const;
    };

    struct values_cached_visitor
        : public boost::static_visitor<bool>
    {
        template <typename T>
        bool operator()(const T& t) const;
    };

    struct key_sexptype_visitor
        : public boost::static_visitor<int>
    {
        template <typename T>
        int operator()(const T& t) const;
    };

    struct value_sexptype_visitor
        : public boost::static_visitor<int>
    {
        template <typename T>
        int operator()(const T& t) const;
    };

    struct key_vector_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        key_vector_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct value_vector_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        value_vector_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct na_value_vector_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        na_value_vector_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct clear_visitor
        : public boost::static_visitor<>
    {
        template <typename T>
        void operator()(T& t);
    };

    struct bucket_count_visitor
        : public boost::static_visitor<std::size_t>
    {
        template <typename T>
        std::size_t operator()(const T& t) const;
    };

    struct rehash_visitor
        : public boost::static_visitor<>
    {
        std::size_t n;
        rehash_visitor(std::size_t n_);

        template <typename T>
        void operator()(T& t);
    };

    struct reserve_visitor
        : public boost::static_visitor<>
    {
        std::size_t n;
        reserve_visitor(std::size_t n_);

        template <typename T>
        void operator()(T& t);
    };

    struct hash_value_visitor
        : public boost::static_visitor<SEXP>
    {
        SEXP keys;
        hash_value_visitor(SEXP keys_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct insert_visitor
        : public boost::static_visitor<>
    {
        SEXP keys, values;
        insert_visitor(SEXP keys_, SEXP values_);

        template <typename T>
        void operator()(T& t);
    };

    struct keys_visitor
        : public boost::static_visitor<SEXP>
    {
        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct keys_n_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        keys_n_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct values_visitor
        : public boost::static_visitor<SEXP>
    {
        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct values_n_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        values_n_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct cache_keys_visitor
        : public boost::static_visitor<>
    {
        template <typename T>
        void operator()(T& t);
    };

    struct cache_values_visitor
        : public boost::static_visitor<>
    {
        template <typename T>
        void operator()(T& t);
    };

    struct erase_visitor
        : public boost::static_visitor<>
    {
        SEXP keys;
        erase_visitor(SEXP keys_);

        template <typename T>
        void operator()(T& t);
    };

    struct find_visitor
        : public boost::static_visitor<SEXP>
    {
        SEXP keys;
        find_visitor(SEXP keys_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct has_key_visitor
        : public boost::static_visitor<bool>
    {
        SEXP keys;
        has_key_visitor(SEXP keys_);

        template <typename T>
        bool operator()(const T& t) const;
    };

    struct has_keys_visitor
        : public boost::static_visitor<SEXP>
    {
        SEXP keys;
        has_keys_visitor(SEXP keys_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct data_visitor
        : public boost::static_visitor<SEXP>
    {
        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct data_n_visitor
        : public boost::static_visitor<SEXP>
    {
        int n;
        data_n_visitor(int n_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct data_frame_visitor
        : public boost::static_visitor<SEXP>
    {
        template <typename T>
        SEXP operator()(const T& t) const;
    };

    struct key_class_name_visitor
        : public boost::static_visitor<std::string>
    {
        template <typename T>
        std::string operator()(const T& t) const;
    };

    struct value_class_name_visitor
        : public boost::static_visitor<std::string>
    {
        template <typename T>
        std::string operator()(const T& t) const;
    };

    struct left_outer_join_visitor
        : public boost::static_visitor<SEXP>
    {
        const HashMap& other;
        left_outer_join_visitor(const HashMap& other_);

        template <typename T>
        SEXP operator()(const T& t) const;
    };

    void init(SEXP x, SEXP y);

public:
    HashMap(SEXP x, SEXP y);

    HashMap(const HashMap& other);

    HashMap(const Rcpp::XPtr<HashMap>& ptr);

    HashMap clone() const;

    void renew(SEXP x, SEXP y);

    int size() const;

    bool empty() const;

    bool keys_cached() const;

    bool values_cached() const;

    int key_sexptype() const;

    int value_sexptype() const;

    SEXP key_vector(int n) const;

    SEXP value_vector(int n) const;

    SEXP na_value_vector(int n) const;

    void clear();

    int bucket_count() const;

    void rehash(int n);

    void reserve(int n);

    SEXP hash_value(SEXP x) const;

    void insert(SEXP x, SEXP y);

    SEXP keys() const;

    SEXP keys_n(int n) const;

    SEXP values() const;

    SEXP values_n(int n) const;

    void cache_keys();

    void cache_values();

    void erase(SEXP x);

    SEXP find(SEXP x) const;

    bool has_key(SEXP x) const;

    SEXP has_keys(SEXP x) const;

    SEXP data() const;

    SEXP data_n(int n) const;

    SEXP data_frame() const;

    std::string key_class_name() const;

    std::string value_class_name() const;

    SEXP left_outer_join(const HashMap& other) const;

    SEXP left_outer_join(const Rcpp::XPtr<HashMap>& other) const;
};

} // hashmap

#endif // hashmap__HashMapClass__h
