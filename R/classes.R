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
            cat("\n", "[empty Hashmap]", "\n")
            return(invisible(object))
        }

        .data <- head(object$data(), 5)
        .keys <- sprintf("[%s]", as.character(names(.data)))
        .values <- sprintf("[%s]", as.character(unname(.data)))
        .width <- max(c(nchar(.keys), nchar(.values)))
        .txt <- sprintf(
            "%s => %s",
            formatC(.keys, width = .width),
            formatC(.values, width = .width)
        )
        cat(.txt, sep = "\n")
        invisible(object)
    }
)
