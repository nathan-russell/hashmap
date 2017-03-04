#include <R.h>
#include <Rinternals.h>
#include <stdlib.h>
#include <R_ext/Rdynload.h>

extern SEXP hashmap_full_outer_join_impl(SEXP, SEXP);
extern SEXP hashmap_inner_join_impl(SEXP, SEXP);
extern SEXP hashmap_left_outer_join_impl(SEXP, SEXP);
extern SEXP hashmap_right_outer_join_impl(SEXP, SEXP);
extern SEXP _rcpp_module_boot_Hashmap(void);

static const R_CallMethodDef CallEntries[] =
{
    {"hashmap_full_outer_join_impl",  (DL_FUNC) &hashmap_full_outer_join_impl,  2},
    {"hashmap_inner_join_impl",       (DL_FUNC) &hashmap_inner_join_impl,       2},
    {"hashmap_left_outer_join_impl",  (DL_FUNC) &hashmap_left_outer_join_impl,  2},
    {"hashmap_right_outer_join_impl", (DL_FUNC) &hashmap_right_outer_join_impl, 2},
    {"_rcpp_module_boot_Hashmap",     (DL_FUNC) &_rcpp_module_boot_Hashmap,     0},
    {NULL,                            NULL,                                     0}
};

void R_init_hashmap(DllInfo* dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
