#' Hashmap internal class
#'
#' @title Hashmap internal class
#'
#' @name Rcpp_Hashmap-class
#' @aliases Rcpp_Hashmap
#' @rdname Rcpp_Hashmap-class
#' @exportClass Rcpp_Hashmap
#' @include hashmap.R
NULL

setClass("Rcpp_Hashmap", contains = "C++Object")

setMethod("show", "Rcpp_Hashmap",
    function(object) {

        if (object$empty()) {
            cat("## [empty Hashmap]", "\n")
            return(invisible(object))
        }

        if (is.null(getOption("hashmap.max.print")) ||
            anyNA(getOption("hashmap.max.print"))) {
            n_print <- 6
        } else {
            n_print <- getOption("hashmap.max.print")[1]
        }
        sz <- object$size()

        .keys <- object$keys_n(min(sz, n_print))
        .values <- object$values_n(min(sz, n_print))


        .lhs_header <- sprintf("(%s)", class(.keys)[1])
        .rhs_header <- sprintf("(%s)", class(.values)[1])

        if (is.integer(.keys)) {
            .keys <- sprintf("[%d]", .keys)
        } else if (is.numeric(.keys)) {
            .keys <- sprintf("[%+f]",
                round(.keys, getOption("digits")))
        } else {
            .keys <- sprintf("[%s]", .keys)
        }

        if (is.integer(.values)) {
            .values <- sprintf("[%d]", .values)
        } else if (is.numeric(.values)) {
            .values <- sprintf("[%+f]",
                round(.values, getOption("digits"))
            )
        } else {
            .values <- sprintf("[%s]", .values)
        }

        .lhs_width <- max(c(nchar(.lhs_header), nchar(.keys)))
        .rhs_width <- max(c(nchar(.rhs_header), nchar(.values)))

        if (sz > n_print) {
            .txt <- sprintf(
                "## %s => %s",
                formatC(c(.lhs_header, .keys, "[...]"),
                        width = .lhs_width),
                formatC(c(.rhs_header, .values, "[...]"),
                        width = .rhs_width, flag = "-")
            )
        } else {
            .txt <- sprintf(
                "## %s => %s",
                formatC(c(.lhs_header, .keys), width = .lhs_width),
                formatC(c(.rhs_header, .values), width = .rhs_width, flag = "-")
            )
        }

        cat(.txt, sep = "\n")
        invisible(object)
    }
)

#' @rdname plot
#' @title Plot method for Hashmap class
#' @name plot
#' @description Plot method for Hashmap class
#' @param x an object created by a call to \code{hashmap}
#' @param \dots arguments passed to \code{plot}
#' @details A convenience function which simply calls \code{plot} using
#'  \code{x$keys()} and \code{x$values()} as plotting coordinates.
#'
#' @examples
#'
#' x <- hashmap(1:20, rnorm(20))
#' plot(x)
#' plot(x, type = 'p', pch = 20, col = 'red')
#'
#' y <- hashmap(Sys.Date() + 1:20, rnorm(20))
#' plot(y, type = 'h', col = 'blue', lwd = 3)

#' @importFrom graphics plot
#' @method plot Rcpp_Hashmap
#' @export
plot.Rcpp_Hashmap <- function(x, ...) {
    if (x$empty()) {
        stop("Cannot plot empty hashmap.")
    }

    keys <- x$keys()
    values <- x$values()
    invisible(plot(keys, values, ...))
}
