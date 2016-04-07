#' @title Atomic vector hash map
#'
#' @name hashmap
#' @rdname hashmap
#'
#' @description Create a new \code{Hashmap} instance
#'
#' @usage hashmap(keys, values, ...)
#'
#' @param keys an atomic vector representing lookup keys
#'
#' @param values an atomic vector of values associated with \code{keys}
#'      in a pair-wise manner
#'
#' @param ... other arguments passed to \code{new} when constructing
#'      the \code{Hashmap} instance
#'
#' @return a \code{Hashmap} object
#'
#' @details The following atomic vector types are currently supported for
#'  \code{keys}:
#'
#'  \itemize{
#'
#'      \item \code{integer}
#'
#'      \item \code{numeric}
#'
#'      \item \code{character}
#'
#'      \item \code{Date}
#'
#'      \item \code{POSIXct}
#'
#'  }
#'
#'  The following atomic vector types are currently supported for
#'  \code{values}:
#'
#'  \itemize{
#'
#'      \item \code{logical}
#'
#'      \item \code{integer}
#'
#'      \item \code{numeric}
#'
#'      \item \code{character}
#'
#'      \item \code{complex}
#'
#'      \item \code{Date}
#'
#'      \item \code{POSIXct}
#'
#'  }
#'
#' @seealso \code{\link{Hashmap-class}} for a more detailed
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

