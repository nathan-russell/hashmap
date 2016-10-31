// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// HashMapClass.cpp
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

#include "../inst/include/hashmap/HashTemplate.hpp"
#include <boost/make_shared.hpp>

namespace hashmap {

template <typename T>
variant_hash HashMap::clone_visitor::operator()(const T& t) const
{
    return variant_hash(t->clone());
}

template <typename T>
std::size_t HashMap::size_visitor::operator()(const T& t) const
{
    return t->size();
}

template <typename T>
bool HashMap::empty_visitor::operator()(const T& t) const
{
    return t->empty();
}

template <typename T>
bool HashMap::keys_cached_visitor::operator()(const T& t) const
{
    return t->keys_cached();
}

template <typename T>
bool HashMap::values_cached_visitor::operator()(const T& t) const
{
    return t->values_cached();
}

template <typename T>
int HashMap::key_sexptype_visitor::operator()(const T& t) const
{
    return t->key_sexptype();
}

template <typename T>
int HashMap::value_sexptype_visitor::operator()(const T& t) const
{
    return t->value_sexptype();
}

HashMap::key_vector_visitor::key_vector_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::key_vector_visitor::operator()(const T& t) const
{
    return t->key_vector(n);
}

HashMap::value_vector_visitor::value_vector_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::value_vector_visitor::operator()(const T& t) const
{
    return t->value_vector(n);
}

HashMap::na_value_vector_visitor::na_value_vector_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::na_value_vector_visitor::operator()(const T& t) const
{
    return t->na_value_vector(n);
}

template <typename T>
void HashMap::clear_visitor::operator()(T& t)
{
    t->clear();
}

template <typename T>
std::size_t HashMap::bucket_count_visitor::operator()(const T& t) const
{
    return t->bucket_count();
};

HashMap::rehash_visitor::rehash_visitor(std::size_t n_)
    : n(n_)
{}

template <typename T>
void HashMap::rehash_visitor::operator()(T& t)
{
    t->rehash(n);
}

HashMap::reserve_visitor::reserve_visitor(std::size_t n_)
    : n(n_)
{}

template <typename T>
void HashMap::reserve_visitor::operator()(T& t)
{
    t->reserve(n);
}

HashMap::hash_value_visitor::hash_value_visitor(SEXP keys_)
    : keys(keys_)
{}

template <typename T>
SEXP HashMap::hash_value_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->hash_value(keys));
}

HashMap::insert_visitor::insert_visitor(SEXP keys_, SEXP values_)
    : keys(keys_), values(values_)
{}

template <typename T>
void HashMap::insert_visitor::operator()(T& t)
{
    t->insert(keys, values);
}

template <typename T>
SEXP HashMap::keys_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->keys());
}

HashMap::keys_n_visitor::keys_n_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::keys_n_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->keys_n(n));
}

template <typename T>
SEXP HashMap::values_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->values());
}

HashMap::values_n_visitor::values_n_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::values_n_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->values_n(n));
}

template <typename T>
void HashMap::cache_keys_visitor::operator()(T& t)
{
    t->cache_keys();
}

template <typename T>
void HashMap::cache_values_visitor::operator()(T& t)
{
    t->cache_values();
}

HashMap::erase_visitor::erase_visitor(SEXP keys_)
    : keys(keys_)
{}

template <typename T>
void HashMap::erase_visitor::operator()(T& t)
{
    t->erase(keys);
}

HashMap::find_visitor::find_visitor(SEXP keys_)
    : keys(keys_)
{}

template <typename T>
SEXP HashMap::find_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->find(keys));
}

HashMap::has_key_visitor::has_key_visitor(SEXP keys_)
    : keys(keys_)
{}

template <typename T>
bool HashMap::has_key_visitor::operator()(const T& t) const
{
    return t->has_key(keys);
}

HashMap::has_keys_visitor::has_keys_visitor(SEXP keys_)
    : keys(keys_)
{}

template <typename T>
SEXP HashMap::has_keys_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->has_keys(keys));
}

template <typename T>
SEXP HashMap::data_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->data());
}

HashMap::data_n_visitor::data_n_visitor(int n_)
    : n(n_)
{}

template <typename T>
SEXP HashMap::data_n_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->data_n(n));
}

template <typename T>
SEXP HashMap::data_frame_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->data_frame());
}

template <typename T>
std::string HashMap::key_class_name_visitor::operator()(const T& t) const
{
    return t->key_class_name();
}

template <typename T>
std::string HashMap::value_class_name_visitor::operator()(const T& t) const
{
    return t->value_class_name();
}

