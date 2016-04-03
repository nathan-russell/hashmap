#' The faster hashmap
#'
#' @title The faster hashmap
#'
#' @name hashmap
#' @rdname hashmap
#'
#' @description An S4 class for fast key-value storage
#'      of atomic vectors
#'
#' @usage hashmap(keys, values, ...)
#'
#' @param keys an atomic vector of type \code{integer},
#'      \code{numeric}, or \code{character} representing
#'      the lookup keys
#'
#' @param values an atomic vector of type \code{integer},
#'      \code{numeric}, \code{character}, or \code{logical}
#'      representing the corresponding lookup values
#'
#' @param ... other arguments passed to \code{new} when constructing
#'      the instance
#'
#' @return a \code{hashmap} object
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
#' H <- hashmap(x, y)
#'
#' all.equal(y[match(z, x)], H[[z]])
#'
#' \dontrun{
#' microbenchmark::microbenchmark(
#'     "R" = y[match(z, x)],
#'     "H" = H[[z]],
#'     times = 500L
#' )
#' }

#' @importFrom methods new

Rcpp::loadModule("hashmap_module", TRUE)

#' @export hashmap
hashmap <- function(keys, values, ...) {
    new("Rcpp_Hashmap", keys, values, ...)
}

