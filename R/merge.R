#' @title Merge two Hashmaps
#'
#' @rdname merge.Rcpp_Hashmap
#' @aliases merge
#' @name merge
#'
#' @description merge method for Hashmap class
#'
#' @param x an object created by a call to \code{hashmap}.
#' @param y an object created by a call to \code{hashmap}.
#' @param type a character string specifying the type of join, with
#'  partial argument matching (abbreviation) supported.
#' @param \dots not used.
#'
#' @return a \code{data.frame}.
#'
#' @details Valid arguments for type are:
#' \itemize{
#'  \item \code{"inner"}: similar to \code{all = FALSE} in \code{base::merge}
#'  \item \code{"left"}: similar to \code{all.x = TRUE} in \code{base::merge}
#'  \item \code{"right"}: similar to \code{all.y = TRUE} in \code{base::merge}
#'  \item \code{"full"}: similar to \code{all = TRUE} in \code{base::merge}
#' }
#'
#' The default value for \code{type} is \code{"inner"}.
#'
#' @examples
#' hx <- hashmap(LETTERS[1:5], 1:5)
#' hy <- hashmap(LETTERS[4:8], 4:8)
#'
#' ## inner join
#' merge(hx, hy)
#'
#' merge(
#'     hx$data.frame(),
#'     hy$data.frame(),
#'     by = "Keys",
#'     sort = FALSE
#' )
#'
#' ## left join
#' merge(hx, hy, "left")
#'
#' merge(
#'     hx$data.frame(),
#'     hy$data.frame(),
#'     by = "Keys",
#'     all.x = TRUE,
#'     sort = FALSE
#' )
#'
#' ## right join
#' merge(hx, hy, "right")
#'
#' merge(
#'     hx$data.frame(),
#'     hy$data.frame(),
#'     by = "Keys",
#'     all.y = TRUE,
#'     sort = FALSE
#' )
#'
#' ## full outer join
#' merge(hx, hy, "full")
#'
#' merge(
#'     hx$data.frame(),
#'     hy$data.frame(),
#'     by = "Keys",
#'     all = TRUE,
#'     sort = FALSE
#' )

#' @method merge Rcpp_Hashmap
#' @export
merge.Rcpp_Hashmap <- function(x, y,
                               type = c("inner", "left", "right", "full"),
                               ...)
{
    type <- match.arg(type)

    if (!inherits(x, "Rcpp_Hashmap")) {
        msg <- sprintf(
            "Object '%s' is not a hashmap.",
            deparse(substitute(x))
        )
        stop(msg)
    }

    if (!inherits(y, "Rcpp_Hashmap")) {
        msg <- sprintf(
            "Object '%s' is not a hashmap.",
            deparse(substitute(y))
        )
        stop(msg)
    }

    fn <- switch(type,
        inner = .inner_join_impl,
        left = .left_outer_join_impl,
        right = .right_outer_join_impl,
        full = .full_outer_join_impl
    )

    fn(x$.pointer, y$.pointer)
}