HashMap::left_outer_join_visitor::left_outer_join_visitor(const HashMap& other_)
    : other(other_)
{}

template <typename T>
SEXP HashMap::left_outer_join_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->left_outer_join(other));
}

HashMap::right_outer_join_visitor::right_outer_join_visitor(const HashMap& other_)
    : other(other_)
{}

template <typename T>
SEXP HashMap::right_outer_join_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->right_outer_join(other));
}

HashMap::inner_join_visitor::inner_join_visitor(const HashMap& other_)
    : other(other_)
{}

template <typename T>
SEXP HashMap::inner_join_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->inner_join(other));
}

HashMap::full_outer_join_visitor::full_outer_join_visitor(const HashMap& other_)
    : other(other_)
{}

template <typename T>
SEXP HashMap::full_outer_join_visitor::operator()(const T& t) const
{
    return Rcpp::wrap(t->full_outer_join(other));
}

void HashMap::init(SEXP x, SEXP y)
{
    switch (TYPEOF(x)) {
        case INTSXP: {
            switch (TYPEOF(y)) {
                case INTSXP: {
                    variant = boost::make_shared<ii_hash>(
                        Rcpp::as<Rcpp::IntegerVector>(x),
                        Rcpp::as<Rcpp::IntegerVector>(y)
                    );
                    break;
                }
                case REALSXP: {
                    variant = boost::make_shared<id_hash>(
                        Rcpp::as<Rcpp::IntegerVector>(x),
                        Rcpp::as<Rcpp::NumericVector>(y)
                    );
                    break;
                }
                case STRSXP: {
                    variant = boost::make_shared<is_hash>(
                        Rcpp::as<Rcpp::IntegerVector>(x),
                        Rcpp::as<Rcpp::CharacterVector>(y)
                    );
                    break;
                }
                case LGLSXP: {
                    variant = boost::make_shared<ib_hash>(
                        Rcpp::as<Rcpp::IntegerVector>(x),
                        Rcpp::as<Rcpp::LogicalVector>(y)
                    );
                    break;
                }
                case CPLXSXP: {
                    variant = boost::make_shared<ix_hash>(
                        Rcpp::as<Rcpp::IntegerVector>(x),
                        Rcpp::as<Rcpp::ComplexVector>(y)
                    );
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
                    variant = boost::make_shared<di_hash>(
                        Rcpp::as<Rcpp::NumericVector>(x),
                        Rcpp::as<Rcpp::IntegerVector>(y)
                    );
                    break;
                }
                case REALSXP: {
                    variant = boost::make_shared<dd_hash>(
                        Rcpp::as<Rcpp::NumericVector>(x),
                        Rcpp::as<Rcpp::NumericVector>(y)
                    );
                    break;
                }
                case STRSXP: {
                    variant = boost::make_shared<ds_hash>(
                        Rcpp::as<Rcpp::NumericVector>(x),
                        Rcpp::as<Rcpp::CharacterVector>(y)
                    );
                    break;
                }
                case LGLSXP: {
                    variant = boost::make_shared<db_hash>(
                        Rcpp::as<Rcpp::NumericVector>(x),
                        Rcpp::as<Rcpp::LogicalVector>(y)
                    );
                    break;
                }
                case CPLXSXP: {
                    variant = boost::make_shared<dx_hash>(
                        Rcpp::as<Rcpp::NumericVector>(x),
                        Rcpp::as<Rcpp::ComplexVector>(y)
                    );
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
                    variant = boost::make_shared<si_hash>(
                        Rcpp::as<Rcpp::CharacterVector>(x),
                        Rcpp::as<Rcpp::IntegerVector>(y)
                    );
                    break;
                }
                case REALSXP: {
                    variant = boost::make_shared<sd_hash>(
                        Rcpp::as<Rcpp::CharacterVector>(x),
                        Rcpp::as<Rcpp::NumericVector>(y)
                    );
                    break;
                }
                case STRSXP: {
                    variant = boost::make_shared<ss_hash>(
                        Rcpp::as<Rcpp::CharacterVector>(x),
                        Rcpp::as<Rcpp::CharacterVector>(y)
                    );
                    break;
                }
                case LGLSXP: {
                    variant = boost::make_shared<sb_hash>(
                        Rcpp::as<Rcpp::CharacterVector>(x),
                        Rcpp::as<Rcpp::LogicalVector>(y)
                    );
                    break;
                }
                case CPLXSXP: {
                    variant = boost::make_shared<sx_hash>(
                        Rcpp::as<Rcpp::CharacterVector>(x),
                        Rcpp::as<Rcpp::ComplexVector>(y)
                    );
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

HashMap::HashMap(SEXP x, SEXP y)
{
    init(x, y);
}

HashMap::HashMap(const Rcpp::XPtr<HashMap>& ptr)
{
    init(Rcpp::clone(ptr->keys()), Rcpp::clone(ptr->values()));
}

HashMap HashMap::clone() const
{
    return HashMap(Rcpp::clone(keys()), Rcpp::clone(values()));
}

void HashMap::renew(SEXP x, SEXP y)
{
    HashMap tmp(x, y);
    variant = tmp.variant;
}

int HashMap::size() const
{
    return boost::apply_visitor(size_visitor(), variant);
}

bool HashMap::empty() const
{
    return boost::apply_visitor(empty_visitor(), variant);
}

bool HashMap::keys_cached() const
{
    return boost::apply_visitor(keys_cached_visitor(), variant);
}

bool HashMap::values_cached() const
{
    return boost::apply_visitor(values_cached_visitor(), variant);
}

int HashMap::key_sexptype() const
{
    return boost::apply_visitor(key_sexptype_visitor(), variant);
}

int HashMap::value_sexptype() const
{
    return boost::apply_visitor(value_sexptype_visitor(), variant);
}

SEXP HashMap::key_vector(int n) const
{
    key_vector_visitor v(n);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::value_vector(int n) const
{
    value_vector_visitor v(n);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::na_value_vector(int n) const
{
    na_value_vector_visitor v(n);
    return boost::apply_visitor(v, variant);
}

void HashMap::clear()
{
    clear_visitor v;
    boost::apply_visitor(v, variant);
}

int HashMap::bucket_count() const
{
    return boost::apply_visitor(bucket_count_visitor(), variant);
}

void HashMap::rehash(int n)
{
    rehash_visitor v(n);
    boost::apply_visitor(v, variant);
}

void HashMap::reserve(int n)
{
    reserve_visitor v(n);
    boost::apply_visitor(v, variant);
}

SEXP HashMap::hash_value(SEXP x) const
{
    hash_value_visitor v(x);
    return boost::apply_visitor(v, variant);
}

void HashMap::insert(SEXP x, SEXP y)
{
    insert_visitor v(x, y);
    boost::apply_visitor(v, variant);
}

SEXP HashMap::keys() const
{
    keys_visitor v;
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::keys_n(int n) const
{
    keys_n_visitor v(n);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::values() const
{
    values_visitor v;
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::values_n(int n) const
{
    values_n_visitor v(n);
    return boost::apply_visitor(v, variant);
}

void HashMap::cache_keys()
{
    cache_keys_visitor v;
    boost::apply_visitor(v, variant);
}

void HashMap::cache_values()
{
    cache_values_visitor v;
    boost::apply_visitor(v, variant);
}

void HashMap::erase(SEXP x)
{
    erase_visitor v(x);
    boost::apply_visitor(v, variant);
}

SEXP HashMap::find(SEXP x) const
{
    find_visitor v(x);
    return boost::apply_visitor(v, variant);
}

bool HashMap::has_key(SEXP x) const
{
    has_key_visitor v(x);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::has_keys(SEXP x) const
{
    has_keys_visitor v(x);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::data() const
{
    data_visitor v;
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::data_n(int n) const
{
    data_n_visitor v(n);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::data_frame() const
{
    data_frame_visitor v;
    return boost::apply_visitor(v, variant);
}

std::string HashMap::key_class_name() const
{
    return boost::apply_visitor(key_class_name_visitor(), variant);
}

std::string HashMap::value_class_name() const
{
    return boost::apply_visitor(value_class_name_visitor(), variant);
}

SEXP HashMap::left_outer_join(const HashMap& other) const
{
    left_outer_join_visitor v(other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::left_outer_join(const Rcpp::XPtr<HashMap>& other) const
{
    left_outer_join_visitor v(*other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::right_outer_join(const HashMap& other) const
{
    right_outer_join_visitor v(other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::right_outer_join(const Rcpp::XPtr<HashMap>& other) const
{
    right_outer_join_visitor v(*other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::inner_join(const HashMap& other) const
{
    inner_join_visitor v(other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::inner_join(const Rcpp::XPtr<HashMap>& other) const
{
    inner_join_visitor v(*other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::full_outer_join(const HashMap& other) const
{
    full_outer_join_visitor v(other);
    return boost::apply_visitor(v, variant);
}

SEXP HashMap::full_outer_join(const Rcpp::XPtr<HashMap>& other) const
{
    full_outer_join_visitor v(*other);
    return boost::apply_visitor(v, variant);
}

} // hashmap
