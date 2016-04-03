#ifndef hashmap__utils__hpp
#define hashmap__utils__hpp

#include <Rcpp.h>

#define HASHMAP_CHECK_INTERRUPT(_incr, _modulo)                \
    do {                                                       \
        if ((_incr) % (_modulo) == 0) {                        \
            Rcpp::checkUserInterrupt();                        \
        }                                                      \
    } while (0)


#endif // hashmap__utils__hpp
