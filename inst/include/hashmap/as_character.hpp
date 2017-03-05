// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// as_character.hpp
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

#ifndef hashmap__as_character__hpp
#define hashmap__as_character__hpp

#include "format_date.hpp"
#include "format_posix.hpp"
#include <boost/lexical_cast.hpp>

namespace hashmap {
namespace detail {

inline Rcpp::Vector<STRSXP>
as_character_date(const Rcpp::Vector<INTSXP>& x)
{
    R_xlen_t i = 0, sz = x.size();
    Rcpp::Vector<STRSXP> res(sz);

    for (; i < sz; i++) {
        if (!Rcpp::traits::is_na<INTSXP>(x[i])) {
            res[i] = format_date((unsigned int)x[i]);
        } else {
            res[i] = NA_STRING;
        }
    }

    return res;
}

inline Rcpp::Vector<STRSXP>
as_character_date(const Rcpp::Vector<REALSXP>& x)
{
    R_xlen_t i = 0, sz = x.size();
    Rcpp::Vector<STRSXP> res(sz);

    for (; i < sz; i++) {
        if (!Rcpp::traits::is_na<REALSXP>(x[i])) {
            res[i] = format_date((unsigned int)x[i]);
        } else {
            res[i] = NA_STRING;
        }
    }

    return res;
}

inline Rcpp::Vector<STRSXP>
as_character_posix(const Rcpp::Vector<INTSXP>& x)
{
    R_xlen_t i = 0, sz = x.size();
    Rcpp::Vector<STRSXP> res(sz);

    for (; i < sz; i++) {
        if (!Rcpp::traits::is_na<INTSXP>(x[i])) {
            res[i] = format_posix(x[i]);
        } else {
            res[i] = NA_STRING;
        }
    }

    return res;
}

inline Rcpp::Vector<STRSXP>
as_character_posix(const Rcpp::Vector<REALSXP>& x)
{
    R_xlen_t i = 0, sz = x.size();
    Rcpp::Vector<STRSXP> res(sz);

    for (; i < sz; i++) {
        if (!Rcpp::traits::is_na<REALSXP>(x[i])) {
            res[i] = format_posix((double)x[i]);
        } else {
            res[i] = NA_STRING;
        }
    }

    return res;
}

inline Rcpp::Vector<STRSXP>
as_character_integer(const Rcpp::Vector<INTSXP>& x)
{
    R_xlen_t i = 0, sz = x.size();
    Rcpp::Vector<STRSXP> res(sz);

    for (; i < sz; i++) {
        if (!Rcpp::traits::is_na<INTSXP>(x[i])) {
            res[i] = boost::lexical_cast<std::string>(x[i]);
        } else {
            res[i] = NA_STRING;
        }
    }

    return res;
}

} // detail

template <int RTYPE>
inline Rcpp::Vector<STRSXP>
as_character(const Rcpp::Vector<RTYPE>& x)
{ return Rcpp::as< Rcpp::Vector<STRSXP> >(x); }

template <>
inline Rcpp::Vector<STRSXP>
as_character<STRSXP>(const Rcpp::Vector<STRSXP>& x)
{ return x; }

template <>
inline Rcpp::Vector<STRSXP>
as_character<INTSXP>(const Rcpp::Vector<INTSXP>& x)
{
    if (Rf_inherits(x, "Date")) {
        return detail::as_character_date(x);
    }
    if (Rf_inherits(x, "POSIXt")) {
        return detail::as_character_posix(x);
    }
    return detail::as_character_integer(x);
}

template <>
inline Rcpp::Vector<STRSXP>
as_character<REALSXP>(const Rcpp::Vector<REALSXP>& x)
{
    if (Rf_inherits(x, "Date")) {
        return detail::as_character_date(x);
    }
    if (Rf_inherits(x, "POSIXt")) {
        return detail::as_character_posix(x);
    }
    return Rcpp::as< Rcpp::Vector<STRSXP> >(x);
}

} // hashmap

#endif // hashmap__as_character__hpp
