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

        .keys <- object$keys()[seq_len(min(sz, n_print))]
        .values <- object$values()[seq_len(min(sz, n_print))]


        .lhs_header <- sprintf("(%s)", class(.keys)[1])
        .rhs_header <- sprintf("(%s)", class(.values)[1])

        #.data <- head(object$data(), n_print)

        if (is.numeric(.keys)) {
            .keys <- sprintf("[%+f]",
                round(.keys, getOption("digits")))
        } else {
            .keys <- sprintf("[%s]", .keys)
        }

        if (is.numeric(.values)) {
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
