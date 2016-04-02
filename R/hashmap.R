#' The faster hashmap
#'
#' @title The faster hashmap
#'
#' @name hashmap
#' @aliases Rcpp_hashmap
#'
#' @rdname hashmap
#' @export
#'
#' @description An S4 class for fast key-value storage
#'      of atomic vectors
#'
#' @usage new(hashmap, x, y)
#'
#' @param x an atomic vector of type \code{integer},
#'      \code{numeric}, or \code{character} representing
#'      the lookup keys
#'
#' @param y an atomic vector of type \code{integer},
#'      \code{numeric}, or \code{character} representing
#'      the corresponding lookup values
#'
#' @return a \code{hashmap} object
#'
#' @useDynLib hashmap
#' @importFrom Rcpp sourceCpp
#'
#' @examples
#'
#' x <- replicate(10e3,
#'     paste0(sample(letters, 12, TRUE),
#'            collapse = "")
#' )
#' y <- rnorm(length(x))
#' z <- sample(x, 100)
#'
#' H <- new(hashmap, x, y)
#'
#' all.equal(y[match(z, x)], H$find_values(z))
#'
#' \dontrun{
#' microbenchmark::microbenchmark(
#'     "R" = y[match(z, x)],
#'     "H" = H$find_values(z),
#'     times = 500L
#' )
#' }

Rcpp::loadModule("hashmap_module", TRUE)


