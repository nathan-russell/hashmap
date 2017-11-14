#include <R.h>
#include <Rinternals.h>
#include <stdlib.h>
#include <R_ext/Rdynload.h>

extern SEXP _hashmap_full_outer_join_impl(SEXP, SEXP);
extern SEXP _hashmap_inner_join_impl(SEXP, SEXP);
extern SEXP _hashmap_left_outer_join_impl(SEXP, SEXP);
extern SEXP _hashmap_right_outer_join_impl(SEXP, SEXP);
extern SEXP _rcpp_module_boot_Hashmap(void);

static const R_CallMethodDef CallEntries[] =
{
    {"_hashmap_full_outer_join_impl",   (DL_FUNC)   &_hashmap_full_outer_join_impl,  2},
    {"_hashmap_inner_join_impl",        (DL_FUNC)   &_hashmap_inner_join_impl,       2},
    {"_hashmap_left_outer_join_impl",   (DL_FUNC)   &_hashmap_left_outer_join_impl,  2},
    {"_hashmap_right_outer_join_impl",  (DL_FUNC)   &_hashmap_right_outer_join_impl, 2},
    {"_rcpp_module_boot_Hashmap",       (DL_FUNC)   &_rcpp_module_boot_Hashmap,      0},
    {NULL,                               NULL,                                       0}
};

void R_init_hashmap(DllInfo* dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
