// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// traits.hpp
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

#ifndef hashmap__traits__hpp
#define hashmap__traits__hpp

#include "utils.hpp"

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
inline T get_na()
{ return Rcpp::traits::get_na<traits::sexp_traits<T>::rtype>(); }

template <>
inline std::string get_na<std::string>()
{ return "NA"; }

// fix me
template <int RTYPE>
inline Rcpp::Vector<RTYPE>
hashmap_no_init_vector(R_xlen_t n)
{ return Rcpp::no_init_vector(n); }

// fix me
template <>
inline Rcpp::Vector<STRSXP>
hashmap_no_init_vector<STRSXP>(R_xlen_t n)
{ return Rcpp::Vector<STRSXP>(n); }

} // traits
} // hashmap

#endif // hashmap__traits__hpp
