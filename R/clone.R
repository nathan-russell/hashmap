#' @title Clone a Hashmap
#'
#' @name clone
#' @rdname clone
#'
#' @include hashmap.R
#'
#' @description \code{clone} creates a deep copy of a \code{Hashmap} so that
#'  modifications made to the cloned object do not affect the original object.
#'
#' @usage clone(x)
#'
#' @param x an object created by a call to \code{hashmap}.
#'
#' @return a \code{Hashmap} identical to the input object.
#'
#' @details Since the actual cloning is done in C++, \code{y <- clone(x)} should
#'  be much more efficient than \code{y <- hashmap(x$keys(), x$values())}.
#'
#' @seealso \code{\link{hashmap}}
#'
#' @examples
#'
#' x <- hashmap(letters[1:5], 1:5)
#'
#' ## shallow copy
#' y <- x
#' y[["a"]] <- 999
#'
#' ## original is affected
#' x[["a"]] == 999
#'
#' z <- clone(x)
#' z[["c"]] <- 888
#'
#' ## original not affected
#' x[["c"]] == 888

#' @export clone
clone <- function(x) {
    if (!inherits(x, "Rcpp_Hashmap")) {
        msg <- sprintf(
            "Object '%s' is not a hashmap.",
            deparse(substitute(x))
        )
        stop(msg)
    }

    new("Rcpp_Hashmap", x$.pointer)
}
