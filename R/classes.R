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

        .lhs_header <- sprintf("(%s)", class(object$keys()))
        .rhs_header <- sprintf("(%s)", class(object$values()))

        .data <- head(object$data(), n_print)

        if (grepl("numeric", .lhs_header)) {
            .keys <- sprintf("[%+f]",
                round(names(.data), getOption("digits"))
            )
        } else {
            .keys <- sprintf("[%s]", as.character(names(.data)))
        }

        if (grepl("numeric", .rhs_header)) {
            .values <- sprintf("[%+f]",
                round(unname(.data), getOption("digits"))
            )
        } else {
            .values <- sprintf("[%s]", as.character(unname(.data)))
        }

        .lhs_width <- max(c(nchar(.lhs_header), nchar(.keys)))
        .rhs_width <- max(c(nchar(.rhs_header), nchar(.values)))

        if (object$size() > n_print) {
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
