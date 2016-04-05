#' @useDynLib hashmap
#' @exportPattern "^[[:alpha:]]+"
#' @importFrom Rcpp evalCpp
#' @importFrom Rcpp cpp_object_initializer
#' @importFrom Rcpp sourceCpp
#' @importClassesFrom Rcpp "C++Object"

.onLoad <- function(libname, pkgname) {

    opts <- options()
    hm_opts <- list(
        hashmap.max.print = 6
    )

    new_opts <- !(names(hm_opts) %in% names(opts))
    if(any(new_opts)) {
        options(hm_opts[new_opts])
    }

    invisible()
}
