// vim: set softtabstop=4:expandtab:number:syntax on:wildmenu:showmatch
//
// format_posix.hpp
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

#ifndef hashmap__format_posix__hpp
#define hashmap__format_posix__hpp

#include "traits.hpp"
#include <ctime>
#include <cstring>

namespace hashmap {

#define TZ_ABBR_MAX_CHAR 5

struct tz_abbr_offset {
    char abbr[TZ_ABBR_MAX_CHAR + 1];
    signed int offset;
    unsigned int sz;
};

static const tz_abbr_offset tz_abbr_offsets[] =
{
	{ "ACDT" ,  37800,  4 }, // Australian Central Daylight Savings Time
 	{ "ACST" ,  34200,  4 }, // Australian Central Standard Time
 	{ "ACT"  , -18000,  3 }, // Acre Time
 	{ "ACT"  ,  28800,  3 }, // ASEAN Common Time
 	{ "ADT"  , -10800,  3 }, // Atlantic Daylight Time
 	{ "AEDT" ,  39600,  4 }, // Australian Eastern Daylight Savings Time
 	{ "AEST" ,  36000,  4 }, // Australian Eastern Standard Time
 	{ "AFT"  ,  16200,  3 }, // Afghanistan Time
 	{ "AKDT" , -28800,  4 }, // Alaska Daylight Time
 	{ "AKST" , -32400,  4 }, // Alaska Standard Time
 	{ "AMST" , -10800,  4 }, // Amazon Summer Time (Brazil)[1]
 	{ "AMT"  , -14400,  3 }, // Amazon Time (Brazil)[2]
 	{ "AMT"  ,  14400,  3 }, // Armenia Time
 	{ "ART"  , -10800,  3 }, // Argentina Time
 	{ "AST"  ,  10800,  3 }, // Arabia Standard Time
 	{ "AST"  , -14400,  3 }, // Atlantic Standard Time
 	{ "AWDT" ,  32400,  4 }, // Australian Western Daylight Time
 	{ "AWST" ,  28800,  4 }, // Australian Western Standard Time
 	{ "AZOST",  -3600,  5 }, // Azores Standard Time
 	{ "AZT"  ,  14400,  3 }, // Azerbaijan Time
 	{ "BDT"  ,  28800,  3 }, // Brunei Time
 	{ "BDT"  ,  21600,  3 }, // Bangladesh Daylight Time (Bangladesh Daylight saving time keeps UTC+06 offset) [3]
 	{ "BIOT" ,  21600,  4 }, // British Indian Ocean Time
 	{ "BIT"  , -43200,  3 }, // Baker Island Time
 	{ "BOT"  , -14400,  3 }, // Bolivia Time
 	{ "BRST" ,  -7200,  4 }, // Brasilia Summer Time
 	{ "BRT"  , -10800,  3 }, // Brasilia Time
 	{ "BST"  ,  21600,  3 }, // Bangladesh Standard Time
 	{ "BST"  ,  39600,  3 }, // Bougainville Standard Time[4]
 	{ "BST"  ,   3600,  3 }, // British Summer Time (British Standard Time from Feb 1968 to Oct 1971)
 	{ "BTT"  ,  21600,  3 }, // Bhutan Time
 	{ "CAT"  ,   7200,  3 }, // Central Africa Time
 	{ "CCT"  ,  23400,  3 }, // Cocos Islands Time
 	{ "CDT"  , -18000,  3 }, // Central Daylight Time (North America)
 	{ "CDT"  , -14400,  3 }, // Cuba Daylight Time[5]
 	{ "CEDT" ,   7200,  4 }, // Central European Daylight Time
 	{ "CEST" ,   7200,  4 }, // Central European Summer Time (Cf. HAEC)
 	{ "CET"  ,   3600,  3 }, // Central European Time
 	{ "CHADT",  49500,  5 }, // Chatham Daylight Time
 	{ "CHAST",  45900,  5 }, // Chatham Standard Time
 	{ "CHOT" ,  28800,  4 }, // Choibalsan
 	{ "ChST" ,  36000,  4 }, // Chamorro Standard Time
 	{ "CHUT" ,  36000,  4 }, // Chuuk Time
 	{ "CIST" , -28800,  4 }, // Clipperton Island Standard Time
 	{ "CIT"  ,  28800,  3 }, // Central Indonesia Time
 	{ "CKT"  , -36000,  3 }, // Cook Island Time
 	{ "CLST" , -10800,  4 }, // Chile Summer Time
 	{ "CLT"  , -14400,  3 }, // Chile Standard Time
 	{ "COST" , -14400,  4 }, // Colombia Summer Time
 	{ "COT"  , -18000,  3 }, // Colombia Time
 	{ "CST"  , -21600,  3 }, // Central Standard Time (North America)
 	{ "CST"  ,  28800,  3 }, // China Standard Time
 	{ "CST"  ,  34200,  3 }, // Central Standard Time (Australia)
 	{ "CST"  ,  37800,  3 }, // Central Summer Time (Australia)
 	{ "CST"  , -18000,  3 }, // Cuba Standard Time
 	{ "CT"   ,  28800,  2 }, // China time
 	{ "CVT"  ,  -3600,  3 }, // Cape Verde Time
 	{ "CWST" ,  31500,  4 }, // Central Western Standard Time (Australia) unofficial
 	{ "CXT"  ,  25200,  3 }, // Christmas Island Time
 	{ "DAVT" ,  25200,  4 }, // Davis Time
 	{ "DDUT" ,  36000,  4 }, // Dumont d'Urville Time
 	{ "DFT"  ,   3600,  3 }, // AIX specific equivalent of Central European Time[6]
 	{ "EASST", -18000,  5 }, // Easter Island Standard Summer Time
 	{ "EAST" , -21600,  4 }, // Easter Island Standard Time
 	{ "EAT"  ,  10800,  3 }, // East Africa Time
 	{ "ECT"  , -14400,  3 }, // Eastern Caribbean Time (does not recognise DST)
 	{ "ECT"  , -18000,  3 }, // Ecuador Time
 	{ "EDT"  , -14400,  3 }, // Eastern Daylight Time (North America)
 	{ "EEDT" ,  10800,  4 }, // Eastern European Daylight Time
 	{ "EEST" ,  10800,  4 }, // Eastern European Summer Time
 	{ "EET"  ,   7200,  3 }, // Eastern European Time
 	{ "EGST" ,      0,  4 }, // Eastern Greenland Summer Time
 	{ "EGT"  ,  -3600,  3 }, // Eastern Greenland Time
 	{ "EIT"  ,  32400,  3 }, // Eastern Indonesian Time
 	{ "EST"  , -18000,  3 }, // Eastern Standard Time (North America)
 	{ "EST"  ,  36000,  3 }, // Eastern Standard Time (Australia)
 	{ "FET"  ,  10800,  3 }, // Further-eastern European Time
 	{ "FJT"  ,  43200,  3 }, // Fiji Time
 	{ "FKST" , -10800,  4 }, // Falkland Islands Standard Time
 	{ "FKST" , -10800,  4 }, // Falkland Islands Summer Time
 	{ "FKT"  , -14400,  3 }, // Falkland Islands Time
 	{ "FNT"  ,  -7200,  3 }, // Fernando de Noronha Time
 	{ "GALT" , -21600,  4 }, // Galapagos Time
 	{ "GAMT" , -32400,  4 }, // Gambier Islands
 	{ "GET"  ,  14400,  3 }, // Georgia Standard Time
 	{ "GFT"  , -10800,  3 }, // French Guiana Time
 	{ "GILT" ,  43200,  4 }, // Gilbert Island Time
 	{ "GIT"  , -32400,  3 }, // Gambier Island Time
 	{ "GMT"  ,      0,  3 }, // Greenwich Mean Time
 	{ "GST"  ,  -7200,  3 }, // South Georgia and the South Sandwich Islands
 	{ "GST"  ,  14400,  3 }, // Gulf Standard Time
 	{ "GYT"  , -14400,  3 }, // Guyana Time
 	{ "HADT" , -32400,  4 }, // Hawaii-Aleutian Daylight Time
 	{ "HAEC" ,   7200,  4 }, // Heure Avancée d'Europe Centrale francised name for CEST
 	{ "HAST" , -36000,  4 }, // Hawaii-Aleutian Standard Time
 	{ "HKT"  ,  28800,  3 }, // Hong Kong Time
 	{ "HMT"  ,  18000,  3 }, // Heard and McDonald Islands Time
 	{ "HOVT" ,  25200,  4 }, // Khovd Time
 	{ "HST"  , -36000,  3 }, // Hawaii Standard Time
 	{ "IBST" ,      0,  4 }, // International Business Standard Time
 	{ "ICT"  ,  25200,  3 }, // Indochina Time
 	{ "IDT"  ,  10800,  3 }, // Israel Daylight Time
 	{ "IOT"  ,  10800,  3 }, // Indian Ocean Time
 	{ "IRDT" ,  16200,  4 }, // Iran Daylight Time
 	{ "IRKT" ,  28800,  4 }, // Irkutsk Time
 	{ "IRST" ,  12600,  4 }, // Iran Standard Time
 	{ "IST"  ,  19800,  3 }, // Indian Standard Time
 	{ "IST"  ,   3600,  3 }, // Irish Standard Time[7]
 	{ "IST"  ,   7200,  3 }, // Israel Standard Time
 	{ "JST"  ,  32400,  3 }, // Japan Standard Time
 	{ "KGT"  ,  21600,  3 }, // Kyrgyzstan time
 	{ "KOST" ,  39600,  4 }, // Kosrae Time
 	{ "KRAT" ,  25200,  4 }, // Krasnoyarsk Time
 	{ "KST"  ,  32400,  3 }, // Korea Standard Time
 	{ "LHST" ,  37800,  4 }, // Lord Howe Standard Time
 	{ "LHST" ,  39600,  4 }, // Lord Howe Summer Time
 	{ "LINT" ,  50400,  4 }, // Line Islands Time
 	{ "MAGT" ,  43200,  4 }, // Magadan Time
 	{ "MART" , -30600,  4 }, // Marquesas Islands Time
 	{ "MAWT" ,  18000,  4 }, // Mawson Station Time
 	{ "MDT"  , -21600,  3 }, // Mountain Daylight Time (North America)
 	{ "MET"  ,   3600,  3 }, // Middle European Time Same zone as CET
 	{ "MEST" ,   7200,  4 }, // Middle European Summer Time Same zone as CEST
 	{ "MHT"  ,  43200,  3 }, // Marshall Islands
 	{ "MIST" ,  39600,  4 }, // Macquarie Island Station Time
 	{ "MIT"  , -30600,  3 }, // Marquesas Islands Time
 	{ "MMT"  ,  23400,  3 }, // Myanmar Time
 	{ "MSK"  ,  10800,  3 }, // Moscow Time
 	{ "MST"  ,  28800,  3 }, // Malaysia Standard Time
 	{ "MST"  , -25200,  3 }, // Mountain Standard Time (North America)
 	{ "MST"  ,  23400,  3 }, // Myanmar Standard Time
 	{ "MUT"  ,  14400,  3 }, // Mauritius Time
 	{ "MVT"  ,  18000,  3 }, // Maldives Time
 	{ "MYT"  ,  28800,  3 }, // Malaysia Time
 	{ "NCT"  ,  39600,  3 }, // New Caledonia Time
 	{ "NDT"  ,  -5400,  3 }, // Newfoundland Daylight Time
 	{ "NFT"  ,  39600,  3 }, // Norfolk Time
 	{ "NPT"  ,  20700,  3 }, // Nepal Time
 	{ "NST"  ,  -9000,  3 }, // Newfoundland Standard Time
 	{ "NT"   ,  -9000,  2 }, // Newfoundland Time
 	{ "NUT"  , -39600,  3 }, // Niue Time
 	{ "NZDT" ,  46800,  4 }, // New Zealand Daylight Time
 	{ "NZST" ,  43200,  4 }, // New Zealand Standard Time
 	{ "OMST" ,  21600,  4 }, // Omsk Time
 	{ "ORAT" ,  18000,  4 }, // Oral Time
 	{ "PDT"  , -25200,  3 }, // Pacific Daylight Time (North America)
 	{ "PET"  , -18000,  3 }, // Peru Time
 	{ "PETT" ,  43200,  4 }, // Kamchatka Time
 	{ "PGT"  ,  36000,  3 }, // Papua New Guinea Time
 	{ "PHOT" ,  46800,  4 }, // Phoenix Island Time
 	{ "PKT"  ,  18000,  3 }, // Pakistan Standard Time
 	{ "PMDT" ,  -7200,  4 }, // Saint Pierre and Miquelon Daylight time
 	{ "PMST" , -10800,  4 }, // Saint Pierre and Miquelon Standard Time
 	{ "PONT" ,  39600,  4 }, // Pohnpei Standard Time
 	{ "PST"  , -28800,  3 }, // Pacific Standard Time (North America)
 	{ "PST"  ,  28800,  3 }, // Philippine Standard Time
 	{ "PYST" , -10800,  4 }, // Paraguay Summer Time (South America)[8]
 	{ "PYT"  , -14400,  3 }, // Paraguay Time (South America)[9]
 	{ "RET"  ,  14400,  3 }, // Réunion Time
 	{ "ROTT" , -10800,  4 }, // Rothera Research Station Time
 	{ "SAKT" ,  39600,  4 }, // Sakhalin Island time
 	{ "SAMT" ,  14400,  4 }, // Samara Time
 	{ "SAST" ,   7200,  4 }, // South African Standard Time
 	{ "SBT"  ,  39600,  3 }, // Solomon Islands Time
 	{ "SCT"  ,  14400,  3 }, // Seychelles Time
 	{ "SGT"  ,  28800,  3 }, // Singapore Time
 	{ "SLST" ,  19800,  4 }, // Sri Lanka Standard Time
 	{ "SRET" ,  39600,  4 }, // Srednekolymsk Time
 	{ "SRT"  , -10800,  3 }, // Suriname Time
 	{ "SST"  , -39600,  3 }, // Samoa Standard Time
 	{ "SST"  ,  28800,  3 }, // Singapore Standard Time
 	{ "SYOT" ,  10800,  4 }, // Showa Station Time
 	{ "TAHT" , -36000,  4 }, // Tahiti Time
 	{ "THA"  ,  25200,  3 }, // Thailand Standard Time
 	{ "TFT"  ,  18000,  3 }, // Indian/Kerguelen
 	{ "TJT"  ,  18000,  3 }, // Tajikistan Time
 	{ "TKT"  ,  46800,  3 }, // Tokelau Time
 	{ "TLT"  ,  32400,  3 }, // Timor Leste Time
 	{ "TMT"  ,  18000,  3 }, // Turkmenistan Time
 	{ "TOT"  ,  46800,  3 }, // Tonga Time
 	{ "TVT"  ,  43200,  3 }, // Tuvalu Time
 	{ "UCT"  ,      0,  3 }, // Coordinated Universal Time
 	{ "ULAT" ,  28800,  4 }, // Ulaanbaatar Time
 	{ "USZ1" ,   7200,  4 }, // Kaliningrad Time
 	{ "UTC"  ,      0,  3 }, // Coordinated Universal Time
 	{ "UYST" ,  -7200,  4 }, // Uruguay Summer Time
 	{ "UYT"  , -10800,  3 }, // Uruguay Standard Time
 	{ "UZT"  ,  18000,  3 }, // Uzbekistan Time
 	{ "VET"  , -12600,  3 }, // Venezuelan Standard Time
 	{ "VLAT" ,  36000,  4 }, // Vladivostok Time
 	{ "VOLT" ,  14400,  4 }, // Volgograd Time
 	{ "VOST" ,  21600,  4 }, // Vostok Station Time
 	{ "VUT"  ,  39600,  3 }, // Vanuatu Time
 	{ "WAKT" ,  43200,  4 }, // Wake Island Time
 	{ "WAST" ,   7200,  4 }, // West Africa Summer Time
 	{ "WAT"  ,   3600,  3 }, // West Africa Time
 	{ "WEDT" ,   3600,  4 }, // Western European Daylight Time
 	{ "WEST" ,   3600,  4 }, // Western European Summer Time
 	{ "WET"  ,      0,  3 }, // Western European Time
 	{ "WIT"  ,  25200,  3 }, // Western Indonesian Time
 	{ "WST"  ,  28800,  3 }, // Western Standard Time
 	{ "YAKT" ,  32400,  4 }, // Yakutsk Time
 	{ "YEKT" ,  18000,  4 }, // Yekaterinburg Time
 	{ "Z"    ,      0,  1 }  // Zulu Time (Coordinated Universal Time)
};

#define TZ_ABBR_COUNT (sizeof(tz_abbr_offsets) / sizeof(tz_abbr_offset))

static inline signed int get_abbr_offset(const char* str)
{
    unsigned int sz = std::strlen(str), i = 0;
    if (sz > TZ_ABBR_MAX_CHAR) return 0;

    for (; i < TZ_ABBR_COUNT; i++) {
        unsigned int nj = tz_abbr_offsets[i].sz;
        if (sz != nj) continue;
        if (std::strcmp(tz_abbr_offsets[i].abbr, str) == 0) {
            return tz_abbr_offsets[i].offset;
        }
    }

    return 0;
}

#undef TZ_ABBR_MAX_CHAR
#undef TZ_ABBR_COUNT

inline std::string format_posix(double x)
{
    if (Rcpp::traits::is_na<REALSXP>(x)) return "NA";

    std::time_t tx = x;
    std::tm* local = std::localtime(&tx);
    char buff[25];

    std::strftime(buff, 25,"%F %T", local);
    return std::string(buff);
}


namespace impl {

template <bool NA, typename T>
class FormatPosix :
    public Rcpp::VectorBase<STRSXP, true, FormatPosix<NA, T> > {
private:
    const Rcpp::VectorBase<REALSXP, NA, T>& vec;
    signed int offset;

public:
    FormatPosix(const Rcpp::VectorBase<REALSXP, NA, T>& vec_)
        : vec(vec_)
    {
        const char* tz = Rf_isNull(vec_.get_ref().attr("tzone")) ?
            "UTC" : Rcpp::as<const char*>(vec_.get_ref().attr("tzone"));
        offset = get_abbr_offset(tz);
    }

    R_xlen_t size() const
    { return vec.size(); }

    std::string operator[](R_xlen_t i) const
    { return format_posix(vec[i] + offset); }
};

} // impl

template <bool NA, typename T>
inline impl::FormatPosix<NA, T>
format_posix(const Rcpp::VectorBase<REALSXP, NA, T>& x)
{ return impl::FormatPosix<NA, T>(x); }

} // hashmap

#endif // hashmap__format_posix__hpp
