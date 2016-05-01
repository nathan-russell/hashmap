// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// format_date.hpp
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

#ifndef hashmap__format_date__hpp
#define hashmap__format_date__hpp

#include "traits.hpp"
#include <cstring>
#include <ctime>

namespace hashmap {

// 'isleap' and 'year_days' (renamed from 'days_in_year')
// are taken from R's datetime.c source file
#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)
#define year_days(year) (isleap(year) ? 366 : 365)

struct days_in_year {
    unsigned int year;
    unsigned int days;
    unsigned int accum;
};

static const days_in_year days_in_years[] =
{
 	{ 1970, 365,   365 },
 	{ 1971, 365,   730 },
 	{ 1972, 366,  1096 },
 	{ 1973, 365,  1461 },
 	{ 1974, 365,  1826 },
 	{ 1975, 365,  2191 },
 	{ 1976, 366,  2557 },
 	{ 1977, 365,  2922 },
 	{ 1978, 365,  3287 },
 	{ 1979, 365,  3652 },
 	{ 1980, 366,  4018 },
 	{ 1981, 365,  4383 },
 	{ 1982, 365,  4748 },
 	{ 1983, 365,  5113 },
 	{ 1984, 366,  5479 },
 	{ 1985, 365,  5844 },
 	{ 1986, 365,  6209 },
 	{ 1987, 365,  6574 },
 	{ 1988, 366,  6940 },
 	{ 1989, 365,  7305 },
 	{ 1990, 365,  7670 },
 	{ 1991, 365,  8035 },
 	{ 1992, 366,  8401 },
 	{ 1993, 365,  8766 },
 	{ 1994, 365,  9131 },
 	{ 1995, 365,  9496 },
 	{ 1996, 366,  9862 },
 	{ 1997, 365, 10227 },
 	{ 1998, 365, 10592 },
 	{ 1999, 365, 10957 },
 	{ 2000, 366, 11323 },
 	{ 2001, 365, 11688 },
 	{ 2002, 365, 12053 },
 	{ 2003, 365, 12418 },
 	{ 2004, 366, 12784 },
 	{ 2005, 365, 13149 },
 	{ 2006, 365, 13514 },
 	{ 2007, 365, 13879 },
 	{ 2008, 366, 14245 },
 	{ 2009, 365, 14610 },
 	{ 2010, 365, 14975 },
 	{ 2011, 365, 15340 },
 	{ 2012, 366, 15706 },
 	{ 2013, 365, 16071 },
 	{ 2014, 365, 16436 },
 	{ 2015, 365, 16801 },
 	{ 2016, 366, 17167 },
 	{ 2017, 365, 17532 },
 	{ 2018, 365, 17897 },
 	{ 2019, 365, 18262 },
 	{ 2020, 366, 18628 },
 	{ 2021, 365, 18993 },
 	{ 2022, 365, 19358 },
 	{ 2023, 365, 19723 },
 	{ 2024, 366, 20089 },
 	{ 2025, 365, 20454 },
 	{ 2026, 365, 20819 },
 	{ 2027, 365, 21184 },
 	{ 2028, 366, 21550 },
 	{ 2029, 365, 21915 },
 	{ 2030, 365, 22280 },
 	{ 2031, 365, 22645 },
 	{ 2032, 366, 23011 },
 	{ 2033, 365, 23376 },
 	{ 2034, 365, 23741 },
 	{ 2035, 365, 24106 },
 	{ 2036, 366, 24472 },
 	{ 2037, 365, 24837 },
 	{ 2038, 365, 25202 },
 	{ 2039, 365, 25567 },
 	{ 2040, 366, 25933 },
 	{ 2041, 365, 26298 },
 	{ 2042, 365, 26663 },
 	{ 2043, 365, 27028 },
 	{ 2044, 366, 27394 },
 	{ 2045, 365, 27759 },
 	{ 2046, 365, 28124 },
 	{ 2047, 365, 28489 },
 	{ 2048, 366, 28855 },
 	{ 2049, 365, 29220 },
 	{ 2050, 365, 29585 },
 	{ 2051, 365, 29950 },
 	{ 2052, 366, 30316 },
 	{ 2053, 365, 30681 },
 	{ 2054, 365, 31046 },
 	{ 2055, 365, 31411 },
 	{ 2056, 366, 31777 },
 	{ 2057, 365, 32142 },
 	{ 2058, 365, 32507 },
 	{ 2059, 365, 32872 },
 	{ 2060, 366, 33238 },
 	{ 2061, 365, 33603 },
 	{ 2062, 365, 33968 },
 	{ 2063, 365, 34333 },
 	{ 2064, 366, 34699 },
 	{ 2065, 365, 35064 },
 	{ 2066, 365, 35429 },
 	{ 2067, 365, 35794 },
 	{ 2068, 366, 36160 },
 	{ 2069, 365, 36525 },
 	{ 2070, 365, 36890 },
 	{ 2071, 365, 37255 },
 	{ 2072, 366, 37621 },
 	{ 2073, 365, 37986 },
 	{ 2074, 365, 38351 },
 	{ 2075, 365, 38716 },
 	{ 2076, 366, 39082 },
 	{ 2077, 365, 39447 },
 	{ 2078, 365, 39812 },
 	{ 2079, 365, 40177 },
 	{ 2080, 366, 40543 },
 	{ 2081, 365, 40908 },
 	{ 2082, 365, 41273 },
 	{ 2083, 365, 41638 },
 	{ 2084, 366, 42004 },
 	{ 2085, 365, 42369 },
 	{ 2086, 365, 42734 },
 	{ 2087, 365, 43099 },
 	{ 2088, 366, 43465 },
 	{ 2089, 365, 43830 },
 	{ 2090, 365, 44195 },
 	{ 2091, 365, 44560 },
 	{ 2092, 366, 44926 },
 	{ 2093, 365, 45291 },
 	{ 2094, 365, 45656 },
 	{ 2095, 365, 46021 },
 	{ 2096, 366, 46387 },
 	{ 2097, 365, 46752 },
 	{ 2098, 365, 47117 },
 	{ 2099, 365, 47482 },
 	{ 2100, 365, 47847 },
 	{ 2101, 365, 48212 },
 	{ 2102, 365, 48577 },
 	{ 2103, 365, 48942 },
 	{ 2104, 366, 49308 },
 	{ 2105, 365, 49673 },
 	{ 2106, 365, 50038 },
 	{ 2107, 365, 50403 },
 	{ 2108, 366, 50769 },
 	{ 2109, 365, 51134 },
 	{ 2110, 365, 51499 },
 	{ 2111, 365, 51864 },
 	{ 2112, 366, 52230 },
 	{ 2113, 365, 52595 },
 	{ 2114, 365, 52960 },
 	{ 2115, 365, 53325 },
 	{ 2116, 366, 53691 },
 	{ 2117, 365, 54056 },
 	{ 2118, 365, 54421 },
 	{ 2119, 365, 54786 },
 	{ 2120, 366, 55152 },
 	{ 2121, 365, 55517 },
 	{ 2122, 365, 55882 },
 	{ 2123, 365, 56247 },
 	{ 2124, 366, 56613 },
 	{ 2125, 365, 56978 },
 	{ 2126, 365, 57343 },
 	{ 2127, 365, 57708 },
 	{ 2128, 366, 58074 },
 	{ 2129, 365, 58439 },
 	{ 2130, 365, 58804 },
 	{ 2131, 365, 59169 },
 	{ 2132, 366, 59535 },
 	{ 2133, 365, 59900 },
 	{ 2134, 365, 60265 },
 	{ 2135, 365, 60630 },
 	{ 2136, 366, 60996 },
 	{ 2137, 365, 61361 },
 	{ 2138, 365, 61726 },
 	{ 2139, 365, 62091 },
 	{ 2140, 366, 62457 },
 	{ 2141, 365, 62822 },
 	{ 2142, 365, 63187 },
 	{ 2143, 365, 63552 },
 	{ 2144, 366, 63918 },
 	{ 2145, 365, 64283 },
 	{ 2146, 365, 64648 },
 	{ 2147, 365, 65013 },
 	{ 2148, 366, 65379 },
 	{ 2149, 365, 65744 },
 	{ 2150, 365, 66109 },
 	{ 2151, 365, 66474 },
 	{ 2152, 366, 66840 },
 	{ 2153, 365, 67205 },
 	{ 2154, 365, 67570 },
 	{ 2155, 365, 67935 },
 	{ 2156, 366, 68301 },
 	{ 2157, 365, 68666 },
 	{ 2158, 365, 69031 },
 	{ 2159, 365, 69396 },
 	{ 2160, 366, 69762 },
 	{ 2161, 365, 70127 },
 	{ 2162, 365, 70492 },
 	{ 2163, 365, 70857 },
 	{ 2164, 366, 71223 },
 	{ 2165, 365, 71588 },
 	{ 2166, 365, 71953 },
 	{ 2167, 365, 72318 },
 	{ 2168, 366, 72684 },
 	{ 2169, 365, 73049 },
 	{ 2170, 365, 73414 },
 	{ 2171, 365, 73779 },
 	{ 2172, 366, 74145 },
 	{ 2173, 365, 74510 },
 	{ 2174, 365, 74875 },
 	{ 2175, 365, 75240 },
 	{ 2176, 366, 75606 },
 	{ 2177, 365, 75971 },
 	{ 2178, 365, 76336 },
 	{ 2179, 365, 76701 },
 	{ 2180, 366, 77067 },
 	{ 2181, 365, 77432 },
 	{ 2182, 365, 77797 },
 	{ 2183, 365, 78162 },
 	{ 2184, 366, 78528 },
 	{ 2185, 365, 78893 },
 	{ 2186, 365, 79258 },
 	{ 2187, 365, 79623 },
 	{ 2188, 366, 79989 },
 	{ 2189, 365, 80354 },
 	{ 2190, 365, 80719 },
 	{ 2191, 365, 81084 },
 	{ 2192, 366, 81450 },
 	{ 2193, 365, 81815 },
 	{ 2194, 365, 82180 },
 	{ 2195, 365, 82545 },
 	{ 2196, 366, 82911 },
 	{ 2197, 365, 83276 },
 	{ 2198, 365, 83641 },
 	{ 2199, 365, 84006 },
 	{ 2200, 365, 84371 }
};

struct days_in_month {
    unsigned int month;
    unsigned int days;
    unsigned int ldays;     // leap year
    unsigned int accum;
    unsigned int laccum;    // leap year
};

static const days_in_month days_in_months[] =
{
 	{ 1 , 31, 31,  31,  31 },
 	{ 2 , 28, 29,  59,  60 },
 	{ 3 , 31, 31,  90,  91 },
 	{ 4 , 30, 30, 120, 121 },
 	{ 5 , 31, 31, 151, 152 },
 	{ 6 , 30, 30, 181, 182 },
 	{ 7 , 31, 31, 212, 213 },
 	{ 8 , 31, 31, 243, 244 },
 	{ 9 , 30, 30, 273, 274 },
 	{ 10, 31, 31, 304, 305 },
 	{ 11, 30, 30, 334, 335 },
 	{ 12, 31, 31, 365, 366 }
};

#define DAYS_IN_YEARS_COUNT (sizeof(days_in_years) / sizeof(days_in_year))
#define DAYS_IN_YEARS_MIN_YEAR (days_in_years[0].year)
#define DAYS_IN_YEARS_MAX_YEAR (days_in_years[DAYS_IN_YEARS_COUNT - 1].year)
#define DAYS_IN_YEARS_MAX_ACCUM (days_in_years[DAYS_IN_YEARS_COUNT - 1].accum)

static inline unsigned int get_year(unsigned int x) {
    unsigned int i = 0;
    unsigned int imax = DAYS_IN_YEARS_COUNT;

    if (x < DAYS_IN_YEARS_MAX_ACCUM) {
        for ( ; i < imax; i++) {
            if (x < days_in_years[i].accum) {
                return days_in_years[i].year;
            }
        }
        return DAYS_IN_YEARS_MAX_YEAR; // not reached
    }

    unsigned int accum = DAYS_IN_YEARS_MAX_ACCUM;
    unsigned int res = DAYS_IN_YEARS_MAX_YEAR + 1;
    for ( ; ; ++res) {
        accum += year_days(res);
        if (x < accum) break;
    }

    return res;
}

inline std::string format_date(unsigned int x) {
    if (Rcpp::traits::is_na<INTSXP>(x)) return "NA";

    char buff[16];
    unsigned int miny = DAYS_IN_YEARS_MIN_YEAR;
    unsigned int y = miny, m = 1, d = 1;

    if (x <= DAYS_IN_YEARS_MAX_ACCUM) {
        y = get_year(x);
        if (y > miny) x -= days_in_years[y - miny - 1].accum;

        unsigned int i = 0;
        if (!isleap(y)) {
            for ( ; i < 12; i++) {
                if (x < days_in_months[i].accum) {
                    m = i + 1;
                    d = (i > 0) ? x - days_in_months[i - 1].accum : x;
                    break;
                }
            }
        } else {
            for ( ; i < 12; i++) {
                if (x < days_in_months[i].laccum) {
                    m = i + 1;
                    d = (i > 0) ? x - days_in_months[i - 1].laccum : x;
                    break;
                }
            }
        }
    } else {
        y = get_year(x);
        unsigned int accum = DAYS_IN_YEARS_MAX_ACCUM;
        unsigned int tmpyear = DAYS_IN_YEARS_MAX_YEAR + 1;

        for ( ; tmpyear < y; tmpyear++) {
            accum += year_days(tmpyear);
        }
        x -= accum;

        unsigned int i = 0;
        if (!isleap(y)) {
            for ( ; i < 12; i++) {
                if (x < days_in_months[i].accum) {
                    m = i + 1;
                    d = (i > 0) ? x - days_in_months[i - 1].accum : x;
                    break;
                }
            }
        } else {
            for ( ; i < 12; i++) {
                if (x < days_in_months[i].laccum) {
                    m = i + 1;
                    d = (i > 0) ? x - days_in_months[i - 1].laccum : x;
                    break;
                }
            }
        }
    }

    std::sprintf(buff, "%u-%02u-%02u", y, m, d + 1);
    return std::string(buff);
}

namespace impl {

template <bool NA, typename T>
class FormatDate :
    public Rcpp::VectorBase<STRSXP, true, FormatDate<NA, T> > {
private:
    const Rcpp::VectorBase<REALSXP, NA, T>& vec;

public:
    FormatDate(const Rcpp::VectorBase<REALSXP, NA, T>& vec_)
        : vec(vec_)
    {}

    R_xlen_t size() const { return vec.size(); }

    std::string operator[](R_xlen_t i) const {
        return format_date(vec[i]);
    }
};

} // impl

template <bool NA, typename T>
inline impl::FormatDate<NA, T>
format_date(const Rcpp::VectorBase<REALSXP, NA, T>& x) {
    return impl::FormatDate<NA, T>(x);
}


#undef isleap
#undef year_days
#undef DAYS_IN_YEARS_COUNT
#undef DAYS_IN_YEARS_MIN_YEAR
#undef DAYS_IN_YEARS_MAX_YEAR
#undef DAYS_IN_YEARS_MAX_ACCUM

} // hashmap

#endif // hashmap__format_date__hpp
