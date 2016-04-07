#ifndef hashmap__utils__hpp
#define hashmap__utils__hpp

#include <Rcpp.h>

#define HASHMAP_CHECK_INTERRUPT(_incr, _modulo)                \
    do {                                                       \
        if ((_incr) % (_modulo) == 0) {                        \
            Rcpp::checkUserInterrupt();                        \
        }                                                      \
    } while (0)


namespace hashmap {
namespace utils {

inline std::string type_name(SEXP x) {
    switch (TYPEOF(x)) {
        case INTSXP: {
            if (Rf_inherits(x, "Date")) return "Date";
            if (Rf_inherits(x, "POSIXt")) return "POSIXct";
            return "integer";
        }
        case REALSXP: {
            if (Rf_inherits(x, "Date")) return "Date";
            if (Rf_inherits(x, "POSIXt")) return "POSIXct";
            return "numeric";
        }
        case LGLSXP: {
            return "logical";
        }
        case STRSXP: {
            return "character";
        }
        case CPLXSXP: {
            return "complex";
        }
        default: {
            return "Unknown type";
        }
    }
    return std::string("");
}

inline std::string sexptype_name(SEXP x) {
    switch (TYPEOF(x)) {
        case INTSXP: {
            return "INTSXP";
        }
        case REALSXP: {
            return "REALSXP";
        }
        case LGLSXP: {
            return "LGLSXP";
        }
        case STRSXP: {
            return "STRSXP";
        }
        case CPLXSXP: {
            return "CPLXSXP";
        }
        default: {
            return "Unknown SEXPTYPE";
        }
    }
    return std::string("");
}

} // utils
} // hashmap


#endif // hashmap__utils__hpp
