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
    libs = sprintf(
        "%s/hashmap/libs/hashmap.so",
        installed.packages()["hashmap","LibPath"][1]
    ),
    package = "hashmap"
)
