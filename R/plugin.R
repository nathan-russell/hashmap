#' @title Rcpp Plugin
#'
#' @name plugin
#' @rdname plugin
#'
#' @description An Rcpp plugin setting the correct linker flags for
#'  Rcpp files using the C++ API of hashmap.
#'
#' @usage plugin
#'
#' @details In order to access the C++ API of hashmap, users must add
#'  \code{// [[Rcpp::plugins(hashmap)]]} and \code{#include <hashmap.h>}
#'  to the top of their Rcpp source files.
plugin <- Rcpp:::Rcpp.plugin.maker(
    libs = (function() {
        libs_path <- sprintf(
            "%s/hashmap/libs",
            installed.packages()["hashmap","LibPath"][1]
        )

        pattern <- sprintf("*hashmap%s", .Platform$dynlib.ext)
        lib_files <- list.files(
            libs_path,
            pattern = pattern,
            full.names = TRUE,
            recursive = TRUE
        )

        if (length(lib_files) < 1) {
            res <- "failed-to-locate-hashmap-shared-library"
        } else {
            res <- lib_files[1]
        }

        res
    })(),
    package = "hashmap"
)
