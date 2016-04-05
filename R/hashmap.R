#' @title Atomic vector hash map
#'
#' @name hashmap
#' @rdname hashmap
#'
#' @description Create a new \code{Hashmap} instance
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
#'      the \code{Hashmap} instance
#'
#' @return a \code{Hashmap} object
#'
#' @details TODO
#'
#' @seealso \code{\link{Hashmap}} for a more detailed
#'      discussion of available methods
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

Rcpp::loadModule("Hashmap", TRUE)

#' @export hashmap
hashmap <- function(keys, values, ...) {
    new("Rcpp_Hashmap", keys, values, ...)
}

